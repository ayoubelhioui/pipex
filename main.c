/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:01:09 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/21 12:20:50 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
int main()
{
    char *path = "/bin/echo";
    char *command[] = {"echo", "HelloWorld", NULL};
    execve(path, command, NULL);
}