#ifndef ATSSET_H
#define ATSSET_H

#include <stdlib.h>

/*
    Sorted Dynamic Array with no duplicate elements
    Goal: Minimum space complexity (Slow)
*/
struct Set
{
    double *elements;
    int size;
};
typedef struct Set set_t;

/*
    Creates an instance of a set

    Params: None

    Returns:
    set_t set
*/
set_t initset()
{
    set_t set;
    set.elements = NULL;
    set.size = 0;
    return set;
}

/*
    Function for back-end use!!!
    Sorts the set
*/
void setsrt(set_t &set)
{

}

/*
    Appends an element to the set

    Params:
    set_t *set -> Pointer to the set to be modified
    double n -> The number to be appended

    Returns: None
*/
void enlarge(set_t *set, double n)
{
    double temp[set->size];
    int i;
    for (i = 0; i<set->size; i++)
        temp[i] = set->elements[i];
    set->elements = (double *) malloc(sizeof(double) * (set->size+1)); 
    for (i = 0; i<set->size; i++)
        set->elements[i] = temp[i];
    set->size++;
    set->elements[set->size-1] = n;
}

/*
    Prints the given set

    Params:
    set_t set -> The set to be printed

    Returns: None
*/
void visualize(set_t set)
{
    printf("( ");
    for (int i = 0; i<set.size; i++)
        printf("%lf ", set.elements[i]);
    printf(" )\n");
}

/*
    Get the union set of two sets

    Params:
    set_t one -> The first set
    set_t two -> The second set

    Returns:
    set_t u -> The union set
*/
set_t getunion(set_t one, set_t two)
{
    set_t foo;
    return foo;
}



#endif