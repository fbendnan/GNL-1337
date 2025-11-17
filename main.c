#include "get_next_line.h"

int main()
{
    int fd = open("text.txt", O_RDWR);

    write(fd, "helllooooooo0o", 14);

    get_next_line(fd);
}