/*переписать четные строки файла f_1 в отсортированном виде в файл f_2.
Количество строк в файле - не более 100. 
Количество символов в строке - не более 80.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Error. Not enough arguments");
		return 0;
	}
	FILE *f_1, *f_2;
	if ((f_1 = fopen(argv[1], "r")) == NULL)
	{
		exit(1);
	}
	if ((f_2 = fopen("t.txt", "w")) == NULL)//create file
	{
		fclose(f_1);
		exit(1);
	}
	char arr_str[100][81];
	char s_tmp[81]; //длина строки не преавышает 80 символов (вкл \n)
	int i_str = 0, c = 1;
	while(fgets(s_tmp, 81, f_1) != NULL)
	{
		if (c % 2 == 0)
		{
			strcpy(arr_str[i_str], s_tmp);
			i_str++;
		}
		c++;
	}
	fclose(f_1);
	for (int j = 1; j < i_str; j++)
	{
		for (int y = 0; y < i_str - j; y++)
		{
			if (strcmp(arr_str[y], arr_str[y+1]) > 0) //надо менять местами
			{
				strcpy(s_tmp, arr_str[y]);
				strcpy(arr_str[y], arr_str[y+1]);
				strcpy(arr_str[y+1], s_tmp);
			}
		}
		
	}
	for(int i = 0; i < i_str; i++)
	{
		fputs(arr_str[i], f_2);
	}
	fclose(f_2);

}