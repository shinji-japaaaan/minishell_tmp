/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:20:24 by karai             #+#    #+#             */
/*   Updated: 2025/01/15 20:17:22 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "parser.h"

t_linked_list	*linked_list_init(t_linked_list *new_node)
{
	new_node = (t_linked_list *)malloc(sizeof(t_linked_list));
	new_node->content = NULL;
	new_node->next = NULL;
	new_node->token_type = TYPE_DEFAULT;
	return (new_node);
}

void	linked_list_append(t_linked_list *list_head, char *str)
{
	t_linked_list	*ptr_temp;
	t_linked_list *new_node = NULL;
    new_node = linked_list_init(new_node);
	new_node->content = strdup(str);
	if (list_head->next == NULL)
	{
		list_head->next = new_node;
	}
	else
	{
		ptr_temp = list_head;
		while (ptr_temp->next != NULL)
		{
			ptr_temp = ptr_temp->next;
		}
		ptr_temp->next = new_node;
	}
}

void	linked_list_expansion(t_linked_list *list_head)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		ptr_temp->content = expansion(ptr_temp->content);
		ptr_temp = ptr_temp->next;
	}
}

// for test
void	linked_list_print(t_linked_list *list_head)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		printf("%s\n", ptr_temp->content);
		ptr_temp = ptr_temp->next;
	}
}

// for test
void	linked_list_print_with_token(t_linked_list *list_head)
{
	t_linked_list *ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		printf("token type: %d\n", ptr_temp->token_type);
		printf("%s\n", ptr_temp->content);
		ptr_temp = ptr_temp->next;
	}
}

void	linked_list_free(t_linked_list *list_head)
{
	t_linked_list *temp;
	t_linked_list *current;

	current = list_head;
	while (current != NULL)
	{
		temp = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = temp;
	}
}
