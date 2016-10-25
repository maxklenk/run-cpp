#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>
#include <sstream>
#include <list>

using namespace std;

string regex_email = "^[a-zA-Z0-9][-a-zA-Z0-9_]*(\\.[_a-zA-Z0-9-]+)*@[a-zA-Z0-9][a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+)*(\\.[a-zA-Z]{2,4})$";

bool valid_email(string email) {
    return regex_match(email, regex(regex_email));
}

vector <string> split_string(const string str, char delimiter) {
    vector <string> retValue;
    stringstream ss;
    ss.str(str);
    string tok;
    while (getline(ss, tok, delimiter)) {
        retValue.push_back(tok);
    }
    return retValue;
}

/**
 * compares email address (1) by ascending order of their domain and (2) by ascending order of their name.
 */
int compare_email(const string email1, const string email2) {
    int retValue = 0;

    vector <string> email1_parts = split_string(email1, '@');
    vector <string> email2_parts = split_string(email2, '@');

    // compare second part may not work for invalid addresses
    if (email1_parts.size() == 2 && email2_parts.size() == 2) {
        retValue = email1_parts[1].compare(email1_parts[1]);
    }

    if (retValue == 0) {
        retValue = email1_parts[0].compare(email1_parts[0]);
    }

    return retValue;
}

int main(int argc, char *argv[]) {
    string line;
    list <string> selected_lines;

    // check mode parameter
    int mode = 1; // valid
    if (argc == 2 && strcmp(argv[1], "--print-invalid") == 0) {
        mode = 2; // invalid
    }

    // select lines by mode into list
    while (cin >> line) {
        {
            switch (mode) {
                case 1: // select valid
                    if (valid_email(line)) {
                        selected_lines.push_back(line);
                        selected_lines.sort(compare_email);
                    }
                    break;
                case 2: // select invalid
                    if (!valid_email(line)) {
                        selected_lines.push_back(line);
                    }
                    break;
            }
        }
    }

    // write lines to std::out
    list<string>::iterator it = selected_lines.begin();
    while (it != selected_lines.end()) {
        cout << *it++ << endl;
    }

    return 0;
}
