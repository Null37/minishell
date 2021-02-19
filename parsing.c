#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct		s_option{
	char *option;
	struct s_option	*next;
}					t_option;

typedef struct		s_argument{
	char *argument;
	struct s_argument	*next;
}					t_argument;

typedef struct		s_commands{
	char        *command;
    char        *type;
    int         option;
    char        **arguments;
	struct s_commands	*next;
}					t_commands;

t_commands  *new_commands()
{
    t_commands   *commands;
    if (!(commands = malloc(sizeof(t_commands))))
        return (NULL);
    commands->command = NULL;
    commands->type = NULL;
    commands->arguments = NULL;
    commands->next = NULL;
    commands->option = 0;
    return (commands);
}

void    skip_double_coats(char *cmds, int *i)
{
    while (cmds[++(*i)])
        if (cmds[*i] == 34)
            break ;
}

void    skip_single_coats(char *cmds, int *i)
{
    while (cmds[++(*i)])
        if (cmds[*i] == 44)
            break ;
}

char	*my_substr(char *s, int start, int end)
{
	char	*str;
	int	j;
    int i;


	if (!s)
		return (NULL);
	if (!(str = (char*)malloc(end - start)))
		return (NULL);
	j = 0;
    i = start;
	while (i < end)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_right_path(char *str, int start, int end)
{
	int		i;
	int		j;
	char	*path;

	if (!(path = malloc((sizeof(char) * (end - start)) + 2)))
		return (NULL);
	i = start - 1;
	j = 0;
	while (++i <= end)
	{
		path[j] = str[i];
		j++;
	}
	path[j] = '\0';
	return (path);
}

int		ft_strlen(char *str)
{
	int		cpt;

	cpt = 0;
	while (str[cpt] != '\0')
	{
		cpt++;
	}
	return (cpt);
}

char	*deletespace(char *str)
{
	int	size;
	int	i;
	int	start;
	int	end;

	start = -1;
	end = -1;
	i = -1;
	size = ft_strlen(str);
	while (++i < size)
		if (str[i] != ' ')
		{
			start = i;
			break ;
		}
	i = size;
	while (--i >= 0)
		if (str[i] != ' ')
		{
			end = i;
			break ;
		}
	if (start == -1 || end == -1)
		return (NULL);
	return (get_right_path(str, start, end));
}

int        check_cmd(char *cmnd)
{
    int i;

    i = -1;
    while(cmnd[++i])
    {
        if (cmnd[i] != ' ')
            return (1);
    }
    return (0);
}

int         nbr_argts(t_commands *commands)
{
    int i;
    int cpt;

    cpt = 0;
    i = -1;
    if (!check_cmd(commands->command))
        return (0);
    while (commands->command[++i])
    {
        if (commands->command[i] == 34)
            skip_double_coats(commands->command, &i);
        else if (commands->command[i] == 44)
            skip_single_coats(commands->command, &i);
        if (commands->command[i] == ' ' && commands->command[i + 1] != ' ')
            cpt++;
    }
    cpt++;
    return (cpt);
}

void        split_command(t_commands *commands, int nbr_args)
{
    int i;
    int start;
    int k;

    k = 0;
    i = -1;
    start = 0;
    commands->arguments = malloc(sizeof(char*) * (nbr_args + 1));
    commands->arguments[nbr_args] = NULL;
    while (commands->command[++i])
    {
        if (commands->command[i] == 34)
            skip_double_coats(commands->command, &i);
        else if (commands->command[i] == 44)
            skip_single_coats(commands->command, &i);
        if ((commands->command[i] == ' ' && commands->command[i + 1] != ' ') || commands->command[i + 1] == '\0')
        {
            commands->arguments[k++] = my_substr(commands->command, start, i + 1);
            start = i + 1;
        }    
    }
}

void        trait_command(t_commands *commands)
{
    int i;

    i = -1;
    int nbr_args;
    nbr_args = nbr_argts(commands);
    split_command(commands, nbr_args);
    //printf("%d", nbr_args);

}
void        get_commands(t_commands *commands, char *cmds)
{
    int     i;
    int     start;
    t_commands  *tmp;

    i = -1;
    start = 0;
    while (1)
    {
        if (cmds[++i] == 34)
            skip_double_coats(cmds, &i);
        else if (cmds[i] == 44)
            skip_single_coats(cmds, &i);
        else if (cmds[i] == 59)
        {
            commands->command = my_substr(cmds, start, i);
            commands->command = deletespace(commands->command);
            trait_command(commands);
            commands->next = new_commands();
            commands = commands->next;
            start = i + 1;
        }
        else if (cmds[i] == '\0')
        {
            commands->command = my_substr(cmds, start, i);
            commands->command = deletespace(commands->command);
            trait_command(commands);
            break ;
        }
    }

    commands = tmp;
}


int main()
{
    char *cmds = strdup("cd Desktop; env");
    t_commands   *commands, *tmp;
    commands = new_commands();
    get_commands(commands, cmds);
    int i;
    tmp = commands;
    while (1)
    {
        i = -1;
        while (commands->arguments[++i])
        {
            printf("| %s |", commands->arguments[i]);
        }
        printf("\n");
        if (!commands->next)
            break ;
        commands = commands->next;
    }
    commands = tmp;
    
}