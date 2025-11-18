#include "get_next_line.h"
#include <stdio.h>

int main()
{
    int fd = open("text.txt", O_RDWR);

    write(fd, "helllooo\n", 8);
    char   *str = get_next_line(fd);
    printf("%s", str);
}
