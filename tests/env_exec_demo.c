// tests/exec_env_demo.c
#include <unistd.h>
#include <stdio.h>
#include "env.h"
int main(int ac, char **av, char **environ)
{
    (void)ac; (void)av; (void)environ;
    t_env *head = env_from_environ(environ);
    env_set(&head, "DEMO_KEY", "DEMO_VAL");
    char **arr = env_to_array(head);
    if (!arr) return 1;
    char *argv[] = {"/usr/bin/env", NULL};
    execve("/usr/bin/env", argv, arr);
    // 실패 시에만 여기 도달
    perror("execve");
    free_env_array(arr);
    env_free(&head);
    return 127;
}
