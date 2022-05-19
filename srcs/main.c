#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

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

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	int		infile;
	int		outfile;
	int		fd[2];
	pid_t	child_1;
	pid_t	child_2;

	if (argc != 5)
		return (1);

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
		perror(argv[1]);
		return (1);
	}
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
	{
		perror(argv[argc - 1]);
		return (1);
	}
	
	paths = fill_paths(envp);
	if (!paths)
	{
		printf("Env error\n");
		printf("No such file of direcroty\n");
		exit(1);
	}

	pipe(fd);
	child_1 = fork();
	if (child_1 == 0)
	{
		dup2(infile, STDIN);
		dup2(fd[1], STDOUT);
		close(fd[0]);
		close(fd[1]);
		close(infile);
		close(outfile);
		char **cmd_args = ft_split(argv[2], ' ');
		char *full_path = get_abs_cmd(paths, cmd_args[0]);
		if (!full_path)
			printf("command not found : %s\n", cmd_args[0]);
		execve(full_path, cmd_args, envp);
	}
	child_2 = fork();
	if (child_2 == 0)
	{
		dup2(outfile, STDOUT);
		dup2(fd[0], STDIN);
		close(fd[0]);
		close(fd[1]);
		close(infile);
		close(outfile);
		char **cmd_args = ft_split(argv[3], ' ');
		char *full_path = get_abs_cmd(paths, cmd_args[0]);
		if (!full_path)
			printf("command not found : %s\n", cmd_args[0]);
		execve(full_path, cmd_args, envp);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(child_1, NULL, 0);
	waitpid(child_2, NULL, 0);

	close(infile);
	close(outfile);

	// free(full_path);
	ft_split_free(paths);
	return (0);
}
