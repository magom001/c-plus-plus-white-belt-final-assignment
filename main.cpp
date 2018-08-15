#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>

using namespace std;


class Date {
    friend istream &operator>>(istream &stream, Date &date) {
        string DATE;
        stream >> DATE;
        int year, month, day;

        stringstream ss(DATE);

        ss >> year;
        date.checkInput(ss, DATE);
        date.SetYear(year);


        ss >> month;
        date.checkInput(ss, DATE);
        date.SetMonth(month);

        ss >> day;
        if (ss.fail() || ss.peek() != -1) {
            date.throwRuntimeException("Wrong date format: " + DATE);
        }
        date.SetDay(day);

        return stream;
    }

    friend ostream &operator<<(ostream &stream, Date &date) {
        stream << setw(4) << setfill('0') << date.GetYear()
               << "-"
               << setw(2) << setfill('0') << date.GetMonth()
               << "-"
               << setw(2) << setfill('0') << date.GetDay();

        return stream;
    }

public:
    int GetYear() const {
        return this->year;
    };

    int GetMonth() const {
        return this->month;
    };

    int GetDay() const {
        return this->day;
    };

    void SetYear(int year) {
        this->year = year;
    }

    void SetMonth(int month) {
        if (month > 0 && month < 13) {
            this->month = month;
        } else {
            this->throwRuntimeException("Month value is invalid: " + month);
        }
    }

    void SetDay(int day) {
        if (day > 0 && month < 32) {
            this->day = day;
        } else {
            this->throwRuntimeException("Day value is invalid: " + day);
        }
    }

private:
    int year;
    int month;
    int day;

    void checkInput(stringstream &stream, string &DATE) {
        if (stream.fail() || stream.peek() != '-') {
            this->throwRuntimeException("Wrong date format: " + DATE);
        }

        stream.ignore(1);
    }

    void throwRuntimeException(const string &error_msg) const {
        throw runtime_error(error_msg);
    }
};

bool operator<(const Date &lhs, const Date &rhs);

class Database {
public:
    void AddEvent(const Date &date, const string &event);

    bool DeleteEvent(const Date &date, const string &event);

    int DeleteDate(const Date &date);

    string &Find(const Date &date) const;

    void Print() const;

private:
    map<Date, set<string>> data;
};

int main() {
    Database db;
    string command;
    try {
        while (getline(cin, command)) {

        }

    }
    catch (exception &ex) {
        cout << ex.what();
    }
    return 0;
}