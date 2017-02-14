#include <stdio.h>
#include <cs50.h>

int main(void)
    {
        printf("minutes: ");
        int minutes = get_int();
        int bottles = minutes * 12;
            if(minutes == 1) printf("%i minute equals %i bottles\n", minutes, bottles); 
            else
            printf("%i minutes equals %i bottles\n", minutes, bottles);
    }