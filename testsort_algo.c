#include "minishell_hr.h"


char **sort_algo(char **sortest)
{
	int  i;
	int j;
	char *tmp;

	i = 0;
	j= 0;
	while(sortest[j] != NULL)
	{
		i = 0;
		while (sortest[i] != NULL)
		{
			if(strcmp(sortest[i],sortest[j]) > 0)
			{
				tmp = sortest[i];
				sortest[i] = NULL;
				sortest[i] = sortest[j];
				sortest[j] = NULL;
				sortest[j] = tmp;
			}
			i++;
		}
		
		j++;
	}
	return (sortest);
}

int main()
{
	char *sortest[10] = {"acbc", "afd", "adde", "abfg", "abhj", "ahrf", "aNaLL"};
	char **test;
	test = sort_algo(sortest);
	for (int i = 0; test[i] != NULL; i++)
	{
		printf("%s\n", test[i]);
	}
}