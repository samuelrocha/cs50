from cs50 import get_int

tam = 0
while True:
    tam = get_int("Height: ")
    if tam >= 1 and tam <= 8:
        for i in range(tam):
            for j in range(tam):
                if i+j >= tam - 1:
                    print("#", end="")
                else:
                    print(" ", end="")
            print("  ", end="")
            for j in range(tam):
                if j <= i:
                    print("#", end="")
            print(end="\n")
        break



