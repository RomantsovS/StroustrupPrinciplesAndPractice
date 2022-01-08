#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

using Line = vector<char>;

class Text_iterator {
    // keep track of line and character position within a line
    list<Line>::iterator ln;
    Line::iterator pos;

   public:
    // start the iterator at line ll’s character position pp:
    Text_iterator(list<Line>::iterator ll, Line::iterator pp)
        : ln{ll}, pos{pp} {}
    char& operator*() { return *pos; }
    Text_iterator& operator++();
    bool operator==(const Text_iterator& other) const {
        return ln == other.ln && pos == other.pos;
    }
    bool operator!=(const Text_iterator& other) const {
        return !(*this == other);
    }
};
Text_iterator& Text_iterator::operator++() {
    ++pos;
    // proceed to next character
    if (pos == (*ln).end()) {
        ++ln;
        // proceed to next line
        pos = (*ln).begin();
        // bad if ln==line.end(); so make sure it isn’t
    }
    return *this;
}

struct Document {
    list<Line> line;
    // a document is a list of lines
    Document() { line.push_back(Line{}); }

    Text_iterator begin()
    // first character of first line
    {
        return Text_iterator(line.begin(), (*line.begin()).begin());
    }
    Text_iterator end()
    // one beyond the last character of the last line
    {
        auto last = line.end();
        --last;
        // we know that the document is not empty
        return Text_iterator(last, (*last).end());
    }
};

istream& operator>>(istream& is, Document& d) {
    for (char ch; is.get(ch);) {
        d.line.back().push_back(ch);
        // add the character
        if (ch == '\n') d.line.push_back(Line{});  // add another line
    }
    if (d.line.back().size()) d.line.push_back(Line{});  // add final empty line
    return is;
}

void print(Document& d) {
    for (auto p : d) cout << p;
}

void find_replace(Document& d, const string& s1, const string& s2) {    
    char first_char = s1[0];
    auto first = d.begin();
    while(true) {
        auto p = first;
        while(p != d.end()) {
            if(*p == first_char) {
                break;
            }
            ++p;
        }
        
        if(p == d.end())
            return;
        else {
            size_t index = 0;
            for(auto iter = p; iter != d.end() && index < s1.size(); ++iter) {
                if(*iter != s1[index])
                    break;
                ++index;
            }
            if(index == s1.size()) {
                size_t i = 0;
                for(; i < index && i < s2.size(); ++i) {
                    *p = s2[i];
                    ++p;
                }
            }
            first = ++p;
        }
    }
 }

int main() {
    {
        string s =
            "Our “text processor” and its operations are very simple."
            "Obviously, we are aiming for simplicity and reasonable efficiency,"
            "rather than at providing a “feature-rich” editor. Don't be fooled"
            "into thinking that providing efficient insertion, deletion, and "
            "search for arbitrary character sequences is trivial, though.";

        istringstream iss(s);

        Document doc;
        iss >> doc;

        print(doc);
        cout << endl;

        find_replace(doc, "and", "*");
        
        print(doc);
        cout << endl;
    }

    return 0;
}