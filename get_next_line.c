/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:49:44 by wshee             #+#    #+#             */
/*   Updated: 2024/11/22 19:03:04 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_nextline(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	//printf("%s\n", buffer);
	if (buffer[i] != '\0')
	{
		free (buffer); //Free old buffer, remove the content before \n
		return (NULL);
	}
	line = (char *)malloc((ft_strlen(buffer) - i + 1) * sizeof(char)); //allocate memory for the remaining character after \n is found
	if (line == NULL)
		return (NULL);

	i++; //skip \n
	j = 0;
	while (buffer[i] != '\0')
	{
		line[j] = buffer[i];
		i++;
		j++;
	}
	line[j] = '\0';
	free(buffer);
	return(line); //Return remaining content
}

// //extracts the first line including \n from the buffer
// //go through buffer to find \n or \0
// //allocate memory for line
// //copy line content into new string
char *ft_extractline(char *buffer)
{
	int	i;
	char *line;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n') //Find \n or \0
		i++;
	line = (char *)malloc((i + 2) * sizeof(char)); //Allocate memory for line (i+2) for \n and \0
	if (line == NULL)
		return(NULL);
	i = 0; // reset i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n') //copy the buffer to line
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n') //until find \n
	{
		line[i] = buffer[i];
		i++;//place \n at the end(1), where to put the \0(2)?
	}
	line[i] = '\0';
	return (line);
}

//join the content of buffer into a new string
char *ft_joinstring(char *newbuffer, char *buffer)
{
	char	*new;

	new = ft_strjoin(newbuffer, buffer);
	free(newbuffer);
	//newbuffer = NULL;
	return (new);
}

//read fd of buffer size until newline or \0 is found
//join two buffer using free
//stop reading if a newline is found
char *read_file(int fd, char *buffer)
{
	int		nbyte_read;
	char	*tempbuf;

	if (!buffer)//initialize buffer as an empty string
	{
		ft_strdup("");
	}
	//tempbuf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)); //Allocate buffer for buf in fd
	tempbuf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!tempbuf)
		return (NULL);
	nbyte_read = 1; //initialize bytes to run below function, contain garbage data if uninitialized
	while (!ft_strchr(tempbuf, '\n') && nbyte_read > 0)
	{
		nbyte_read = read(fd, tempbuf, BUFFER_SIZE); //return the number of bytes read
		//printf("%d\n", nbyte_read);
		if (nbyte_read == -1) //happens when the file is close or error(-1) or
		{
			free(tempbuf);
			return (NULL);
		}
		// if (nbyte_read == 0)
		// {
		// 	free(tempbuf);
		// 	//break ;
		// 	return (NULL);
		// }
		tempbuf[nbyte_read] = '\0'; //end with null teminator
		buffer = ft_joinstring(buffer, tempbuf); //overwrite buffer into new buffer after join
		// if (ft_strchr(tempbuf, '\n'))
		// 	break ;
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
	static char	*buffer;//initial state would be null
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	//printf("%s\n", buffer);
	if (!buffer)
		return (NULL);
	line = ft_extractline(buffer);
	// char	*newbuffer = ft_nextline(buffer);
	// if (newbuffer)
	// 	buffer = newbuffer;
	// else
	// 	buffer = NULL;
	buffer = ft_nextline(buffer);
	return (line);
}

//buffer is a section of memory that temperarily stores data that is being transferred from one place to another.
//static char acts as a persistent storage for unread data from the fd
//allow to resume reading from where it left off
//char is local variable with single call only, ends when the function call ends
int main(void)
{
	int		fd;
	char	*line;

	fd = open("test1.txt", O_RDONLY);
	if (fd < 0) //if there is no file, print error
	{
		printf("Error");
		return (1);
	}
	line = get_next_line(fd);//print the first line of the file end with \n
	while (line != NULL) //continue get next line until the line reach NULL (EOF)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
