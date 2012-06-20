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

#include <stdio.h>
#include "str.h"

unsigned char str_is_letter(const char p_c)
{

    return 0;
}

unsigned char str_begins_with(const char* p_s, const char* p_s2)
{
    unsigned char v_result = 0;
    int v_i = 0;
    int v_s2_length = 0;
    if(p_s != NULL && p_s2 != NULL)
    {
        v_s2_length = strlen(p_s2);
        if(strlen(p_s) >= v_s2_length)
        {
            while(v_i < v_s2_length && p_s[v_i] == p_s2[v_i])
                v_i++;
            if(v_i == v_s2_length)
                v_result = 1;

        }
    }
    return v_result;
}

unsigned char str_ends_with(const char* p_s, const char* p_s2)
{
    unsigned char v_result = 0;
    int v_i1;
    int v_i2;
    int v_s_length;
    int v_s2_length;
    if(p_s != NULL && p_s2 != NULL)
    {
        v_s_length = strlen(p_s);
        v_s2_length = strlen(p_s2);
        if(v_s_length >= v_s2_length)
        {
            v_i1 = v_s_length-1;
            v_i2 = v_s2_length-1;
            while(v_i2 >= 0 && p_s[v_i1] == p_s2[v_i2])
            {
                v_i1--;
                v_i2--;
            }
            if(v_i2 == -1)
                v_result = 1;

        }
    }
    return v_result;
}

char* str_g_csv_element(const char* p_line,
                        const int p_i,
                        const char p_delimiter,
                        const char p_opt_enclosed)
{
    char* v_ret;
    char* v_chk;
    int v_i = -1;
    int v_i2 = 0;
    int v_p_first = 0;
    int v_p_last = 0;
    int v_found_pos = 0;
    char* v_c = NULL;
    if (str_g_inch(p_line, p_delimiter, 1) == -1)
    {
        v_p_first = 1;
        v_p_last  = strlen(p_line) + 1;
        v_found_pos = 1;
    }
    else
    {
        do
        {
            v_i++;
            if(v_c!=NULL)
                free(v_c);

            v_c = str_g_substr(p_line, v_i-1, 1);
            if (v_c[0] == p_opt_enclosed)
            {
                v_i2 = str_g_inch(p_line, p_opt_enclosed, v_i + 1);
                if (v_i2 > 0)
                    v_i = v_i2+1;

            }
            else if (v_c[0] == 0  || v_c[0] == p_delimiter || v_i>=strlen(p_line))
            {
                v_p_first   = v_p_last + 1;
                v_p_last    = v_i;
                v_found_pos++;
            }
        }
        while(!(v_c == NULL || v_c[0] == 0 || v_found_pos == p_i || v_i > strlen(p_line) ));
        free(v_c);
    }
    if (v_found_pos == p_i)
    {
        v_ret = str_g_substr(p_line, v_p_first-1, v_p_last - v_p_first);

        v_chk = str_g_left(v_ret, 1);
        if (v_chk[0]==p_opt_enclosed)
        {
            free(v_chk);
            v_chk = v_ret;
            v_ret = str_g_substr(v_chk, 1, strlen(v_ret)-1);
        }
        free(v_chk);
        v_chk = str_g_right(v_ret, 1);
        if (v_chk[0]==p_opt_enclosed)
        {
            free(v_chk);
            v_chk = v_ret;
            v_ret = str_g_substr(v_chk, 0, strlen(v_ret)-1);
        }
        free(v_chk);

    }
    else
    {
        v_ret = malloc(sizeof(char));
        *v_ret = 0;
    }
    return v_ret;
}

int str_g_inch(const char* p_s, const char p_c, const int p_x)
{
    int v_result = p_x;
    if(v_result<0) v_result = 0;
    if(p_s != NULL)
    {
        if(v_result > strlen(p_s)) v_result = strlen(p_s);
        while(v_result < strlen(p_s) && p_s[v_result] != p_c)
            v_result++;
        if (v_result == strlen(p_s) && p_s[v_result] != p_c) v_result = -1;
    }
    else
        v_result = -1;

    return v_result;
}

