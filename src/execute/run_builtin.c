#include "../../include/minishell.h"

static void	exec_builtin(int save_stdout, t_data *data, t_command *commands)
{
	if (!ft_strncmp("echo", commands->command_param[0], INT_MAX))
		data->exit_code = ft_echo(commands->command_param);
	else if (!ft_strncmp("cd", commands->command_param[0], INT_MAX))
		data->exit_code = ft_cd(data, commands->command_param);
	else if (!ft_strncmp("pwd", commands->command_param[0], INT_MAX))
		data->exit_code = ft_pwd();
	else if (!ft_strncmp("export", commands->command_param[0], INT_MAX))
		data->exit_code = ft_export(commands->command_param, &data->env);
	else if (!ft_strncmp("unset", commands->command_param[0], INT_MAX))
		data->exit_code = ft_unset(commands->command_param, &data->env);
	else if (!ft_strncmp("env", commands->command_param[0], INT_MAX))
		data->exit_code = ft_env(data->env);
	else if (!ft_strncmp("exit", commands->command_param[0], INT_MAX))
	{
		if (commands->outfile >= 0)
		{
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		ft_exit(data, commands->command_param);
	}
}
bool run_builtin(t_data *data, t_command *commands)
{
    int save_stdout;

    save_stdout = -1;
    if (commands->outfile >= 0)
    {
        save_stdout = dup(STDOUT_FILENO);  // Sauvegarde de l'ancienne sortie
        if (dup2(commands->outfile, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            data->exit_code = 1;
            return false;
        }
    }
    exec_builtin(save_stdout, data, commands);
    if (commands->outfile >= 0)
    {
        dup2(save_stdout, STDOUT_FILENO);  // Restauration de la sortie standard
        close(save_stdout);  // Fermeture de l'ancien descripteur de fichier
    }
    return true;
}