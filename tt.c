#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdbool.h>

int main()
{
    int fs;
	int fd;
	struct stat buf;
	fs = stat("/usr/bin/sudo", &buf);
    if(fs == 0)
        printf("ok");
    else if (fs == -1)
    {
        printf("ko %s", strerror(errno));
    }
}