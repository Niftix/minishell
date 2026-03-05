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
  t_shell shell;
  char *input;

  shell_init(&shell, &envp);
  signal(SIGINT, sigint_handle);
while (shell.run)
{
 input = readline("minishell > ");
 if (input == NULL)
  shell.run = 0;
 if (input[0] != '\0')
   add_history(input);
   // APPEL DU PARSING
  free(input);
}
re_clear_history();
return (0);
}
