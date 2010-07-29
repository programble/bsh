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

int run_command(char **command)
{
    /* Fork before running the command, since execvp replaces
       the current process */
    int pid = fork();
    if (pid == 0)
    {
        /* Run the command in the child */
        execvp(command[0], command);
        /* If execution reaches this point, an error has occured
           TODO: Handle errors */
    }
    else
    {
        /* The processes exit code */
        int status;
        /* Wait for the child to finish */
        waitpid(pid, &status, 0);
        /* Return the process' exit status */
        return status;
    }
    return -1;
}
