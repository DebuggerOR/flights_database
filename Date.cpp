
#include "interface.h"

bool isInt(char c){
    return (c>='0'&& c<='9');
}

bool isMonth(const string& str) {
    return (str == "12" || str == "11" || str == "10" || str[0] == '0');
}

bool isDay(const string& str){
    return (str == "31" || str == "30" || str[0] < '3');
}

Date::Date(string date) {
    if (date.length() != 10) { throw "illegal date"; }
    // year
    int i = 0;
    while (date[i] != '-') {
        if (!isInt(date[i])) { throw "illegal date"; }
        this->date += date[i++];
    }
    if (i != 4) { throw "illegal date"; }
    this->date += date[i++];
    // month
    string month;
    while (date[i] != '-') {
        if (!isInt(date[i])) { throw "illegal date"; }
        month += date[i++];
    }
    if (i != 7 || !isMonth(month)) { throw "illegal date"; }
    this->date += (month + date[i++]);
    // day
    string day;
    while (i < 10) {
        if (!isInt(date[i])) { throw "illegal date"; }
        day += date[i++];
    }
    if (!isDay(day)) { throw "illegal date"; }
    this->date += day;
}

bool Date::operator>(const Date& d) const {
    return this->date > d.getDate();
}

bool Date::operator<(const Date& d) const {
    return !(*this == d || *this > d);
}

bool Date::operator==(const Date& d) const {
    return (this->date == d.getDate());
}