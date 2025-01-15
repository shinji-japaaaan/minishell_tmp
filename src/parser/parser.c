/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:11:06 by karai             #+#    #+#             */
/*   Updated: 2025/01/15 20:18:50 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "parser.h"

// char	*delete_blank_start_end(char *input)
// {
// 	size_t	len;

// 	while (is_blank(*input))
// 	{
// 		input += 1;
// 	}
// 	len = strlen(input);
// 	while (len >= 0 && is_blank(input[len]))
// 	{
// 		input[len] = '\0';
// 		len -= 1;
// 	}
// 	return (input);
// }

size_t	split_len(char *input)
{
	bool	inside_single_quote;
	bool	inside_double_quote;
	size_t	len;

	inside_single_quote = false;
	inside_double_quote = false;
	len = 0;
	// while (*input != '\0' && is_blank(*input))
	// 	input += 1;
	if (is_delimeter(input) != 0)
		return (is_delimeter(input));
	while (input[len])
	{
		if (input[len] == '\'')
			inside_single_quote = !inside_single_quote;
		if (input[len] == '\"')
			inside_double_quote = !inside_double_quote;
		if (inside_double_quote == false && inside_single_quote == false)
		{
			if (is_delimeter(&(input[len])) != 0)
				return (len);
			if (is_blank(input[len]))
				return (len);
		}
		len += 1;
	}
	return (len);
}

t_linked_list	*parser(char *input)
{
	char			*str_temp;
	size_t			len;

	t_linked_list *head = NULL;
	head = linked_list_init(head);
	while (*input != '\0')
	{
		while (*input != '\0' && is_blank(*input))
			input += 1;
		if (*input == '\0')
		 	break ;
		len = split_len(input);
		str_temp = strdup_len(input, len);
		linked_list_append(head, str_temp);
		input += len;
	}
	linked_list_tokenize(head);
	linked_list_expansion(head);
	linked_list_remove_quote(head);
	return (head);
}
