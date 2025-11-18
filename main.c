#include "get_next_line.h"
#include <stdio.h>

int main()
{
    int fd = open("text.txt", O_RDWR);
    // printf("%d", fd);

    char   *str = get_next_line(fd);
    printf("%s", str);
}
