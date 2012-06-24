/*
    rdbms4c.org - How to use RDBMS4C
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
#include <math.h>

#include "../src/db.h"
#include "database/therm_event_types.h"
#include "database/therm_events.h"

__therm_event_type_s therm_event_type;
__therm_event_s therm_event;

__db_cursor cursor;
__db_record record;

void timer_2s(int pid)
{
    int i;
    int event_type_id;
    printf("\nTimer: %i\n", pid);
    printf("Creating event... num of rec: %i\n", therm_events_count());
    for(i=0; i<10000; i++)
    {
        event_type_id = i%3 == 0 ? 1 : 2;
        therm_event.event_type_fk = therm_event_type_find(event_type_id);
        therm_event_insert(&therm_event);
    }

    printf("Find event... ");
    cursor = therm_event_find( llround (therm_events_count()/2 ));
    printf("Find event2... ");
    cursor = therm_event_find( llround (therm_events_count()/2 ));
    printf("Done.\n");
}

void timer_60s(int pid)
{
    printf("Timer: %i\n", pid);
    printf("Reporting events in insert order...\n");

    cursor = therm_events_new_cursor();
    __for_cursor_loop(record, cursor)
        printf("Evnts: %i - %s \n",
           get_THERM_EVENTS_id(record),
           get_THERM_EVENT_TYPES_name(
               get_THERM_EVENTS_event_type_fk(record))
          );
    __end_loop(record, cursor)

    db_drop_cursor(cursor);


    printf("\nReporting events in event_type order...\n");

    cursor = db_create_cursor(get_therm_events_table(), THERM_EVENTS_event_type_fk_idx);
    __for_cursor_loop(record, cursor)
        printf("Evnt type: %i - %s, Event: %i \n",
           get_THERM_EVENT_TYPES_id(
               get_THERM_EVENTS_event_type_fk(record)),
           get_THERM_EVENT_TYPES_name(
               get_THERM_EVENTS_event_type_fk(record)),
           get_THERM_EVENTS_id(record)
          );
    __end_loop(record, cursor)

    db_drop_cursor(cursor);

    printf("Done.\n\n");
}

void timer_10m(int pid)
{
    printf("Timer: %i\n", pid);
    printf("Timer 10 m\n");
    timer_pool_exit();
}

int main(int argc, char *argv[])
{
    volatile int i;
    unsigned int *v_ui;
    __db_string v_string;
    __db_string v_s1, v_s2;
    int timer;
    int timer2;
    int timer10m;

    printf("String examles\n");

    v_string = db_string_create("**Long string example*");
    printf("%s\n\n", v_string->str);

    db_string_s_trim(v_string, '*');
    printf("After trim * : %s\n\n", v_string->str);

    v_s1 = db_string_create("e");
    v_s2 = db_string_create("E");

    db_string_s_replace(v_string, v_s1, v_s2);
    printf("Replace * : %s\n\n", v_string->str);

    db_string_drop(v_s1);
    db_string_drop(v_s2);

    db_string_s_substr(v_string, 5, 6);
    printf("After substring: %s\n\n", v_string->str);

    db_string_s_lpad(v_string, 100, 33);
    printf("After lpad: %s\n\n", v_string->str);

    db_string_s_concat(v_string, " Hello");
    printf("After concat: %s\n\n", v_string->str);

    db_string_s_trim(v_string, ' ');
    v_s1 = db_string_create("string");
    if(db_string_begins_with(v_string, v_s1))
    {
        printf("Begins with string\n\n");
    }
    db_string_drop(v_s1);
    db_string_drop(v_string);

    printf("Creating database...\n");

    therm_event_types_constructor();
    therm_events_constructor();
    printf("Done.\n\n");

    printf("Creating event types...\n");

    therm_event_type.id = 1;
    therm_event_type.name = db_string_create("WIND_UP");
    therm_event_type_insert(&therm_event_type);

    therm_event_type.id = 2;
    therm_event_type.name = db_string_create("WIND_DOWN");
    therm_event_type_insert(&therm_event_type);

    printf("Done.\n\n");

    printf("Reporting event types...\n");

    cursor = therm_event_types_new_cursor();
    __for_cursor_loop(record, cursor)
        printf("Evnt type: %i -  %s\n",
           get_THERM_EVENT_TYPES_id(record),
           get_THERM_EVENT_TYPES_name(record)
          );
    __end_loop(record, cursor)

    db_drop_cursor(cursor);
    printf("Done.\n\n");

    printf("Starting timer pool...\n");

    timer = create_timer(1, 2000, timer_2s);
    timer2 = create_timer(2, 60000, timer_60s);
    timer10m = create_timer(3, 1000*60*60, timer_10m);

    timer_pool();

    drop_timer(timer);
    drop_timer(timer2);
    drop_timer(timer10m);

    printf("Droping database...\n");
    therm_events_desctructor();
    therm_event_types_desctructor();

    printf("Done.\n\n");

    return 0;
}
