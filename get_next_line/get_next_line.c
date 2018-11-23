/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarrieu <jlarrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 21:32:12 by jlarrieu          #+#    #+#             */
/*   Updated: 2018/11/23 07:36:16 by jlarrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoinfree(char *str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	i = 0;
	j = 0;
	if (str)
		i = ft_strlen(str);
	if (buff)
		j = ft_strlen(buff);
	newstr = (char*)malloc(sizeof(*newstr) * (i + j + 1));
	ft_memcpy(newstr, str, i);
	ft_memcpy(newstr + i, buff, j);
	newstr[i + j] = '\0';
	free(str);
	ft_bzero(buff, 1);
	return (newstr);
}

char		*ft_putline(char *str)
{
	int		i;
	int		len;
	char	*newstr;

	len = ft_strlen(str);
	newstr = (char*)malloc(sizeof(char) * len + 1);
	i = 0;
	while (str[i] != '\n' && i < len)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

static char	*ft_delete(char *str)
{
	char	*newstr;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if ((str[i] && !str[i + 1]) || !str[i])
	{
		ft_strdel(&str);
		return (NULL);
	}
	newstr = ft_strdup(str + i + 1);
	ft_strdel(&str);
	return (newstr);
}

int			get_next_line(const int fd, char **line)
{
	static char		*tmp;
	int				ret;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || BUFF_SIZE <= 0 || !line)
		return (ERROR);
	if (!tmp)
		tmp = ft_strnew(1);
	while (!(ft_strchr(tmp, '\n')))
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (ERROR);
		buf[ret] = '\0';
		tmp = ft_strjoinfree(tmp, buf);
		if (ret == 0 && *tmp == '\0')
			return (FINISH);
		if (ret == 0)
			break ;
	}
	*line = ft_putline(tmp);
	tmp = ft_delete(tmp);
	return (SUCCESS);
}
