#define VERBOSE
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#ifdef _DEBUG
#   include <conio.h>
#endif

#ifndef _DEBUG
#   undef VERBOSE
#endif

#define eps      1e-8
#define inf      (1000 * 1000 * 1000)
#define linf     (4LL * 1000 * 1000 * 1000 * 1000 * 1000 * 1000)
#define sqr(x)   ((x) * (x))
#define eq(x, y) (((x) > (y) ? (x) - (y) : (y) - (x)) <= eps)
#define sz(x)    int((x).size())
#define all(x)   (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()
#define mp       make_pair

using namespace std;

typedef unsigned           uint;
typedef long long          llong;
typedef unsigned long long ullong;
typedef long double        ldouble;
typedef vector<int>        vi;
typedef vector<vi>         vvi;
typedef vector<double>     vd;
typedef vector<vd>         vvd;

struct debug_t {
    template <typename T>
    debug_t& operator<<(const T& value) {
#       ifdef VERBOSE
            cout << value;
#       endif
        return *this;
    }
} debug;

/*struct Date {
  int year,month,day,hour,minute;
  int book; // 0 if it's start point
  Date() { }
  Date(const string& yymmdd, const string& hhmm, const bool book = 0) {
    init(yymmdd,hhmm); this->book = book;
  }
  int dig(char c) {
    return c - '0';
  }
  void init(const string& yymmdd, const string& hhmm) {
    year = dig(yymmdd[0])*1000+dig(yymmdd[1])*100+dig(yymmdd[2])*10+dig(yymmdd[3]);
    month = dig(yymmdd[5])*10+dig(yymmdd[6]);
    day = dig(yymmdd[8])*10+dig(yymmdd[9]);
    hour = dig(hhmm[0])*10+dig(hhmm[1]);
    minute = dig(hhmm[3])*10+dig(hhmm[4]);
  }
  void increment(int int_minutes) {
    minute += int_minutes;
    int inc_hours = minute/60; minute %= 60;
    hour += inc_hours;
    int inc_days = hour/24; hour %= 24;
    day += inc_days;
    int inc_months = day/get_days_in_month(month); day %= get_days_in_month(month);
    month += inc_months;
    int inc_years = month/12; month %= 12;
    year += inc_years;
  }
  int get_days_in_month(int num) {
    if( year == 2016 && num == 2 )
      return 29;
    int days_in_month[] = {-1,31,28,31,30,31,30,31,31,30,31,30,31};
    return days_in_month[num];
  }
  bool operator<(const Date& d) const {
    bool t = mp(year,mp(month,mp(day,mp(hour,mp(minute,book))))) < mp(d.year,mp(d.month,mp(d.day,mp(d.hour,mp(d.minute,d.book)))));    
    return t;
  }
};

struct Book {
  Date start, stop;
  string code;
  Book() {}
  Book(const string& code, const Date& start, const Date& stop) : code(code), start(start), stop(stop) {}
  bool operator<(const Book& book) const {
    return mp(start,mp(stop,code)) < mp(book.start,mp(book.stop,book.code));
  }
};*/

time_t ReadDate() {
    int year, month, day, hour, minute;
    char delim;
    cin >> year >> delim >> month >> delim >> day >> hour >> delim >> minute;
    tm t = {
        0,/*sec*/
        minute,
        hour,
        day,
        month - 1,
        year - 1900,
    };
    return mktime(&t);
}

struct Booking {
    time_t timePoint;
    bool book;

    static bool SortByDate(const Booking& a, const Booking& b) {
        return make_pair(a.timePoint, a.book) < make_pair(b.timePoint, b.book);
    }
};

Booking bookings[10000];

int main() {
#   ifdef _DEBUG
        freopen("b.in", "r", stdin);
#   else
        freopen("b.in", "r", stdin);
        freopen("b.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tests;
    cin >> tests;
    string s;
    while( tests-- ) {
      /*int n,c; cin >> n >> c;
      //vector<Book> books; books.reserve(n);
      vector<Date> dates; 
      for(int i = 0; i < n; i++) {
        string code,a,aa,b,bb;
        cin >> code >> a >> aa >> b >> bb;
        Date start(a,aa, 1), stop(b, bb, 0); 
        stop.increment(c);
        //books.push_back(Book(code, start, stop));
        dates.push_back(start); dates.push_back(stop);
      }
      sort(all(dates));

      int cnt = 0, res = 0;
      for(int i = 0; i < sz(dates); i++)
        if( dates[i].book == 1 )
          ++cnt, res = max(res,cnt);
        else
          --cnt;
      cout << res << "\n";*/
        int i, b, c;
        cin >> b >> c;
        c *= 60;
        for (i = 0; i < b; i++) {
            cin >> s;
            bookings[i].timePoint = ReadDate();
            bookings[i].book = true;
            bookings[i + b].timePoint = ReadDate() + c;
            bookings[i + b].book = false;
        }
        sort(bookings, bookings + (b << 1), Booking::SortByDate);
        int result = 0;
        int stackSize = 0;
        for (i = 0; i < b << 1; i++)
            if (bookings[i].book) {
                stackSize++;
                if (stackSize > result)
                    result = stackSize;
            } else
                stackSize--;
        cout << result << '\n';
    }
    

#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
