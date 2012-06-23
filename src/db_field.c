/*
    rdbms4c.org - db_field
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

#include "db_field.h"

__db_field_s_field* db_field_create(int p_num_of_fields)
{
    int i;
    __db_field_s_field* v_result = malloc(sizeof(__db_field_s_field) * p_num_of_fields);
    for(i = 0; i < p_num_of_fields; i++)
        v_result[i].field = NULL;
    return v_result;
}

void db_field_drop(__db_field_s_field* p_fields,
                   int p_num_of_fields)
{
    int i;

    for(i = 0; i < p_num_of_fields; i++)
        if(p_fields[i].field != NULL)
            free(p_fields[i].field);
    free(p_fields);
}

void db_field_set_value(__db_field_s_field_definition* p_fields_definition,
                        __db_field_s_field* p_fields,
                        const __db_field_position p_position,
                        const void* p_value)
{
    db_error_reset();

    if(p_fields_definition[p_position].null_definition == __NULL ||
            p_value != NULL)
    {
        if(p_fields[p_position].field != NULL)
            free(p_fields[p_position].field);

        if(p_value != NULL)
        {
            switch (p_fields_definition[p_position].data_type)
            {
            case __char_array:
                p_fields[p_position].field = malloc((sizeof(char) * (strlen((char*)p_value) + 1)));
                strcpy((char*)p_fields[p_position].field, (char*)p_value);
                break;
            case __char:
                p_fields[p_position].field = malloc(sizeof(char));
                *(char*)p_fields[p_position].field = *(char*)p_value;
                break;
            case __unsigned_char:
                p_fields[p_position].field = malloc(sizeof(unsigned char));
                *(unsigned char*)p_fields[p_position].field = *(unsigned char*)p_value;
                break;
            case __int:
                p_fields[p_position].field = malloc(sizeof(int));
                *(int*)p_fields[p_position].field = *(int*)p_value;
                break;
            case __unsigned_int:
                p_fields[p_position].field = malloc(sizeof(unsigned int));
                *(unsigned int*)p_fields[p_position].field = *(unsigned int*)p_value;
                break;
            case __long:
                p_fields[p_position].field = malloc(sizeof(long));
                *(long*)p_fields[p_position].field = *(long*)p_value;
                break;
            case __unsigned_long:
                p_fields[p_position].field = malloc(sizeof(unsigned long));
                *(unsigned long*)p_fields[p_position].field = *(unsigned long*)p_value;
                break;
            case __float:
                p_fields[p_position].field = malloc(sizeof(float));
                *(float*)p_fields[p_position].field = *(float*)p_value;
                break;
            case __double:
                p_fields[p_position].field = malloc(sizeof(double));
                *(double*)p_fields[p_position].field = *(double*)p_value;
                break;
            case __void_pointer:
                p_fields[p_position].field = malloc(sizeof(void*));
                memcpy(p_fields[p_position].field, p_value, sizeof(void*));
                break;
            case __foreign_key:
                p_fields[p_position].field = p_value;
                break;
            default:
                p_fields[p_position].field = p_value;
                break;
            }
        }
        else
            p_fields[p_position].field = NULL;
    }
    else
        db_error_set_error(__EMPTY_MANDATORY_FIELD);

}

unsigned char db_field_is_filled(__db_field_s_field* p_fields,
                                 const __db_field_position p_position)
{
    unsigned char  v_result = 0;
    if(p_fields[p_position].field != NULL)
        v_result = 1;

    return v_result;
}

const char db_field_get_char(__db_field_s_field* p_fields,
                             const __db_field_position p_position)
{
    char  v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = *(char *)p_fields[p_position].field;

    return v_result;
}

const unsigned char db_field_get_unsigned_char(__db_field_s_field* p_fields,
        const __db_field_position p_position)
{
    unsigned char  v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = *(unsigned char *)p_fields[p_position].field;

    return v_result;
}

const int db_field_get_int(__db_field_s_field* p_fields,
                           const __db_field_position p_position)
{
    int v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = *(int*)p_fields[p_position].field;

    return v_result;
}

const unsigned int db_field_get_unsigned_int(__db_field_s_field* p_fields,
        const __db_field_position p_position)
{
    unsigned int v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = *(unsigned int*)p_fields[p_position].field;

    return v_result;
}

const long db_field_get_long(__db_field_s_field* p_fields,
                             const __db_field_position p_position)
{
    long v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = *(long*)p_fields[p_position].field;

    return v_result;
}

const unsigned long db_field_get_unsigned_long(__db_field_s_field* p_fields,
        const __db_field_position p_position)
{
    unsigned long v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = *(unsigned long*)p_fields[p_position].field;

    return v_result;
}

const float db_field_get_float(__db_field_s_field* p_fields,
                               const __db_field_position p_position)
{
    float v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = *(float*)p_fields[p_position].field;

    return v_result;
}

const double db_field_get_double(__db_field_s_field* p_fields,
                                 const __db_field_position p_position)
{
    double v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = *(double*)p_fields[p_position].field;

    return v_result;
}

const void* db_field_get_void(__db_field_s_field* p_fields,
                              const __db_field_position p_position)
{
    void* v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = p_fields[p_position].field;

    return v_result;
}

const char* db_field_get_char_array(__db_field_s_field* p_fields,
                                    const __db_field_position p_position)
{
    char* v_result = 0;
    if(db_field_is_filled(p_fields, p_position))
        v_result = (char*)p_fields[p_position].field;

    return v_result;
}

