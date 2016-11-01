#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>

using namespace std;

regex ws_re("\\s+"); // whitespace

int isNotAlphaNum(char c) {
    return !isalnum(c); 
    // TODO check type of apostroph's
}

pair<int, string> flip_pair(const pair<string, int> &p) {
    return pair<int, string>(p.second, p.first);
}

int main(int argc, char *argv[]) {
    int limit = 32;
    if (argc == 2) {
        limit = atoi(argv[1]);
    }

    string line;
    string word;
    map<string, int> counter;

    ifstream myfile("../hgg.txt");

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            // replace non alphanumeric
            replace_if(line.begin(), line.end(), isNotAlphaNum, ' ');

            // to lowercase
            transform(line.begin(), line.end(), line.begin(), ::tolower);

            // iterate over words
            sregex_token_iterator it(line.begin(), line.end(), ws_re, -1);
            sregex_token_iterator reg_end;

            // count words if not whitespace
            for (; it != reg_end; ++it) {
                word = it->str();
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

        // TODO fails on same word count! use vector instead
        map<int, string> dst;
        transform(counter.begin(), counter.end(), inserter(dst, dst.begin()), flip_pair);

        // print
        int printed = 0;
        int maxCountLength = 4;
        for (map<int, string>::iterator it = --dst.end(); it != dst.begin() && printed < limit; --it) {
            for (int c = maxCountLength - to_string(it->first).length(); c > 0; c --) {
                cout << " "; 
                // TODO    printf ("Preceding with blanks: %10d \n", 1977);
            }
            cout << it->first << " " << it->second << endl;
            printed++;
        }

    }

    else cout << "Unable to open file"; 
    // short error to top

    return 0;
}
