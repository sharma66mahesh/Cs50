/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool find(int lower, int upper, int val, int values[])
{
    if(upper < lower)
        return 0;
    int mp = (lower + upper) / 2;
    if(values[mp] == val)
        return true;
    else if(upper != lower)
        return (find(lower, mp, val, values) || find(mp+1, upper, val, values));
    else
        return false;
}

bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if(find(0, n-1, value, values))
        return true;
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    if(n < 2)
        return;
    int i, j, temp;
    for(i = 0; i < n-1; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(values[i] > values[j]){
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
    return;
}