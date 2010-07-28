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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#include "command.h"

int main(int argc, char *argv[])
{
#ifdef DEBUG
    argument_list *test = read_argument_list();
    printf("%d\n", test->size);
    argument_list_node *node = test->first;
    for (int i = 0; i < test->size; i++)
    {
        printf("%s\n", node->data);
        node = node->next;
    }
    char **test_array = argument_list_to_array(test);
    int pid = fork();
    if (pid == 0)
        execvp(test_array[0], test_array);
    else
        waitpid(pid, NULL, 0);
    printf("yo, im the parent, still running");
#endif
    return 0;
}
