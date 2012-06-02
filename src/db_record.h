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

#ifndef __DB_RECORD__
#define __DB_RECORD__

#include "db_general.h"
#include "db_field.h"

typedef struct __db_record_ss_definition
{
    __db_field_s_field_definition* fields_definition;
    int num_of_fields;
} __db_record_s_definition;

typedef struct __db_record_ss_record
{
    __db_field_s_field* fields;
    struct __db_record_ss_record *prev_record;
    struct __db_record_ss_record *next_record;
} __db_record_s_record;

__db_record_s_definition* db_record_create_definition(int p_num_of_fields);

void db_record_set_definition_field(__db_record_s_definition* p_record_definition,
                                    int p_position,
                                    __db_general_name p_name,
                                    __db_field_NULL_definition p_NULL_definition,
                                    __db_field_data_type p_data_type);

__db_record_s_record* db_record_create(__db_record_s_record* p_prev_record,
                                       __db_record_s_record* p_next_record,
                                       __db_field_s_field* p_fields);

void db_record_drop(__db_record_s_record* p_record,
                    __db_record_s_definition* p_record_definition);

void db_record_drop_definition(__db_record_s_definition* p_record_definition);

#endif
