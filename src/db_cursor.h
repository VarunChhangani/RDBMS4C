/*
    rdbms4c.org - db_cursor
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

#ifndef __DB_CURSOR__
#define __DB_CURSOR__

#include "db.h"

typedef unsigned char __db_cursor_for_function(__db_table_s_table* p_table,
        __db_record_s_record* p_record,
        void* p_args[],
        long p_rownum);

typedef __db_cursor_for_function* __db_cursor_p_for_function;

typedef struct __db_cursor_ss_cursor
{
    __db_table_s_table* table;
    __db_index_position index_position;
    __db_index_record_position current;
    __db_record_s_record* buffer;
} __db_cursor_s_cursor;

typedef struct __db_cursor_ss_key
{
    __db_cursor_s_cursor* cursor;
    __db_field_s_field* fields;
} __db_cursor_s_key;

__db_cursor_s_cursor* db_cursor_create(__db_table_s_table* p_table,
                                       const __db_index_position p_index_position);

void db_cursor_drop(__db_cursor_s_cursor* p_cursor);

__db_record_s_record* db_cursor_current(__db_cursor_s_cursor* p_cursor);

__db_record_s_record* db_cursor_next(__db_cursor_s_cursor* p_cursor);

__db_record_s_record* db_cursor_prev(__db_cursor_s_cursor* p_cursor);

__db_record_s_record* db_cursor_first(__db_cursor_s_cursor* p_cursor);

__db_record_s_record* db_cursor_last(__db_cursor_s_cursor* p_cursor);

unsigned char db_cursor_for_all(__db_cursor_s_cursor* p_cursor,
                                __db_cursor_p_for_function p_cursor_for_function,
                                void* p_args[]);

__db_cursor_s_key* db_cursor_create_key(__db_cursor_s_cursor* p_cursor);

void db_cursor_drop_key(__db_cursor_s_key* p_key);

void db_cursor_set_key_fields(__db_cursor_s_key* p_key,
                              const __db_field_position p_field_position,
                              const void* p_value);

__db_record_s_record* db_cursor_find_by_key(__db_cursor_s_key* p_key);

void db_cursor_update_field(__db_cursor_s_cursor* p_cursor,
                            __db_field_s_field* p_fields,
                            __db_field_position p_field_position,
                            void* p_value);

void db_cursor_update_field_fk(__db_cursor_s_cursor* p_cursor,
                               __db_field_s_field* p_fields,
                               __db_field_position p_field_position,
                               __db_cursor_s_cursor* p_foreign_cursor);

__db_cursor_s_cursor* db_cursor_insert(__db_cursor_s_cursor* p_cursor,
                                       __db_field_s_field* p_fields);

void db_cursor_update(__db_cursor_s_cursor* p_cursor,
                      __db_field_position p_field_position,
                      void* p_value);

void db_cursor_update_fk(__db_cursor_s_cursor* p_cursor,
                         __db_field_position p_field_position,
                         __db_cursor_s_cursor* p_foreign_cursor);

void db_cursor_delete(__db_cursor_s_cursor* p_cursor);

#endif
