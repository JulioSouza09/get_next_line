/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:05:26 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/05/14 13:05:29 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include "libft.h"

int is_eol(char *str)
{
  int i;

  i = 0;
  while (str[i])
  {
    if (str[i] == '\n') 
      return (++i);
    ++i;
  }
  return (0);
}

char  *ft_realloc(char *dst, size_t size, size_t nb_el)
{
  char    *result;
  size_t  i;
  size_t  len;

  if (!dst)
    return (malloc(size * nb_el));
  len = nb_el + ft_strlen(dst);
  result = malloc(size * (len));
  if (!result)
    return (NULL);
  i = 0;
  while (dst[i])
  {
    result[i] = dst[i];
    i++;
  }
  result[i] = 0;
  free(dst);
  return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned long	lens;
	char			*arr;
	int				i;

	lens = ft_strlen(s1) + ft_strlen(s2) + 1;
	arr = malloc(sizeof(char) * lens);
	if (!arr)
		return (NULL);
	i = 0;
	while (*s1)
	{
		arr[i] = *s1;
		++i;
		++s1;
	}
	while (*s2)
	{
		arr[i] = *s2;
		++s2;
		++i;
	}
	arr[i] = '\0';
	return (arr);
}

void  fill_arr(char **dst, char *buffer, int size)
{
    char  *sub_str;

    *dst = ft_realloc(*dst, sizeof(char), size);
    sub_str = ft_strdup(buffer);
    *dst = ft_strjoin(*dst, sub_str);
}


char  *get_next_line(int fd)
{
  static char buf[BUFFER_SIZE + 1];
  char        *result;
  int         bytes_read;
  int         n;

  result = NULL;
  bytes_read = 1;
  while (bytes_read)
  {
    if (!buf[0])
    {
      bytes_read = read(fd, buf, BUFFER_SIZE);
      if (!bytes_read)
        break ;
    }
    else 
    {
      fill_arr(&result, buf, BUFFER_SIZE + 1);
      buf[0] = 0;
    }
    if (bytes_read == 0 || bytes_read < 0)
      return (NULL);
    n = is_eol(buf);
    if (n)
    {
      fill_arr(&result, ft_substr(buf, n - 1, n), n);
      ft_memmove(buf, &buf[n], BUFFER_SIZE - n);
      buf[BUFFER_SIZE - n] = 0;
      break ;
    }
  }
  return (result);
}

// get line len until '\n' previous allocated space + buffer
size_t  get_len(char *previous, char *buffer)
{
  size_t  i;
  size_t  j;

  i = 0;
  // previous buffer content len
  while (previous && previous[i])
    ++i;
  j = 0;
  // buffer len until '\0' or '\n'
  while (buffer && buffer[i] && buffer[i - 1] != '\n')
    ++j;
  return (i + j);
}

// allocate space with buffer len
char  *strjoin(char *previous, char *buffer)
{
  size_t  len;
  size_t  i;
  size_t  j;
  char    *new_string;

  len = get_len(previous, buffer);
  new_string = malloc(sizeof(char) * (len + 1));
  if (!new_string)
    return (NULL);
  i = 0;
  // copy previous string to new string
  while (previous && previous[i])
  {
    new_string[i] = previous[i]; 
    ++i;
  }
  j = 0;
  // copy buffer into allocated space
  while (i < len)
  {
    new_string[i] = buffer[0];
    ++i;
    ++j;
  }
  new_string[i] = 0;
  free(previous);
  return (new_string);
}

char  *move_buffer(char *buffer, size_t size)
{
  size_t  i;
  size_t  j;

  i = 0;
  while (buffer[i] && buffer[i] != '\n')
    ++i;
  j = 0;
  while (buffer[i])
  {
    buffer[j] = buffer[i];
    ++i;
    ++j;
  }
  buffer[j] = 0;
  return (buffer);
}

// read into buffer if buffer is 'clear'
// 'clear' buffer

/*
int main(int argc, char **argv)
{
  int fd;

  if (argc != 2)
    return (1);
  fd = open(argv[1], O_RDONLY);
  if (fd < 0)
    return (2);
  printf("%s", get_next_line(fd));
  printf("%s", get_next_line(fd));
  printf("%s", get_next_line(fd));
  printf("%s", get_next_line(fd));
  close(fd);
  return (0);
}
*/
