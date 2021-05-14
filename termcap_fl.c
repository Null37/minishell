#include "minishell_hr.h"

char    *ft_strjoinchar(char *s, char c)
{
	int        i;
	char    *str;
	i = 0;
	if(s == NULL)
	{
		if (!(str = (char *)malloc(2)))
			return (0);
		str[0] = c;
		str[1] = '\0';
		return (str);
	}
	while (s[i])
		i++;
	if (!(str = (char *)malloc(i + 2)))
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	// free(s);
	return (str);
}
int ft_putc(int s)
{
	return write(1,&s,1);
}
int             get_char()
{
		char    c;
		int		total;
		struct termios old;
		struct	termios term; //, init; //init made to reset to default
		tcgetattr(0, &old); //get terminal attributes and store them in in the struct
		term = old;
		// tcgetattr(0, &init); //set terminal attributes in the struct
		term.c_lflag &= ~(ICANON|ECHO); //Set to Non Canonical, Reads instantly without waiting for "ENTER" key, Maximum length is 4096
		//term.c_lflag &= ~(ECHO);  // Stops the keys read from printing in terminal
		term.c_cc[VMIN] = 0;  // VMIN   Minimum number of characters for noncanonical read (MIN).
		term.c_cc[VTIME] = 0;  //VTIME Timeout in deciseconds for noncanonical read (TIME).
		tcsetattr(0, TCSANOW, &term); //Set Atrributes of termios (Update Changes)
		total = 0;
		while (read(0, &c, 1) <= 0);
		total += c;
		while (read(0, &c, 1) > 0)
				total += c;
		tcsetattr(0, TCSANOW, &old);
		return (total);
}

