/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:36:48 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/23 19:13:34 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (src[i])
	{
		i++;
	}
	if (dstsize == 0)
		return (i);
	while (j < dstsize - 1 && src[j])
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (i);
}

char	*ft_strnstr(const char *d, const char *s, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	dst = (char *)d;
	if (!s[i] || dst == s)
		return ((char *)dst);
	while (dst[i] && len > i)
	{
		j = 0;
		while (s[j] && i + j < len && dst[i + j] == s[j])
		{
			if (s[j + 1] == '\0')
				return (dst + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	i1;

	if (dstsize <= strlen(dst))
		return (dstsize + strlen(src));
	i = strlen(dst);
	i1 = 0;
	while (src[i1] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i1];
		i++;
		i1++;
	}
	dst[i] = '\0';
	return (strlen(dst) + strlen(&src[i1]));
}

static	long int	ft_len(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n = n * -1 ;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*b;
	long		l;

	l = n;
	len = ft_len(l);
	b = (char *)malloc((len + 1) * sizeof(char));
	if (!b)
		return (NULL);
	b[len--] = '\0';
	if (l == 0)
		b[0] = '0';
	if (l < 0)
	{
		b[0] = '-';
		l = l * -1;
	}
	while (l > 0)
	{
		b[len--] = (l % 10) + 48;
		l = l / 10;
	}
	return (b);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s1;
	unsigned int	b;
	size_t			l;

	l = 0;
	if (!s)
		return (NULL);
	if (len > strlen(s + start))
	{
		l = strlen(s + start);
		len = l;
	}
	b = 0;
	s1 = (char *)malloc((len + 1) * sizeof(char));
	if (!s1)
		return (NULL);
	while (b < len && start < strlen(s))
	{
		s1[b] = s[start];
		b++;
		start++;
	}
	s1[b] = '\0';
	return (s1);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	int		b;
	int		c;

	if (!s1 || !s2)
		return (NULL);
	b = strlen(s1);
	c = strlen(s2);
	a = (char *)malloc((b + c + 1) * sizeof(char));
	if (!a)
		return (NULL);
	ft_strlcpy(a, s1, b + 1);
	ft_strlcat(&a[strlen(a)], s2, c + 1);
	return (a);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	j;

	j = 0;
	if (!s1)
		return (NULL);
	while (*s1 && (strchr(set,*s1)))
		s1++;
	j = strlen(s1);
	while (*s1 && (strchr(set, s1[j])))
	{
		j--;
	}
	return (ft_substr(s1, 0, j + 1));
}

static size_t	ft_count(char const *s, char c)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] != c)
			w++;
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (w);
}

static char	*ft_mem_word(char const *s, char c)
{
	size_t		i;
	char	*tab;

	i = 0;
	tab = 0;
	while (s[i] && s[i] != c)
		i++;
	tab = (char *)malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s, i + 1);
	return (tab);
}

static char	**ft_free( char **tab, int i)
{
	while (i > 0)
		free(tab[i--]);
	free(tab);
	return (NULL);
}

static char	**ft_rir_norm(char const *s, char c)
{
	int		i;
	int		words;
	char	**tab;

	i = 0;
	words = ft_count(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	while (i < words)
	{
		while (s[0] == c)
			s++;
		tab[i] = ft_mem_word(s, c);
		if (!tab)
		{
			return (ft_free(tab, i));
		}
		s += strlen(tab[i]);
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_rir_norm(s, c));
}