/*
    blogcprog.com - db_index
    Copyright (C) 2010  blogcprog.com
                  2012  rdbms4c.org

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

#ifndef __DB_INDEX__
#define __DB_INDEX__

#include <stdlib.h>
#include "db_record.h"

typedef enum {__normal = 1, __primary = 2, __unique = 3} __db_index_index_type;

typedef enum {__asc = 0, __desc = 1} __db_index_field_sort_type;

typedef unsigned char __db_index_position;

typedef unsigned long __db_index_record_position;

typedef __db_record_s_record** __db_index_index;

typedef int __db_index_function_based(const __db_record_s_record* p_record_1,
                                      const __db_record_s_record* p_record_2);

typedef __db_index_function_based* __db_index_p_function_based;

typedef struct __db_index_ss_index_field_definition
{
    int field_index;
    __db_index_field_sort_type sort_type;
} __db_index_s_index_field_definition;

typedef struct __db_index_ss_index
{
    __db_index_index index;
    int num_of_index_fields;
    __db_index_s_index_field_definition* index_fields_definition;
    __db_index_p_function_based function_based_index;
    __db_index_index_type index_type;
    unsigned char index_rebuild_needed;
    char enabled;
} __db_index_s_index;

__db_index_s_index db_index_create(int p_num_of_index_fields,
                                   __db_index_index_type p_index_type,
                                   __db_index_p_function_based p_f);

void db_index_set_field_definition(
    __db_index_s_index_field_definition* p_index_fields_definition,
    int p_position,
    int p_field_index,
    __db_index_field_sort_type p_field_sort_type);

#endif
