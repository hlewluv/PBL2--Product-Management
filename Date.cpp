#include "Date.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Date::Date(): day(1), month(1), year(1900) {}

Date::Date(int day, int month, int year): day(day), month(month), year(year) {}

Date::Date(const string & ngayThangNam) {
  istringstream iss(ngayThangNam);
  char delimiter;
  iss >> day >> delimiter >> month >> delimiter >> year;
}

int Date::getDay() const {
  return day;
}

int Date::getMonth() const {
  return month;
}

int Date::getYear() const {
  return year;
}

void Date::setDay(int day) {
  this -> day = day;
}

void Date::setMonth(int month) {
  this -> month = month;
}

void Date::setYear(int year) {
  this -> year = year;
}

bool Date::isValid() const {
  return true;
}

void Date::HienThiNgayThang() const {
  cout << right << setw(3) << day << " /" << right << setw(3) << month << " /" << right << setw(5) << year << "\t\t|" << endl;
}

bool Date::operator < (const Date & other) const {
  if (year < other.year) {
    return true;
  } else if (year == other.year && month < other.month) {
    return true;
  } else if (year == other.year && month == other.month && day < other.day) {
    return true;
  }
  return false;
}
