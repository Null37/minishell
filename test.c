#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "libft/libft.h"

// extern char*

void command_cd(char **args)
{
	write(1, "\033[0;32m", 8);
	int eee = chdir(args[1]);
	if (eee == -1)
	{
		write(1, args[1], strlen(args[1]));
		write(1, ": ", 2);
		char *ee = strerror(errno);
		write(1, ee, strlen(ee));
		write(1, "\n", 1);
	}
}

void command_pwd(char *ptr)
{

	char *ech;

	if(ptr != NULL)
	{
		write(1, ptr, strlen(ptr));
		write(1, "\n", 1);
	}
	else
	{
		ech = strerror(errno);
		write(1, ech, ft_strlen(ech));
	}
}

void command_exit(void)
{
	exit(EXIT_SUCCESS);
}

void command_env(char **envp)
{
	  int i = 0;
    while(envp[i] != NULL)
    {
        printf("%s\n", envp[i]);
        i++;
    }

}

int our_command(char **args, char*ptr, char **envp)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		command_cd(args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		command_pwd(ptr);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		command_exit();
	else if (ft_strncmp(args[0], "env", 3) == 0)
		command_env(envp);
	else 
		return 2;
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	char *r = (char*)malloc(10240);
	while(1)
	{
		//puts("\033[0;33m");
		char path[200];
		write(1, "\033[0;33mNull37$ ", 15);
		int errcd;
		char *buf;
		char *ptr;
		ptr = getcwd(buf, 1024);
		//write(1, ptr, size);
		ft_bzero(r, 1024);
		read(0, r, 1024);
		write(1, r, strlen(r));
		if (ft_strchr(r, '\n'))
			*ft_strchr(r, '\n') = '\0';
		char **args = ft_split(r, ' ');
		if (our_command(args, ptr, envp) == 2)
		{
			write(1, "not our", 7);
			write(1, "\n", 1);
		}
	}
}
