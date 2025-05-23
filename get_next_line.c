/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:05:26 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/05/23 14:43:43 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char  *get_next_line(int fd)
{
  static char buf[BUFFER_SIZE + 1];
  char        *result;
  int         bytes_read;

  if (fd < 0)
    return (NULL);
  result = NULL;
  bytes_read = 1;
  while (bytes_read)
  {
    if (!buf[0])
      bytes_read = read(fd, buf, BUFFER_SIZE);
    if (!buf[0] && (!bytes_read || bytes_read < 0))
    {
      free(result);
      return (NULL);
    }
    result = strjoin(result, buf);
    if (is_eol(result))
      break ;
    move_buffer(buf);
  }
  return (result);
}

/*
int main(int argc, char **argv)
{
  int fd;

  if (argc != 2)
    return (1);
  fd = open(argv[1], O_RDONLY);
  if (fd < 0)
    return (2);

  char  *result = get_next_line(fd);
  printf("%s", result);
  close(fd);
  return (0);
}
*/
