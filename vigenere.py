import cs50
import sys

def main():  
    k = sys.argv[1] 
    if len(sys.argv) != 2:
        print("Usage: ./vigenere k")
        exit(1)
    else: 
        kl = len(k)
        i = 0
        #print("len kl = {}".format(kl))
        for i in range(kl):
            if not (sys.argv[1][i].isalpha):
                print("Error key, must be alphabet")
                return 2
    
    print("plaintext: ", end="")
    s = cs50.get_string()
    
    kk = len(k)
    
    print("ciphertext: ", end="")
    
    encrypts_vigenere(kk, s, k)

def encrypts_vigenere(kk, s, k):
    j = 0
    for i in s:
        kj = ord((sys.argv[1][j % kk]).lower()) - ord('a')
        if i.isupper():
            symbol = ord(s[j]) + kj
            s1 = (symbol - ord('A')) % 26
            s2 = chr(s1 + ord('A'))
            print("{}".format(s2), end="")
            j = j + 1
        elif i.islower():
            symbol = ord(i) + kj
            s1 = (symbol - ord('a')) % 26
            s2 = chr(s1 + ord('a'))
            print("{}".format(s2), end="")
            j = j + 1
        else:
            print("{}".format(i), end="")
            #printf("%c", s[i])
    print("")
    exit(0)

if __name__ == "__main__":
    main()