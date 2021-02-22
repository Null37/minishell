#include "minishell_hr.h"
 // typedef struct		s_commands{
// 	char        *command;
//     char        *type;
//     int         option;
//     char        **arguments;
// 	struct s_commands	*next;
// }					t_commands;

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
        if (cmds[*i] == 34 && cmds[*i - 1] != '\\')
            break ;
}

void    skip_single_coats(char *cmds, int *i)
{
    while (cmds[++(*i)])
        if (cmds[*i] == 39)
            break ;
}

char	*my_substr(char *s, int start, int end)
{
	char	*str;
	int	j;
    int i;


	if (!s)
		return (NULL);
	if (!(str = (char*)malloc(end - start + 1)))
		return (NULL);
	j = 0;
    i = start;
	while (s[i] != '\0' && i < end)
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

void    dlt_dbl_cts(char *str, int i)
{
    while (str[++i])
    {
        if (str[i] == '\\')
            continue ;
        if (str[i] == 34 && str[i - 1] != '\\')
            break ;
            str[i - 1] = str[i];
    }
}

void    getdblcoat(char *str, char *s, int *i, int *j)
{
    while (str[++(*i)])
    {
        if (str[*i] == '\\')
        {
            s[*j] = str[*i + 1];
            (*i)++;
            (*j)++;
            continue ;
        }
        if (str[*i] == 34)
            break ;
        s[*j] = str[*i];
        (*j)++;
    }
}

void    getsglcoat(char *str, char *s, int *i, int *j)
{
    while (str[++(*i)])
    {
        if (str[*i] == 39)
            break ;
        s[*j] = str[*i];
        (*j)++;
    }
}

char *deletecoats(char *str)
{
    int i,j;
    char    *s;

    s = malloc(ft_strlen(str) + 1);
    i = -1;
    j = 0;
    while (str[++i])
    {
        if (str[i] == '\\')
        {
            s[j] = str[i + 1];
            i++;
            j++;
            continue ;
        }
        if (str[i] == 34)
        {
            getdblcoat(str, s, &i, &j);
            continue ;
        }
        if (str[i] == 39)
        {
            getsglcoat(str, s, &i, &j);
            continue ;
        }
        s[j] = str[i];
        j++;
    }
    s[j] = '\0';
    return (s);
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
    while (1)
    {
        if (commands->command[++i] == 34)
            skip_double_coats(commands->command, &i);
        else if (commands->command[i] == 39)
            skip_single_coats(commands->command, &i);
        if (commands->command[i] == ' ' && commands->command[i + 1] != ' ')
            cpt++;
        if (!commands->command[i])
            break ;
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
    commands->arguments = malloc(sizeof(char*) * (nbr_args));
    commands->arguments[nbr_args - 1] = NULL;
    while (commands->command[++i])
    {
        if (commands->command[i] == 34)
            skip_double_coats(commands->command, &i);
        else if (commands->command[i] == 39)
            skip_single_coats(commands->command, &i);
        if ((commands->command[i] == ' ' && commands->command[i + 1] != ' ')
        || commands->command[i + 1] == '\0')
        {
            if (!commands->type)
            {
                commands->type = my_substr(commands->command, start, i + 1);
                commands->type = deletespace(commands->type);
                commands->type = deletecoats(commands->type);
            }
            else
            {
                commands->arguments[k] = my_substr(commands->command, start, i + 1);
                commands->arguments[k] = deletespace(commands->arguments[k]);
                commands->arguments[k] = deletecoats(commands->arguments[k]);
                k++;
            }
            start = i + 1;
        }
        if (commands->command[i] == '\0')
            break ;  
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
    tmp = commands;
    while (1)
    {
        if (cmds[++i] == 34)
            skip_double_coats(cmds, &i);
        else if (cmds[i] == 39)
            skip_single_coats(cmds, &i);
        if (cmds[i] == 59)
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


t_commands   *parssing_shell(char *cmds)
{
    //char *cmds = strdup("cd Desktop; env");
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
    /*int i = -1;
    char c;
    while (commands->arguments[0][++i])
    {
        c = commands->arguments[0][i];
    }*/
    return (commands);
}