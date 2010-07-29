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

#include "internals.h"

int cd(char **command)
{
    /* Save current directory */
    char *oldwd = getcwd(NULL, 0);
    char *directory;
    if (command[1] == NULL)
        directory = getenv("HOME");
    else if (strequ(command[1], "-"))
    {
        directory = getenv("OLDPWD");
        if (!directory)
            directory = command[1];
    }
    else
        directory = command[1];
    if (chdir(directory) == -1)
    {
        perror(directory);
        return 1;
    }
    else
    {
        setenv("OLDPWD", oldwd, true);
        free(oldwd);
        setenv("PWD", directory, true);
        return 0;
    }
}

int exit_(char **command)
{
    int status = 0;
    if (command[1] != NULL)
    {
        int match = sscanf(command[1], "%d", &status);
        if (match == 0)
        {
            printf("exit: numeric argument required\n");
            return 1;
        }
    }
    exit(status);
}
