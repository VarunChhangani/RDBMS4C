/*
    rdbms4c.org - therm_events
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

#include "therm_events.h"
#include "../../src/db_implement.h"
#include "therm_event_types.h"

void therm_events_constructor()
{
    __db_primary_key primary_key;
    __db_index event_type_index;
    record_definition = db_create_record_definition(2);
    db_set_record_definition_field(record_definition, THERM_EVENTS_id, "id", __NOT_NULL, __unsigned_long);
    db_set_record_definition_field(record_definition, THERM_EVENTS_event_type_fk, "event_type_fk", __NOT_NULL, __foreign_key);

    primary_key = db_create_pk(1);
    db_set_index_field(primary_key, THERM_EVENTS_id, PRIMARY_KEY, __asc);

    table = db_create_table(record_definition, primary_key);

    db_set_foreign_key_table(table, THERM_EVENTS_event_type_fk, therm_event_type_foreign_key_parent());

    db_table_auto_increment(table);

    event_type_index = db_create_index(1, __normal);
    db_set_index_field(event_type_index, 0, THERM_EVENTS_event_type_fk, __asc);
    db_table_set_index(table, THERM_EVENTS_event_type_fk_idx, event_type_index);

    cursor = db_create_cursor(table, PRIMARY_KEY);
}

void therm_events_desctructor()
{
    db_drop_cursor(cursor);
    db_drop_table(table);
}

__db_cursor therm_event_insert(__therm_event_s* therm_event)
{
    __db_field db_field = db_insert_preparation(record_definition->num_of_fields);
    therm_event->id = 0;
    db_insert_set_field(cursor, db_field, THERM_EVENTS_id, &therm_event->id);
    db_insert_set_field_fk(cursor, db_field, THERM_EVENTS_event_type_fk, therm_event->event_type_fk);

    db_insert_into(cursor, db_field);
    therm_event_clear(therm_event);
    return cursor;
}

__db_cursor therm_event_find(unsigned char id)
{
    __db_key key = db_create_key(cursor);
    db_set_key_field(key, THERM_EVENTS_id, &id);
    db_find_by_key(key);
    db_drop_key(key);
    return cursor;
}

void therm_event_clear(__therm_event_s* therm_event)
{
    therm_event->id = 0;

}

__db_cursor therm_events_new_cursor()
{
    return db_create_cursor(table, PRIMARY_KEY);
}

long therm_events_count()
{
    return table->count;
}

__db_table get_therm_events_table()
{
    return table;
}
