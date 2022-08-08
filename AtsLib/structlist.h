#ifndef ATSLIST_H
#define ATSLIST_H

#include <stdlib.h>
#include <stdio.h>

/* 
    The node for a linked list designated to store structs of varying sizes
*/
typedef struct Node
{
    void *val;
    struct Node *next;
}node_t;

/* 
    Initializes the Structure Linked List

    Params: None

    Returns: node_t head
*/
node_t initlist()
{
    node_t head;
    head.next = 0x0;
    head.val = 0x0;
    return head;
}

/*
    Gets the last node of the Linked List

    Params:
    node_t *head -> The pointer to the head of the Linked List to be used

    Returns:
    node_t *last
*/
node_t * getlastnode(node_t *head)
{
    if (head->next == 0x0) return head;
    node_t *last = head->next;
    while (last->next != 0x0)
        last = last->next;
    return last;
}

/*
    Adds an element to the Linked List

    Params: 
    node_t *head -> The pointer to the head of the Linked List to be used
    void *element -> The pointer to the element to be added

    Returns: None
*/
void stretch(node_t *head, void *element)
{
    node_t *new = (node_t *) malloc(sizeof(node_t));
    new->next = 0x0;
    new->val = element;
    getlastnode(head)->next = new;
}

/*
    Prints an overview of the Linked List

    Params:
    node_t head -> The head of the Linked List to be used

    Returns: None
*/
void overview(node_t head)
{
    if (head.next == 0x0) 
    { 
        puts("Empty List"); 
        return; 
    }

    node_t *ptr = head.next;
    int counter = 1;
    while (1)
    {
        printf("Node %d points to %p\n", counter, ptr->val);
        if(ptr->next == 0x0) break;
        ptr = ptr->next;
        counter++;
    }
}

/*
    Deallocates the designated heap memory of the Linked List

    Params: 
    node_t *head

    Returns: None
*/
void collapse(node_t *head)
{
    if (head->next == 0) return;
    node_t *ptr = head->next;
    node_t *temp;
    node_t *last = getlastnode(head);

    while (1)
    {
        if (ptr->next != 0x0)
            temp = ptr->next;
        free(ptr);
        if (ptr == last) break;
        ptr = temp;
    }
    head->next = 0x0;
    head->val = 0x0;
}

#endif