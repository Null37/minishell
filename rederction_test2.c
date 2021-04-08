#include "minishell_hr.h"

int valid_rdr(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ';')
		return (-1);
	return (0);
}

int	check_rdr(char *s, int i)
{
	if (s[i] == '>' && s[i + 1] == '>')
		return (2);
	else if (s[i] == '>')
		return (1);
	else if (s[i] == '<')
		return (0);
	return (1);
}

int valid_type(char c0, char c1,char c2)
{
	
	if (c1 == '>' && c2 == '<')
	{
		// printf("bash: syntax error near unexpected token `%c'", c1);
		write(2, "minishell: syntax error near unexpected token ", 46);
		write(2, "`", 1);
		write(2, &c1, 1);
		write(2, "'", 1);
		write(2, "\n", 1);
	}
	else if ((c1 == '>' || c1 == '<')
	&& (c2 == '>' || c2 == '<'))
		{
			//printf("bash: syntax error near unexpected token `%c%c'", c1,c2);
			write(2, "minishell: syntax error near unexpected token ", 46);
			write(2, "`", 1);
			write(2, &c1, 1);
			write(2, &c2, 1);
			write(2, "'", 1);
			write(2, "\n", 1);
		}
	else if (c0 == ';' && c1 == ';')
		{
			//printf("bash: syntax error near unexpected token `%c%c'", c1,c2);
			write(2, "minishell: syntax error near unexpected token ", 46);
			write(2, "`", 1);
			write(2, &c0, 1);
			write(2, &c1, 1);
			write(2, "'", 1);
			write(2, "\n", 1);
			
		}
		else if (c1 == '|' && c2 == '|')
		{
			//printf("bash: syntax error near unexpected token `%c%c'", c1,c2);
			write(2, "minishell: syntax error near unexpected token ", 46);
			write(2, "`", 1);
			write(2, &c1, 1);
			write(2, &c2, 1);
			write(2, "'", 1);
			write(2, "\n", 1);
			
		}
		else
		{
			//printf("bash: syntax error near unexpected token `%c'", c1);
			write(2, "minishell: syntax error near unexpected token ", 46);
			write(2, "`", 1);
			write(2, &c1, 1);
			write(2, "'", 1);
			write(2, "\n", 1);
		}
		return(-1);
}

int check_fname(int r, char *s, int i)
{
	int b;
	b = 1;
	if (r == 2)
		i++;
	while (s[++i])
	{
		if (s[i] == ' ')
			continue ;
		else if (s[i] == 34)
		{
			if(skip_double_coats(s, &i) == 1)
			{
				b = 0;
				return -6;
			}
			return i;
		}
		else if (s[i] == 39)
		{
			if(skip_single_coats(s, &i) == 1)
			{
				b = 0;
				return -6;
			}
			return i;
		}
		else if (s[i] != '|' &&  s[i] != '>' && s[i] != ';' && s[i] != '<')
			return i;
		else if (valid_rdr(s[i]) == -1)
		{
			if (valid_type(s[i - 1], s[i], s[i + 1]) == -1)
			{
				b = 0;
				return -1;
			}
		}
	}
	if(!b)
	{
		// printf("bash: syntax error near unexpected token `newline'");
		write(2, "minishell: syntax error near unexpected token `newline'", 54);
		write(2, "\n", 1);
		return (-1);
	}
	return 0;
}

int check_pipp_sy(char *s)
{
	int  i =-1;
	while (s[++i])
	{
		if(s[i] == 32)
			continue;
		else if((s[i] == '|' && s[i + 1] != '|')|| (s[i] == ';' && s[i + 1] != ';'))
		{
			write(2, "minishell: syntax error near unexpected token ", 46);
			write(2, "`", 1);
			write(2, &s[i], 1);
			write(2, "'", 1);
			write(2, "\n", 1);
			//printf("bash: syntax error near unexpected token `%c'\n", s[i]);
			return -1;
		}
		else
			break;
	}
	return 0;
}

int  check_syntax_rederction(char *av)
{
	int i = -1;
	int j = 0;
	int h = 0;
	int li = 0;
	int right = 0;
	int ch = 0;
	i = 0 ;
	
	int r;
	i = -1;
	if(check_pipp_sy(av) == -1)
		return -1;
	while (av[++i])
	{
		if (av[i] == 34)
		{
			if(skip_double_coats(av, &i) == 1)
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				return -1;
			}
			return i;
		}
		else if (av[i] == 39)
		{
			if(skip_single_coats(av, &i) == 1)
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				return -1;
			}
			return i;
		}
		if (av[i] == '>' || av[i] == '<')
		{
			r = check_rdr(av, i);
			if ((i = check_fname(r, av, i))== -1)
				return -1;
			else if(i == -6)
			{
				// printf("not in subject");
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				return -1;
			}
		}
		else if (av[i] == '|')
		{
			if ((i = check_fname(0, av, i))== -1)
				return -1;
			else if(i == -6)
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				return -1;
			}
		}
		else if (av[i] == ';')
		{
			if ((i = check_fname(0, av, i))== -1)
				return -1;
			else if(i == -6)
			{
				write(2, "minishell: not in subject", 25);
				write(2, "\n", 1);
				return -1;
			}
		}

	}
	return (0);
}

// int main(int argc, char *av[])
// {
// 	int g = check_syntax_rederction(av[1]);
// 	// if(g == -3)
// 	// 	printf("bash: syntax error near unexpected token `>'");
// 	// else if (g == 2)
// 	// 	printf("bash: syntax error near unexpected token `newline'");
// 	// else if(g == -4)
// 	// 	printf("bash: syntax error near unexpected token `<'");
// 	// else if(g == -5)
// 	// 	printf("bash: syntax error near unexpected token `>>'");
// 	if(g == -1)
// 		printf("false");
// 	else if(g == 0)
// 		printf("TRUE");
	
// }