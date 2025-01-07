/***
@author Thien Twee Zian
@since 30/07/2023
@version 1.02
Holds the date for records of wind speed
*/

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
Array used to contain name of months in a year stored as strings.
To be used to convert int month to string month.
*/
const string MONTH_STRING[13] = {"NULL","January","February","March","April","May","June","July","August","September","October","November","December"};

/**
This class is used to store the date of wind record
*/
class Date
{
private:
    /**
    Date of wind record
    */
    string m_date;

    /**
    Day of the wind record
    */
    int m_day;

    /**
    Month of the wind record, in number format
    */
    int m_month;

    /**
    Year of the wind record
    */
    int m_year;

    /**
    Month of the wind record, in string format
    */
    string m_monthString;

public:
    /**
    Default constructor
    */
    Date();

    /**
    Constructor to initialize the date attribute
    @param date - Date of wind record
    */
    Date(string date);

    /**
    Get date of wind record
    @return m_date - Date of wind record
    */
    string GetDate() const;

    /**
    Set date of wind record
    @param date - Date of wind record
    */
    void SetDate(const string &date);

    /**
    Get day of wind record
    @return m_day - Day of wind record
    */
    int GetDay() const;

    /**
    Get month of wind record, as int
    @return m_month - Month of wind record
    */
    int GetMonth() const;

    /**
    Get year of wind record
    @return m_year - Year of wind record
    */
    int GetYear() const;

    /**
    Set day of wind record
    @param day - Day of wind record
    */
    void SetDay(const int day);

    /**
    Set month of wind record, as int
    @param month - Month of wind record
    */
    void SetMonth(const int month);

    /**
    Set year of wind record
    @param year - Year of wind record
    */
    void SetYear(const int year);

    /**
    Get month of wind record, as string
    */
    string GetMonthString() const;

    /**
    Set month of wind record, as string
    */
    void SetMonthString(const int month);
};

/**
Overloaded << operator to print attributes of the Date
@param os - Variable initialized to store output stream
@param date - Date object containing data to be printed
@return os - Return output stream to be printed
*/
ostream & operator <<( ostream & os, const Date & date );

/**
Overloaded >> operator to read attributes of a Date
@param input - Variable initialized to store input stream
@param date - Date object whose attributes is to be set
@return input - Return EOF once all lines are read
*/
istream & operator >>( istream & input, Date & date );

#endif // DATE_H
