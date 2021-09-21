/*Реализовать игру «пинг-понг» для n процессов. Задаём в командной строке.
Начальное и конечное целые числа переданы в командной строке. 
Принимающий увеличивает число на 1 и передаёт дальше, и так по кругу до тех пор, 
пока число не превысит заданный максимум.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int count, max, k, n;
int fd[2];
pid_t* p;

void SigHndlr (int s)
{
	read(fd[0], &count, sizeof(int));
	read(fd[0], &k, sizeof(int));
	if (count <= max)
	{
		printf("%d %d\n", getpid(), count);
		count++;
		write(fd[1], &count, sizeof(int));
		if (k == 0)
		{
			k = n - 1;
			write(fd[1], &k, sizeof(int));
			kill(p[k], SIGUSR1); //отец опять отправляет послденему сыну сигнал
		}
		else if (k == 1)
		{
			k--;
			write(fd[1], &k, sizeof(int));
			kill(getppid(), SIGUSR1);
		}
		else
		{
			k--;
			write(fd[1], &k, sizeof(int));
			kill(p[k], SIGUSR1);
		}
	}
	else
	{
		if (k != 0)
		{
			k = 0;
			write(fd[1], &count, sizeof(int));
			write(fd[1], &k, sizeof(int));
			kill(getppid(), SIGUSR1);

		}
		else
		{
			for (int j = 1; j < n; j++)
			{
				kill(p[j], SIGKILL);
			}
		}
	}
}

int main (int argc, char* argv[])
{
	if (argc < 4)
	{
		printf("Not enough arguments\n");
		return 1;
	}
	pipe(fd);//глобальная
	signal(SIGUSR1, SigHndlr);
	count = atoi(argv[1]);
	max = atoi(argv[2]);
	n = atoi(argv[3]);
	p = (pid_t*)malloc(n*sizeof(pid_t)); //массив пидов
	for (int i = 1; i < n; i++)
	{
		p[i] = fork();
		if (p[i] == 0)
		{
			for(;;); //зацикливаем сыновей
		}
	}
	k = n - 1;
	write(fd[1], &count, sizeof(int)); //записываем count в канал
	write(fd[1], &k, sizeof(int)); // хаписываем номер процесса в массиве пидов, которому мы передаем сигнал
	kill(p[k], SIGUSR1); //отправляем сигнал катому процессу
	for (int i = 0; i < (n - 1); i++)
	{
		wait(NULL); //зомби пока пока
	}
	close(fd[0]);
	close(fd[1]);
	free(p);

	return 0;

}