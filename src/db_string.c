/*
    rdbms4c.org - db_string
    Copyright (C) 2011  blogcprog.com
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
#include <stdio.h>
#include <stdlib.h>

#include "db_string.h"
#include "str.h"

__db_string db_string_create(const char *p_str)
{
    __db_string v_ret;
    v_ret = malloc(sizeof(__db_string_s));
    if(p_str != NULL)
    {
        v_ret->str = malloc(sizeof(char)*(strlen(p_str)+1));
        strcpy(v_ret->str, p_str);
    }
    else
        v_ret->str = NULL;

    return v_ret;
}

void db_string_drop(__db_string p_db_string)
{
    if (p_db_string != NULL)
    {
        if(p_db_string->str != NULL)
            free(p_db_string->str);

        free(p_db_string);
    }
}

void db_string_assign(__db_string p_s, const char *p_str)
{
    if(p_s != NULL)
    {
        if(p_s->str != NULL)
            free(p_s->str);
        if(p_str == NULL)
        {
            p_s->str = NULL;
        }
        else
        {
            p_s->str = malloc(sizeof(char)*(strlen(p_str)+1));
            strcpy(p_s->str, p_str);
        }

    }
}

void db_string_s_concat(__db_string p_s, const char *p_str)
{
    char* v_str;
    if(p_s != NULL && p_str !=NULL)
    {
        if(p_s->str != NULL)
        {
            v_str = str_g_ins(p_s->str, p_str, strlen(p_s->str));
            free(p_s->str);
        }
        else
        {
            v_str = malloc(sizeof(char)*(strlen(p_str)+1));
            strcpy(v_str, p_str);
        }
        p_s->str = v_str;
    }
}

unsigned char db_string_begins_with(__db_string p_s, __db_string p_s2)
{
    return str_begins_with(p_s->str, p_s2->str);
}

unsigned char db_string_ends_with(__db_string p_s, __db_string p_s2)
{
    return str_ends_with(p_s->str, p_s2->str);
}

__db_string db_string_g_csv_element(__db_string p_line,
                                    const int p_i,
                                    const char p_delimiter,
                                    const char p_opt_enclosed)
{
    __db_string v_ret;
    if(p_line != NULL && p_line->str != NULL)
        v_ret = db_string_create(str_g_csv_element(p_line->str, p_i, p_delimiter, p_opt_enclosed));
    else
        v_ret = db_string_create(NULL);

    return v_ret;
}

__db_string db_string_g_substr(__db_string p_s, const int p_x, const int p_n)
{
    __db_string v_ret;
    if (p_s != NULL)
        v_ret = db_string_create(str_g_substr(p_s->str, p_x, p_n));
    else
        v_ret = db_string_create(NULL);

    return v_ret;
}

void db_string_s_substr(__db_string p_s, const int p_x, const int p_n)
{
    char* v_str;
    if(p_s != NULL && p_s->str != NULL)
    {
        v_str = str_g_substr(p_s->str, p_x, p_n);
        free(p_s->str);
        p_s->str = v_str;
    }
}

__db_string db_string_g_trim(__db_string p_s, const char p_c)
{
    __db_string v_ret;
    if (p_s != NULL)
        v_ret = db_string_create(str_g_trim(p_s->str, p_c));
    else
        v_ret = db_string_create(NULL);

    return v_ret;
}

void db_string_s_trim(__db_string p_s, const char p_c)
{
    char* v_str;
    if(p_s != NULL && p_s->str != NULL)
    {
        v_str = str_g_trim(p_s->str, p_c);
        free(p_s->str);
        p_s->str = v_str;
    }
}

__db_string db_string_g_lpad(__db_string p_s, const int p_n, const char p_c)
{
    __db_string v_ret;
    if (p_s != NULL)
        v_ret = db_string_create(str_g_lpad(p_s->str, p_n, p_c));
    else
        v_ret = db_string_create(NULL);

    return v_ret;
}

void db_string_s_lpad(__db_string p_s, const int p_n, const char p_c)
{
    char* v_str;
    if(p_s != NULL && p_s->str != NULL)
    {
        v_str = str_g_lpad(p_s->str, p_n, p_c);
        free(p_s->str);
        p_s->str = v_str;
    }
}

__db_string db_string_g_rpad(__db_string p_s, const int p_n, const char p_c)
{
    __db_string v_ret;
    if (p_s != NULL)
        v_ret = db_string_create(str_g_rpad(p_s->str, p_n, p_c));
    else
        v_ret = db_string_create(NULL);

    return v_ret;
}

void db_string_s_rpad(__db_string p_s, const int p_n, const char p_c)
{
    char* v_str;
    if(p_s != NULL && p_s->str != NULL)
    {
        v_str = str_g_rpad(p_s->str, p_n, p_c);
        free(p_s->str);
        p_s->str = v_str;
    }
}

int db_string_g_inch(__db_string p_s, const char p_c, const int p_x)
{
    int v_ret = -1;
    if(p_s != NULL && p_s->str != NULL)
        v_ret = str_g_inch(p_s->str, p_c, p_x);

    return v_ret;
}

int db_string_g_instr(__db_string p_s, __db_string p_s2, const int p_x)
{
    int v_ret = -1;
    if(p_s != NULL && p_s->str != NULL && p_s2 != NULL && p_s2->str != NULL)
        v_ret = str_g_instr(p_s->str, p_s2->str, p_x);

    return v_ret;
}

__db_string db_string_g_ins(__db_string p_s, __db_string p_s2, const int p_x)
{
    __db_string v_ret;
    if (p_s != NULL && p_s2 != NULL)
        v_ret = db_string_create(str_g_ins(p_s->str, p_s2->str, p_x));
    else
        v_ret = db_string_create(NULL);

    return v_ret;
}

void db_string_s_ins(__db_string p_s, __db_string p_s2, const int p_x)
{
    char* v_str;
    if(p_s != NULL && p_s2 != NULL)
    {
        v_str = str_g_ins(p_s->str, p_s2->str, p_x);
        free(p_s->str);
        p_s->str = v_str;
    }
}

__db_string db_string_g_replace(__db_string p_s, __db_string p_s1, __db_string p_s2)
{
    __db_string v_ret;
    if (p_s != NULL && p_s1 && p_s2 != NULL)
        v_ret = db_string_create(str_g_replace(p_s->str, p_s1->str, p_s2->str));
    else
        v_ret = db_string_create(NULL);

    return v_ret;
}

void db_string_s_replace(__db_string p_s, __db_string p_s1, __db_string p_s2)
{
    char* v_str;
    if(p_s != NULL && p_s1 != NULL && p_s2 != NULL)
    {
        v_str = str_g_replace(p_s->str, p_s1->str, p_s2->str);
        free(p_s->str);
        p_s->str = v_str;
    }
}

