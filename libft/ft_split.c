/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 14:40:10 by skorteka      #+#    #+#                 */
/*   Updated: 2019/10/31 14:40:11 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_slots(char const *s, char c)
{
	int	i;
	int	slots;

	i = 0;
	slots = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			slots++;
		i++;
	}
	return (slots);
}

static char	**ft_free(char **array, int slot)
{
	while (slot > 0)
	{
		slot--;
		free(array[slot]);
	}
	free(array);
	return (NULL);
}

static char	**ft_malloc_array(char const *s, char c, char **array)
{
	int i;
	int len;
	int slot;

	i = 0;
	slot = 0;
	while (s[i] == c && c != '\0')
		i++;
	while (s[i])
	{
		len = 0;
		while (s[i] != c && s[i] != '\0')
		{
			len++;
			i++;
		}
		array[slot] = malloc((len + 1) * sizeof(char));
		if (!array[slot])
			return (ft_free(array, slot));
		slot++;
		while (s[i] == c && c != '\0')
			i++;
	}
	return (array);
}

static void	ft_fill_array(const char *s, char c, char **array)
{
	int i;
	int slot_i;
	int slot;

	i = 0;
	slot = 0;
	while (s[i] == c && c != '\0')
		i++;
	while (s[i])
	{
		slot_i = 0;
		while (s[i] != c && s[i] != '\0')
		{
			array[slot][slot_i] = s[i];
			slot_i++;
			i++;
		}
		array[slot][slot_i] = '\0';
		slot++;
		while (s[i] == c && c != '\0')
			i++;
	}
}

char		**ft_split(char const *s, char c)
{
	char	**array;
	int		slots;

	if (s == NULL)
		return (NULL);
	slots = ft_slots(s, c);
	array = malloc((slots + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array[slots] = NULL;
	if (slots == 0)
		return (array);
	if (!ft_malloc_array(s, c, array))
		return (NULL);
	ft_fill_array(s, c, array);
	return (array);
}
