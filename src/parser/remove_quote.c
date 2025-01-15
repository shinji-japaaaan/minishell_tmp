/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:45:13 by karai             #+#    #+#             */
/*   Updated: 2025/01/15 20:24:22 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "parser.h"

size_t	remove_quote_get_newlen(char *str)
{
	size_t	new_len;
	size_t	i;

	int state; // 0:outside quote, 1:inside single quote, 2: inside double quote
	new_len = 0;
	i = 0;
	state = 0;
	while (str[i])
	{
		if (state == 0)
		{
			if (str[i] == '\'')
				state = 1;
			else if (str[i] == '\"')
				state = 2;
			else
				new_len += 1;
		}
		else if (state == 1)
		{
			if (str[i] == '\'')
				state = 0;
			else
				new_len += 1;
		}
		else if (state == 2)
		{
			if (str[i] == '\"')
				state = 0;
			else
				new_len += 1;
		}
		i += 1;
	}
	return (new_len);
}

char	*remove_quote(char *str)
{
	char	*new_str;
	size_t	new_len;
	size_t	i;
	size_t	j;

	int state; // 0:outside quote, 1:inside single quote, 2: inside double quote
	new_len = remove_quote_get_newlen(str);
	new_str = (char *)malloc(sizeof(char) * (new_len + 1));
	i = 0;
	j = 0;
	state = 0;
	while (str[i])
	{
		if (state == 0)
		{
			if (str[i] == '\'')
				state = 1;
			else if (str[i] == '\"')
				state = 2;
			else
				new_str[j++] = str[i];
		}
		else if (state == 1)
		{
			if (str[i] == '\'')
				state = 0;
			else
				new_str[j++] = str[i];
		}
		else if (state == 2)
		{
			if (str[i] == '\"')
				state = 0;
			else
				new_str[j++] = str[i];
		}
		i += 1;
	}
	free(str);
	new_str[j] = '\0';
	return (new_str);
}

t_linked_list	linked_list_remove_quote(t_linked_list *list_head)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		if (ptr_temp->token_type == TYPE_COMMAND)
		{
			ptr_temp->content = remove_quote(ptr_temp->content);
		}
		ptr_temp = ptr_temp->next;
	}
	return *list_head;  // list_headの値を返す
}
