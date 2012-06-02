/*
    blogcprog.com - db_string
    Copyright (C) 2011  blogcprog.com

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

#ifndef __DB_STRING__
#define __DB_STRING__

typedef struct __db_string_ss
{
    char *str;
} __db_string_s;

typedef __db_string_s* __db_string;

__db_string db_string_create(const char *p_str);

void db_string_drop(__db_string p_db_string);

void db_string_s_assign(__db_string p_s, const char *p_str);

void db_string_s_concat(__db_string p_s, const char *p_str);

unsigned char db_string_begins_with(__db_string p_s, __db_string p_s2);

unsigned char db_string_ends_with(__db_string p_s, __db_string p_s2);

__db_string db_string_g_csv_element(__db_string p_line,
                                    const int p_i,
                                    const char p_delimiter,
                                    const char p_opt_enclosed);

__db_string db_string_g_substr(__db_string p_s, const int p_x, const int p_n);

void db_string_s_substr(__db_string p_s, const int p_x, const int p_n);

__db_string db_string_g_trim(__db_string p_s, const char p_c);

void db_string_s_trim(__db_string p_s, const char p_c);

__db_string db_string_g_lpad(__db_string p_s, const int p_n, const char p_c);

void db_string_s_lpad(__db_string p_s, const int p_n, const char p_c);

__db_string db_string_g_rpad(__db_string p_s, const int p_n, const char p_c);

void db_string_s_rpad(__db_string p_s, const int p_n, const char p_c);

int db_string_g_inch(__db_string p_s, const char p_c, const int p_x);

int db_string_g_instr(__db_string p_s, __db_string p_s2, const int p_x);

__db_string db_string_g_ins(__db_string p_s, __db_string p_s2, const int p_x);

void db_string_s_ins(__db_string p_s, __db_string p_s2, const int p_x);

__db_string db_string_g_replace(__db_string p_s, __db_string p_s1, __db_string p_s2);

void db_string_s_replace(__db_string p_s, __db_string p_s1, __db_string p_s2);


#endif
