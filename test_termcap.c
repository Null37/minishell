#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <termcap.h>

static void en(void)
{
    char buf[1024];
    char *str;
    tgetent(buf, getenv("TERM"));
    char *ar;
    str = tgetstr("dl", NULL);
    fputs(str, stdout);
}

int main(void)
{
    en();
    // printf("Hello World!\n");
    return (0);
}