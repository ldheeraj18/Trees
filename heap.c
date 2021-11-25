#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(int *heap, int data, int *h_size);
void delete(int *heap, int data , int *h_size);
void restore_up(int *heap, int i);
void restore_down(int *heap, int h_size, int i);
void display(int *heap, int *h_size);
int main()
{
    int h_size=0, heap[100];
    heap[0] = 99999;
    int n, choice, data;
    do{
        printf("1.Insert.\n");
        printf("2.Delete.\n");
        printf("3.Display.\n");
        printf("4.Exit\n");
        printf("*******************************\n");
        printf("\nEnter your choice.\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("Enter number of Terms you want to enter in the heap.\n");
                scanf("%d", &n);
                printf("Enter the elements you want to enter.\n");
                for(int i=0; i<n; i++)
                {
                    scanf("%d", &data);
                    insert(heap, data, &h_size);
                }
                break;
            case 2:
                printf("Enter the number you want to delete.\n");
                scanf("%d", &data);
                delete(heap, data, &h_size);
                break;
            case 3:
                display(heap, &h_size);
                break;
            case 4:
                break;
            default:
                printf("Wrong choice.\n");
        }
    }while(choice != 4);
    return 0;
}
void insert(int *heap, int data, int *h_size)
{
    (*h_size)++;
    heap[*h_size] = data;
    restore_up(heap, *h_size);
}
void delete(int *heap, int data , int *h_size)
{
    int i = 1;
    while(heap[i] != data)
        i++;
    heap[i] = heap[*h_size];
    (*h_size)--;
    restore_down(heap, *h_size, i);
}
void restore_up(int *heap, int i)
{
    int par = i/2, num = heap[i];
    while(heap[par]<num)
    {
        heap[i] = heap[par];
        i = par;
        par = i/2;
    }
    heap[i] = num; 
}
void restore_down(int *heap, int h_size, int i)
{
    int left = i*2, right = left+1;
    int num = heap[i];
    while(right <= h_size)
    {
        if(heap[left] <= num && heap[right] <= num)
        return;
        else if(heap[left] > heap[right])
        {
            heap[i] = heap[left];
            i = left;
        }
        else
        {
            heap[i] = heap[right];
            i = right;
        }
        left = i*2; right = left+1;
    }
    if(left == h_size && num < heap[left])
    {
        heap[i] = heap[left];
        i = left;
    }
    heap[i] = num;
}
void display(int *heap, int *h_size)
{
    for(int i=1; i<=*h_size; i++)
        printf("%d - ", heap[i]);
    printf("\n");
}