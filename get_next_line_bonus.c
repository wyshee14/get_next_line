/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:28:42 by wshee             #+#    #+#             */
/*   Updated: 2024/11/25 15:04:58 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//get the line inside buffer after the new line
//Free old buffer, remove the content before \n
//allocate memory for the remaining character after \n is found
//Return remaining content
char	*next_line(char *buffer)
{
	char	*line;
	int		i;

	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	line = ft_substr(buffer, i + 1, ft_strlen(buffer) - i);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	free (buffer);
	return (line);
}

//extracts the first line including \n from the buffer
//go through buffer to find \n or \0
//allocate memory for line
//(i + 1) to include the new line
//copy line content into new string
char	*make_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

//join the content of buffer into a new string
//free the old buffer to prevent overwrite buffer
char	*ft_join(char *oldbuffer, char *tempbuf)
{
	char	*new;

	new = ft_strjoin(oldbuffer, tempbuf);
	free(oldbuffer);
	return (new);
}

//initialize buffer as an empty string
//initialize bytes to run below function, contain garbage data if uninitialized
//read fd of buffer size until newline or \0 is found
//byte_read -1 happens when the file is close or error(-1) or
//read return the number of bytes read
//join two buffer using join
//stop reading if a newline is found
char	*read_file(int fd, char *buffer)
{
	char	*tempbuf;
	int		byte_read;

	if (buffer == NULL)
		buffer = ft_calloc(1, 1);
	tempbuf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (tempbuf == NULL)
		return (NULL);
	tempbuf[0] = 0;
	byte_read = 1;
	while (!ft_strchr(tempbuf, '\n') && byte_read > 0)
	{
		byte_read = read(fd, tempbuf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(tempbuf);
			return (NULL);
		}
		tempbuf[byte_read] = '\0';
		buffer = ft_join(buffer, tempbuf);
	}
	free(tempbuf);
	return (buffer);
}

//check fd is valid, handle errors
//read and update buffer
//free buffer after line is read
//extract the line end with new line
//remove processed line, keep unread content
//return extracted line
char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = make_line(buffer[fd]);
	buffer[fd] = next_line(buffer[fd]);
	return (line);
}

//run command ulimit -n will get the soft limit
//can be cahnged anytime for non-root user in the
//range of [0-hard limit], to disable core dumps
//buffer array can read up to 1024 files
// run command ulimit -Hn will get hard limit
//can only be raised by root(for security)

// # include <stdio.h>
// # include <unistd.h>
// # include <fcntl.h>

// int main(void)
// {
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	int		i;
// 	char	*res1;
// 	char	*res2;
// 	char	*res3;

// 	fd1 = open("test1.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	fd3 = open("test3.txt", O_RDONLY);
// 	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
// 	{
// 		printf("Error\n");
// 		return (1);
// 	}
// 	res1 = get_next_line(fd1);
// 	res2 = get_next_line(fd2);
// 	res3 = get_next_line(fd3);
// 	i = 0;
// 	while ((res1 != NULL || res2 != NULL || res3 != NULL) && i < 7)
// 	{
// 		printf("test1[line %d]: %s", i, res1);
// 		printf("test2[line %d]: %s", i, res2);
// 		printf("test3[line %d]: %s", i, res3);
// 		free(res1);
// 		free(res2);
// 		free(res3);
// 		res1 = get_next_line(fd1);
// 		res2 = get_next_line(fd2);
// 		res3 = get_next_line(fd3);
// 		printf("\n");
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
