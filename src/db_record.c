/*
    blogcprog.com - db_record
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

#include "stdlib.h"
#include "db_record.h"


__db_record_s_definition* db_record_create_definition(int p_num_of_fields)
{
    int i;
    __db_field_s_field_definition* v_fields_definition = malloc(sizeof(__db_field_s_field_definition) * p_num_of_fields);
    __db_record_s_definition* v_result = malloc(sizeof(__db_record_s_definition));
    v_result->fields_definition = v_fields_definition;
    for(i = 0; i < p_num_of_fields; i++)
    {
        v_result->fields_definition[i].name = NULL;
        v_result->fields_definition[i].data_type = 0;
        v_result->fields_definition[i].foreign_key_target = NULL;
        v_result->fields_definition[i].null_definition = __NULL;
    }
    v_result->num_of_fields = p_num_of_fields;
    return v_result;
}

void db_record_set_definition_field(__db_record_s_definition* p_record_definition,
                                    int p_position,
                                    __db_general_name p_name,
                                    __db_field_NULL_definition p_NULL_definition,
                                    __db_field_data_type p_data_type)
{

    p_record_definition->fields_definition[p_position].name =
        malloc(sizeof(char)*(strlen(p_name) + 1));
    strcpy(p_record_definition->fields_definition[p_position].name, p_name);
    p_record_definition->fields_definition[p_position].data_type = p_data_type;
    p_record_definition->fields_definition[p_position].null_definition =
        p_NULL_definition;
    p_record_definition->fields_definition[p_position].foreign_key_target = NULL;

}

__db_record_s_record* db_record_create(__db_record_s_record* p_prev_record,
                                       __db_record_s_record* p_next_record,
                                       __db_field_s_field* p_fields)
{
    __db_record_s_record* v_result = malloc(sizeof(__db_record_s_record));
    v_result->prev_record = p_prev_record;
    v_result->next_record = p_next_record;
    v_result->fields = p_fields;

    return v_result;
}

void db_record_drop(__db_record_s_record* p_record,
                    __db_record_s_definition* p_record_definition)
{
    int i;

    for(i = 0; i < p_record_definition->num_of_fields; i++)
        if(p_record_definition->fields_definition[i].data_type == __foreign_key &&
                p_record->fields[i].field != NULL)
            free(p_record->fields[i].field);

    free(p_record->fields);
    if(p_record != NULL)
        free(p_record);

}

void db_record_drop_definition(__db_record_s_definition* p_record_definition)
{
    if(p_record_definition->fields_definition != NULL)
        free(p_record_definition->fields_definition);

    free(p_record_definition);

}

