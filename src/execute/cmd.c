#include "../../include/minishell.h"

char **get_path(char **env)
{
    int i;
    char **all_pathname;
    char **pathname;

    i = 0;
    if (env == NULL)
    {
        return (NULL);
    }
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            all_pathname = ft_split(env[i], '=');
            if (all_pathname && all_pathname[1])
            {
                pathname = ft_split(all_pathname[1], ':');
                free_array(all_pathname);
                return (pathname);
            }
            free_array(all_pathname);
        }
        i++;
    }
    return (NULL);
}
bool cmd_exist(char **path, char *cmd, char **env)
{
    char **all_paths;
    char *tmp_path;
    int i;
    if (!cmd || !env)
        return (false);

    if (ft_strchr(cmd, '/'))
    {
        *path = ft_strdup(cmd);
        return (*path && access(*path, X_OK) == 0);
    }
    all_paths = get_path(env);
    if (!all_paths)
        return (false);
    i = 0;
    while (all_paths[i])
    {
        tmp_path = ft_strjoin(all_paths[i], "/");
        *path = ft_strjoin(tmp_path, cmd);
        free(tmp_path);

        if (*path && access(*path, X_OK) == 0)
        {
            free_array(all_paths);
            return (true);
        }
        free(*path);
        *path = NULL;
        i++;
    }
    free_array(all_paths);
    return (false);
}