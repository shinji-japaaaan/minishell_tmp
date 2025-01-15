/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:21:34 by karai             #+#    #+#             */
/*   Updated: 2025/01/15 19:57:46 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum TokenType
{
	TYPE_DEFAULT = 1,
	TYPE_COMMAND,
	TYPE_PIPE,
	TYPE_REDIRECT_IN,
	TYPE_HEREDOC,
	TYPE_REDIRECT_OUT,
	TYPE_REDIRECT_APPEND
}				TokenType;

typedef struct s_linked_list
{
	char *content;              // moziretu
	TokenType token_type;       // pipe or string or redirect or someting
	struct s_linked_list *next; // next pointer
}				t_linked_list;

t_linked_list	*linked_list_init(t_linked_list *new_node);
void			linked_list_append(t_linked_list *list_head, char *str);
void			linked_list_expansion(t_linked_list *list_head);
void			linked_list_print(t_linked_list *list_head);
void			linked_list_print_with_token(t_linked_list *list_head);
void			linked_list_free(t_linked_list *list_head);
#endif
