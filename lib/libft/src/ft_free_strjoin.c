/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:07:50 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/09 15:27:57 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_free_strjoin(char *s1, char *s2, int critical)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2, critical);
	if (!new_str)
	{
		wfree(s1);
		return (NULL);
	}
	wfree(s1);
	return (new_str);
}
