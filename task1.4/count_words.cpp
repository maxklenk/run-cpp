#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>

using namespace std;

const regex ws_re("\\s+"); // whitespace

int isNotAlphaNum(const char c) {
    return !isalnum(c) && c != '\'';
}

int main(int argc, char *argv[]) {
    int limit = 32;
    if (argc == 2) {
        limit = atoi(argv[1]);
    }

    ifstream myfile("../hgg.txt");

    if (!myfile.is_open()) {
        cout << "Unable to open file" << endl;
    } else {
        map<string, int> counter;
        string line;
        while (getline(myfile, line)) {
            // replace non alphanumeric
            replace_if(line.begin(), line.end(), isNotAlphaNum, ' ');

            // to lowercase
            transform(line.begin(), line.end(), line.begin(), ::tolower);

            // iterate over words
            sregex_token_iterator it(line.begin(), line.end(), ws_re, -1);
            sregex_token_iterator reg_end;
            for (; it != reg_end; ++it) {
                // count words if not whitespace
                string word = it->str();
                // we may have words of spaces
                if (word.find_first_not_of(' ') != string::npos) {
                    // add or increment word
                    if (counter.find(word) == counter.end()) {
                        counter[word] = 1;
                    } else {
                        counter[word] += 1;
                    }
                }
            }
        }
        myfile.close();

        // sort word counter
        vector<pair<int, string> > sorted_counter;
        for (map<string, int>::iterator it = counter.begin(); it != counter.end(); ++it) {
            sorted_counter.push_back(pair<int, string>(it->second, it->first));
        }

        // sort by counter
        sort(sorted_counter.begin(), sorted_counter.end(), [](pair<int, string> &left, pair<int, string> &right){
            return left.first > right.first;
        });

        // print
        int printed = 0;
        auto it = sorted_counter.begin();
        for(; it != sorted_counter.end() && printed < limit; ++it) {
            printf ("%5d ", it->first);
            cout << it->second << endl;
            printed++;
        }

    }

    return 0;
}
