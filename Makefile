# Copyright 2010 Curtis McEnroe <programble@gmail.com>
#
# This file is part of BSH.
#
# BSH is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# BSH is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with BSH.  If not, see <http://www.gnu.org/licenses/>.

CC=clang
INCLUDES=-Iinclude/
CFLAGS=-std=c99 -Wall -Wextra -Wno-unused-parameter $(INCLUDES) -include config.h
LDFLAGS=
DFLAGS=-g -DDEBUG -O0
SOURCES:=$(wildcard src/*.c)
OBJECTS:=$(SOURCES:%.c=%.o)
EXECUTABLE=bsh

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

debug:
	@$(MAKE) $(MFLAGS) CFLAGS="$(CFLAGS) $(DFLAGS)"

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)

distclean: clean
	rm -f *~
	rm -f src/*~
	rm -f include/*~

.PHONY: clean distclean debug
