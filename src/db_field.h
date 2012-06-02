/*
    blogcprog.com - db_field
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

#ifndef __DB_FIELD__
#define __DB_FIELD__

#include <stdlib.h>

#include "db_general.h"
#include "db_error.h"

typedef enum {__NULL = 0, __NOT_NULL = 1} __db_field_NULL_definition;

typedef enum {__char = 0,
              __unsigned_char = 1,
              __int = 2,
              __unsigned_int = 3,
              __long = 4,
              __unsigned_long = 5,
              __float = 6,
              __double = 7,
              __void_pointer = 8,
              __char_array = 9,
              __foreign_key = 100
             } __db_field_data_type;

typedef unsigned char __db_field_position;

typedef struct __db_field_ss_field_definition
{
    __db_general_name name;
    __db_field_data_type data_type;
    __db_field_NULL_definition null_definition;
    void* foreign_key_target;
} __db_field_s_field_definition;

typedef struct __db_field_ss_field
{
    void* field;
} __db_field_s_field;

__db_field_s_field* db_field_create(int p_num_of_fields);

void db_field_drop(__db_field_s_field* p_fields,
                   int p_num_of_fields);

void db_field_set_value(__db_field_s_field_definition* p_fields_definition,
                        __db_field_s_field* p_fields,
                        const __db_field_position p_position,
                        const void* p_value);

const char db_field_get_char(__db_field_s_field* p_fields,
                             const __db_field_position p_position);

const unsigned char db_field_get_unsigned_char(__db_field_s_field* p_fields,
        const __db_field_position p_position);

const int db_field_get_int(__db_field_s_field* p_fields,
                           const __db_field_position p_position);

const unsigned int db_field_get_unsigned_int(__db_field_s_field* p_fields,
        const __db_field_position p_position);

const long db_field_get_long(__db_field_s_field* p_fields,
                             const __db_field_position p_position);

const unsigned long db_field_get_unsigned_long(__db_field_s_field* p_fields,
        const __db_field_position p_position);

const float db_field_get_float(__db_field_s_field* p_fields,
                               const __db_field_position p_position);

const double db_field_get_double(__db_field_s_field* p_fields,
                                 const __db_field_position p_position);

const void* db_field_get_void(__db_field_s_field* p_fields,
                              const __db_field_position p_position);

const char* db_field_get_char_array(__db_field_s_field* p_fields,
                                    const __db_field_position p_position);


#endif
