import string


class UsernameContainsIllegalCharacter(Exception):
    def __init__(self, char, index):
        self.char = char
        self.index = index
        super().__init__(f"Username contains illegal character '{char}' at index {index}")


class UsernameTooShort(Exception):
    def __init__(self):
        super().__init__("Username is too short (minimum is 3 characters)")


class UsernameTooLong(Exception):
    def __init__(self):
        super().__init__("Username is too long (maximum is 16 characters)")


class PasswordMissingCharacter(Exception):
    def __init__(self, missing_type):
        super().__init__(f"Password is missing a {missing_type}")


class PasswordTooShort(Exception):
    def __init__(self):
        super().__init__("Password is too short (minimum is 8 characters)")


class PasswordTooLong(Exception):
    def __init__(self):
        super().__init__("Password is too long (maximum is 40 characters)")


def check_input(username, password):
    if len(username) < 3:
        raise UsernameTooShort()
    if len(username) > 16:
        raise UsernameTooLong()
    for i, char in enumerate(username):
        if not (char.isalnum() or char == '_'):
            raise UsernameContainsIllegalCharacter(char, i)
    if len(password) < 8:
        raise PasswordTooShort()
    if len(password) > 40:
        raise PasswordTooLong()

    if not any(c.isupper() for c in password):
        raise PasswordMissingCharacter("uppercase letter")
    if not any(c.islower() for c in password):
        raise PasswordMissingCharacter("lowercase letter")
    if not any(c.isdigit() for c in password):
        raise PasswordMissingCharacter("digit")
    if not any(c in string.punctuation for c in password):
        raise PasswordMissingCharacter("special character")

    print("OK")


def main():
    while True:
        username = input("Enter username: ")
        password = input("Enter password: ")
        try:
            check_input(username, password)
            break
        except Exception as e:
            print("Error:", e)


if __name__ == "__main__":
    main()
