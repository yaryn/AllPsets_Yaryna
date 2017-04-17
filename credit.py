import cs50
import sys

def main():
    while True:
        print("Number: ", end="")
        number = cs50.get_int()
        if not (number < 0):
            break
    # print("number = {}".format(number))
    number0 = number
    kol = GetKol(number)
    # print("kol = {}".format(kol))
    if ((kol == 13) or (kol == 15) or (kol == 16)):
        x = GetLegit(number0, kol)
        if (x % 10 == 0):
            GetNameCard(number, kol)
        else: 
            print("INVALID")
    else:
        print("INVALID")

def GetKol(number):
    #print("number in GetKol= {}".format(number))
    kol = len(str(number))
    #print("kol for GetKol = {}".format(kol))
    return kol

def GetLegit(number0, kol):
    ch = 0
    ch_double = 0 
    suma = 0
    ch_suma1 = 0
    ch_suma2 = 0
    j = 1
    for i in range(kol):
        if j == 2:
            ch = number0 % 10 # ostatok
            ch_double = ch*2  
            if ch_double > 9: 
                ch_double = (ch_double - 10) + (1)
            ch_suma1 = ch_suma1 + ch_double
            j = 1
        else:
            ch = number0 % 10
            ch_suma2 = ch_suma2 + ch
            j = 2
        number0 = (number0 // 10)
    suma = ch_suma1 + ch_suma2
    # print("suma = {}".format(suma))
    return suma

def GetNameCard(number, kol):
    if kol == 15:
        number = number // 10000000000000
        if((number == 34) or (number == 37)): 
            print("AMEX") 
        else: 
            print("INVALID")
    if kol == 13:
        number = number // 1000000000000
        if(number == 4):  
            print("VISA") 
        else:
            print("INVALID")
    if kol == 16:    
        number = number // 100000000000000
        if (number // 10 == 4): 
            print("VISA")
        elif ((number >= 51) or (number <= 55)):
            print("MASTERCARD") 
        else:
            print("INVALID")
    if not (kol == 13 or kol == 15 or kol == 14):
        print("INVALID")
    number = number * 1
    kol = kol * 1
    return 1

if __name__ == "__main__":
    main()