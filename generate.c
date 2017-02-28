/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // очікує один або два аргументи командного рядка
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        // Використання 1-го, n, обов’язкове - ск. псевдовипадк. чисел створити
        // 2-й,s,НЕ є обов'язк.(вказ.квадратні дужки),якщо використовується,то
        // являє собою значення, яке генератор псевдовипадк.чисел використ-ме в
        // якості «насіння» - вхідні дані у генератор псевдовипадкових чисел
        // (впливають на його виведення)
        return 1;
    }

    // atoi() перетворює рядок,що містить числа,на число:
    // string number="125";int a=atoi(number);printf("%d\n", a); => 125
    int n = atoi(argv[1]);

    // якщо аргумента 3
    if (argc == 3)
    {
    // генерируют псевдослучайные числа (линейный алгоритм и 48-битных целочисленных
    // арифметических операций: Xn+1 = (aXn + c) mod m, where n >= 0
        srand48((long) atoi(argv[2]));
    }
    // The  srand48(),  seed48()  and  lcong48()  functions  are initialization functions, 
    // one of which should be called before using drand48(), lrand48() or mrand48().
    else
    {
        srand48((long) time(NULL));
        // time (NULL); => получить текущую дату, выраженную в секундах
        // может быть нулевым указателем, тогда параметр не использ,
        // но объект time_t  по-прежнему возвращается функцией
    }
    // Эти функции объявлены устаревшими by SVID 3 и вместо этого следует использовать rand(3)

    // проходимо поки < за аргумент argv[1] і генеруємо числа
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }
    // The drand48() and erand48() functions return nonnegative double-precision floating-point values 
    // uniformly distributed  between  [0.0, 1.0).

    // success
    return 0;
}