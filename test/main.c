/*
    blogcprog.com - How to use the blogcprog.com C functions
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

#include "../src/db.h"
#include "../src/db_string.h"
#include "therm_event_types.h"
#include "therm_events.h"


__db_record_definition v_folder_rdef;
__db_field v_folder_fld;
__db_primary_key v_folder_pk;
__db_index v_folder_idx2;
__db_table v_folder_tab;
__db_cursor v_folder_cur1;
__db_record v_folder_rec;


__db_record_definition v_file_rdef;
__db_field v_file_fld;
__db_primary_key v_file_pk;
__db_index v_file_idx2;
__db_table v_file_tab;
__db_cursor v_file_cur1;
__db_cursor v_file_cur2;
__db_key v_file_key;
__db_record v_file_rec;

__therm_event_type_s therm_event_type;
__therm_event_s therm_event;

__db_cursor cursor;
__db_record record;

unsigned int v_exit = 0;

void timer_2s(void)
{
    printf("Timer 2 s\n");
}

void timer_10s(void)
{
    printf("Timer 10 s\n");
    v_exit = 1;
}

void ins_folder(unsigned int p_id, char* p_path)
{
    unsigned int *v_ui;
    v_ui = malloc(sizeof(unsigned int));
    *v_ui = p_id;

    v_folder_fld = db_insert_preparation(2);

    db_insert_set_field(v_folder_rdef, v_folder_fld, 0, v_ui);
    db_insert_set_field(v_folder_rdef, v_folder_fld, 1, p_path);
    db_insert_into(v_folder_cur1, v_folder_fld);

    free(v_ui);
}

void ins_file(unsigned int p_id, char* p_name, char* p_extension)
{
    unsigned int *v_ui;
    v_ui = malloc(sizeof(unsigned int));
    *v_ui = p_id;

    v_file_fld = db_insert_preparation(4);

    db_insert_set_field(v_file_rdef, v_file_fld, 0, v_ui);
    db_insert_set_field(v_file_rdef, v_file_fld, 1, db_cursor_current(v_folder_cur1));
    db_insert_set_field(v_file_rdef, v_file_fld, 2, p_name);
    db_insert_set_field(v_file_rdef, v_file_fld, 3, p_extension);
    db_insert_into(v_file_cur1, v_file_fld);

    free(v_ui);
}

int main(int argc, char *argv[])
{
    volatile int i;
    unsigned int *v_ui;
    __db_string v_string;
    __db_string v_s1, v_s2;
    int timer;
    int timer2;

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

    printf("DB examles\n");

    v_folder_rdef = db_create_record_definition(2);
    db_set_record_definition_field(v_folder_rdef, 0, "id", __NOT_NULL, __unsigned_int);
    db_set_record_definition_field(v_folder_rdef, 1, "path", __NOT_NULL, __char_array);

    v_folder_pk = db_create_pk(1);

    db_set_index_field(v_folder_pk, 0, 0, __asc);

    v_folder_tab = db_create_table(v_folder_rdef, v_folder_pk);

    v_file_rdef = db_create_record_definition(4);
    db_set_record_definition_field(v_file_rdef, 0, "id", __NOT_NULL, __unsigned_int);
    db_set_record_definition_field(v_file_rdef, 1, "folder", __NOT_NULL, __foreign_key);
    db_set_record_definition_field(v_file_rdef, 2, "name", __NOT_NULL, __char_array);
    db_set_record_definition_field(v_file_rdef, 3, "extension", __NOT_NULL, __char_array);

    v_file_pk = db_create_pk(1);

    db_set_index_field(v_file_pk, 0, 0, __asc);

    v_file_tab = db_create_table(v_file_rdef, v_file_pk);

    v_folder_idx2 = db_create_index(1, __normal);
    db_set_index_field(v_folder_idx2, 0, 1, __asc);
    db_set_table_index(v_folder_tab, 1, v_folder_idx2);

    v_file_idx2 = db_create_index(1, __normal);
    db_set_index_field(v_file_idx2, 0, 1, __asc);
    db_set_table_index(v_file_tab, 1, v_file_idx2);

    db_set_foreign_key_table(v_file_tab, 1, v_folder_tab);

    v_folder_cur1 = db_create_cursor(v_folder_tab, 0);
    v_file_cur1 = db_create_cursor(v_file_tab, 1);

    ins_folder(105, "c:\\proj\\sources\\");
    ins_folder(103, "c:\\proj\\inc\\");
    ins_folder(102, "c:\\proj\\doc22\\");

    ins_folder(104, "c:\\proj\\lib\\");
    /* Key violation test */
    ins_folder(104, "c:\\proj\\lib\\");

    ins_folder(101, "c:\\proj\\txt1\\");
    ins_folder(106, "c:\\proj\\lic\\");
    ins_folder(100, "c:\\proj\\bin\\");


    db_cursor_first(v_folder_cur1);
    ins_file(1, "util","h");
    ins_file(2, "main2","c");

    db_cursor_next(v_folder_cur1);
    ins_file(3, "main3","c");
    ins_file(4, "main4","c");

    db_cursor_next(v_folder_cur1);
    ins_file(5, "main5","c");
    ins_file(6, "main6","c");
    ins_file(7, "main7","c");

    db_cursor_next(v_folder_cur1);
    ins_file(8, "main8","c");
    ins_file(9, "main9","c");
    ins_file(10, "main10","c");

    printf("%s\n", "Loop on Folders:");
    __for_cursor_loop(v_folder_rec, v_folder_cur1)
    printf("%i -  %s\n",
           db_get_field_as_unsigned_int(v_folder_rec, 0),
           db_get_field_as_char_array(v_folder_rec, 1));
    __end_loop(v_folder_rec, v_folder_cur1)

    printf("\n%s\n", "Loop on Files with path:");

    __for_cursor_loop(v_file_rec, v_file_cur1)

    printf("%i -  %s %s.%s\n",
           db_get_field_as_unsigned_int(v_file_rec, 0),
           db_get_field_as_char_array(db_get_field_as_foreign_key_record(v_file_rec, 1) , 1),
           db_get_field_as_char_array(v_file_rec, 2),
           db_get_field_as_char_array(v_file_rec, 3));

    __end_loop(v_file_rec, v_file_cur1)

    printf("\nFind a record by key\n");
    v_file_cur2 = db_create_cursor(v_file_tab, 0);
    v_ui = malloc(sizeof(unsigned int));
    *v_ui = 2;

    v_file_key = db_create_key(v_file_cur2);
    db_set_key_field(v_file_key, 0, v_ui);
    v_file_rec = db_find_by_key(v_file_key);

    if(v_file_rec != NULL)
    {
        printf(" %i -  %s %s.%s\n\n",
               db_get_field_as_unsigned_int(v_file_rec, 0),
               db_get_field_as_char_array(db_get_field_as_foreign_key_record(v_file_rec, 1) , 1),
               db_get_field_as_char_array(v_file_rec, 2),
               db_get_field_as_char_array(v_file_rec, 3));
    }

    db_drop_cursor(v_folder_cur1);
    db_drop_table(v_folder_tab);

    db_drop_key(v_file_key);
    db_drop_cursor(v_file_cur1);
    db_drop_table(v_file_tab);

    timer = create_timer(1, 2000, timer_2s);
    timer2 = create_timer(1, 10000, timer_10s);

    while(!v_exit)
    {
        timer_listener();
    }

    drop_timer(timer);

    therm_event_types_constructor();
    therm_events_constructor();

    therm_event_type.id = 1;
    therm_event_type.name = db_string_create("WIND_UP");
    therm_event_type_insert(&therm_event_type);
    therm_event_type.id = 2;
    therm_event_type.name = db_string_create("WIND_DOWN");
    therm_event_type_insert(&therm_event_type);

    cursor = therm_event_types_new_cursor();
    __for_cursor_loop(record, cursor)
    printf("Evnt type: %i -  %s\n",
           db_get_field_as_unsigned_long(record, THERM_EVENT_TYPES_id),
           db_get_field_as_char_array(record, THERM_EVENT_TYPES_name)
          );
    __end_loop(record, cursor)

    db_drop_cursor(cursor);

    therm_event.id = 1;
    therm_event.event_type_fk = therm_event_type_find(1);
    therm_event_insert(&therm_event);

    therm_event.id = 2;
    therm_event.event_type_fk = therm_event_type_find(1);
    therm_event_insert(&therm_event);

    cursor = therm_events_new_cursor();

    __for_cursor_loop(record, cursor)
    printf("Evnts: %i - %s \n",
           db_get_field_as_unsigned_long(record, THERM_EVENTS_id),
           db_get_field_as_char_array(
               db_get_field_as_foreign_key_record(
                   record, THERM_EVENTS_event_type_fk
               ),
               THERM_EVENT_TYPES_name)
          );
    __end_loop(record, cursor)

    db_drop_cursor(cursor);

    therm_events_desctructor();
    therm_event_types_desctructor();

    return 0;
}
