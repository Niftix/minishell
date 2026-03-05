#include "minishell.h"

void sigint_handle(int sigint)
{
 (void)sigint;
 write(1, "\n", 1);
 rl_on_new_line();
 rl_replace_line("", 0);
 rl_redisplay();
}

int main(int ac, char **av, char **envp)
{
 char *input;

signal(SIGINT, sigint_handle);
while (1)
{
 input = readline("minishell > ");

 if (input == NULL || signal(SIGQUIT, 0))
   break;
  if (input[0] != '\0')
   add_history(input);
   // APPEL DU PARSING
  free(input);
}
re_clear_history();
return (0);
}