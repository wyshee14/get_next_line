/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:24:16 by wshee             #+#    #+#             */
/*   Updated: 2024/11/22 16:39:37 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// {
// 	size_t	i;
// 	size_t	dst_len;
// 	size_t	src_len;

// 	dst_len = strlen(dst);
// 	src_len = strlen(src);
// 	i = 0;
// 	if (dst_len >= size)
// 		dst_len = size;
// 	if (dst_len < size - 1 && size > 0)
// 	{
// 		while (dst_len + i < size - 1 && src[i] != '\0')
// 		{
// 			dst[dst_len + i] = src[i];
// 			i++;
// 		}
// 		dst[dst_len + i] = 0;
// 	}

// 	return (dst_len + src_len);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*strjoin;
// 	size_t	len1;
// 	size_t	len2;
// 	size_t	i;
// 	size_t	j;

// 	len1 = strlen(s1);
// 	len2 = strlen(s2);
// 	i = 0;
// 	if (s1 == (NULL) || s2 == (NULL))
// 		return (NULL);
// 	strjoin = (char *)malloc((len1 + len2 + 1) * sizeof(char));
// 	if (strjoin == (NULL))
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		strjoin[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 		strjoin[i++] = s2[j++];
// 	strjoin[i] = '\0';
// 	return (strjoin);
// }

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	int i = 0;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (nmemb > 4294967295 / size)
		return (NULL);
	ptr = (void *)malloc (nmemb * size);
	if (ptr == NULL)
		return (NULL);
	int n = nmemb * size;
	while (n > 0)
	{
		ptr[i] = 0;
		n--;
		i++;
	}
	return (ptr);
}

int main(void)
{
	char *ptr;
	ptr = ft_calloc(1, 1);
	if (ptr == NULL)
	{
		printf("Failed! %zu\n", (size_t)-1);
	}
	else
	{
		printf("Successful\n");
		printf("%s\n", ptr);
		free(ptr);
	}
}

// int main(void)
// {
// 	char *s1 = NULL;
// 	char *s2 = "World";
// 	char *res = ft_strjoin(s1,s2);
// 	printf("%s\n", res);
// }
