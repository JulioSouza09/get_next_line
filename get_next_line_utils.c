/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:02:12 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/05/14 14:02:13 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*arr;

	if (!len || !*s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		arr[i] = s[start + i];
		++i;
	}
	arr[i] = 0;
	return (arr);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_b;
	unsigned char	*src_b;
	size_t			i;

	dest_b = (unsigned char *)dest;
	src_b = (unsigned char *)src;
	if (n == 0)
		return (dest);
	if (dest > src)
	{
		i = n;
		while (i-- > 0)
			dest_b[i] = src_b[i];
		return (dest);
	}
  i = 0;
	while (i < n)
	{
		dest_b[i] = src_b[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (dst_len >= size)
		return (src_len + size);
	i = 0;
	while (src[i] && (size - dst_len - 1) > i)
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (dst_len + src_len);
}

char	*ft_strdup(const char *s)
{
	long	len;
	char	*arr;

	len = ft_strlen(s) + 1;
	arr = malloc(sizeof(char) * len);
	if (arr == NULL)
		return (NULL);
	while (len--)
		arr[len] = s[len];
	return (arr);
}

