/*
    blogcprog.com - db_error
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

#include "db_error.h"

void db_error_reset(void)
{
    gv_db_error.error_status = __NO_ERROR;
    gv_db_error.error_type = __WITHOUT_ERROR;
}

void db_error_set_error(__db_error_type p_error_type)
{
    gv_db_error.error_status = __ERROR;
    gv_db_error.error_type = p_error_type;
}

