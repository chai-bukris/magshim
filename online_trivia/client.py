import socket
import chatlib  # To use chat lib functions or consts, use chat lib.****

SERVER_IP = "127.0.0.1"  # Our server will run on same computer as client
SERVER_PORT = 5678


def build_and_send_message(conn, code, data):
    """
    Builds a new message using chat lib, wanted code and message.
    Prints debug info, then sends it to the given socket.
    Parameters: conn (socket object), code (str), data (str)
    Returns: Nothing
    """
    full_msg = chatlib.build_message(code, data)
    print(f"[DEBUG] Sending: {full_msg}")  # Debug print
    conn.send(full_msg.encode())


def recv_message_and_parse(conn):
    """
    Receives a new message from given socket,
    then parses the message using chat lib.
    Parameters: conn (socket object)
    Returns: cmd (str) and data (str) of the received message.
    If error occurred, will return None, None
    """
    try:
        full_msg = conn.recv(1024).decode()
        print(f"[DEBUG] Received: {full_msg}")  # Debug print
        cmd, data = chatlib.parse_message(full_msg)
        return cmd, data
    except Exception as e:
        print(f"[ERROR] Failed to receive/parse message: {e}")
        return None, None


def build_send_recv_parse(sock, cmd, data):
    build_and_send_message(sock, cmd, data)
    return recv_message_and_parse(sock)


def get_score(sock):
    msg_code, data = build_send_recv_parse(sock, "SCORE", "")
    if msg_code != "SCORE":
        print("[ERROR] Invalid response from server")
    else:
        print(f"Your current score is: {data}")


def get_highscore(sock):
    msg_code, data = build_send_recv_parse(sock, "HIGHSCORE", "")
    if msg_code != "HIGHSCORE":
        print("[ERROR] Invalid response from server")
    else:
        print("Highscores table:")
        print(data)


def connect():
    my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    my_socket.connect((SERVER_IP, SERVER_PORT))
    print("[DEBUG] Connected to server")
    return my_socket


def error_and_exit(error_msg):
    print(error_msg)
    exit(1)


def login(conn):
    while True:
        username = input("Please enter username: \n")
        password = input("Please enter password: ")
        data = f"{username}#{password}"
        build_and_send_message(conn, chatlib.PROTOCOL_CLIENT["login_msg"], data)

        cmd, data = recv_message_and_parse(conn)
        if cmd is None:
            error_and_exit("Connection lost during login.")

        if cmd == chatlib.PROTOCOL_SERVER["login_ok_msg"]:
            print("Login successful!")
            return
        elif cmd == chatlib.PROTOCOL_SERVER["login_failed_msg"]:
            print(f"Login failed: {data}")
        else:
            error_and_exit(f"Unexpected server response: {cmd}")


def logout(conn):
    build_and_send_message(conn, chatlib.PROTOCOL_CLIENT["logout_msg"], "")
    print("[DEBUG] Sent logout request")


def play_question(sock):
    cmd, data = build_send_recv_parse(sock, chatlib.PROTOCOL_CLIENT["get_question_msg"], "")
    if cmd is None:
        print("[ERROR] Failed to get question from server")
        return
    if cmd == chatlib.PROTOCOL_SERVER["no_questions_msg"]:
        print("No more questions available!")
        return
    if cmd != chatlib.PROTOCOL_SERVER["your_question_msg"]:
        print(f"[ERROR] Unexpected server response: {cmd}")
        return
    # Data format: question_id#question_text#answer1#answer2#answer3#answer4
    parts = chatlib.split_data(data, 6)
    if parts is None or len(parts) != 6:
        print("[ERROR] Bad question format from server")
        return

    q_id, q_text, ans1, ans2, ans3, ans4 = parts
    print(f"\nQuestion: {q_text}")
    print(f"1. {ans1}")
    print(f"2. {ans2}")
    print(f"3. {ans3}")
    print(f"4. {ans4}")
    while True:
        answer = input("Your answer (1-4): ").strip()
        if answer in ["1", "2", "3", "4"]:
            break
        print("Please enter a valid choice (1-4)")
    cmd, data = build_send_recv_parse(sock, chatlib.PROTOCOL_CLIENT["send_answer_msg"], f"{q_id}#{answer}")
    if cmd is None:
        print("[ERROR] Failed to send answer or receive response")
        return

    # Check server's feedback
    if cmd == chatlib.PROTOCOL_SERVER["correct_answer_msg"]:
        print("Correct")
    elif cmd == chatlib.PROTOCOL_SERVER["wrong_answer_msg"]:
        print(f"Wrong. The correct answer is {data}")
    else:
        print(f"[ERROR] Unexpected server response: {cmd}")


def get_logged_users(sock):
    cmd, data = build_send_recv_parse(sock, chatlib.PROTOCOL_CLIENT["logged_msg"], "")
    if cmd is None:
        print("Failed to get logged users")
        return
    if cmd != chatlib.PROTOCOL_SERVER["logged_answer_msg"]:
        print(f"Unexpected server response: {cmd}")
        return
    print("Currently logged in users:")
    print(data)


def main():
    conn = connect()
    login(conn)
    while True:
        print("1- get your score\n 2 - view highscores\n 3 - play question\n 4 - view logged users\n 5 - logout")
        choice = input("enter your choice: ")
        if choice == "1":
            get_score(conn)
        elif choice == "2":
            get_highscore(conn)
        elif choice == "3":
            play_question(conn)
        elif choice == "4":
            get_logged_users(conn)
        elif choice == "5":
            logout(conn)
            break
        else:
            print("invalid")

    conn.close()
    print("connection closed")


if __name__ == '__main__':
    main()
