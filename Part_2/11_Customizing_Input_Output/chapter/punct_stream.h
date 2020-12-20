#ifndef PUNCSTREAM_H_
#define PUNCSTREAM_H_

#include "../../../std_lib_facilities.h"

class Punct_stream
{
    // like an istream, but the user can add to
    // the set of whitespace characters
public:
    Punct_stream(istream &is)
        : source{is}, sensitive{true} {}
    void whitespace(const string &s)
    // make s the whitespace set
    {
        white = s;
    }
    void add_white(char c) { white += c; } // add to the whitespace set
    bool is_whitespace(char c);
    // is c in the whitespace set?
    void case_sensitive(bool b) { sensitive = b; }
    bool is_case_sensitive() { return sensitive; }
    Punct_stream &operator>>(string &s);
    operator bool();

private:
    istream &source;
    istringstream buffer;
    string white;
    bool sensitive;
};

#endif