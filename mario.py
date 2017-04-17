import cs50

def main():
    height = get_positive_int()
    print_pyramid(height)

def get_positive_int():
    while True:
        print("Please give me a height where 0>=h>=24: ", end="")
        h = cs50.get_int()
        if not (h > 23 or h < 0):
            break
    return h

def print_pyramid(height):
    k1 = 1
    k2 = height
    for i in range(height):
        for j in range(k2 - 1):
            print(" ", end="")
        for j in range(k1):
            print("#", end="")
        print("  ", end="")
        for j in range(k1):
            print("#", end="")
        print("")
        k1 = k1 + 1
        k2 = k2 - 1
    return 0
    
if __name__ == "__main__":
    main()