/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:18:17 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/01/27 15:38:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "../includes/get_next_line.h"
#define MAX_INT 2147483647
typedef struct s_stack
{
	int				content;
	int 			index;
	struct s_stack	*next;
	struct s_stack	*previous;
}					t_stack;
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	ft_lstadd_back(t_stack **lst, t_stack *new);
t_stack	*ft_lstnew(int content);
char	**ft_split(char *s, char c);
t_stack	*ft_lstlast(t_stack *lst);
void	ft_bzero(void *s, size_t n);
long long		ft_atoi(const char *str);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_lstadd_front(t_stack **lst, t_stack *new);
int		ft_lstsize(t_stack *lst);
char	*ft_itoa(int c);

#endif
