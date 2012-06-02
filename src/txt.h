/*
    blogcprog.com - Texts
    Copyright (C) 2010  blogcprog.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __TXT__
#define __TXT__

#include <stdio.h>
#include "db.h"

__db_table_s_table* txt_read(const char* p_file_name,
                             const int p_max_line_size);

char* txt_g_remove_EOL(const char* p_line);

#endif

