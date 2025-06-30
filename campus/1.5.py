import functools
print(functools.reduce(max, open("names.txt", "r")))

print(sum([len(line) - 1 for line in open("names.txt", "r")]) + 1)

m = min(len(name.strip()) for name in open("names.txt", "r"))
new_list = [line for line in open("names.txt", "r") if len(line.strip()) == m]
for i in new_list:
    print(i.strip())

open("name_length", "w").write("\n".join([str(len(line.strip())) for line in open("names.txt", "r")]))

x = int(input("enter a number "))
for i in [word for word in open("names.txt", "r") if len(word.strip()) == x]:
    print(i.strip())
