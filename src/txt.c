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

#include "txt.h"

char* txt_g_remove_EOL(const char* p_line)
{
    int v_line_length;
    char* v_line;
    char* v_result = NULL;
    if(p_line != NULL)
    {
        v_line_length = strlen(p_line);
        v_line = malloc(sizeof(char)*(v_line_length + 1));
        strcpy(v_line, p_line);
        if (v_line_length > 0 && v_line[v_line_length-1] == '\n')
            v_line[--v_line_length] = '\0';
        if (v_line_length > 0 && v_line[v_line_length-1] == '\r')
            v_line[--v_line_length] = '\0';
        v_result = malloc(sizeof(char) * (v_line_length + 1));
        strcpy(v_result, v_line);
        free(v_line);
    }
    return v_result;
}

__db_table_s_table* txt_read(const char* p_file_name,
                             const int p_max_line_size)
{
    __db_table_s_table* v_result;
    __db_index_s_index v_primary_index;
    unsigned long *v_line_counter;
    FILE* v_file;
    char* v_line;
    char* v_line2;

    __db_record_s_definition* v_record_definition;
    __db_field_s_field* v_fields;

    v_line_counter = malloc(sizeof(unsigned long));

    if(p_file_name != NULL)
    {
        v_file = fopen(p_file_name, "r");
        if(v_file != NULL && v_file != 0)
        {

            v_record_definition = db_record_create_definition(2);

            db_record_set_definition_field(
                v_record_definition,
                0,
                "id", __NOT_NULL, __unsigned_long);

            db_record_set_definition_field(
                v_record_definition,
                1,
                "line", __NULL, __char_array);

            v_primary_index = db_index_create(1, __primary, NULL);

            db_index_set_field_definition(
                v_primary_index.index_fields_definition, 0, 0, __asc);

            v_result = db_table_create(v_record_definition, v_primary_index);
            *v_line_counter = 0;
            while(!feof(v_file))
            {
                v_line = malloc(sizeof(char) * p_max_line_size);
                fgets(v_line, p_max_line_size, v_file);
                v_line2 = txt_g_remove_EOL(v_line);
                (*v_line_counter)++;
                free(v_line);
                if(!feof(v_file))
                {
                    v_fields = db_field_create(2);

                    db_field_set_value(
                        v_record_definition->fields_definition,
                        v_fields,
                        0,
                        v_line_counter);

                    db_field_set_value(
                        v_record_definition->fields_definition,
                        v_fields,
                        1,
                        v_line2);
                    free(v_line2);
                    db_table_insert_into(v_result, v_fields);
                }
            }
            fclose(v_file);
            free(v_line_counter);
        }
    }
    return v_result;
}
