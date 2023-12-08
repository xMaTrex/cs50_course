from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

space = 1
# Zeilen
for i in range(height):
    for space in range(height-i-1): # because i is 0 at the beginning
        print(" ", end = "")

    for j in range(i+1):
        print("#", end = "")

    print()