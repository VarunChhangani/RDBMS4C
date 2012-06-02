/*
    blogcprog.com - db_index
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


#include "db_index.h"

__db_index_s_index db_index_create(int p_num_of_index_fields,
                                   __db_index_index_type p_index_type,
                                   __db_index_p_function_based p_f)
{
    __db_index_s_index v_result;
    int i;

    v_result.function_based_index = p_f;
    v_result.index_type = p_index_type;
    v_result.index = NULL;
    v_result.index_rebuild_needed = 1;

    v_result.index_fields_definition = malloc(
                                           sizeof(__db_index_s_index_field_definition) * p_num_of_index_fields);

    for(i = 0; i < p_num_of_index_fields; i++)
    {
        v_result.index_fields_definition[i].field_index = 0;
        v_result.index_fields_definition[i].sort_type = __asc;
    }
    v_result.num_of_index_fields = p_num_of_index_fields;
    v_result.enabled = 1;
    return v_result;
}

void db_index_set_field_definition(
    __db_index_s_index_field_definition* p_index_fields_definition,
    int p_position,
    int p_field_index,
    __db_index_field_sort_type p_field_sort_type)
{
    p_index_fields_definition[p_position].field_index = p_field_index;
    p_index_fields_definition[p_position].sort_type = p_field_sort_type;
}

