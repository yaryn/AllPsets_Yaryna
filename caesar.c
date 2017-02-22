#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int encrypts_caesar(int kl, string s);

int main(int argc, string argv[])//int argc - лічильник кількості аргументів командн. рядка,
                                //string argv[] - масив, що містить аргументи командного рядка.
{                               //Цифра після ./caesar - це аргумент командного рядку, який може змінюватися кожного разу, як ви виконуєте програму
    if (argc != 2)
    {
        printf("./caesar k\n");
        return 1;
    } 
    printf("plaintext:  ");
    string s = GetString(); 
    string k = argv[1];
    int kl = atoi(k);//atoi() перетворює рядок,що містить числа,на число: string number="125";int a=atoi(number);printf("%d\n", a);//125
    encrypts_caesar(kl, s);    
}

int encrypts_caesar(int kl, string s)
{
    printf("ciphertext: ");
    int symbol, s1, s2;
    for(int i = 0, l = strlen(s); i < l; i++)
    {
        // if >
        if (isupper(s[i]))
        {
            symbol = (s[i] + kl);
            s1 = (symbol - 'A') % 26;
            s2 = s1 + 'A';
            printf("%c", s2);
        }
        // if <  
        else 
            if (islower(s[i]))
            {
                symbol = (s[i] + kl);
                s1 = (symbol - 'a') % 26;
                s2 = s1 + 'a';
                printf("%c", s2);
            }
            else 
            //other
                printf("%c", s[i]);
    }
        
    printf("\n");    
    return 0;
}