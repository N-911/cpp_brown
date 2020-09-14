#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <sstream>


using namespace std;
using namespace chrono;

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define ADD_DURATION(value) \
  AddDuration UNIQ_ID(__LINE__) {value};

struct TotalDuration {
    string message;
    steady_clock::duration value;
    explicit TotalDuration(const string& msg = "") : message(msg + ": ")
            , value(0)
    { }
    ~TotalDuration() { ostringstream os; os << message
                                            << duration_cast<milliseconds>(value).count()
                                            << " ms" << endl; cerr << os.str();
    }
};


class AddDuration {
public:
    explicit AddDuration(steady_clock::duration& dest)
            : add_to(dest)
            , start(steady_clock::now())
    { }
    explicit AddDuration(TotalDuration& dest) : AddDuration(dest.value)
    { }
    ~AddDuration() {
        add_to += steady_clock::now() - start;
    }
private:
    steady_clock::duration& add_to;
    steady_clock::time_point start;
};

//#define ADD_DURATION(value) \
//  AddDuration UNIQ_ID(__LINE__){value};
//
//
