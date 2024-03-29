#ifndef ATSDYNARR_H
#define ATSDYNARR_H

#include <stdio.h>
#include <stdlib.h>

/*
    Dynamic Array
    Goal: Slight emphasis on space complexity (Reasonable speed)

    Functions:
    - initdynarr
    - freedynarr
    - display
    - append
    - squeeze
    - pick
    - indexof
    - yeet
 
    Variables (DO NOT MODIFY FOR PROPER FUNCTIONALITY!!!):
    - double *items
    - int size
    - int len
*/
typedef struct DynArr
{
    double *items;
    int size;
    int len;
}dynarr_t;

/*
    Initializes a Dynamic Array

    Params: None

    Returns:
    dynarr_t *arr -> Pointer to a Dynamic Array with initial size 2
*/
dynarr_t *initdynarr()
{
    dynarr_t *arr = (dynarr_t *) malloc(sizeof(dynarr_t));
    arr->size = 2;
    arr->len = 0;
    arr->items = (double *) malloc(sizeof(double) * arr->size);
    return arr;
}

/*
    Frees the Memory Used by the Dynamic Array
    DO NOT REFERENCE THE DYNAMIC ARRAY AFTER THIS!

    Params:
    dynarr_t *arr -> The pointer to the dynamic array to be freed

    Returns: None
*/
void freedynarr(dynarr_t *arr)
{
    free(arr->items);
    free(arr);
}

/*
    Prints the given Dynamic Array

    Params: 
    dynarr_t *arr -> A Pointer to the Dynamic Array to be printed

    Returns: None
*/
void display(dynarr_t *arr)
{
    printf("{ ");
    for (int i = 0; i<arr->len; i++)
        printf("%lf ", arr->items[i]);
    printf("}\n");
}

/*
    Appends the given number to the end of the Dynamic Array

    Params: 
    dynarr_t *arr -> Pointer to the Dynamic Array to be used
    double n -> The number to be appended

    Returns: None 
*/
void append(dynarr_t *arr, double n)
{
    if (arr->size <= arr->len)
    {
        double temp[arr->len];
        int i;
        for (i = 0; i<arr->len; i++)
            temp[i] = arr->items[i];
        arr->size+=6;
        free(arr->items);
        arr->items = (double *) malloc(sizeof(double) * arr->size);
        for (i = 0; i<arr->len; i++)
            arr->items[i] = temp[i];
    }
    arr->items[arr->len] = n;
    arr->len++;
}

/*
    Inserts an element into the given index

    Params:
    dynarr_t *arr -> The pointer to the array to be used
    double n -> The value to be inserted
    int ind -> The index to be inserted into

    Returns:
    int success -> Success = 0, Fail = -1
*/
int squeeze(dynarr_t *arr, double n, int ind)
{
    if (!(ind >= 0 && ind < arr->len)) return -1;

    append(arr, arr->items[arr->len]); // in case there has to be a size increase
    for (int i = arr->len-1; i>ind; i--)
        arr->items[i] = arr->items[i-1];
    arr->items[ind] = n;
    return 0;
}

/*
    Removes the element at the given index

    Params:
    dynarr_t *arr -> A Pointer to the Dynamic Array to be used
    int ind -> The index to be removed; the last element is removed
    if it equals -1

    Returns:
    int success -> Success = 0, Fail = -1
*/
int pick(dynarr_t *arr, int ind)
{
    arr->items[arr->len] = 0;
    arr->len--;
    if (ind == -1) return -1;

    double temp[arr->len];

    int i;
    int count = 0;
    for (i = 0; i<=arr->len; i++)
    {
        if (i != ind)
        {
            temp[count] = arr->items[i];
            count++;
        }
    }
    
    free(arr->items);
    arr->items = (double *) malloc(sizeof(double) * arr->size);
    for (i = 0; i<arr->len; i++)
        arr->items[i] = temp[i];
    return 0;
}

/*
    Finds the indexes of an each occurance of a number

    Params: 
    dynarr_t arr -> A Pointer to the Dynamic Array to be checked
    double n -> The value to be searched

    Returns: 
    int *indexes (Allocated to the heap)
    -1 -> Terminator at the end of the returned array to help with loops etc, 
    no instances were found if it's the only element of the returned array
*/
int *indexof(dynarr_t *arr, double n)
{
    int list[arr->len];
    int list_size = 0;
    int i;

    for (i = 0; i<arr->len; i++)
        if (arr->items[i] == n)
        {
            list[list_size] = i;
            list_size++;
        }
    
    int *temp;
    if (list_size == 0)
    {
        temp = (int *) malloc(sizeof(int) * 1);
        temp[0] = -1;
        return temp;
    }
    // The extra slot will be -1 end be used as a terminator when needed
    temp = (int *) malloc((list_size+1) * sizeof(int));
    temp[list_size] = -1; 
    for (i = 0; i<list_size; i++)
        temp[i] = list[i];
    return temp;
}

/*
    Removes all instances of a number

    Params:
    dynarr_t *arr -> Pointer to the Dynamic Array to be used
    double n -> The number to be removed

    Returns:
    int success -> Success = 0, Fail = -1
*/
int yeet(dynarr_t *arr, double n)
{
    int *ind = indexof(arr, n);
    if (ind[0] == -1) return -1;
    int i = 0;
    while (ind[i] != -1) // -1 -> terminator
    {
        pick(arr, ind[i]);
        i++;
    }
    free(ind);
    return 0;
}

/*
    Manually reserves some extra space for the given Dynamic Array

    Params:
    dynarr_t *arr -> Pointer to the array to be used
    int n -> How much the space will be expanded in terms of elements

    Returns: None
*/
void manualreserve(dynarr_t *arr, int n)
{
    double temp[arr->len];
    int i;

    for (i = 0; i<arr->len; i++)
        temp[i] = arr->items[i];

    arr->size+=n;
    free(arr->items);
    arr->items = (double *) malloc(sizeof(double) * arr->size);

    for (i = 0; i<arr->len; i++)
        arr->items[i] = temp[i];
}

#endif
