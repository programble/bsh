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
#include <string.h>

#include "common.h"
#include "reader.h"
#include "command.h"

int main(int argc, char *argv[])
{
    while (true)
    {
        printf("$ ");
        char **command = read_command(stdin);
        if (!command)
            break;
        if (strcmp(command[0], "") == 0)
            continue;
        run_command(command);
        free_command(command);
    }
    return 0;
}
