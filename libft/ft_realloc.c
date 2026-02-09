/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:58:26 by MP9               #+#    #+#             */
/*   Updated: 2025/12/18 19:22:05 by MP9              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

char	*ft_realloc(char *str, size_t new_size)
{
	char	*newstr;
	size_t	len;

	len = ft_strlen(str);
	newstr = (char *)malloc(sizeof(char) * new_size);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, str, len + 1);
	if (str)
		free(str);
	return (newstr);
}
