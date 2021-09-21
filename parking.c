/*
на парковку приезжает машина и ей выбирается рандомное место - одно из 20. 
Всего приедет 10 машин. Вывести: номер машины(пид) и парковочное место(номер ряда(всего 5 рядов) 
и номер колонны(их 4) в ряду)*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int create_parking(int rows, int cols)
{
    // create IPC resources
    int shmid = shmget(IPC_PRIVATE, sizeof(int) *rows * cols, 0666);
    int * shared = shmat(shmid, (void*)0 ,0);
    for (int i = 0; i < rows * cols; i++)
    {    
        shared[i] = 0;
    }
    shmdt(shared);
    return shmid;
}

void delete_parking(int shmid)
{
    // remove IPC resources
    shmctl(shmid, IPC_RMID, 0);
    return;
}

int choose_park_place(int* shared, int rows, int cols)
{
    srand(time(0));
    int place = rand() % (rows * cols);
    while (shared[place] != 0)
    {
        place = rand() % (rows * cols);
        
    }
    shared[place] == 1;
    return place;
}

int main(void)
{
    int rows = 5, cols = 4, n = 10;
    int share_id = create_parking(rows, cols);
    for(int i = 0; i < n; i++)
    {
    	pid_t pid = fork();
    	if (pid == 0) //child
    	{
    		int * shared = shmat(share_id, (void*)0 ,0);
    		int i = choose_park_place(shared, rows, cols);
            shmdt(shared);
            exit(i);
    	}
    	else
    	{
    		int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
            {
                int place = WEXITSTATUS(status);
                int place_row = place / rows;
                int place_cols = place - place_row * rows;
                int * shared = shmat(share_id, (void*)0 ,0);
                shared[place] = pid;
                shmdt(shared);
                fprintf(stdout, "Car: %d\n Place:\n row number: %d\n col number: %d\n\n\n", pid, place_row, place_cols);
            }
    	}
    }
    delete_parking(share_id);
    return 0;
}