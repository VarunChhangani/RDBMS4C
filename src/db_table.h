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

#ifndef __DB_TABLE__
#define __DB_TABLE__

#include "db_general.h"
#include "db_error.h"
#include "db_field.h"
#include "db_index.h"
#include "db_record.h"

typedef struct __db_table_ss_table
{
    __db_general_name name;
    __db_record_s_record* first_record;
    __db_record_s_record* last_record;
    __db_record_s_definition* record_definition;
    __db_index_s_index* indexes;
    __db_index_record_position count;
    struct __db_table_ss_table** child_tables;
    int num_of_child_tables;
} __db_table_s_table;


__db_table_s_table* db_table_create(__db_record_s_definition* p_record_definition,
                                    __db_index_s_index p_primary_index);

__db_table_s_table* db_table_create_for_structure(void);

signed char db_table_compare_records(const __db_record_s_record* p_record_1,
                                     const __db_record_s_record* p_record_2,
                                     __db_table_s_table* p_table,
                                     const __db_index_position p_index_position);

void db_table_set_index(__db_table_s_table* p_table,
                        const __db_index_position p_position,
                        __db_index_s_index p_index);

void db_table_set_foreign_key(__db_table_s_table* p_table,
                              const __db_field_position p_field_position,
                              __db_table_s_table* p_foreign_table);

void db_table_drop(__db_table_s_table* p_table);

unsigned char db_table_is_unique_field(__db_table_s_table* p_table,
                                       __db_field_position p_field_position);

unsigned char db_table_is_fk_field(__db_table_s_table* p_table,
                                   __db_field_position p_field_position);

void db_table_drop_column(__db_table_s_table* p_table,
                          __db_field_position p_field_position);

__db_record_s_record* db_table_insert_into(__db_table_s_table* p_table,
        __db_field_s_field* p_fields);

__db_record_s_record* db_table_insert_structure_into(__db_table_s_table* p_table,
        void* p_structure);

void db_table_delete_from(__db_table_s_table* p_table,
                          const __db_index_position p_index,
                          const __db_index_record_position p_position);

__db_record_s_record* db_table_get_record(__db_table_s_table* p_table,
        const __db_index_position p_index_position,
        const __db_index_record_position p_position);

#endif
