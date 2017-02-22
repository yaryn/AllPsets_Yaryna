//алгоритм Блеза де Віженера.шифрування в ньому шляхом використання послідовності ключів (або ключових слів). 
//Тобто, якщо р - деякий текст і k - ключове слово (як де А та а -  0, Z та z - 25),
//то кожна літера ci  в зашифрованому тексті c обраховується як:
// ci = (pi + kj) % 26
#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int encrypts_vigenere(int kk, string s, string k);

int main (int argc, string argv[])  //int argc - лічильник кількості аргументів командного рядка,
                                    //string argv[] - масив, що містить аргументи командного рядка.
{                                   //після ./файл ab- це аргумент командного рядку, який змін. кожного разу, як виконуєmo програму
    string k = argv[1];             //argc == 3 argv[0] == ./файл    argv[1] == ab 

    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    else 
    {
        for (int i = 0, kl = strlen(k); i < kl; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Error key, must be alphabet\n");

                return 1;
            }    
        }
    }
    
    printf("plaintext: ");
    string s = GetString();
    
    //string k = argv[1];
    int kk = strlen(k);
    
    printf("ciphertext: "); 
    
    encrypts_vigenere(kk, s, k);
}

int encrypts_vigenere(int kk, string s, string k)
{
    int j = 0;
    int s1, s2, symbol;
    int kj;
    
    for (int i = 0, l = strlen(s); i < l; i++)
    {
            kj = tolower(k[j % kk]) - 'a';
            //printf("\nj=%i kj= k[%i]\n", j, kj);
        if (isupper(s[i]))
        {
            symbol = s[j] + kj;
            s1 = (symbol - 'A') % 26;
            s2 = s1 + 'A';
            printf("%c", s2);
            j++;
        }
        else
            if (islower(s[i]))
            {
                symbol = s[i] + kj;
                s1 = (symbol - 'a') % 26;
                s2 = s1 + 'a';
                printf("%c", s2); 
                j++;
            }
            else
                printf("%c", s[i]);
    }      
    printf("\n");
    return 0;
}