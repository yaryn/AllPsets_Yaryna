/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

#include <stdio.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
// needle, haystack, size
{
    // TODO: implement a searching algorithm
    if (n < 0) 
    {
        return false;
    }
    
    for(int i = 0; i < n; i++)
    {
        if (values[i] == value)
        { 
            // printf("values[%i] == value -> %i", values[i], value);
            return true;
        }
    }    
    return false;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    /**
    * Сортування масиву із використанням сортування вибором.
    */
    // Пройти по масиву
    for (int i = 1; i < n; i++)
    {
        // Найменший елемент у відсортованій частині
        int min = i;
        // Пройти по невідсортованій частині масиву
        for (int position = i + 1; position < n - 2; position++)
        {
            // Знайти наступний найменший елемент
            if (values[position] < values[min])
            {
                min = position;
            }
            // Обміняти місцями
            int temp = values[i];
            values[i] = min;
            values[position] = temp;
        }
    }
    return;
}