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

char **read_command(FILE *stream)
{
    int word_count = 0;
    char **command = malloc(word_count);
    do
    {
        word_count++;
        command = realloc(command, word_count * sizeof(char*));
        int word_length = 0;
        char *word = malloc(word_length);
        int c;
        while (true)
        {
            c = fgetc(stream);
            if (c == EOF)
                return NULL;
            if (c == ' ')
            {
                c = 0x0;
            }
            else if (c == '\n')
            {
                command = realloc(command, (word_count + 1) * sizeof(char*));
                command[word_count] = NULL;
            }
            word_length++;
            word = realloc(word, word_length);
            if (c == '\n')
                word[word_length-1] = 0x0;
            else
                word[word_length-1] = (char) c;
            if (c == 0x0 || c == '\n')
                break;
        }
        command[word_count-1] = word;
        if (c == '\n')
            word_count++;
    } while (command[word_count-1] != NULL);
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
