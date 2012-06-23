/*
    rdbms4c.org - DB
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

#ifndef __DB__
#define __DB__

#include "db_general.h"
#include "db_error.h"
#include "db_field.h"
#include "db_index.h"
#include "db_record.h"
#include "db_table.h"
#include "db_cursor.h"

#include "db_string.h"
#include "db_timer.h"

#define __db_record_definition __db_record_s_definition*
#define __db_record __db_record_s_record*
#define __db_field __db_field_s_field*
#define __db_primary_key __db_index_s_index
#define __db_index __db_index_s_index
#define __db_table __db_table_s_table*
#define __db_cursor __db_cursor_s_cursor*
#define __db_key __db_cursor_s_key*

#define db_create_record_definition(p_num_of_fld) db_record_create_definition(p_num_of_fld)
#define db_set_record_definition_field(p_rec_def, p_fld_idx, p_fld_name, p_null_def, p_data_type) \
    db_record_set_definition_field(p_rec_def, p_fld_idx, p_fld_name, p_null_def, p_data_type)

#define db_create_pk(p_num_of_fld) db_index_create(p_num_of_fld, __primary, NULL)

#define db_set_index_field(p_idx_fld_def, p_pos, p_idx_fld_pos, p_sort_typ) \
    db_index_set_field_definition(p_idx_fld_def.index_fields_definition, \
        p_pos, p_idx_fld_pos, p_sort_typ)

#define db_create_table(p_rec_def, p_pk) db_table_create(p_rec_def, p_pk)

#define db_set_foreign_key_table(p_tab, p_fld_pos, p_fk_tab)\
    db_table_set_foreign_key(p_tab, p_fld_pos, p_fk_tab);

#define db_create_index(p_num_of_fld, p_idx_typ) db_index_create(p_num_of_fld, p_idx_typ, NULL)
#define db_create_function_based_index(p_idx_typ, p_f) db_index_create(0, p_idx_typ, p_f)
#define db_set_table_index(p_tab, p_pos, p_idx) db_table_set_index(p_tab, p_pos, p_idx)

#define db_create_cursor(p_tab, p_idx) db_cursor_create(p_tab, p_idx)
#define db_create_key(p_cur) db_cursor_create_key(p_cur)
#define db_set_key_field(p_key, p_pos, p_val) db_cursor_set_key_fields(p_key, p_pos, p_val)
#define db_find_by_key(p_key) db_cursor_find_by_key(p_key)

#define db_insert_preparation(p_num_of_fld) db_field_create(p_num_of_fld)

#define db_insert_set_field(p_cur, p_fld, p_idx, p_val) \
            db_cursor_update_field(p_cur, p_fld, p_idx, p_val)

#define db_insert_set_field_fk(p_cur, p_fld, p_idx, p_cur_par) \
            db_cursor_update_field_fk(p_cur, p_fld, p_idx, p_cur_par)

#define db_insert_into(p_cur, p_fld) db_cursor_insert(p_cur, p_fld)

#define db_update(p_cur, p_fld_pos, p_val) db_cursor_update(p_cur, p_fld_pos, p_val)
#define db_update_foreign_key(p_cur, p_fld_pos, p_fk_cur) db_cursor_update_fk(p_cur, p_fld_pos, p_fk_cur)

#define db_get_field_as_char(p_rec, p_pos) db_field_get_char(p_rec->fields, p_pos)
#define db_get_field_as_unsigned_char(p_rec, p_pos) db_field_get_unsigned_char(p_rec->fields, p_pos)
#define db_get_field_as_int(p_rec, p_pos) db_field_get_int(p_rec->fields, p_pos)
#define db_get_field_as_unsigned_int(p_rec, p_pos) db_field_get_unsigned_int(p_rec->fields, p_pos)
#define db_get_field_as_long(p_rec, p_pos) db_field_get_long(p_rec->fields, p_pos)
#define db_get_field_as_unsigned_long(p_rec, p_pos) db_field_get_unsigned_long(p_rec->fields, p_pos)
#define db_get_field_as_float(p_rec, p_pos) db_field_get_float(p_rec->fields, p_pos)
#define db_get_field_as_double(p_rec, p_pos) db_field_get_double(p_rec->fields, p_pos)
#define db_get_field_as_void(p_rec, p_pos) db_field_get_void(p_rec->fields, p_pos)
#define db_get_field_as_char_array(p_rec, p_pos) db_field_get_char_array(p_rec->fields, p_pos)
#define db_get_field_as_foreign_key_record(p_rec, p_pos) ((__db_record_s_record*)db_field_get_void(p_rec->fields, p_pos))

#define db_drop_key(p_key) db_cursor_drop_key(p_key)
#define db_drop_cursor(p_cur) db_cursor_drop(p_cur)
#define db_drop_table(p_tab) db_table_drop(p_tab)

#define __for_cursor_loop(p_rec, p_cur) p_rec = db_cursor_first(p_cur);\
                         if(p_rec != NULL)do {


#define __end_loop(p_rec, p_cur)\
                    } while ((p_rec = db_cursor_next(p_cur)) != NULL);

#endif

