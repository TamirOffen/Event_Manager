#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "date.h"

//Checks if day and month are legal dates.
#define DATE_VALIDATION ((day >= 1 && day <= 30) && (month >= 1 && month <= 12))

//Date structure.
struct Date_t{
    int day;
    int month;
    int year;
};

//Converts the given date to the total number of days in it and return that, it is useful in dateCompare function.
int convertDateToDays (Date date){
    int total_days = 0;
    total_days = total_days + date->day;
    total_days = total_days + (date->month * 30);
    total_days = total_days + (date->year * 365);

    return total_days;
}

//creates a new Date and returns it.
Date dateCreate(int day, int month, int year){
    if(!DATE_VALIDATION){
        return NULL;
    }

    Date date = malloc(sizeof(*date));
    if(date == NULL){
        return NULL;
    }

    date->day = day;
    date->month = month;
    date->year = year;

    return date;
}

//Destroys a Date.
void dateDestroy(Date date){
    free(date);
}

//Copies the given date into another one and returns it.
Date dateCopy(Date date){
    if(date == NULL){
        return NULL;
    }

    Date copied_date = malloc(sizeof(*copied_date));
    if(copied_date == NULL){
        return NULL;
    }

    copied_date->day = date->day;
    copied_date->month = date->month;
    copied_date->year = date->year;

    return copied_date;
}

//Takes the day, month and year from the given date and puts them into a pointer for each one.
bool dateGet(Date date, int* day, int* month, int* year){
    if (date == NULL || day == NULL || month == NULL || year == NULL){
        return false;
    }

    *day = date->day;
    *month = date->month;
    *year = date->year;

    return true;
}

//Compares between two dates and returns 1 if date2 is before date1 or -1 if date1 is before date2 or 0 if they are the same date
int dateCompare(Date date1, Date date2){
    if (date1 == NULL || date2 == NULL){
        return 0;
    }
    int date1_total_days, date2_total_days;

    //Using converDateToDays is easier than checking manually by loops.
    date1_total_days = convertDateToDays (date1);
    date2_total_days = convertDateToDays (date2);

    if(date1_total_days < date2_total_days){
        return -1;
    }else if (date1_total_days > date2_total_days){
        return 1;
    }else{
        return 0;
    }
}

//Increases the date by 1 day.
void dateTick(Date date){
    if(date != NULL){
        if(date->day < 30){
            date->day++;
        }else if(date->month < 12){
            date->day = 1;
            date->month++;
        }else{
            date->day = 1;
            date->month = 1;
            date->year++;
        }
    }
}
