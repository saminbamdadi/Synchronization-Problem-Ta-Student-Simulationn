#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int list[SIZE] = {10, 11, 12, 13, 15, 16, 1, 2, 4, 3};
int sorted_list[SIZE];

typedef struct
{
    int start;
    int end;
} ThreadArgs;

void *bubble_sort(void *args)
{
    ThreadArgs *arg = (ThreadArgs *)args;
    int start = arg->start;
    int end = arg->end;

    for (int i = start; i < end - 1; i++)
    {
        for (int j = start; j < end - 1 - (i - start); j++)
        {
            if (list[j] > list[j + 1])
            {
                int temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    pthread_exit(0);
}

void *merge(void *args)
{
    int i = 0;
    int j = SIZE / 2;
    int k = 0;

    while (i < SIZE / 2 && j < SIZE)
    {
        if (list[i] < list[j])
            sorted_list[k++] = list[i++];
        else
            sorted_list[k++] = list[j++];
    }

    while (i < SIZE / 2)
        sorted_list[k++] = list[i++];

    while (j < SIZE)
        sorted_list[k++] = list[j++];

    pthread_exit(0);
}

int main()
{
    pthread_t tid1, tid2, tid_merge;

    ThreadArgs arg1 = {0, SIZE / 2};
    ThreadArgs arg2 = {SIZE / 2, SIZE};

    pthread_create(&tid1, NULL, bubble_sort, &arg1);
    pthread_create(&tid2, NULL, bubble_sort, &arg2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_create(&tid_merge, NULL, merge, NULL);
    pthread_join(tid_merge, NULL);

    printf("Sorted List: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", sorted_list[i]);
    printf("\n");

    return 0;
}
