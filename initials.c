#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int print_initials(string s);

int main (void)
{
    string s = GetString();
    
    if (s != NULL)
    {
        print_initials(s);
    }
    printf("\n");
}

int print_initials(string s)
{
    if (s[0] != ' ')
        printf("%c", toupper(s[0]));
        
        for (int i = 1, l = strlen(s); i < l; i++)
        {
            if ((s[i-1] == ' ') && (s[i]) != ' ') 
                printf("%c", toupper(s[i]));
        }
    return 0;
}