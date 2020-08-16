#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {

    vector<string> names;
    vector<int> scores;

    string name;
    int score;

    cout << "enter name and score:\n";
    while(cin >> name >> score) {
    	auto iter = std::find(names.begin(), names.end(), name);

    	if(iter != names.end()) {
    		cout << name << " already exists\n";
    		continue;
    	}

    	names.push_back(name);
    	scores.push_back(score);

    	cout << "enter name and score:\n";
    }

    for(int i = 0; i < names.size(); ++i) {
    	cout << names[i] << " " << scores[i] << endl;
    }


    return 0;
}
