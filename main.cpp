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

    friend ostream &operator<<(ostream &stream, const Date &date) {
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

bool operator<(const Date &lhs, const Date &rhs) {
    return (lhs.GetYear() * 12 * 31 + lhs.GetMonth() * 31 + lhs.GetDay()) <
           (rhs.GetYear() * 12 * 31 + rhs.GetMonth() * 31 + rhs.GetDay());
};

class Database {
public:
    void AddEvent(const Date &date, const string &event) {
        this->data[date].insert(event);
    };

    bool DeleteEvent(const Date &date, const string &event) {
        if (this->data.count(date) > 0) {
            if (this->data[date].count(event) > 0) {
                data[date].erase(event);
                return true;
            }
        }
        return false;
    };

    int DeleteDate(const Date &date) {
        int number_of_events = data[date].size();
        data.erase(date);
        return number_of_events;
    };

    set<string> Find(const Date &date) const {
        if (this->data.count(date) > 0) {
            return this->data.at(date);
        }
    };

    void Print() const {
        for (const auto &record : this->data) {
            for (const auto &event: record.second) {
                cout << record.first << " " << event << "\n";
            }
        }
    };

private:
    map<Date, set<string>> data;
};

void HandleInput(const string &command, Database &db) {

    string op_code;
    stringstream ss(command);
    ss >> op_code;

    if (op_code == "Add") {
        Date date;
        string event;
        ss >> date >> event;
        db.AddEvent(date, event);
    }

    if (op_code == "Del") {
        Date date;
        string event;
        ss >> date >> event;
        if (event.empty()) {
            cout << "Deleted " << db.DeleteDate(date) << " events" << "\n";
        } else {
            if (db.DeleteEvent(date, event)) {
                cout << "Deleted successfully" << "\n";
            } else {
                cout << "Event not found" << "\n";
            }
        }
    }

    if (op_code == "Find") {
        Date date;
        ss >> date;

        auto events = db.Find(date);
        if (!events.empty()) {
            for (const auto &e: events) {
                cout << e << "\n";
            }
        }

    }

    if (op_code == "Print") {
        db.Print();
    }
}

int main() {
    Database db;
    string command;
    try {
        while (getline(cin, command)) {
            HandleInput(command, db);
        }

    }
    catch (exception &ex) {
        cout << ex.what();
    }
    return 0;
}