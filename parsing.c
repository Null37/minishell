#include "minishell_hr.h"
 // typedef struct		s_commands{
// 	char        *command;
//     char        *type;
//     int         option;
//     char        **arguments;
// 	struct s_commands	*next;
// }					t_commands;
typedef struct		s_tmp{
	char *s1;
	char *s2;
	int i;
	int j;
}					t_tmp;
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
int syntax(char ch, int i)
{
    if((ft_isalpha(ch) == 1 && i == 0) || (ch == '_' && i == 0))
        return 1;
    else if((ft_isalpha(ch) == 1 && i != 0) || (ft_isdigit(ch) ==1 && i != 0))
        return 1;
    return 0;
}
char		*ft_strjoin1(char *s1, char *s2)
{
	size_t	size;
	char	*str;
	int i;
	int j;

	i = -1;
	j = 0;
	if (!s1)
		return ((str = ft_strdup(s2)));
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char *search_in_env(char *variable, char **envp)
{
    int lenp;
    int lenarg;
    char *buff;
    char *fsf;
    int k = 0;
    int j = 0;
    int  hh = 0;
    fsf = ft_strdup(" ");
    buff = ft_strdup("");
    lenp = len_of_args(envp);
    lenarg = nbr_argts2(g_cmds) - 1;
	variable = ft_strjoin(variable, "=");
    for (int i = 0; i < lenp; i++)
    {
        if (ft_strncmp(envp[i], variable, ft_strlen(variable)) == 0)
        {
            j = 0;
            while (envp[i][j])
            {
                if(envp[i][j] == '=')
                {
                    j += 1;
                    while(envp[i][j])
                    {
                        fsf[0] = envp[i][j];
                        buff = ft_strjoin(buff, fsf);
                        j++;
                    }
                    return buff;
                }
                j++;
            }
        }
    }
	return NULL;
}


int    find_equal(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		return (i);
	}
	return (-1);
}

int    chck_sntx(char *str)
{
	int i;
	int q;

	if ((q = find_equal(str)) != -1)
	{
		if (ft_isalpha(str[0]) || str[0] == '_')
		{
			i = 0;
			while (++i < q)
				if (!ft_isalnum(str[i]) || str[i] == '_')
					return (0);
		}
		else
			return (0);
	}
	return (1);
}

int		skip_double_coats(char *cmds, int *i)
{
	while (cmds[++(*i)])
		if (cmds[*i] == 34 && cmds[*i - 1] != '\\')
			return (0);
	return (1);
}

