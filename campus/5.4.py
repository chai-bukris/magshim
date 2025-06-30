def check_id_valid(id_number):
    total = 0
    for i in range(len(str(id_number))):
        if i % 2 == 0:
            total += int(str(id_number)[i])
        else:
            if int(str(id_number)[i]) * 2 < 10:
                total += int(str(id_number)[i]) * 2
            else:
                total += int(str(id_number)[i]) * 2 - 9
    return total % 10 == 0


class IDIterator:
    def __init__(self, id):
        self._id = id

    def __iter__(self):
        return self

    def __next__(self):
        while self._id <= 999999999:
            current = self._id
            self._id += 1
            if check_id_valid(current):
                return current
        raise StopIteration


def id_generator(x):
    while x <= 999999999:
        if check_id_valid(x):
            yield x
        x += 1


def main():
    x = int(input("enter an id: "))
    mode = input("Generator or Iterator? (gen/it)? ")
    if mode == "it":
        iterator = IDIterator(x)
        for i in range(10):
            print(next(iterator))
    elif mode == "gen":
        generator = id_generator(x)
        for _ in range(10):
            print(next(generator))


if __name__ == "__main__":
    main()
