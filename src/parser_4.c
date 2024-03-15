/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:42:08 by anttorre          #+#    #+#             */
/*   Updated: 2024/03/15 14:44:34 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser_6_continue(t_data *d, t_mini **node, int i)
{
	if (d->subsplit[i + 1][0] == '>' || d->subsplit[i + 1][0] == '|')
		return (d->clean = ft_lstnew(*node), print_error(NL, NULL),
			g_status = 1, EXIT_FAILURE);
	(*node)->infile = open(d->subsplit[i + 1], O_RDONLY);
	if ((*node)->infile == -1)
	{
		print_error(DIRR, "\0");
		g_status = 1;
	}
	return (EXIT_SUCCESS);
}

void	free_node_2(t_mini *node)
{
	if (node != NULL)
	{
		free_bidimensional_array(&node->full_cmd);
		free(node->full_path);
		free(node);
	}
}

int	parser_8_continue(t_data *d, t_mini **node, int *i)
{
	if (parser_2(d, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (d->subsplit[*i] && d->subsplit[*i][0] != '|'
		&& d->subsplit[*i][0] != '>'
		&& d->subsplit[*i][0] != '<' && d->subsplit[*i])
		(*node)->full_cmd = set_full_cmd(d->subsplit + *i);
	if ((*node)->full_cmd && !(*node)->full_path)
		(*node)->full_path = get_paths(d, (*node)->full_cmd[0]);
	if (d->subsplit[*i] && d->subsplit[*i + 1] && d->subsplit[*i + 1][0] == '|' \
		&& !d->subsplit[*i + 2])
		return (print_error(D_PIPE, NULL), EXIT_FAILURE);
	while (d->subsplit[*i] && d->subsplit[*i][0] != '|'
		&& d->subsplit[*i][0] != '>'
		&& d->subsplit[*i][0] != '<')
		(*i)++;
	return (EXIT_SUCCESS);
}

void	parser_8_continue_2(t_mini **node)
{
	(*node) = ft_calloc(1, sizeof(t_mini));
	(*node)->outfile = 1;
	(*node)->infile = 0;
}