char *termcap_khedma(t_history *history)
{

	int		d;
	char	*s;
	t_history *h_tmp;

	static int i;

	while(1)
	{
		if (history->next == NULL)
			break ;
		history = history->next;
	}


	h_tmp = history;
	g_all->line = NULL;
	g_all->ret = NULL;
	//g_all->ret[0] = '\0';
	while(1)
	{
		d = get_char();
		if (d == 4)
		{
			if (g_all->ret ==  NULL)
			{
				write(1,"exit",4);
				exit(0);
			}
		}
		else if (d >= 32 && d < 127)
		{
			g_all->ret = ft_strjoinchar(g_all->ret, d);
			free(g_all->line);
			g_all->line = ft_strdup(g_all->ret);
			write(1, &d ,1);
		}
		else if (d == KEY_REMOVE)//delete
		{
			int i;

			i = 0;
			if (ft_strlen(g_all->ret) > 0)
			{
				while (i < (ft_strlen(g_all->ret) - 1))
					i++;
				g_all->ret[i] = '\0';
				tputs(tgetstr("le",NULL), 1, ft_putc);
				// tputs(tgetstr("dm",NULL), 1, ft_putc);
				tputs(tgetstr("dc",NULL), 1, ft_putc);
				// tputs(tgetstr("ed",NULL), 1, ft_putc);
			}
		}
		else if (d == KEY_DOWN)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
			tputs(tgetstr("dl",NULL), 1, ft_putc);
			// print_prompt1();
			// if (tmp)
			// {
	
			// 	write(1, tmp->data, strlen(tmp->data));
			// 	if (tmp->prev != NULL)
			// 		tmp = tmp->prev;
			// 	g_all->ret = tmp->data;
			// }

			if (h_tmp && h_tmp->next)
			{
				h_tmp = h_tmp->next;
				write(1, "\033[0;33mNull37$\033[0m ", 19);
				write(1, h_tmp->cmd, ft_strlen(h_tmp->cmd));
				free(g_all->ret);
				g_all->ret = ft_strdup(h_tmp->cmd);
			}
			else
			{
				free(g_all->ret);
				if (g_all->line)
				{
					g_all->ret = ft_strdup(g_all->line);
				}
				else
				{
					g_all->ret = ft_strdup("");
				}
				write(1, "\033[0;33mNull37$\033[0m ", 19);
				write(1, g_all->ret, ft_strlen(g_all->ret));
			}

		// 	// else
		// 	// 	g_all->ret[0] = 0;
		// 	// s = tgoto(tgetstr("ch", NULL), 0 ,0);
		// 	// write(1, s, strlen(s)); 
		// 	// s = tgetstr("dl", NULL); //Get the string entry id 'ce' means clear from the cursor to the end of the current line.
		// 	// write(1, s, strlen(s)); // execute the string entry id
		}
		else if (d == KEY_UP)
		{
			if (history->cmd == NULL && g_all->line && !h_tmp->preview)
			{
				continue ;
			}
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
			tputs(tgetstr("dl",NULL), 1, ft_putc);

			if (h_tmp && h_tmp->preview)
			{
				write(1, "\033[0;33mNull37$\033[0m ", 19);
				write(1, h_tmp->cmd, ft_strlen(h_tmp->cmd));
				free(g_all->ret);
				g_all->ret = ft_strdup(h_tmp->cmd);
				h_tmp = h_tmp->preview;
			}
			else if (!h_tmp->preview)
			{
				write(1, "\033[0;33mNull37$\033[0m ", 19);
				if (h_tmp->cmd)
				{
					write(1, h_tmp->cmd, ft_strlen(h_tmp->cmd));
					free(g_all->ret);
					g_all->ret = ft_strdup(h_tmp->cmd);
				}
			}

			// print_prompt1(); // hna
			// if (tmp)
			// {
			// 	// fprintf(stderr, "%s", tmp->next);

			// 	write(1, tmp->data, strlen(tmp->data));
			// 	if(tmp->next != NULL)
			// 		tmp = tmp->next;
			// 	g_all->ret = tmp->data;
			// }
			// if (tmp)
			// 	{
			// 		if (!tmp->prev && !help)
			// 		{
			// 			g_all->ret = (char*)tmp->data;
			// 			help = 1;
			// 		}
			// 		else
			// 		{
			// 			if(tmp->next)
			// 				tmp = tmp->next;
			// 			g_all->ret = (char*)tmp->data;		
			// 		}
			// 		write(1, tmp->data, strlen(tmp->data));
			// 	}
			// else 
			// {
			// 	g_all->ret[0] = 0;
			// }
			// t_stack *tmp;
			// tmp = head;
			// while (tmp)
			// {
			// 	printf("%s\n", (char*)tmp->data);
			// 	tmp = tmp->next;
			// }
		}
		else if (d == ENTER)
		{
			// tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
			// tputs(tgetstr("dl",NULL), 1, ft_putc);
			free(g_all->line);
			g_all->line = NULL;
			write(1,"\n",1);
			if(g_all->ret == NULL)
			{
				write(1, "\033[0;33mNull37$\033[0m ", 19);
			}
			// s = tgetstr("ch", NULL);
			// write(1, s, strlen(s)); 
			// s = tgetstr("dl", NULL); //Get the string entry id 'ce' means clear from the cursor to the end of the current line.
			// write(1, s, strlen(s)); // execute the string entry id
				// fprintf(stderr, "Else made it here");
			if (g_all->ret != NULL)
			{
			// 	// head->data = g_all->ret;
			// 	// head->next = (t_stack *) malloc(sizeof(t_stack));
			// 	// head->next->next = NULL;
			// 	// head->next->prev = head;
			// 	// head = head->next;
			// 	// tmp = head;
			// 	// lstadd_dlist(&head, lstnewc(g_all->ret)); //hna
			// 	// fprintf(stderr, "%s", tmp);
			// 	// tmp = head;//hna
			// 	// printf("%s\n",tmp->data);
			if (history->cmd == NULL)
			{
				history->cmd = ft_strdup(g_all->ret);
			}
			else
			{
				h_tmp = history;
				history->next = new_commnd(g_all->ret);
				history = history->next;
				history->preview = h_tmp;
			}
			return (g_all->ret);
			}

		// 	// if (help == 0)
		// 		ret = "";
		// 	// tmp = head->next;
		// 	// tmp->prev = head;
		// 	// tmp->next = NULL;
		// 	// head = head->next;
			continue ;
		}
	}
}