int		skip_single_coats(char *cmds, int *i)
{
	while (cmds[++(*i)])
		if (cmds[*i] == 39)
			return (0);
	return (1);
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

/*char *syn_dollar(char *test)
{
	int i = 0;
	while (test[i])
	{
		if(syntax(test[i], i) == 1)
			i++;
		else
			break;
	}
	if(i == 0)
		i += 1;
	return (test  i);
}*/

char	*add_vrbs(char **envp, char *str, t_tmp *tmp, char *typ)
{
	int k;
	char *test;
	int z;

	k = tmp->i;
	z = -1;
	while (1)
	{
		if (!syntax(typ[++(tmp->i)], ++z) && z == 0)
		{
			test = my_substr(typ, k + 1, tmp->i + 1);
			//test =  syn_dollar(test);
			test = search_in_env(test, envp);
			break ;
		}
		else if (!syntax(typ[tmp->i], z))
		{
			
			test = my_substr(typ, k + 1, tmp->i);
			//test =  syn_dollar(test);
			test = search_in_env(test, envp);
			--(tmp->i);
			break ;
		}
	}
	if (test)
		str = ft_strjoin1(str, test);
	return (str);
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

char	*getdblcoat(char **envp, char *rstr, char *str, t_tmp *tmp)
{
	while (str[++(tmp->i)])
	{
		if (str[tmp->i] == '$')
		{
			rstr = add_vrbs(envp, rstr, tmp, str);
			continue ;
		}
		if (str[tmp->i] == '\\')
		{
			tmp->s1[0] = str[tmp->i + 1];
			rstr = ft_strjoin1(rstr, tmp->s1);
			(tmp->i)++;
			continue ;
		}
		if (str[tmp->i] == 34)
			break ;
		tmp->s1[0] = str[tmp->i];
		rstr = ft_strjoin1(rstr, tmp->s1);
	}
	return (rstr);
}

char	*getsglcoat(char *rstr, char *str, t_tmp *tmp)
{
	while (str[++(tmp->i)])
	{
		if (str[tmp->i] == 39)
			break ;
		tmp->s1[0] = str[tmp->i];
		rstr = ft_strjoin1(rstr, tmp->s1);
	}
	return (rstr);
}

/*int get_size(char *str, t_tmp *tmp)
{
	int k;
	int cpt;

	cpt = 0;
	k = *i;
	while(1)
		if (str[k] != '\0')
			cpt++;
		else
			break ;
	return (cpt);
}*/





char *deletecoats(char **envp, char *str)
{
	char *ss;
	char    *rstr;
	t_tmp	*tmp;
	
	rstr = NULL;
	tmp = malloc(sizeof(t_tmp));
	tmp->s1 = malloc(2);
	tmp->s1[1] = '\0';
	tmp->i = -1;
	tmp->j = 0;
	while (str[++(tmp->i)])
	{
		if (str[tmp->i] == '\\')
		{
			tmp->s1[0] = str[tmp->i + 1];
			rstr = ft_strjoin1(rstr, tmp->s1);
			(tmp->i)++;
			continue ;
		}
		if (str[tmp->i] == 34)
		{
			rstr = getdblcoat(envp, rstr, str, tmp);
			continue ;
		}
		if (str[tmp->i] == 39)
		{
			rstr = getsglcoat(rstr, str, tmp);
			continue ;
		}
		if (str[tmp->i] == '$')
		{
			rstr = add_vrbs(envp, rstr, tmp, str);
			continue ;
		}
		tmp->s1[0] = str[tmp->i];
		rstr = ft_strjoin1(rstr, tmp->s1);
		tmp->j++;
	}
	return (rstr);
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

int         nbr_argts2(char *command)
{
	int i;
	int cpt;

	cpt = 0;
	i = -1;
	if (!check_cmd(command))
		return (0);
	while (1)
	{
		if (command[++i] == 34)
			skip_double_coats(command, &i);
		else if (command[i] == 39)
			skip_single_coats(command, &i);
		if (command[i] == ' ' && command[i + 1] != ' ')
			cpt++;
		if (!command[i])
			break ;
	}
	cpt++;
	return (cpt);
}

void        split_command(char **envp, t_commands *commands, int nbr_args)
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
		if (commands->command[i] == '\\')
			continue ;
		if (commands->command[i] == 34 && commands->command[i - 1] != '\\')
			skip_double_coats(commands->command, &i);
		else if (commands->command[i] == 39 && commands->command[i - 1] != '\\')
			skip_single_coats(commands->command, &i);
		if ((commands->command[i] == ' ' && commands->command[i + 1] != ' ')
		|| commands->command[i + 1] == '\0')
		{
			if (!commands->type)
			{
				commands->type = my_substr(commands->command, start, i + 1);
				commands->type = deletespace(commands->type);
				commands->type = deletecoats(envp,commands->type);
			}
			else
			{
				commands->arguments[k] = my_substr(commands->command, start, i + 1);
				commands->arguments[k] = deletespace(commands->arguments[k]);
				commands->arguments[k] = deletecoats(envp, commands->arguments[k]);
				k++;
			}
			start = i + 1;
		}
		if (commands->command[i] == '\0')
			break ;  
	}
}

void        trait_command(char **envp, t_commands *commands)
{
	int i;

	i = -1;
	int nbr_args;
	nbr_args = nbr_argts(commands);
	split_command(envp,commands, nbr_args);
	//printf("%d", nbr_args);

}
int        get_commands(char **envp, t_commands *commands, char *cmds)
{
	int     i;
	int     start;
	t_commands  *tmp;

	i = -1;
	start = 0;
	tmp = commands;
	while (1)
	{
		if (cmds[++i] == '\\')
		{
			continue ;
		}
		if (cmds[++i] == 34 && cmds[i - 1] != '\\')
		{
			if ((commands->multiple = skip_double_coats(cmds, &i)))
				return (0);
		}
		else if (cmds[i] == 39 && cmds[i - 1] != '\\')
		{
			if ((commands->multiple = skip_single_coats(cmds, &i)))
				return (0);
		}
		if (cmds[i] == 59)
		{
			commands->command = my_substr(cmds, start, i);
			commands->command = deletespace(commands->command);
			g_cmds = commands->command;
			trait_command(envp, commands);
			commands->next = new_commands();
			commands = commands->next;
			start = i + 1;
		}
		else if (cmds[i] == '\0')
		{
			if (start == i)
				break ;
			commands->command = my_substr(cmds, start, i);
			commands->command = deletespace(commands->command);
			g_cmds = commands->command;
			trait_command(envp, commands);
			break ;
		}
	}

	commands = tmp;
	return (1);
}

t_commands   *parssing_shell(char **envp, char *cmds)
{
	//char *cmds = strdup("cd Desktop; env");
	t_commands   *commands, *tmp;
	commands = new_commands();
	get_commands(envp, commands, cmds);
	/*int i;
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
	commands = tmp;*/
	/*int i = -1;
	char c;
	while (commands->arguments[0][++i])
	{
		c = commands->arguments[0][i];
	}*/
	return (commands);
}