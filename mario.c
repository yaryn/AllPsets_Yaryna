#include<stdio.h>
#include<cs50.h>
int GetPositiveInt();
int PrintPyramid(int height);
int main(void)
{
    int height=GetPositiveInt();        
    PrintPyramid(height);
}

int GetPositiveInt()
{
    int h;
    do
    {
        printf("Please give me a height where 0>=h>=24: ");
        h = GetFloat();
    }
    while (h > 23 || h < 0);
    return h;
}

int PrintPyramid(int height)
{
    int k1 = 1; 
    int k2 = height;
    for (int i = 0; i < height; i++, k1++, k2--)
    {
        for (int j = 0; j < k2 - 1; j++)
            printf(" ");   
        for (int j = 0; j < k1; j++)
            printf("#");   
        printf("#\n");   //dodatkova stupenka 
    }
    return 0;
}