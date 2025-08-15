# Protocol Constants

CMD_FIELD_LENGTH = 16  # Exact length of cmd field (in bytes)
LENGTH_FIELD_LENGTH = 4  # Exact length of length field (in bytes)
MAX_DATA_LENGTH = 10 ** LENGTH_FIELD_LENGTH - 1  # Max size of data field according to protocol
MSG_HEADER_LENGTH = CMD_FIELD_LENGTH + 1 + LENGTH_FIELD_LENGTH + 1  # Exact size of header (CMD+LENGTH fields)
MAX_MSG_LENGTH = MSG_HEADER_LENGTH + MAX_DATA_LENGTH  # Max size of total message
DELIMITER = "|"  # Delimiter character in protocol
DATA_DELIMITER = "#"  # Delimiter in the data part of the message

# Protocol Messages
# In this dictionary we will have all the client and server command names

PROTOCOL_CLIENT = {
    "login_msg": "LOGIN",
    "logout_msg": "LOGOUT"
}

PROTOCOL_SERVER = {
    "login_ok_msg": "LOGIN_OK",
    "login_failed_msg": "ERROR"
}

# Other constants

ERROR_RETURN = None  # What is returned in case of an error


def build_message(cmd, data):
    """
    Gets command name (str) and data field (str) and creates a valid protocol message
    Returns: str, or None if error occurred
    """
    if not isinstance(cmd, str) or not isinstance(data, str):
        return ERROR_RETURN
    if len(cmd) > CMD_FIELD_LENGTH:
        return ERROR_RETURN
    if len(data) > MAX_DATA_LENGTH:
        return ERROR_RETURN
    cmd_str = cmd.ljust(CMD_FIELD_LENGTH)
    length_str = str(len(data)).zfill(LENGTH_FIELD_LENGTH)
    full_msg = f"{cmd_str}{DELIMITER}{length_str}{DELIMITER}{data}"
    return full_msg


def parse_message(data):
    """
    Parses protocol message and returns command name and data field
    Returns: cmd (str), data (str). If some error occurred, returns None, None
    """
    if not isinstance(data, str):
        return None, None
    try:
        cmd_padded = data[:CMD_FIELD_LENGTH]
        if len(cmd_padded) != CMD_FIELD_LENGTH:
            return None, None
        if data[CMD_FIELD_LENGTH] != DELIMITER:
            return None, None
        length_str = data[CMD_FIELD_LENGTH + 1:CMD_FIELD_LENGTH + 1 + LENGTH_FIELD_LENGTH]
        if not length_str.isdigit():
            return None, None
        length_val = int(length_str)
        if data[CMD_FIELD_LENGTH + 1 + LENGTH_FIELD_LENGTH] != DELIMITER:
            return None, None
        data = data[MSG_HEADER_LENGTH:]
        if len(data) != length_val:
            return None, None
        cmd = cmd_padded.strip()
        return cmd, data

    except Exception:
        return None, None


def split_data(msg, expected_fields):
    fields = msg.split(DATA_DELIMITER)
    if len(fields) != expected_fields:
        return [ERROR_RETURN]
    return fields


def join_data(msg_fields):
    """
    Helper method. Gets a list, joins all of its fields to one string divided by the data delimiter.
    Returns: string that looks like cell1#cell2#cell3
    """
    return DATA_DELIMITER.join(str(f) for f in msg_fields)
