/*
    blogcprog.com - timer.c
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

#include"timer.h"
#include<stdlib.h>
#include<time.h>

typedef struct sstimer
{
    int id;
    long fire;
    long last;
    __p_timer_function pf;
    struct sstimer* next_timer;
} __stimer;

void timer_action(__stimer* search_timer);

__stimer* timer_list_first_element=NULL;


int create_timer(int pid, int p_seconds, __p_timer_function p_pf)
{
    __stimer* stimer;
    __stimer* search_timer;
    stimer=malloc(sizeof(__stimer));
    stimer->id=pid;
    stimer->fire=p_seconds;
    stimer->pf=p_pf;
    stimer->next_timer=NULL;
    stimer->last=clock();
    if(timer_list_first_element==NULL)
        timer_list_first_element=stimer;
    else
    {
        search_timer=timer_list_first_element;
        while(search_timer->next_timer!=NULL)
        {
            search_timer=search_timer->next_timer;
        }
        search_timer->next_timer=stimer;
    }
    return pid;
}

void timer_listener(void)
{
    __stimer* search_timer;
    search_timer=timer_list_first_element;
    if(search_timer!=NULL)
    {
        timer_action(search_timer);
        while(search_timer->next_timer!=NULL)
        {
            search_timer=search_timer->next_timer;
            timer_action(search_timer);
        }
    }
}

void timer_action(__stimer* search_timer)
{
    if((search_timer->last+search_timer->fire)<clock())
    {
        (*search_timer->pf)();
        search_timer->last=clock();
    }
}

void drop_timer(int pid)
{
    __stimer* search_timer=NULL;
    __stimer* previous_timer=NULL;
    search_timer=timer_list_first_element;
    if(search_timer!=NULL)
    {
        while(search_timer->next_timer!=NULL&&search_timer->id!=pid)
        {
            previous_timer=search_timer;
            search_timer=search_timer->next_timer;
        }
        if(search_timer!=NULL&&search_timer->id==pid)
        {
            if(previous_timer!=NULL&&previous_timer!=timer_list_first_element)
                previous_timer->next_timer=search_timer->next_timer;
            else
                timer_list_first_element=search_timer->next_timer;

            free(search_timer);
        }
    }
}

