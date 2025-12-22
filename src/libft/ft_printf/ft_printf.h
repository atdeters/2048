/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josefelghnam <josefelghnam@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:03:35 by adeters           #+#    #+#             */
/*   Updated: 2025/12/22 22:57:15 by josefelghna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "../../../inc/libft.h"

int	ft_putunbr_fd(unsigned int n, int fd);
int	ft_putnbr_base_fd(long long nbr, char *base, int fd);
int	ft_putstr_fd_retbytes(char *str, int fd);
int	ft_count_bytes(int nbr);
int	ft_puthexas_fd(char code, va_list list, int fd);
int	ft_putchars_fd(char code, va_list list, int fd);
int	ft_putnumbers_fd(char code, va_list list, int fd);
int	ft_puthexaident_fd(char code, int fd);
//int	ft_printf(const char *str, ...);
//int	ft_fprintf(int fd, const char *str, ...);

#endif