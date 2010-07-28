/*  Copyright 2010 Curtis McEnroe <programble@gmail.com>
 *
 *  This file is part of BSH.
 *
 *  BSH is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  BSH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with BSH.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "command.h"

#include <stdlib.h>
#include <stdio.h>

argument_list *read_argument_list()
{
    argument_list *arglist = malloc(sizeof(argument_list));
    arglist->first = NULL;
    arglist->size = 0;

    argument_list_node *last_node = NULL;

    int stop = 0;
    while (!stop)
    {
        char *arg = malloc(sizeof(char));
        for (int arglen = 1;; arglen++)
        {
            arg = realloc(arg, arglen);
            int c;
            c = getchar();
            if (c == EOF)
                return NULL;
            if (c == ' ')
            {
                arg[arglen-1] = 0x0;
                break;
            }
            if (c == '\n')
            {
                arg[arglen-1] = 0x0;
                stop = 1;
                break;
            }
            arg[arglen-1] = (char) c;
        }
        argument_list_node *new_node = malloc(sizeof(argument_list_node));
        new_node->data = arg;
        new_node->next = NULL;
        if (last_node)
            last_node->next = new_node;
        else
            arglist->first = new_node;
        last_node = new_node;
        arglist->size++;
    }

    return arglist;
}

char **argument_list_to_array(argument_list *arglist)
{
    char **array = malloc(arglist->size + 1);
    argument_list_node *node = arglist->first;
    for (int i = 0; i < arglist->size; i++)
    {
        array[i] = node->data;
        node = node->next;
    }
    array[arglist->size] = NULL;
    return array;
}
