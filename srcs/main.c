#include "../libft/libft.h"
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

typedef struct	s_data
{
	int		infile;
	int		outfile;
	int		fd[2];
	pid_t	child_1;
	pid_t	child_2;
	char	**paths;

}				t_data;

char	**fill_paths(char **envp)
{
	int		i;
	char	*buf;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			buf = ft_strdup(envp[i]);
			paths = ft_split(buf + 5, ':');
			free(buf);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_abs_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*abs_cmd;
	int		i;

	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		abs_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(abs_cmd, X_OK))
			return (abs_cmd);
		free(abs_cmd);
		i++;
	}
	return (NULL);
}

int	init(int argc, char **argv, char **envp, t_data *data)
{
	if (argc != 5)
	{
		printf("Usage: ./pipex <infile> <cmd1> <cdm2> <outfile>\n");
		return (0);
	}
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
	{
		perror(argv[1]);
		return (0);
	}
	data->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->infile == -1)
	{
		perror(argv[argc - 1]);
		return (0);
	}
	data->paths = fill_paths(envp);
	if (!data->paths)
	{
		printf("%s: command not found\n", argv[2]);
		return (0);
	}
	return (1);
}

void	process_child_1(char **argv, char **envp, t_data data)
{
	char	**cmd_args;
	char	*full_path;

	cmd_args = ft_split(argv[2], ' ');
	full_path = get_abs_cmd(data.paths, cmd_args[0]);
	if (!full_path)
	{
		printf("%s : command not found\n", cmd_args[0]);
		ft_split_free(cmd_args);
		exit(127);
	}
	dup2(data.infile, STDIN);
	dup2(data.fd[1], STDOUT);
	close(data.fd[0]);
	close(data.fd[1]);
	close(data.infile);
	close(data.outfile);
	execve(full_path, cmd_args, envp);
}

void	process_child_2(char **argv, char **envp, t_data data)
{
	char	**cmd_args;
	char	*full_path;

	cmd_args = ft_split(argv[3], ' ');
	full_path = get_abs_cmd(data.paths, cmd_args[0]);
	if (!full_path)
	{
		printf("%s : command not found\n", cmd_args[0]);
		ft_split_free(cmd_args);
		exit(127);
	}
	dup2(data.outfile, STDOUT);
	dup2(data.fd[0], STDIN);
	close(data.fd[0]);
	close(data.fd[1]);
	close(data.infile);
	close(data.outfile);
	execve(full_path, cmd_args, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (!init(argc, argv, envp, &data))
		return (1);
	pipe(data.fd);
	data.child_1 = fork();
	if (data.child_1 == 0)
		process_child_1(argv, envp, data);
	else if (data.child_1 == -1)
		ft_error(strerror(errno));
	data.child_2 = fork();
	if (data.child_2 == 0)
		process_child_2(argv, envp, data);
	else if (data.child_1 == -1)
		ft_error(strerror(errno));
	close(data.fd[0]);
	close(data.fd[1]);
	waitpid(data.child_1, NULL, 0);
	waitpid(data.child_2, NULL, 0);
	close(data.infile);
	close(data.outfile);
	ft_split_free(data.paths);
	return (0);
}
