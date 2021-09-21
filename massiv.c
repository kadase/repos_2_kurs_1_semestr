/*
найти в матрице в каждой строке максимальные элементы 
и записать их в другой массив, который будет их хранить
*/
#include <stdio.h>
#include <stdlib.h>

int** create_matr (int arr_i, int arr_j)
{
    int** arr_1;
    arr_1 = (int**)malloc(arr_i * sizeof(int));
    for (size_t i = 0; i < arr_i; i++)
    {
        arr_1[i] = (int*)malloc(arr_j * sizeof(int));
        for (size_t j = 0; j < arr_j; j++)
        {
            scanf("%d", &arr_1[i][j]);
        }
    }
    return arr_1;
}

void max_elem_row (int **arr_1, int* arr_2, int arr_i, int arr_j)
{
    for (size_t i = 0; i < arr_i; i++)
    {
        int max_elem = arr_1[i][0];
        for (size_t j = 0; j < arr_j; j++)
        {
            if (arr_1[i][j] > max_elem)
            {
                max_elem = arr_1[i][j];
            }
        }
        arr_2[i] = max_elem;
    }
}

int main (void)
{
    //create matr
    int arr_i, arr_j;
    printf("Write size of array: ");
    scanf("%d %d", &arr_i, &arr_j);
    printf("Write array:\n");
    int** arr_1 = create_matr(arr_i, arr_j);

    //create matr for max elements from rows
    int* arr_2;
    arr_2 = (int*)malloc(arr_i * sizeof(int));

    max_elem_row(arr_1,arr_2, arr_i, arr_j);

    //print our arr
    printf("Max_elem_row array: ");
    for (int i = 0; i < arr_i; i++)
    {
        printf("%d ", arr_2[i]);
        //printf("\n");
    }
    return 0;
}