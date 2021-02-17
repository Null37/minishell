#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "libft/libft.h"


int  motloba(char *args)
{
	if (ft_strncmp(args, "cd", 2) == 0)
		return 2;
	else if (ft_strncmp(args, "echo", 2) == 0)
		return 2;
	else if(ft_strncmp(args, "pwd", 2) == 0)
		return 2;
	else if(ft_strncmp(args, "echo", 2) == 0)
			return 2;
	else
		return 1;

}

int main()
{
	char *r = (char*)malloc(1024);
	while(1)
	{
		//puts("\033[0;33m");
		char path[200];
		write(1, "\033[0;33m Null37$", 15);
		long size;
		char *buf;
		char *ptr;
		int errcd;
		size = pathconf(".", _PC_PATH_MAX);
		// char *line = 
		if ((buf  = (char *)malloc((size_t)size)) != NULL)
		ptr = getcwd(buf, (size_t)size);
		//write(1, ptr, size);
		ft_bzero(r, 1024);
		read(0, r, 1024);
		write(1, r, strlen(r));
		// if (ft_strchr(r, '\n'))
		// 	*ft_strchr(r, '\n') = '\0';
		char **args = ft_split(r, ' ');
		motloba(args[0]);
		if (strncmp(args[0], "ls", 2) == 0)
		{
			write(1, "\033[0;32m", 8);
			system("/bin/ls");
		}
		else if(strncmp(args[0], "cd", 3) == 0)
		{
			write(1, "\033[0;32m", 8);
			int eee = chdir(args[0]);
			if (eee == -1)
			{
        		 write(1, args[1], strlen(args[1]));
				 write(1, ": ", 2);
				 char *ee = strerror(errno);
				 write(1, ee, strlen(ee));
				 write(1, "\n", 1);
    		}
		}
		else if (strncmp(args[0], "pwd", 3) == 0)
		{
			write(1, ptr, (size_t)size);
			write(1, "\n", 1);
		}
		else if(strncmp(args[0], "exit", 4) == 0)
		{
			exit(1);
		}
	}
}
