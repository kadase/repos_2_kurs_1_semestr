#include <stdio.h>
#include <string.h>

char* strcpy(char* s_1, const char* s_2)
{
    int i = 0;
    while(*(s_2 + i) != '\0')
    {
        *(s_1+i) = *(s_2+i);
        i++;
    }
    *(s_1+i) = *(s_2+i);
    return s_1;
}

size_t strcspn(const char* s_1, const char* s_2)
{
    int len = 0;
    for (int i = 0; i < strlen(s_1);i++)
    {
        for (int j = 0; j < strlen(s_2); j++)
        {
            if (s_1[i] == s_2[j])
            {
                return len;
            }
        }
        len++;
    }
    return len;
}

int main()
{
    /*const char s1[6] = "qwerty";
    const char s2[7] = "qweplou";
    int n = 3;
    printf("%d\n", strncmp(s1, s2, n));*/


    char s1[14] = "1234ab154256ab", s2[14] = "56";
    printf("%ld\n", strcspn(s1,s2));
    puts(strcpy(s1, s2));



    /* char c;
    int i;
    scanf_s("%c", &c);
    i = c;
    printf("%d", i);*/
    return 0;
}

