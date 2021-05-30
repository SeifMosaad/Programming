package model;

import java.io.Serializable;
import java.util.Calendar;

public class Date implements Serializable{
    private static final String weekDays[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    private static final int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    private int year;
    private int month;
    private int day;
    public Date(){
        year = 1920; month = 1; day = 1;
    }
    public Date(int day, int month, int year){
        this.year = year; this.month = month; this.day = day;
    }

    public int getYear() {
        return year;
    }
    public void setYear(int year) {
        this.year = year;
    }

    public int getMonth() {
        return month;
    }
    public void setMonth(int month) {
        this.month = month;
    }

    public int getDay() {
        return day;
    }
    public void setDay(int day) {
        this.day = day;
    }

    // REQUIRES: A valid date
    // EFFECTS: returns the day name of the current date
    public String getDayName(){
        int years = year - 1920, leapYears = years / 4, normalYears = years - leapYears;
        int days = normalYears * 365 + leapYears * 366 + 4 + day;
        boolean leapYear = years % 4 == 0;
        for (int i = 0; i < month - 1; ++i) {
            days += monthDays[i];
            if (i == 1 && leapYear) days++;
        }
        return weekDays[days % 7];
    }
    // REQUIRES: A valid date
    // EFFECTS: returns the date in format "DD-MM-YYYY"
    public String getDate(){
        return (day + "-" + month + "-" + year);
        //  + ": " + getDayName() + " February 25, 2020");
    }

    // EFFECTS: returns true if the data is valid else false
    public boolean valid(){
        int year = Calendar.getInstance().get(Calendar.YEAR), month = Calendar.getInstance().get(Calendar.MONTH) + 1, day = Calendar.getInstance().get(Calendar.DAY_OF_MONTH);
        if (this.year >= year && this.month >=  month && this.day >= day && this.month > 0 && this.month <= 12 &&
                this.day > 0 && this.day <= monthDays[this.month - 1])
            return true;
        return false;
    }

    // EFFECTS: returns true if current date is today
    public boolean today(){
        if (this.year == Calendar.getInstance().get(Calendar.YEAR) && this.month == Calendar.getInstance().get(Calendar.MONTH) + 1 &&
                this.day == Calendar.getInstance().get(Calendar.DAY_OF_MONTH))
            return true;
        return false;
    }


}
