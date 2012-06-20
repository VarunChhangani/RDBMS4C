/*
    blogcprog.com - DB_ERROR
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

#ifndef __DB_ERROR__
#define __DB_ERROR__

#define db_error_is_error gv_db_error.error_status

typedef enum {__NO_ERROR = 0, __ERROR = 1} __db_error_status;

typedef enum {__WITHOUT_ERROR = 0,
              __NOT_NULL_VIOLATION = 100,
              __MISSING_PRIMARY_INDEX = 600,
              __PRIMARY_INDEX_REDEF = 601,
              __PRIMARY_INDEX_DELETE = 602,
              __MISSING_RECORD_DEFINITION = 603,
              __UNIQUE_INDEX_NEEDED = 604,
              __FIELD_IS_NOT_FOREIGN_KEY = 605,
              __UNIQUE_VIOLATION = 800,
              __EMPTY_MANDATORY_FIELD = 810,
              __CANNOT_MODIFY_UNIQUE_KEY = 820,
              __CANNOT_MODIFY_FOREIGN_KEY = 830,
              __WRONG_PARENT_TABLE = 840,
              __FOREIGN_KEY_NEEDED = 850,
              __NO_DATA_FOUND = 900
             } __db_error_type;

typedef struct __db_error_ss_error
{
    __db_error_status error_status;
    __db_error_type error_type;
} __db_error_s_error;

__db_error_s_error gv_db_error;

void db_error_reset(void);

void db_error_set_error(__db_error_type p_error_type);


#endif

