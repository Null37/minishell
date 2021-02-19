#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "libft1/libft.h"


typedef struct		s_commands{
	char        *command;
    char        *type;
    int         option;
    char        **arguments;
	struct s_commands	*next;
}					t_commands;

t_commands   *parssing_shell(char *cmds);