from PIL import Image, ImageDraw

first = (
    146, 399, 163, 403, 170, 393, 169, 391, 166, 386, 170, 381, 170, 371, 170,
    355, 169, 346, 167, 335, 170, 329, 170, 320, 170, 310, 171, 301, 173, 290,
    149, 379, 147, 394, 146, 399
)
second = (
    156, 141, 165, 135, 169, 131, 176, 130, 187, 134, 191, 140, 191, 146, 186,
    156, 134, 157, 136, 156, 136
)


def to_points(lst):
    return [(lst[i], lst[i+1]) for i in range(0, len(lst), 2)]


first_points = to_points(first)
second_points = to_points(second)
image = Image.new("RGB", (400, 450), "white")
draw = ImageDraw.Draw(image)
draw.line(first_points, fill="black", width=2)
draw.line(second_points, fill="black", width=2)
image.show()
