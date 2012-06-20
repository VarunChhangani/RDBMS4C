/*
    blogcprog.com - therm_events
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

#ifndef THERM_EVENTS_H_INCLUDED
#define THERM_EVENTS_H_INCLUDED

#include "../../src/db.h"

#define THERM_EVENTS_id 0
#define THERM_EVENTS_event_type_fk 1

typedef struct __therm_event_ss {
    unsigned long id;
    __db_record event_type_fk;

} __therm_event_s;


void therm_event_constructor();
void therm_event_desctructor();

void therm_event_insert(__therm_event_s* therm_event);

__db_record therm_event_find(unsigned char id);

void therm_event_clear(__therm_event_s* therm_event);

__db_cursor therm_events_new_cursor();

long therm_events_count();


#endif
