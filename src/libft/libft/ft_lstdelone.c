/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josefelghnam <josefelghnam@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:25:40 by adeters           #+#    #+#             */
/*   Updated: 2025/12/22 22:57:14 by josefelghna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != 0)
	{
		del(lst->content);
		free(lst);
	}
}
/*
void	del_tlist_node(void *content)
{
	free(content);
}

#include <stdio.h>

int	main(void)
{
	char *test = (char *)malloc(12 * sizeof(char));
	int size = ft_strlcpy(test, "Hello World", 12);
	t_list *hello = ft_lstnew(test);
	printf("%s\n", (char *)hello->content);
	ft_lstdelone(hello, del_tlist_node);
} */