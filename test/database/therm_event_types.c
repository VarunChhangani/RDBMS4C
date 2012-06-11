/*
    blogcprog.com - therm_event_types
    Copyright (C) 2012  blogcprog.com

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

#include "therm_event_types.h"
#include "../../src/db_implement.h"

void record_to_therm_event_type(__db_record record, __therm_event_type_s* therm_event_type);

void therm_event_types_constructor()
{
    __db_primary_key primary_key;
    record_definition = db_create_record_definition(2);
    db_set_record_definition_field(record_definition, THERM_EVENT_TYPES_id, "id", __NOT_NULL, __unsigned_char);
    db_set_record_definition_field(record_definition, THERM_EVENT_TYPES_name, "name", __NOT_NULL, __char_array);

    primary_key = db_create_pk(1);
    db_set_index_field(primary_key, THERM_EVENT_TYPES_id, PRIMARY_KEY, __asc);

    table = db_create_table(record_definition, primary_key);

    cursor = db_create_cursor(table, PRIMARY_KEY);
}

void therm_event_types_desctructor()
{
    db_drop_cursor(cursor);
    db_drop_table(table);
}

void therm_event_type_insert(__therm_event_type_s* therm_event_type)
{
    __db_field db_field = db_insert_preparation(2);
    db_insert_set_field(record_definition, db_field, THERM_EVENT_TYPES_id, &therm_event_type->id);
    db_insert_set_field(record_definition, db_field, THERM_EVENT_TYPES_name, therm_event_type->name->str);
    db_insert_into(cursor, db_field);
    therm_event_type_clear(therm_event_type);
}

__db_record therm_event_type_find(unsigned char id)
{
    __db_record rec;
    __db_key key = db_create_key(cursor);
    db_set_key_field(key, THERM_EVENT_TYPES_id, &id);
    rec = db_find_by_key(key);
    db_drop_key(key);
    return rec;
}

void therm_event_type_clear(__therm_event_type_s* therm_event_type)
{
    therm_event_type->id = 0;
    db_string_drop(therm_event_type->name);
    therm_event_type->name = NULL;
}

__db_cursor therm_event_types_new_cursor()
{
    return db_create_cursor(table, PRIMARY_KEY);
}
