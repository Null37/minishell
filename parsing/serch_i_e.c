/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serch_i_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-bour <rel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 18:07:46 by fbouibao          #+#    #+#             */
/*   Updated: 2021/05/25 20:26:13 by rel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_hr.h"

t_tmp	*new_tmp_search(char **envp)
{
	t_tmp	*tmp;

	tmp = malloc(sizeof(t_tmp));
	tmp->i = -1;
	tmp->j = 0;
	tmp->lenp = len_of_args(envp);
	tmp->buff = ft_strdup("");
	tmp->fsf = ft_strdup(" ");
	return (tmp);
}

char	*norm_se_env(t_tmp *tmp, char **envp)
{
	tmp->j = 0;
	while (envp[tmp->i][tmp->j])
	{
		if (envp[tmp->i][tmp->j] == '=')
		{
			tmp->j += 1;
			while (envp[tmp->i][tmp->j])
			{
				tmp->fsf[0] = envp[tmp->i][tmp->j];
				tmp->buff = ft_strjoin1(tmp->buff, tmp->fsf);
				tmp->j++;
			}
			free(tmp->fsf);
			return (tmp->buff);
		}
		tmp->j++;
	}
	return (NULL);
}

char	*free_tmp2(t_tmp *tmp)
{
	char	*s;

	s = tmp->buff;
	free(tmp);
	return (s);
}

char	*search_in_env(char *variable, char **envp)
{
	t_tmp	*tmp;

	tmp = new_tmp_search(envp);
	variable = ft_strjoin1(variable, "=");
	while (++tmp->i < tmp->lenp)
	{
		if (ft_strncmp(envp[tmp->i], variable, ft_strlen(variable)) == 0)
		{
			if (norm_se_env(tmp, envp))
			{
				free(variable);
				return (free_tmp2(tmp));
			}
		}
	}
	free(variable);
	free(tmp->fsf);
	free(tmp->buff);
	free(tmp);
	return (NULL);
}

int	find_equal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (-1);
}

int	chck_sntx(char *str)
{
	int	i;
	int	q;

	q = find_equal(str);
	if (q != -1)
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
