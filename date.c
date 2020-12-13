#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "date.h"

#define DATE_VALIDATION ((day >= 1 && day <= 30) && (month >= 1 && month <= 12)) // check validation for day, month and year

struct Date_t 
{
    int day;
    int month;
    int year;
};

long long dateToDays (Date date)//returns the total days in a specific date.
{
    int* day, *month, *year;
    long long total_days = 0;
    dateGet(date, day, month, year);
    total_days += *day;
    total_days += (*month * 30);
    total_days += (*year * 365);

    return total_days;
}

Date dateCreate(int day, int month, int year)//creates a new Date.
{
    if(DATE_VALIDATION){
        return NULL;
    }

    Date date = malloc(sizeof(*date));
    if(date == NULL)
    {
        return NULL;
    }

    date->day = day;
    date->month = month;
    date->year = year;

    return date;
}

void dateDestroy(Date date)//Destroys a Date.
{
    free(date);
}

Date dateCopy(Date date)//Copies the given date into another one and returns it.
{
    Date copied_date = malloc(sizeof(*copied_date));
    if(copied_date == NULL)
    {
        return NULL;
    }

    copied_date->day = date->day;
    copied_date->month = date->month;
    copied_date->year = date->year;

    return copied_date;
}

bool dateGet(Date date, int* day, int* month, int* year)//Gets the day, month and year from the given date and puts them into a pointer for each one
{
    if (date == NULL || day == NULL || month == NULL || year == NULL)
    {
        return false;
    }

    day = &(date->day);
    month = &(date->month);
    year = &(date->year);

    return true;
}

int dateCompare(Date date1, Date date2)//Compares between two dates and returns 1 if date2 is before date1 or -1 if date1 is before date2 or 0 if they are the same date
{
    if (date1 == NULL || date2 == NULL)
    {
        return 0;
    }
    long long date1_total_days, date2_total_days;

    date1_total_days = dateToDays (date1);
    date2_total_days = dateToDays (date2);

    if(date1 < date2){
        return -1;
    }else if (date2 > date1){
        return 1;
    }else{
        return 0;
    }
    
}

void dateTick(Date date)//Increases the date by 1 day.
{
    if(date != NULL)
    {
        if(date->day < 30)
        {
            date->day++;
        }else if(date->month < 12)
        {
            date->day = 1;
            date->month++;
        }else{
            date->day = 1;
            date->month = 1;
            date->year++;
        }
    
        
    }
}
