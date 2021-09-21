#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Программа. Дан файл f. Создать два файла f1 и f2 следующим образом: 
в файл f1 записать в том же порядке все строки из файла f, состоящие 
только из латинских букв (прописных и строчных);в файл f2 – строки файла f, 
состоящие только из цифр; все остальные строки файла f 
не записываются ни в один из этих файлов
*/
#define SAFE(msg, call, file)\
if ((call) == -1)\
{\
    perror(msg);\
    close(file);\
    exit(1);\
}\

void write_in_file(char* s, int flag_znak, int flag_let, int flag_num, int f_1, int f_2)
{
    if (flag_znak == 0)
    {
        if ((flag_let != 0) && (flag_num == 0))
        {
            write (f_1, s, strlen(s));
        }
        else if ((flag_let == 0) && (flag_num != 0))
        {
            write (f_2, s, strlen(s));
        }
        else
        {
            return;
        }
    }
    return;
}

int main (int argc, char **argv)
{
    int f, f_1, f_2;
    SAFE("Error with f", (f = open(argv[1], O_RDONLY)), f)
    SAFE("Error with f_1", (f_1 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0777)), f_1)
    SAFE("Error with f_1", (f_2 = open(argv[3], O_CREAT | O_WRONLY | O_TRUNC, 0777)), f_2)
    char buf;
    char s[1024];
    int i = 0, flag_let = 0, flag_num = 0, flag_znak = 0;
    while (read(f, &buf, sizeof(char)) > 0) 
    {
        if (buf != '\n')
        {
            if (((buf >= 'a') && (buf <= 'z'))  || ((buf >= 'A') && (buf <= 'Z')))
            {
                flag_let = 1;
            } 
            else if ((buf >= '0') && (buf <= '9'))  
            {
                flag_num = 1;
            }
            else if (buf != ' ')
            {
                flag_znak = 1;  
            }
            s[i++] = buf;
        }
        else
        {
            s[i++] = '\n';
            s[i] = '\0';
            write_in_file(s, flag_znak, flag_let, flag_num, f_1, f_2);
            for (int j = 0; j < i; j++)
            {
                s[j] = '\0';
            }
            i = 0;
            flag_znak = 0;
            flag_let = 0;
            flag_num = 0;
        } 
    }
    if (i != 0)
    {
        s[i] = '\0';
        write_in_file(s, flag_znak, flag_let, flag_num, f_1, f_2);
    }
    close(f);
    close(f_1);
    close(f_2);
    return 0;
}