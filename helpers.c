/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n >= 0)
    {
        // TODO: if value is in values return true
        // Встановити значення верхньої і нижньої межі пошуку
        int lower = 0;
        int upper = n - 1;
              
        while(lower <= upper)
        {
            int middle = (lower + upper) / 2;
            if (values[middle] == value)
                return true;
            else if (values[middle] > value)
                upper = middle - 1;
            else if (values[middle] < value)
                lower = middle + 1;
        }
        return false;
    }
    else
        return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    
    // find max for n
    int max = values[0];
    for (int i = 0; i < n; i++)
    {
        if (max < values[i])
            max = values[i];
            // printf("max=%i\n",max);
    }
    max++;
    // drugij masyv mas[max]
    int mas2[max + 1];
    for (int j = 0; j < max; j++)
    {
        mas2[j] = 0;
    }
    int k;
    for (int j = 0; j < n; j++)
    {
        k = values[j];
        // printf("k=%i\n",k);
        // kk = mas2[k];
        mas2[k] = (mas2[k] + 1);
        // printf("mas2[%i]=%i\n", k, mas2[k]);
        // printf("j=%i\n",j);
    }
    
    // zapyshemo vidsortovanyi masyv
    int i = 0;
    for (int j = 0; j < max; j++)
    {
        printf("j=%i\n",j);
        if (mas2[j] != 0)
        {
            int kol_chysel = mas2[j];
            // printf("kol_chysel=%i\n",kol_chysel);
            while(kol_chysel > 0)
            {
                values[i] = j;
                // printf("values[%i]= %i\n", values[i], j);
                i++;
                kol_chysel--;
            }
        }
    }
    
    /*for (int j = 0; j < n; j++)
    {
        printf("values[%i]= %i\n", j, values[j]);
        
    }*/
    return;
}