#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SAFE(msg, call)\
if ((call) == -1)\
{\
	perror(msg);\
	exit(1);\
}\

int main(int argc, char const *argv[])
{
	//создали канал
	int fd[2];
	pipe(fd);
	//порождаем 1-й процесс (команду передаем в аргументах командной строки)
	pid_t pid_1 = fork();
	if (pid_1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		SAFE("Error exec", execlp(argv[1], argv[1], NULL));
	}
	//его вывод направляем на вход второго процесса
	//порождаем 2-й процесс(команду передаем в аргументах командной строки)
	pid_t pid_2 = fork();
	if (pid_2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		SAFE("Error exec", execlp(argv[2], argv[2], NULL));
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return 0;
}