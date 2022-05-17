#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

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

void	update_paths(char *arg, char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		char	*tmp;
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
		tmp = ft_strjoin(paths[i], arg);
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}	
}

char	*get_real_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (!access(paths[i], X_OK))
			return (ft_strdup(paths[i]));
		i++;
	}	
	return (NULL);
}

void	print_paths(char **paths)
{
	int	i;
	
	i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	p1;
	pid_t	p2;
	int	infile;
	int	outfile;
	int	fd[2];
	char	**args;
	char	**paths;
	char	*true_path;

	if (argc != 5)
		return (1);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_WRONLY, O_CREAT | O_CREAT, 0644);
	pipe(fd);
	p1 = fork();
	if (p1 == 0)
	{
		dup2(fd[1], STDOUT);
		dup2(infile, STDIN);
		paths = fill_paths(envp);
		update_paths(argv[2], paths);
		args = ft_split(argv[2], ' ');
		true_path = get_real_path(paths);
		close(fd[0]);
		close(fd[1]);
		close(infile);
		execve(true_path, args, envp);
		free(true_path);
		ft_split_free(paths);
		ft_split_free(args);
	}
	p2 = fork();
	if (p2 == 0)
	{
		dup2(fd[0], STDIN);
		dup2(outfile, STDOUT);
		paths = fill_paths(envp);
		update_paths(argv[3], paths);
		args = ft_split(argv[3], ' ');
		true_path = get_real_path(paths);
		close(fd[0]);
		close(fd[1]);
		close(outfile);
		execve(true_path, args, envp);
		free(true_path);
		ft_split_free(paths);
		ft_split_free(args);
	}
	close(fd[0]);
	close(fd[1]);
	close(infile);
	close(outfile);
	waitpid(p1, NULL, 0);
	waitpid(p2, NULL, 0);
	return (0);
}
