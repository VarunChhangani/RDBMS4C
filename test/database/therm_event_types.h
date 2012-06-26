/*
    rdbms4c.org - therm_event_types
    Copyright (C) 2012  blogcprog.com
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

#ifndef THERM_EVENT_TYPES_H_INCLUDED
#define THERM_EVENT_TYPES_H_INCLUDED

#include "../../src/db.h"

#define THERM_EVENT_TYPES_id 0
#define THERM_EVENT_TYPES_name 1

#define get_THERM_EVENT_TYPES_id(p_record) db_get_field_as_unsigned_char(p_record, THERM_EVENT_TYPES_id)
#define get_THERM_EVENT_TYPES_name(p_record) db_get_field_as_char_array(p_record, THERM_EVENT_TYPES_name)

typedef struct __therm_event_type_ss {
    unsigned char id;
    __db_string name;
} __therm_event_type_s;


void therm_event_types_constructor();
void therm_event_types_desctructor();

__db_cursor therm_event_type_insert(__therm_event_type_s* therm_event_type);

__db_cursor therm_event_type_find(unsigned char id);

void therm_event_type_clear(__therm_event_type_s* therm_event_type);

__db_cursor therm_event_types_new_cursor();

__db_table therm_event_type_foreign_key_parent();

long therm_event_types_count();

#endif
