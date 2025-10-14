#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "libft.h"

/* 간단한 출력 헬퍼 */
static void print_env_list(t_env *head)
{
    t_env *cur = head;
    while (cur != NULL)
    {
        printf("%s=%s\n", cur->key, cur->value ? cur->value : "(null)");
        cur = cur->next;
    }
}

int main(int argc, char **argv, char **environ)
{
    t_env   *env;
    char    **arr;
    int     i;

    (void)argc;
    (void)argv;

    /* 1) environ으로부터 초기화 */
    env = env_from_environ(environ);
    if (env == NULL)
    {
        printf("env_from_environ failed\n");
        return (1);
    }
    printf("=== Initial PATH ===\n%s\n\n", env_get(env, "PATH"));

    /* 2) set */
    if (env_set(&env, "FOO", "BAR") == -1)
    {
        printf("env_set failed\n");
        env_free(&env);
        return (1);
    }
    printf("=== After set FOO=BAR ===\n");
    print_env_list(env);
    printf("\n");

    /* 3) overwrite */
    env_set(&env, "FOO", "BAZ");
    printf("=== After overwrite FOO=BAZ ===\n");
    print_env_list(env);
    printf("\n");

    /* 4) unset */
    env_unset(&env, "FOO");
    printf("=== After unset FOO ===\n");
    print_env_list(env);
    printf("\n");

    /* --- 추가 블록 1: 값 없는 key 테스트 --- */
    printf("=== Set EMPTY with NULL value ===\n");
    env_set(&env, "EMPTY", NULL);
    print_env_list(env);
    arr = env_to_array(env);
    if (arr)
    {
        i = 0;
        while (arr[i])
        {
            if (ft_strncmp(arr[i], "EMPTY", 5) == 0)
                printf("Found in array: %s\n", arr[i]);
            i++;
        }
        free_env_array(arr);
    }
    env_unset(&env, "EMPTY");
    printf("\n");

    /* --- 추가 블록 2: 없는 key unset --- */
    printf("=== Unset non-existing key ===\n");
    if (env_unset(&env, "NOT_EXISTS") == 1)
        printf("OK: NOT_EXISTS not found (rc=1)\n\n");
    else
        printf("Error: unexpected rc when unsetting NOT_EXISTS\n\n");

    /* 5) array 변환 */
    arr = env_to_array(env);
    if (arr == NULL)
    {
        printf("env_to_array failed\n");
        env_free(&env);
        return (1);
    }
    printf("=== env_to_array result ===\n");
    i = 0;
    while (arr[i] != NULL)
    {
        printf("%s\n", arr[i]);
        i++;
    }
    printf("\n");

    free_env_array(arr);
    env_free(&env);
    return (0);
}