int str_g_instr(const char* p_s, const char* p_s2, const int p_x)
{
    int v_result = p_x;
    int v_j, v_j2,v_s_length, v_s2_length;
    unsigned char v_found = 0;
    unsigned char v_mistake = 0;
    if(v_result < 0) v_result = 0;
    if(p_s != NULL && p_s2 != NULL)
    {
        v_s_length = strlen(p_s);
        v_s2_length = strlen(p_s2);
        if(v_s2_length <= v_s_length && v_result + v_s2_length <= v_s_length)
        {
            while(!v_found && v_result + v_s2_length <= v_s_length)
            {
                v_j = v_result;
                v_j2 = 0;
                v_mistake = 0;
                while(!v_found && !v_mistake && v_j2 < v_s2_length)
                {
                    if(p_s[v_j] == p_s2[v_j2])
                    {
                        v_j++;
                        v_j2++;
                    }
                    else
                        v_mistake = 1;

                }
                if(v_mistake == 0)
                    v_found = 1;
                else
                    v_result++;
            }
            if(!v_found)
                v_result = -1;
        }
        else
            v_result = -1;
    }
    else
        v_result = -1;

    return v_result;
}

char* str_g_ins(const char* p_s, const char* p_s2, const int p_x)
{
    char* v_result = NULL;
    char* v_i = NULL;
    char* v_o = NULL;
    int v_s_length, v_s2_length;
    int x2 = p_x;
    if(x2<0) x2 = 0;
    if(p_s != NULL && p_s2 != NULL)
    {
        v_s_length = strlen(p_s);
        v_s2_length = strlen(p_s2);
        if(x2 > strlen(p_s)) x2 = v_s_length;
        v_result = malloc(sizeof(char) * (v_s_length + v_s2_length + 1));
        v_o = v_result;
        for(v_i = p_s; v_i < p_s + x2; v_i++)
            *v_o++ = *v_i;
        for(v_i = p_s2; v_i < p_s2 + v_s2_length; v_i++)
            *v_o++ = *v_i;
        for(v_i = p_s + x2; v_i < p_s + v_s_length; v_i++)
            *v_o++ = *v_i;
        *v_o = 0;
    }
    else if(p_s == NULL && p_s2 != NULL)
        v_result = NULL;
    else if(p_s != NULL && p_s2 == NULL)
    {
        v_result = malloc(sizeof(char) * (v_s_length + 1));
        strcpy(v_result, p_s);
    }
    return v_result;
}

char* str_g_left(const char* p_s, const int p_n)
{
    char* v_result = NULL;
    int v_i;
    char* v_o = NULL;
    char* v_s = NULL;
    int v_s_length;
    int v_n = p_n;
    if(p_s != NULL)
    {
        v_s = p_s;
        v_s_length = strlen(v_s);
        if(v_n < 0) v_n = 0;
        if(v_n > v_s_length) v_n = v_s_length;
        v_result = malloc(sizeof(char) * (v_n + 1));
        v_o = v_result;
        for(v_i = 0; v_i < v_n; v_i++)
            *v_o++ = *v_s++;
        *v_o = 0;
    }
    else
        v_result = NULL;

    return v_result;
}

char* str_g_lpad(const char* p_s, const int p_n, const char p_c)
{
    char* v_result = NULL;
    int v_n = p_n;
    int v_i;
    int v_j;
    char* v_o = NULL;
    char* v_s = NULL;
    if(p_s != NULL)
    {
        v_s = p_s;
        v_j = strlen(p_s);
        if(v_n < 0) v_n = 0;
        v_result = malloc(sizeof(char) * (v_n + 1));
        v_o = v_result;
        if(v_n >= v_j)
            for(v_i = 0; v_i < v_n; v_i++)
                if(v_i < (v_n - v_j))
                    *v_o++ = p_c;
                else
                    *v_o++ = *v_s++;
        else
            for(v_i = 0; v_i < v_n; v_i++)
                *v_o++ = *v_s++;

        *v_o = 0;
    }
    else
        v_result = str_g_repeat(p_c, p_n);
    return v_result;
}

char* str_g_repeat(const char p_c, const int p_n)
{
    char* v_result;
    int v_i;
    int v_n = p_n;
    char* v_o;
    if(v_n < 0) v_n = 0;
    v_result = malloc(sizeof(char) * (v_n + 1));
    v_o = v_result;
    for(v_i = 0; v_i < v_n; v_i++)
        *v_o++ = p_c;
    *v_o = 0;
    return v_result;
}

