/*
    blogcprog.com - db_cursor
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

#include <stdlib.h>
#include "db_cursor.h"

__db_cursor_s_cursor* db_cursor_create(__db_table_s_table* p_table,
                                       const __db_index_position p_index_position)
{
    __db_cursor_s_cursor* v_result = malloc(sizeof(__db_cursor_s_cursor));
    v_result->current = 0;
    v_result->index_position = p_index_position;
    v_result->table = p_table;

    return v_result;
}

void db_cursor_drop(__db_cursor_s_cursor* p_cursor)
{
    free(p_cursor);
}

__db_record_s_record* db_cursor_current(__db_cursor_s_cursor* p_cursor)
{
    __db_record_s_record* v_result = NULL;

    v_result = db_table_get_record(p_cursor->table,
                                   p_cursor->index_position,
                                   p_cursor->current);

    return v_result;
}

__db_record_s_record* db_cursor_next(__db_cursor_s_cursor* p_cursor)
{
    __db_record_s_record* v_result = NULL;

    if(p_cursor->current < p_cursor->table->count - 1)
        v_result = db_table_get_record(p_cursor->table,
                                       p_cursor->index_position,
                                       ++p_cursor->current);

    return v_result;
}

__db_record_s_record* db_cursor_prev(__db_cursor_s_cursor* p_cursor)
{
    __db_record_s_record* v_result = NULL;

    if(p_cursor->current >= p_cursor->table->count)
        p_cursor->current = p_cursor->table->count - 1;

    v_result = db_table_get_record(p_cursor->table,
                                   p_cursor->index_position,
                                   --p_cursor->current);
    return v_result;
}

__db_record_s_record* db_cursor_first(__db_cursor_s_cursor* p_cursor)
{
    __db_record_s_record* v_result = NULL;
    p_cursor->current = 0;
    if(p_cursor->table->count == 0)
        return NULL;

    v_result = db_table_get_record(p_cursor->table,
                                   p_cursor->index_position,
                                   p_cursor->current);
    return v_result;
}

__db_record_s_record* db_cursor_last(__db_cursor_s_cursor* p_cursor)
{
    __db_record_s_record* v_result = NULL;

    if(p_cursor->table->count == 0){
        p_cursor->current = 0;
        return NULL;
    }

    p_cursor->current = p_cursor->table->count-1;
    v_result = db_table_get_record(p_cursor->table,
                                   p_cursor->index_position,
                                   p_cursor->current);
    return v_result;
}

unsigned char db_cursor_for_all(__db_cursor_s_cursor* p_cursor,
                                __db_cursor_p_for_function p_cursor_for_function,
                                void* p_args[])
{
    unsigned long l=0;
    unsigned char v_ret=0;

    while(v_ret==0 && l < p_cursor->table->count)
    {
        v_ret = (*p_cursor_for_function)
                (p_cursor->table,
                 db_table_get_record(p_cursor->table,
                                     p_cursor->index_position, l),
                 p_args, l);
        l++;
    }
    return v_ret;
}

__db_cursor_s_key* db_cursor_create_key(__db_cursor_s_cursor* p_cursor)
{
    __db_cursor_s_key* v_result = NULL;
    db_error_reset();
    if(p_cursor->table->indexes[p_cursor->index_position].
            index_type == __primary ||
            p_cursor->table->indexes[p_cursor->index_position].
            index_type == __unique)
    {

        v_result = malloc(sizeof(__db_cursor_s_key));
        v_result->cursor = p_cursor;
        v_result->fields = db_field_create(
                               p_cursor->table->indexes[p_cursor->index_position].num_of_index_fields);
    }
    else
        db_error_set_error(__UNIQUE_INDEX_NEEDED);

    return v_result;
}

void db_cursor_drop_key(__db_cursor_s_key* p_key)
{
    db_field_drop(p_key->fields,
                  p_key->cursor->table->indexes[p_key->cursor->index_position].num_of_index_fields);
    free(p_key);
}

void db_cursor_set_key_fields(__db_cursor_s_key* p_key,
                              const __db_field_position p_field_position,
                              const void* p_value)
{
    db_field_set_value(p_key->cursor->table->record_definition->fields_definition,
                       p_key->fields,
                       p_field_position,
                       p_value);
}

__db_record_s_record* __key_to_record(__db_cursor_s_key* p_key)
{
    __db_record_s_record* v_result = NULL;
    __db_field_s_field* v_fields;
    __db_field_position i;
    v_fields =
        db_field_create(p_key->cursor->table->record_definition->num_of_fields);

    for(i = 0;
            i < p_key->cursor->table->indexes[p_key->cursor->index_position].
            num_of_index_fields;
            i++)
    {

        db_field_set_value(
            p_key->cursor->table->record_definition->fields_definition,
            v_fields,
            p_key->cursor->table->indexes[p_key->cursor->index_position].
            index_fields_definition[i].field_index,
            p_key->fields[i].field);
    }
    v_result = db_record_create(NULL, NULL, v_fields);
    return v_result;
}

__db_record_s_record* db_cursor_find_by_key(__db_cursor_s_key* p_key)
{
    __db_record_s_record* v_result = NULL;
    __db_record_s_record* v_record_key = NULL;
    signed char v_compare = 0;
    __db_index_record_position v_low;
    __db_index_record_position v_high;
    __db_index_record_position v_middle;

    v_low = 0;
    v_high = p_key->cursor->table->count - 1;
    v_record_key = __key_to_record(p_key);
    if(p_key->cursor->table->indexes[p_key->cursor->index_position].index_rebuild_needed)
        db_table_get_record(p_key->cursor->table, p_key->cursor->index_position, 0);

    do
    {
        v_middle = (__db_index_record_position)((v_low + v_high) / 2);
        v_compare = db_table_compare_records(
                        p_key->cursor->table->indexes[p_key->cursor->index_position].
                        index[v_middle],
                        v_record_key,
                        p_key->cursor->table,
                        p_key->cursor->index_position);

        if (v_compare < 0)
            v_low = v_middle + 1;
        else if (v_compare > 0)
            v_high = v_middle - 1;
    }
    while (v_low <= v_high && v_compare != 0);
    if (v_low <= v_high)
    {
        v_result = db_table_get_record(p_key->cursor->table,
                                       p_key->cursor->index_position,
                                       v_middle);
        p_key->cursor->current = v_middle;
    }
    db_record_drop(v_record_key, p_key->cursor->table->record_definition);

    return v_result;
}

void db_cursor_insert(__db_cursor_s_cursor* p_cursor,
                      __db_field_s_field* p_fields)
{
    db_table_insert_into(p_cursor->table, p_fields);
}

void db_cursor_update(__db_cursor_s_cursor* p_cursor,
                      __db_field_position p_field_position,
                      void* p_value)
{
    __db_record_s_record* v_record;
    db_error_reset();
    if(!db_table_is_unique_field(p_cursor->table,
                                 p_field_position))
    {
        if(!db_table_is_fk_field(p_cursor->table,
                                 p_field_position))
        {
            v_record = db_table_get_record(p_cursor->table,
                                           p_cursor->index_position,
                                           p_cursor->current);

            db_field_set_value(p_cursor->table->record_definition->fields_definition,
                               v_record->fields,
                               p_field_position,
                               p_value);

        }
        else
            db_error_set_error(__CANNOT_MODIFY_FOREIGN_KEY);
    }
    else
        db_error_set_error(__CANNOT_MODIFY_UNIQUE_KEY);

}

void db_cursor_update_fk(__db_cursor_s_cursor* p_cursor,
                         __db_field_position p_field_position,
                         __db_cursor_s_cursor* p_foreign_cursor)
{
    __db_record_s_record* v_record;
    db_error_reset();

    if(!db_table_is_unique_field(p_cursor->table,
                                 p_field_position))
    {
        if(db_table_is_fk_field(p_cursor->table,
                                p_field_position))
        {
            v_record = db_table_get_record(p_cursor->table,
                                           p_cursor->index_position,
                                           p_cursor->current);
            if(v_record != NULL)
                db_field_set_value(p_cursor->table->record_definition->fields_definition,
                                   v_record->fields,
                                   p_field_position,
                                   db_cursor_current(p_foreign_cursor));
            else
                db_error_set_error(__NO_DATA_FOUND);
        }
        else
            db_error_set_error(__FOREIGN_KEY_NEEDED);
    }
    else
        db_error_set_error(__CANNOT_MODIFY_UNIQUE_KEY);

}

void db_cursor_delete(__db_cursor_s_cursor* p_cursor)
{
    db_table_delete_from(p_cursor->table,
                         p_cursor->index_position,
                         p_cursor->current);
    if(p_cursor->current >= p_cursor->table->count)
        p_cursor->current--;
}
