#ifndef ATSSET_H
#define ATSSET_H

#include <stdlib.h>

/*
    Sorted Dynamic Array with no duplicate elements
    Goal: Minimum space complexity (Slow)
    
    Functions:
    - initset
    - exists
    - enlarge
    - visualize
    - getunion
*/
struct Set
{
    double *elements;
    int size;
};
/*
    Sorted Dynamic Array with no duplicate elements
    Goal: Minimum space complexity (Slow)
    
    Functions:
    - initset
    - exists
    - enlarge
    - visualize
    - getunion
*/
typedef struct Set set_t;

/*
    Function for back-end use!!!
    Swamps two numbers
*/
void __swap(double *x, double *y)
{
    double temp = *x;
    *x = *y;
    *y = temp;
}

/*
    Function for back-end use!!!
    Sorts the set
*/
void __setsrt(set_t *set) // Bubble Sort
{
    int i, j;
    for (i = 0; i < set->size-1; i++)
  
        // Last i elements are already in place
        for (j = 0; j < set->size-i-1; j++)
            if (set->elements[j] > set->elements[j+1])
                __swap(&set->elements[j], &set->elements[j+1]);
}

/*
    Function for back-end use!!!
    Checks if an element exists in a set until a given index
*/
int __xist(set_t set, double n, int ind)
{
    int index = -1;
    for (int i = 0; i<ind; i++)
        if (set.elements[i] == n)
        {
            index = i;
            break;
        }
    return index;
}

/*
    Function for back-end use!!!
    Synchronizes the set's size variable and element array's size
*/
void __sync(set_t *set, int offset)
{
    int i;
    double temp[set->size];
    for (i = 0; i<set->size; i++)
        temp[i] = set->elements[i];
    free(set->elements);
    set->elements = (double *) malloc(sizeof(double) * (set->size+offset)); 
    for (i = 0; i<set->size; i++)
        set->elements[i] = temp[i];
}

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
    Checks if an element exists in a set

    Params:
    set_t set -> The set to be checked
    double n -> The number to be checked

    Returns: 
    int index -> The index of the number in the set 
    (-1 if it doesn't exists in the set)
*/
int exists(set_t set, double n)
{
    int index = -1;
    for (int i = 0; i<set.size; i++)
        if (set.elements[i] == n)
        {
            index = i;
            break;
        }
    return index;
}


/*
    Appends an element to the set

    Params:
    set_t *set -> Pointer to the set to be modified
    double n -> The number to be appended

    Returns:
    int success -> Fail = -1, Success = 0
*/
int enlarge(set_t *set, double n)
{
    if (exists(*set, n) != -1) return -1;
    __sync(set, 1);
    set->size++;
    set->elements[set->size-1] = n;
    __setsrt(set);
    return 0;
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
    printf(")\n");
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
    set_t u = initset();
    u.size = one.size + two.size;
    u.elements = (double *) malloc(sizeof(double) * u.size);
    int i;
    int count = 0;

    for (i = 0; i < one.size; i++)
    {
        if (__xist(u, one.elements[i], count) == -1)
        {
            u.elements[count] = one.elements[i];
            count++;
        }
        else u.size--;
    }
    for (i = 0; i < two.size; i++)
    {
        if (__xist(u, two.elements[i], count) == -1)
        {
            u.elements[count] = two.elements[i];
            count++;
        }
        else u.size--;
    }

    __sync(&u, 0);
    __setsrt(&u);
    return u;
}

/*
    Get the intersection set of two sets

    Params:
    set_t one -> The first set
    set_t two -> The second set

    Returns:
    set_t new -> The intersection set
*/
set_t getintersection(set_t one, set_t two)
{
    set_t new = initset();
    if (one.size >= two.size) new.size = one.size;
    else new.size = two.size;
    new.elements = (double *) malloc(sizeof(double) * new.size);

    int count = 0;
    for (int i = 0; i<one.size; i++)
        if (exists(two, one.elements[i]) != -1)
        {
            new.elements[count] = one.elements[i];
            count++;
        }
        else new.size--;
    __sync(&new, 0);
    __setsrt(&new);
    return new;
}


#endif