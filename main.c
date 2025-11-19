#include "get_next_line.h"
#include <stdio.h>

int main()
{
    int fd = open("text.txt", O_RDWR);
    // printf("%d", fd);
    char *a = get_next_line(fd);
    char *b = get_next_line(fd);

    
    printf("line1 %s\n", a);
    printf("line1 %s\n", b);
    free(a);
    free(b);
    // printf("line2 %s\n", get_next_line(fd));
    // printf("line3 %s\n", get_next_line(fd));
    // printf("line4 %s\n", get_next_line(fd));
}