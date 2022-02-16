import sys
# import os
import typing
import random


class RandomGenerator:
    def __init__(self) -> None:
        pass

    def randString(self, len : int) -> str:
        if (len < 0):
            len = -len
        data = ''.join([chr(random.randint(33, 126)) for _ in range(len)])
        return data.replace('"', '-').replace("'","_").replace("`", ".")

    def randRange(self, length : int, low : int, up : int) -> typing.List[int]:
        data = [_ for _ in range(low, up, 1 if (low < up) else -1)]
        random.shuffle(data)
        if (length < len(data)):
            data = data[:length]
        return data

    def randRangeStr(self, len : int, low : int, up : int) -> str:
        return '"' + ' '.join([str(_) for _ in self.randRange(len, low, up)]) + '"'

def main() -> None:
    low = 0
    up = 0
    as_string = 1
    try:
        lenght = int(sys.argv[1])
        low = int(sys.argv[2])
        up = int(sys.argv[3])
        try:
            as_string = int(sys.argv[4])
        except:
            pass
    except :
        try:
            lenght = int(sys.argv[1])
            low = 0
        except:
            print("to genrate a random range:")
            print(f"usage : python3 {sys.argv[0]} <lenght> <lower bound> <up bound> <as string>")
            print("the param <as string> is optional, give it a non-null value\nif u want the output as a string, otherwise the output will be formtted as an array\n")
            print("to genrate a random string:")
            print(f"usage : python3 {sys.argv[0]} <lenght>\n")
            exit(-1)

    g = RandomGenerator()
    if (up == 0 and low == 0):
        print(g.randString(lenght))
    else:
        if (as_string):
            print(g.randRangeStr(lenght, low, up))
        else:
            print(g.randRange(lenght, low, up))

if (__name__ == "__main__"):
    main()