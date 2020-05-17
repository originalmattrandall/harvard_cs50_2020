def main():
    i = get_positive_int()
    build_pieces(i)

def get_positive_int():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0 and n < 9:
                break
        except:
            print("must be a non negative integer")
    return n

def build_pieces(height):
    for brick in range(height):
        print(("#" * (brick + 1)).rjust(height))

main()