char* str_g_replace(const char* p_s, const char* p_s1, const char* p_s2)
{
    char* v_result = NULL;
    int v_pos = 0;
    int v_i;
    char* v_st1 = NULL, *v_st2 = NULL, *v_st3 = NULL;
    if(p_s != NULL)
    {
        v_result = malloc(sizeof(char) * (strlen(p_s) + 1));
        strcpy(v_result, p_s);
        if(strlen(v_result) > 0)
        {
            if(p_s2 != NULL && strlen(p_s2) > 0 && p_s1 != NULL && strlen(p_s1) > 0)
            {
                while(v_pos < strlen(v_result))
                {
                    v_i = str_g_instr(v_result, p_s1, v_pos);
                    if(v_i > -1)
                    {
                        v_st1 = str_g_substr(v_result, 0, v_i);
                        v_st2 = str_g_substr(v_result, v_i + strlen(p_s1), strlen(v_result));
                        v_st3 = malloc(sizeof(char) * (strlen(v_st1) +
                                                       strlen(v_st2) +
                                                       strlen(p_s2) + 1));
                        strcpy(v_st3, v_st1);
                        strcat(v_st3, p_s2);
                        strcat(v_st3, v_st2);
                        v_pos = v_i + strlen(p_s2);
                        free(v_st1);
                        free(v_st2);
                        if(v_result != NULL) free(v_result);
                        v_result = v_st3;
                    }
                    else
                        v_pos = strlen(v_result);
                }
            }
        }
    }
    return v_result;
}

char* str_g_right(const char* p_s, const int p_n)
{
    char* v_result;
    char* v_i;
    char* v_o;
    int v_s_length;
    int v_n = p_n;
    if(v_n < 0) v_n = 0;
    v_s_length = strlen(p_s);
    if(v_n > v_s_length) v_n = v_s_length;
    v_result = malloc(sizeof(char) * (v_n + 1));
    v_o = v_result;
    for(v_i = p_s + v_s_length - v_n; v_i < p_s + v_s_length; v_i++)
        *v_o++ = *v_i;
    *v_o = 0;
    return v_result;
}

char* str_g_rpad(const char* p_s, const int p_n, const char p_c)
{
    char* v_result;
    int v_n = p_n;
    int v_i;
    int v_s_length = strlen(p_s);
    char* v_o;
    char* v_s;
    v_s = p_s;
    if(v_n < 0) v_n = 0;
    v_result = malloc(sizeof(char) * (v_n + 1));
    v_o = v_result;
    if(v_n > v_s_length)
        for(v_i = 0; v_i < v_n; v_i++)
            if(v_i < v_s_length)
                *v_o++ = *v_s++;
            else
                *v_o++ = p_c;
    else
        for(v_i = 0; v_i < v_n; v_i++)
            *v_o++ = *v_s++;

    *v_o = 0;
    return v_result;
}

char* str_g_substr(const char* p_s, const int p_x, const int p_n)
{
    char* v_result=NULL;
    char* v_i;
    char* v_o;
    int v_s_length;
    int v_x = p_x;
    int v_n = p_n;
    if(p_s != NULL)
    {
        v_s_length = strlen(p_s);
        if (v_x < 0) v_x = 0;
        if (v_x > v_s_length - 1) v_x = v_s_length;
        if(v_s_length - v_n - v_x < 0) v_n = v_s_length - v_x;
        v_result = malloc((sizeof(char) * (v_n + 1)));
        v_o = v_result;
        for(v_i = p_s + v_x; v_i < p_s + v_x + v_n; v_i++)
            *v_o++ = *v_i;
        *v_o = 0;
    }
    return v_result;
}

char* str_g_trim(const char* p_s, const char p_c)
{
    char* v_result = NULL;
    int v_first = 0;
    int v_last = 0;
    int v_s_length;
    char* v_s = p_s;
    int i = 0;
    if(v_s != NULL && p_c != NULL)
    {
        v_s_length = strlen(v_s);
        if(v_s_length > 0)
        {
            i = strlen(p_s) - 1;
            while(*v_s++ == p_c) v_first++;
            while(p_s[i--] == p_c) v_last++;
            v_result = str_g_substr(p_s, v_first, v_s_length - v_first - v_last);
        }
    }
    return v_result;
}

