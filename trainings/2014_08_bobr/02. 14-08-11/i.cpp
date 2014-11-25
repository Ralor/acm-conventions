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

struct Person;

struct Car {
    int id;
#   ifdef _DEBUG
        string name;
#   endif
    int price;
    int pickUpCost;
    int gasolinePerKmCost;
    //Person* user;
};

struct Person {
    int id;
    string name;
    bool inconsistent;
    llong payment;
    Car* car;

    static bool SortByName(const Person& a, const Person& b) {
        return a.name < b.name;
    }
};

Car cars[502];
Person persons[502];
int personCount;
map<string, int> carMap;
map<string, int> personMap;

int main() {
#   ifdef _DEBUG
        freopen("i.in", "r", stdin);
#   else
        freopen("i.in", "r", stdin);
        freopen("i.out", "w", stdout);
#   endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tests;
    cin >> tests;
    string name;
    while (tests--) {
        int i, n, m;
        cin >> n >> m;
        personCount = 0;
        carMap.clear();
        personMap.clear();
        for (i = 1; i <= n; i++) {
            cin >> name >> cars[i].price >> cars[i].pickUpCost >> cars[i].gasolinePerKmCost;
            carMap[name] = i;
            cars[i].id = i;
#           ifdef _DEBUG
                cars[i].name = name;
#           endif
            //cars[i].user = NULL;
        }
        for (i = 0; i < m; i++) {
            int t;
            char c;
            cin >> t >> name >> c;
            map<string, int>::const_iterator it = personMap.find(name);
            int id;
            if (it == personMap.end()) {
                id = ++personCount;
                personMap[name] = id;
                persons[id].id = id;
                persons[id].name = name;
                persons[id].inconsistent = false;
                persons[id].payment = 0;
                persons[id].car = NULL;
            } else
                id = it->second;
            Person& person = persons[id];
            switch (c) {
                case 'p': {
                    cin >> name;
                    if (person.car) {
                        person.inconsistent = true;
                        //person.car->user = NULL;
                    }
                    int carId = carMap[name];
                    /*if (cars[carId].user) {
                        cars[carId].user->inconsistent = true;
                        cars[carId].user->car = NULL;
                    }*/
                    //cars[carId].user = &persons[id];
                    person.car = &cars[carId];
                    person.payment += cars[carId].pickUpCost;
                    break;
                }
                case 'r': {
                    int km;
                    cin >> km;
                    if (!person.car)
                        person.inconsistent = true;
                    else {
                        person.payment += km * person.car->gasolinePerKmCost;
                        //person.car->user = NULL;
                        person.car = NULL;
                    }
                    break;
                }
                case 'a': {
                    int percent;
                    cin >> percent;
                    if (!person.car)
                        person.inconsistent = true;
                    else
                        person.payment += (llong)ceil(person.car->price * percent *.01 - eps);
                }
            }
        }
        for (i = 1; i <= personCount; i++)
            if (persons[i].car)
                persons[i].inconsistent = true;
        sort(persons + 1, persons + personCount + 1, Person::SortByName);
        for (i = 1; i <= personCount; i++) {
            cout << persons[i].name << ' ';
            if (persons[i].inconsistent)
                cout << "INCONSISTENT\n";
            else
                cout << persons[i].payment << '\n';
        }
    }
#   ifdef _DEBUG
        _getch();
#   endif
    return 0;
}
