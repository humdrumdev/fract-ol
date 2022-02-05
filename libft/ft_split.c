/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:27:47 by hel-moud          #+#    #+#             */
/*   Updated: 2021/11/05 17:00:28 by hel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static t_chunk	*lstnew(int wend, int wbeg, char const *s)
{
	t_chunk	*new;
	int		i;

	new = (t_chunk *)malloc(sizeof(t_chunk));
	if (new)
	{
		new->word = (char *)malloc((wend - wbeg + 1) * sizeof(char));
		if (!(new->word))
		{
			free(new);
			return (NULL);
		}
		i = -1;
		while (++i < (wend - wbeg))
			(new->word)[i] = s[wbeg + i];
		(new->word)[i] = 0;
		new->next = NULL;
	}
	return (new);
}

static int	lstfree(t_chunk **head, int all)
{
	t_chunk	*tmp;
	t_chunk	*next;

	if (!head || !(*head))
		return (0);
	tmp = (*head)->next;
	while (tmp)
	{
		next = tmp->next;
		if (all)
			free(tmp->word);
		free(tmp);
		tmp = next;
	}
	if (all)
		free((*head)->word);
	free(*head);
	*head = NULL;
	return (0);
}

static int	addback(t_chunk **head, int wend, int wbeg, char const *s)
{
	t_chunk	*new;
	t_chunk	*tmp;

	if (!head)
		return (0);
	new = lstnew(wend, wbeg, s);
	if (!new)
		return (0);
	if (!(*head))
	{
		*head = new;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

static	int	get_words(char const *s, char d, t_chunk **head)
{
	int	wend;
	int	wbeg;
	int	count;

	wend = 0;
	wbeg = 0;
	count = 1;
	while (s[wend])
	{
		while (s[wend] && s[wend] == d)
		{
			wend++;
			wbeg++;
		}
		if (!(s[wend]))
			break ;
		while (s[wend] && s[wend] != d)
			wend++;
		if (!addback(head, wend, wbeg, s))
			return (lstfree(head, 1));
		count++;
		wbeg = wend;
	}
	return (count);
}

char	**ft_split(char const *s, char d)
{
	t_chunk	*head;
	t_chunk	*tmp;
	int		i;
	int		count;
	char	**new;

	if (!s)
		return (NULL);
	head = NULL;
	count = get_words(s, d, &head);
	if (!count)
		return (NULL);
	new = (char **)malloc(count * sizeof(char *));
	if (!new)
		return (lstfree(&head, 1), NULL);
	i = -1;
	tmp = head;
	while (++i < (count - 1))
	{
		new[i] = tmp->word;
		tmp = tmp->next;
	}
	new[i] = NULL;
	lstfree(&head, 0);
	return (new);
}
