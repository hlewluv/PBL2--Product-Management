#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

class Date {
protected:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int day, int month, int year);
    Date(const string& ngayThangNam);


    int getDay() const;
    int getMonth() const;
    int getYear() const;

    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    bool isValid() const;
    void HienThiNgayThang() const;
    bool operator<(const Date& other) const;

};

#endif // DATE_H

