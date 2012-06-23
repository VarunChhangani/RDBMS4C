/*
    rdbms4c.org - db_timer.h
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

#ifndef __TIMER__
#define __TIMER__

typedef void __timer_function(int pid);

typedef __timer_function *__p_timer_function;

int create_timer(int pid, int p_seconds, __p_timer_function p_pf);

void drop_timer(int pid);

void timer_pool();

void timer_pool_exit();

#endif
