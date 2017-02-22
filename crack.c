//Предположим: что каждый пароль хешированы с DES на основе (with C’s DES-based, not MD5-based) crypt функции языка C.
//что каждый пароль не длиннее (gasp) четыре символа
//что каждый пароль состоит исключительно из буквенных символов (прописные и / или в нижнем регистре).
/* at the top of your file in order to use crypt. 
Moreover, you’ll want to link with -lcrypt, as by compiling not with make but with:
    clang -ggdb3 -O0 -std=c11 -Wall -Werror -Wshadow crack.c -lcrypt -lcs50 -lm -o crack */
#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <crypt.h>
#define _XOPEN_SOURCE /* See feature_test_macros(7) */
#include <unistd.h> //char *crypt(const char *key, const char *salt); //является функцией шифрования паролей,
                                    //  чтобы препятствовать использованию аппаратных реализаций ключа поиска
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    } //Если без каких-либо аргументов командной строки или с более чем 1 аргументом - напечатать сообщ. об ошибке
    else 
    {
        //  program must proceed to crack the given password, 
        //  ideally as quickly as possible, ultimately printing the password in the clear followed by \n, 
        //  nothing more, nothing less, with main returning 0.
        string hesh = argv[1];
        
        char s_1[] = {'\0','\0'};
        char s_2[] = {'\0','\0','\0'};
        char s_3[] = {'\0','\0','\0','\0'};
        char s[] = {'\0','\0','\0','\0','\0'};
        // obch. solj:
        char salt[3];
        strncpy(salt, hesh, 2);
        salt[2]='\0';
        
        for (int i = 'a'; i <= 'z'; i++)
        {
            s_1[0] = (char) i;  //  if strlen(key) == 1
            s_2[0] = (char) i;  //  if strlen(key) == 2
            s_3[0] = (char) i;  //  if strlen(key) == 3
            s[0] = (char) i;    //  if strlen(key) == 4
            //  if strlen(key) == 1:
            if ( strcmp (crypt (s_1, salt), hesh) == 0 )
            {
                printf ("%s\n", s_1); 
                return 0;
            }
            // endif 1
            for (int j = 'a'; j <= 'z'; j++)
            {
                s_2[1] = (char) j;  //  if strlen(key) == 2
                s_3[1] = (char) j;  //  if strlen(key) == 3
                s[1] = (char) j;    //  if strlen(key) == 4
                //  if strlen(key) == 2:
                if ( strcmp (crypt (s_2, salt), hesh) == 0 )
                {
                    printf ("%s\n", s_2); 
                    return 0;
                }
                // endif 2
                for (int z = 'a'; z <= 'z'; z++)
                {
                    s_3[2] = (char) z;  //  if strlen(key) == 3
                    s[2] = (char) z;    //  if strlen(key) == 4
                    //  if strlen(key) == 3:
                    if ( strcmp (crypt (s_3, salt), hesh) == 0 )
                        {
                            printf ("%s\n", s_3); 
                            return 0;
                        }//endif 3
                        for (int y = 'a'; y <= 'z'; y++)
                        {
                        s[3] = (char) y; 
                        //  if strlen(key) == 4:
                        if ( strcmp (crypt (s, salt), hesh) == 0 )
                        {
                            printf ("%s\n", s); 
                            return 0;
                        }//endif 4
                    }
                }
            }
        }
        printf("Password not found\n");
    }
}/*
    $ ./crack
    Usage: ./crack hash

    $ ./crack 50fkUxYHbnXGw
    rofl
Testing: No check50 for this one! But odds are, if you can crack all ten passwords above, you’re in good shape!*/