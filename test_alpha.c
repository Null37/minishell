#include "minishell_hr.h"

int main(int argc, char*av[])
{
    int a =  ft_isalpha(av[1][0]);
    printf("|%d|\n", a);
    return 1;
}