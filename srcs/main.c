#include "../libft/libft.h"
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

void	update_paths(char **argv, char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		char	*tmp;
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
		tmp = ft_strjoin(paths[i], argv[1]);
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
	(void)argc;
	//(void)argv;
	char	**paths;
	char	*true_path;

	paths = fill_paths(envp);
	update_paths(argv, paths);
	true_path = get_real_path(paths);
	printf("%s\n", true_path);
	//print_paths(paths);
	free(true_path);
	ft_split_free(paths);
	return (0);
}
