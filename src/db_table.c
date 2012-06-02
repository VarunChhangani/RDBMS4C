/*
    blogcprog.com - db_table
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
#include "db_table.h"

typedef unsigned char __table_for_function(__db_table_s_table* p_table,
        __db_record_s_record* p_record,
        void* p_args[],
        long p_rownum);

typedef __table_for_function* __p_table_for_function;

void __enable_index(__db_table_s_table* p_table,
                    const __db_index_position p_index_position);

void __disable_indexes(__db_table_s_table* p_table);

void __sort_index(__db_table_s_table* p_table,
                  const __db_index_position p_index_position);

unsigned char __for_all(__db_table_s_table* p_table,
                        __p_table_for_function p_table_for_function,
                        void* p_args[]);
unsigned char __index_creation(__db_table_s_table* p_table,
                               __db_record_s_record* p_tablerecord,
                               void* p_args[],
                               long p_rownum);

unsigned char __unique_exists(__db_table_s_table* p_table,
                              __db_record_s_record* p_record);

void db_table_delete_record(__db_table_s_table* p_table,
                            __db_record_s_record* p_record);

__db_table_s_table* db_table_create(__db_record_s_definition* p_record_definition,
                                    __db_index_s_index p_primary_index)
{
    int i;
    __db_table_s_table* v_table = NULL;
    db_error_reset();
    if(p_primary_index.enabled &&
            p_primary_index.index_type == __primary &&
            p_primary_index.num_of_index_fields > 0 &&
            p_primary_index.index_fields_definition != NULL)
    {
        v_table = malloc(sizeof(__db_table_s_table));
        v_table->first_record = NULL;
        v_table->last_record = NULL;
        v_table->name = NULL;
        v_table->count = 0;
        v_table->record_definition = p_record_definition;
        v_table->indexes = malloc(sizeof(__db_index_s_index) * 32);
        v_table->child_tables = NULL;
        v_table->num_of_child_tables = 0;
        for(i=0; i < 32; i++)
        {
            v_table->indexes[i].function_based_index = NULL;
            v_table->indexes[i].index = NULL;
            v_table->indexes[i].num_of_index_fields = 0;
            v_table->indexes[i].index_fields_definition = NULL;
            v_table->indexes[i].function_based_index = NULL;
            v_table->indexes[i].index_type = 0;
            v_table->indexes[i].index_rebuild_needed = 0;
            v_table->indexes[i].enabled = 0;
        }
        v_table->indexes[0] = p_primary_index;
    }
    else
        db_error_set_error(__MISSING_PRIMARY_INDEX);

    return v_table;
}

__db_table_s_table* db_table_create_for_structure(void)
{
    int v_i;
    __db_table_s_table* v_table = NULL;
    __db_record_s_definition* v_record_definition = NULL;
    __db_index_s_index v_primary_index;
    v_record_definition = db_record_create_definition(1);
    db_record_set_definition_field(
        v_record_definition,
        0,
        "structure", __void_pointer, __NOT_NULL);

    v_primary_index = db_index_create(1, __primary, NULL);

    db_index_set_field_definition(
        v_primary_index.index_fields_definition, 0, 0, __asc);

    v_table = db_table_create(v_record_definition, v_primary_index);
    return v_table;
}

unsigned char __for_all(__db_table_s_table* p_table,
                        __p_table_for_function p_table_for_function,
                        void* p_args[])
{
    long l=0;
    unsigned char v_ret=0;
    __db_record_s_record* v_record = p_table->first_record;
    while(v_ret==0&&v_record!=NULL&&l<p_table->count)
    {
        v_ret = (*p_table_for_function)(p_table, v_record, p_args, l);
        v_record = v_record->next_record;
        l++;
    }
    return v_ret;
}

signed char db_table_compare_records(const __db_record_s_record* p_record_1,
                                     const __db_record_s_record* p_record_2,
                                     __db_table_s_table* p_table,
                                     const __db_index_position p_index_position)
{
    signed char v_result = 0;
    char *v_char_array1, *v_char_array2;
    char v_char1, v_char2;
    unsigned char  v_unsigned_char1, v_unsigned_char2;
    int v_int1, v_int2;
    unsigned int v_unsigned_int1, v_unsigned_int2;
    long v_long1, v_long2;
    unsigned long v_unsigned_long1, v_unsigned_long2;
    float v_float1, v_float2;
    double v_double1, v_double2;
    __db_record_s_record* v_fk_record_1;
    __db_record_s_record* v_fk_record_2;
    __db_table_s_table* v_fk_table;

    int i, v_field_index;
    __db_field_data_type v_data_type;
    i = -1;
    while(++i < p_table->indexes[p_index_position].num_of_index_fields && v_result == 0)
    {
        v_field_index =
            p_table->indexes[p_index_position].index_fields_definition[i].field_index;
        v_data_type =
            p_table->record_definition->fields_definition[v_field_index].data_type;
        switch (v_data_type)
        {
        case __char_array:
            v_char_array1 = (char*)p_record_1->fields[v_field_index].field;
            v_char_array2 = (char*)p_record_2->fields[v_field_index].field;
            v_result = strcmp(v_char_array1, v_char_array2);
            break;
        case __char:
            v_char1 = *(char*)p_record_1->fields[v_field_index].field;
            v_char2 = *(char*)p_record_2->fields[v_field_index].field;
            v_result = v_char1 > v_char2 ? 1 : v_char1 < v_char2 ? -1 : 0;
            break;
        case __unsigned_char:
            v_unsigned_char1 = *(unsigned char*)p_record_1->fields[v_field_index].field;
            v_unsigned_char2 = *(unsigned char*)p_record_2->fields[v_field_index].field;
            v_result =
                v_unsigned_char1 > v_unsigned_char2 ? 1 :
                v_unsigned_char1 < v_unsigned_char2 ? -1 : 0;
            break;
        case __int:
            v_int1 = *(int*)p_record_1->fields[v_field_index].field;
            v_int2 = *(int*)p_record_2->fields[v_field_index].field;
            v_result = v_int1 > v_int2 ? 1 : v_int1 < v_int2 ? -1 : 0;
            break;
        case __unsigned_int:
            v_unsigned_int1 = *(unsigned int*)p_record_1->fields[v_field_index].field;
            v_unsigned_int2 = *(unsigned int*)p_record_2->fields[v_field_index].field;
            v_result =
                v_unsigned_int1 > v_unsigned_int2 ? 1 :
                v_unsigned_int1 < v_unsigned_int2 ? -1 : 0;
            break;
        case __long:
            v_long1 = *(long*)p_record_1->fields[v_field_index].field;
            v_long2 = *(long*)p_record_2->fields[v_field_index].field;
            v_result = v_long1 > v_long2 ? 1 : v_long1 < v_long2 ? -1 : 0;
            break;
        case __unsigned_long:
            v_unsigned_long1 = *(unsigned long*)p_record_1->fields[v_field_index].field;
            v_unsigned_long2 = *(unsigned long*)p_record_2->fields[v_field_index].field;
            v_result =
                v_unsigned_long1 > v_unsigned_long2 ? 1 :
                v_unsigned_long1 < v_unsigned_long2 ? -1 : 0;
            break;
        case __float:
            v_float1 = *(float*)p_record_1->fields[v_field_index].field;
            v_float2 = *(float*)p_record_2->fields[v_field_index].field;
            v_result = v_float1 > v_float2 ? 1 : v_float1 < v_float2 ? -1 : 0;
            break;
        case __double:
            v_double1 = *(double*)p_record_1->fields[v_field_index].field;
            v_double2 = *(double*)p_record_2->fields[v_field_index].field;
            v_result = v_double1 > v_double2 ? 1 : v_double1 < v_double2 ? -1 : 0;
            break;
        case __foreign_key:
            v_fk_record_1 = (__db_record_s_record*)p_record_1->fields[v_field_index].field;
            v_fk_record_2 = (__db_record_s_record*)p_record_2->fields[v_field_index].field;
            v_fk_table = (__db_table_s_table*)p_table->record_definition->
                         fields_definition[v_field_index].foreign_key_target;
            if(v_fk_table != NULL)
                v_result = db_table_compare_records(
                               v_fk_record_1,
                               v_fk_record_2,
                               v_fk_table,
                               0);
            break;
        }
    }
    return v_result;
}

void __sort_index(__db_table_s_table* p_table,
                  const __db_index_position p_index_position)
{
    long i, j;
    __db_record_s_record* v_record;
    for(i = (p_table->count - 1); i >= 0; i--)
        for(j = 1; j <= i; j++)
            if(db_table_compare_records
                    (p_table->indexes[p_index_position].index[j - 1],
                     p_table->indexes[p_index_position].index[j],
                     p_table,
                     p_index_position) > 0)
            {
                v_record = p_table->indexes[p_index_position].index[j - 1];
                p_table->indexes[p_index_position].index[j - 1] =
                    p_table->indexes[p_index_position].index[j];

                p_table->indexes[p_index_position].index[j] = v_record;
            }
}

void __disable_indexes(__db_table_s_table* p_table)
{
    int i;
    long l;

    for(i = 0; i < 32; i++)
        if(p_table->indexes[i].enabled)
        {
            p_table->indexes[i].index_rebuild_needed = 1;
            if(p_table->indexes[i].index != NULL)
            {
                free(p_table->indexes[i].index);
                p_table->indexes[i].index = NULL;
            }
        }
}

void __enable_index(__db_table_s_table* p_table,
                    const __db_index_position p_index_position)
{
    void* v_params[1];
    unsigned long l = 0;
    __db_record_s_record* v_record;
    if(p_table->indexes[p_index_position].enabled)
    {
        if(p_table->indexes[p_index_position].index != NULL)
            free(p_table->indexes[p_index_position].index);

        p_table->indexes[p_index_position].index = malloc(sizeof(__db_record_s_record*) * p_table->count);
        v_record = p_table->first_record;
        while(v_record!=NULL&&l<p_table->count)
        {
            p_table->indexes[p_index_position].index[l] = v_record;
            v_record = v_record->next_record;
            l++;
        }
        __sort_index(p_table, p_index_position);
    }
    p_table->indexes[p_index_position].index_rebuild_needed = 0;
}

void db_table_set_index(__db_table_s_table* p_table,
                        const __db_index_position p_position,
                        __db_index_s_index p_index)
{
    db_error_reset();
    if (p_position == 0)
        db_error_set_error(__PRIMARY_INDEX_REDEF);
    else
        p_table->indexes[p_position] = p_index;

}

void db_table_set_foreign_key(__db_table_s_table* p_table,
                              const __db_field_position p_field_position,
                              __db_table_s_table* p_foreign_table)
{
    db_error_reset();
    if(p_table->record_definition->fields_definition[p_field_position].
            data_type == __foreign_key)
    {
        p_table->record_definition->fields_definition[p_field_position].
        foreign_key_target = p_foreign_table;
        p_foreign_table->num_of_child_tables++;
        p_foreign_table->child_tables =
            realloc(p_foreign_table->child_tables,
                    sizeof(__db_table_s_table*)*p_foreign_table->num_of_child_tables);
        p_foreign_table->child_tables[p_foreign_table->num_of_child_tables-1] = p_table;
    }
    else
        db_error_set_error(__FIELD_IS_NOT_FOREIGN_KEY);

}

void db_table_drop(__db_table_s_table* p_table)
{
    long l = 0;
    int i;
    __db_record_s_record* v_record;
    __db_record_s_record* v_record_next;
    __disable_indexes(p_table);
    for(i = 0; i < 32; i++)
    {
        if(p_table->indexes[i].index_fields_definition != NULL)
            free(p_table->indexes[i].index_fields_definition);

    }
    if(p_table->indexes != NULL)
        free(p_table->indexes);

    if(p_table->child_tables != NULL)
        free(p_table->child_tables);

    v_record = p_table->first_record;
    while(v_record != NULL && l < p_table->count)
    {
        v_record_next = v_record->next_record;
        db_record_drop(v_record, p_table->record_definition);
        l++;
        v_record = v_record_next;
    }
    db_record_drop_definition(p_table->record_definition);
    free(p_table);
}

void db_table_drop_index(__db_table_s_table* p_table,
                         const __db_index_position p_index)
{
    db_error_reset();
    if (p_index == 0)
        db_error_set_error(__PRIMARY_INDEX_DELETE);
    else
    {
        free(p_table->indexes[p_index].index);
        p_table->indexes[p_index].index = NULL;
    }
}

unsigned char db_table_is_unique_field(__db_table_s_table* p_table,
                                       __db_field_position p_field_position)
{
    unsigned char v_ret = 0;
    int i, j;
    i=0;
    while(!v_ret && i < 32)
    {
        if((p_table->indexes[i].enabled) &&
                ((p_table->indexes[i].index_type == __primary) ||
                 (p_table->indexes[i].index_type == __unique)))
        {
            j=0;
            while(!v_ret && j < p_table->indexes[i].num_of_index_fields)
                if(p_table->indexes[i].index_fields_definition[j].
                        field_index == p_field_position)
                    v_ret = 1;
                else
                    j++;
        }
        i++;
    }
    return v_ret;
}

unsigned char db_table_is_fk_field(__db_table_s_table* p_table,
                                   __db_field_position p_field_position)
{
    unsigned char v_ret = 0;
    if(p_table->record_definition->fields_definition[p_field_position].
            data_type == __foreign_key)
        v_ret = 1;

    return v_ret;
}

unsigned char __unique_exists(__db_table_s_table* p_table,
                              __db_record_s_record* p_record)
{
    unsigned char v_result = 0;
    unsigned long l = 0;
    unsigned int i;
    __db_record_s_record* v_record;
    db_error_reset();
    v_record = p_table->first_record;
    while(v_record!=NULL && !v_result && l < p_table->count)
    {
        if(db_table_compare_records(p_record, v_record, p_table, 0)==0)
            v_result = 1;
        else
            for(i = 1; i < 32; i++)
                if(p_table->indexes[i].enabled && p_table->indexes[i].index_type == __unique)
                    if(db_table_compare_records(p_record, v_record, p_table, i)==0){
                        v_result = 1;
                        break;
                    }


        v_record = v_record->next_record;
        l++;
    }
    return v_result;
}

unsigned char __not_null_check(__db_table_s_table* p_table,
                               __db_field_s_field* p_fields)
{
    unsigned char v_ret = 1;
    int v_i;
    v_i = 0;
    while(v_i < p_table->record_definition->num_of_fields && v_ret)
    {
        if(p_table->record_definition->fields_definition[v_i].null_definition
                == __NOT_NULL)
        {
            if(p_fields[v_i].field == NULL)
                v_ret = 0;

        }
        v_i++;
    }
    return v_ret;
}

void db_table_drop_column(__db_table_s_table* p_table,
                          __db_field_position p_field_position)
{
    int i, j;
    __db_record_s_definition* new_record_definition;

    new_record_definition = db_record_create_definition(p_table->record_definition->num_of_fields - 1);
    for(i = 0; i < p_table->record_definition->num_of_fields; i++)
    {
        // Under construction
    }

    p_table->record_definition = new_record_definition;
    p_table->record_definition->num_of_fields--;

}

__db_record_s_record* db_table_insert_into(__db_table_s_table* p_table,
        __db_field_s_field* p_fields)
{
    __db_record_s_record* v_record = NULL;
    int v_i;
    db_error_reset();
    if(__not_null_check(p_table, p_fields))
    {
        v_record = db_record_create(p_table->last_record, NULL, p_fields);
        if(!__unique_exists(p_table, v_record))
        {
            p_table->count++;
            __disable_indexes(p_table);
            if(p_table->last_record!=NULL)
                p_table->last_record->next_record = v_record;

            p_table->last_record = v_record;
            if(p_table->first_record == NULL)
                p_table->first_record = v_record;

        }
        else
            db_error_set_error(__UNIQUE_VIOLATION);
    }
    else
        db_error_set_error(__EMPTY_MANDATORY_FIELD);

    return v_record;
}

__db_record_s_record* db_table_insert_structure_into(__db_table_s_table* p_table,
        void* p_structure)
{
    __db_record_s_record* v_record = NULL;
    __db_field_s_field* v_fields;
    v_fields = db_field_create(1);
    db_field_set_value(
        p_table->record_definition->fields_definition ,
        v_fields,
        0,
        p_structure);
    v_record = db_table_insert_into(p_table, v_fields);
    return v_record;
}

void db_table_delete_child_records(__db_table_s_table* p_table,
                                   __db_record_s_record* p_record)
{
    int i;
    __db_field_position v_i_fk;
    __db_index_record_position j, l;
    __db_record_s_record* v_child_record;
    __db_table_s_table* v_child_table;

    for(i=0; i < p_table->num_of_child_tables; i++)
    {
        v_child_table = p_table->child_tables[i];
        for(v_i_fk=0; v_i_fk < v_child_table->record_definition->num_of_fields; v_i_fk++)
            if(v_child_table->record_definition->fields_definition[v_i_fk].data_type == __foreign_key &&
                    v_child_table->record_definition->fields_definition[v_i_fk].foreign_key_target == p_table)
            {
                l = 0;
                v_child_record = v_child_table->first_record;
                while(v_child_record!=NULL && l < v_child_table->count)
                {
                    if(v_child_record->fields[v_i_fk].field == p_record)
                        db_table_delete_record(v_child_table, v_child_record);

                    v_child_record = v_child_record->next_record;
                    l++;
                }
            }
    }
}

void db_table_delete_record(__db_table_s_table* p_table,
                            __db_record_s_record* p_record)
{
    db_table_delete_child_records(p_table, p_record);
    if(p_table->count==1)
    {
        p_table->first_record = NULL;
        p_table->last_record = NULL;
    }
    else
    {
        if(p_table->first_record == p_record)
        {
            p_table->first_record = p_record->next_record;
            p_record->next_record->prev_record = NULL;
        }
        else if(p_table->last_record == p_record)
        {
            p_table->last_record = p_record->prev_record;
            p_record->prev_record->next_record = NULL;
        }
        else
        {
            p_record->next_record->prev_record = p_record->prev_record;
            p_record->prev_record->next_record = p_record->next_record;
        }
    }
    db_record_drop(p_record, p_table->record_definition);
    p_table->count--;
    __disable_indexes(p_table);
}

void db_table_delete_from(__db_table_s_table* p_table,
                          const __db_index_position p_index,
                          const __db_index_record_position p_position)
{
    __db_record_s_record* v_se = db_table_get_record(p_table, p_index, p_position);
    db_error_reset();
    db_table_delete_record(p_table, v_se);
}

__db_record_s_record* db_table_get_record(__db_table_s_table* p_table,
        const __db_index_position p_index_position,
        const __db_index_record_position p_position)
{
    __db_record_s_record* v_result = NULL;
    __db_index_index v_index;
    db_error_reset();
    if (p_table->indexes[p_index_position].index_rebuild_needed != 0)
        __enable_index(p_table, p_index_position);

    v_index = p_table->indexes[p_index_position].index;
    v_result = v_index[p_position];

    return v_result;
}

