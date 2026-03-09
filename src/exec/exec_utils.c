/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mville <mville@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:21:48 by mville            #+#    #+#             */
/*   Updated: 2026/03/07 12:54:19 by mville           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_builtins(char *cmd)
{
 if (!cmd)
  return (0);
 if (ft_strcmp(cmd, "export") == 0)
  return (1);
 if (ft_strcmp(cmd, "echo") == 0)
  return (1);
 if (ft_strcmp(cmd, "cd") == 0)
  return (1);
 if (ft_strcmp(cmd, "pwd") == 0)
  return (1);
 if (ft_strcmp(cmd, "exit") == 0)
  return (1);
 if (ft_strcmp(cmd, "end") == 0)
  return (1);
return (0);
}