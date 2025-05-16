/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:02:12 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/05/16 15:20:09 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	is_eol(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		++i;
	}
	return (0);
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
  while (buffer && buffer[j] && buffer[j - 1] != '\n')
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
    new_string[i] = buffer[j];
    ++i;
    ++j;
  }
  new_string[i] = 0;
  free(previous);
  return (new_string);
}

char  *move_buffer(char *buffer)
{
  size_t  i;
  size_t  j;

  i = 0;
  // find '\n' position. Otherwise, find '\0'
  while (buffer[i] && buffer[i] != '\n')
    ++i;
  j = 0;
  // in case of finding '\n'
  while (buffer[i])
  {
    buffer[j] = buffer[++i];
    ++j;
  }
  // otherwise, clear buffer first position
  buffer[j] = 0;
  return (buffer);
}

// read into buffer if buffer is 'clear'

// 'clear' buffer