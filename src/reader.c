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

#include "reader.h"

char *read_word(FILE *stream, int *more)
{
    *more = 1;
    int length = 0;
    char *word = malloc(length);
    int quote_type = 0;
    int c;
    while (true)
    {
        /* Get a new character from the stream */
        c = fgetc(stream);
        /* Eof? */
        if (c == EOF)
        {
            *more = EOF;
            return NULL;
        }
        /* Skip leading whitespace */
        if (c == ' ' && length == 0)
            continue;
        /* Quoting */
        if (c == '"')
        {
            quote_type = 1;
            continue;
        }
        else if (c == '\'')
        {
            quote_type = 2;
            continue;
        }
        /* Outside of quotes, ; is treated as \n */
        if (c == ';' && !quote_type)
            c = '\n';
        /* Outside of quotes, the word ends at a space */
        if (c == ' ' && !quote_type)
            c = 0;
        /* Inside quotes, a word ends at the next quote */
        else if (c == '"' && quote_type == 1)
            c = 0;
        else if (c == '\'' && quote_type == 1)
            c = 0;
        /* \n means there are no more words */
        if (c == '\n')
        {
            *more = 0;
            c = 0;
        }
        /* Add character to word */
        word = realloc(word, ++length);
        word[length-1] = c;
        /* Break if the word is terminated */
        if (c == 0)
            break;
    }
    return word;
}

char **read_command(FILE *stream)
{
    int count = 0;
    char **command = malloc(count);
    int more = 1;
    while (more == 1)
    {
        command = realloc(command, (++count) * sizeof(char*));
        command[count-1] = read_word(stream, &more);
        if (more == EOF)
            return NULL;
    }
    command = realloc(command, (++count) * sizeof(char*));
    command[count-1] = NULL;
    return command;
}

void free_command(char **command)
{
    for (int i = 0; command[i] != NULL; i++)
        free(command[i]);
    free(command);
}

int count_arguments(char **command)
{
    int count = 0;
    for (int i = 1; command[i] != NULL; i++)
        count++;
    return count;
}
