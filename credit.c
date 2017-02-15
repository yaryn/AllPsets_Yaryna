#include<stdio.h>
#include<cs50.h>
#include<math.h>

int GetKol (long long number);
int GetLegit(long long number0, int kol);
int GetNameCard(long long number, int kol);

int main(void)
{
    long long number;
    do
    {
        printf("Number: ");
        number = GetLongLong();
    }
    while (number < 0);
    
    long long number0 = number;
    
    int kol = GetKol(number);
    if (kol == 13 || kol == 15 || kol == 16) //shchob marno ne schytaty
    {
        int x = GetLegit(number0, kol);
    
        if (x % 10 == 0)
            GetNameCard(number, kol);
        else 
            printf("INVALID\n");
    }        
    else 
            printf("INVALID\n");
}


int GetKol (long long number)
{
    int kol = 0;        //strlen(number);
    long number_s = number;
    
    do
    {
        kol++;
        number_s = number_s / 10;
    } 
    while (number_s  > 0);
    
    return kol;
}

int GetLegit(long long number0, int kol)
{
    int ch = 0; int ch_double =0; 
    int suma = 0, ch_suma1 = 0, ch_suma2 = 0;
    
    int j = 1 ;
   
    for (int i = 0; i < kol; i++)
    {
        if (j == 2)
        {
            ch = number0 % 10; //ostatok
            ch_double = ch*2;   
            
            if(ch_double > 9) 
                ch_double = (ch_double - 10) + (1);
                
            ch_suma1 = ch_suma1 + ch_double;
            j = 1;
            ///printf("ch= %i\n", ch);printf("ch_double= %i\n", ch_double);printf("ch_suma1= %i\n", ch_suma1);
        }
        else
        {
            ch = number0 % 10;
            ch_suma2 = ch_suma2 + ch;
            ///printf("ch= %i\n", ch);printf("ch_suma2= %i\n", ch_suma2);            
            j = 2;
        }
        number0 = (number0 / 10);  
        ///printf("number0= %lli\n\n", number0);
    }
    suma = ch_suma1 + ch_suma2;
    ///printf("suma= ch_suma1 + ch_suma2= %i\n\n", suma);
    //printf("suma= %i/n", suma);
    return suma;
       
       
}

int GetNameCard(long long number, int kol)
{
    switch(kol)
    {
        case 15:    //start with 34, 37 Amex
            number = number / 10000000000000;
            if((number == 34) || (number == 37)) printf("AMEX\n"); else printf("INVALID\n");
        break;
        
        case 13:    //13 i 16 if... //start with 4 Visa
            number = number / 1000000000000;
            if(number == 4)  printf("VISA\n"); else printf("INVALID\n");
        break;
        
        case 16:    //start with 51 - 55 MasterCard
            number = number / 100000000000000;
            if(number / 10 == 4) printf("VISA\n"); 
                else if((number >= 51) || (number <= 55)) printf("MASTERCARD\n"); 
                    else printf("INVALID\n");
        break;
        
        default: printf("INVALID\n");
        break;
    }
    
    number = number * 1;
    kol = kol * 1;
    //printf("\nYour number: %lli legit, kol = %i\n", number, kol);
   
    return 1;
    
}