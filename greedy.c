#include <stdio.h>
#include <cs50.h>
#include <math.h>
int MinAmountCoins(int money); 

int main(void)
    {
        float money;
        do
        {
            printf("O hai! How much change is owed?\n");
            money = GetFloat();
        }
        while (money < 0);
        //float centy = money * 100;
        int centy = round(money * 100);     //double round(double x); 
                                            //printf("%.2f\n", round(4.7));
                                    //----->//      printf("centy = %f * 100\n", money);
            //printf(" money =  %f \n", money);
            //printf(" money * 100 =  %f \n", centy);
            //printf(" 4.2 * 100 =  %f \n", 4.2*100);
        //-------/
        int c = MinAmountCoins(centy);              //min kolich monet
        printf("%i\n", c);
    }
    
int MinAmountCoins(int centy)
{
    int coins, coins2, coins3, coins4;
    int coinsAll = 0;
    int ostatok = 0;
                                //67    420 centy
    coins = centy / 25;         //2     16
    ostatok = centy % 25;       //17    20
    
    coins2 = ostatok / 10;      //1    
    ostatok = ostatok % 10;      //7
        
    coins3 = ostatok / 5;       //1
    ostatok = ostatok % 5;       //2
        
    coins4 = ostatok / 1;       //2
        
    coinsAll = coins + coins2 + coins3 + coins4;
    return coinsAll;
}    