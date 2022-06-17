# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/_types.h>
# include <sys/syslimits.h>
# include <readline/history.h>
# include <readline/readline.h>

int    main(void)
{
    char    *line;
    char    **cmd;
    int        i;
    line =NULL;

    while (1)
    {
        line = readline("\x1b[35m" "machi Minishell (◕‿◕)  " "\x1b[m");
            add_history(line);
            free(line);
            line = NULL;
    }
}