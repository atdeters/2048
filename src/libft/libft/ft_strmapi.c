/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josefelghnam <josefelghnam@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:08:58 by adeters           #+#    #+#             */
/*   Updated: 2025/12/22 22:57:14 by josefelghna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*ptr;
	int			i;
	int			len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)s);
	ptr = malloc(len + 1);
	if (ptr == 0)
		return (0);
	while (i < len)
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return ((char *)ptr);
}
/*
char	test_func(unsigned int i, char c)
{
	c = c + (i % 2);
	return (c);
}

#include <stdio.h>

int	main(void)
{
	char *s = "Hello World!";
	printf("%s\n", ft_strmapi(s, test_func));
}*/
