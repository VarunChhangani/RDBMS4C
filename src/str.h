/*
    blogcprog.com - C string utility
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

#ifndef __STR__
#define __STR__

unsigned char str_is_letter(const char p_c);

unsigned char str_begins_with(const char* p_s, const char* p_s2);

unsigned char str_ends_with(const char* p_s, const char* p_s2);

char* str_g_csv_element(const char* p_line,
                        const int p_i,
                        const char p_delimiter,
                        const char p_opt_enclosed);

int str_g_inch(const char* p_s, const char p_c, const int p_x);

int str_g_instr(const char* p_s, const char* p_s2, const int p_x);

char* str_g_ins(const char* p_s, const char* p_s2, const int p_x);

char* str_g_left(const char* p_s, const int p_n);

char* str_g_lpad(const char* p_s, const int p_n, const char p_c);

char* str_g_repeat(const char p_c, const int p_n);

char* str_g_replace(const char* p_s, const char* p_s1, const char* p_s2);

char* str_g_right(const char* p_s, const int p_n);

char* str_g_rpad(const char* p_s, const int p_n, const char p_c);

char* str_g_substr(const char* p_s, const int p_x, const int p_n);

char* str_g_trim(const char* p_s, const char p_c);

#endif
