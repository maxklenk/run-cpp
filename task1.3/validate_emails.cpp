#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>
#include <sstream>
#include <list>

/*
#include <getopt.h>
*/

using namespace std;

string regex_email = "^[a-zA-Z0-9][-a-zA-Z0-9_]*(\\.[_a-zA-Z0-9-]+)*@[a-zA-Z0-9][a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+)*(\\.[a-zA-Z]{2,4})$";

string param_valid = "--print-valid";
string param_invalid = "--print-invalid";

/* 
 * returns true if email matches
 */
bool valid_email(string email)
{
    return regex_match(email, regex(regex_email));
}

/**
 * separates a string by given delimiter and returns 
 * a vector containing chunked string parts.
 */
vector<string> split_string(const string str, char delimiter)
{
	vector<string> retValue;
	stringstream ss;
	ss.str(str);
	string current;
	while(getline(ss, current, delimiter))
	{
		retValue.push_back(current);
	}
	return retValue;
}

/**
 * compares email address (1) by ascending order of their domain and (2) by ascending order of their name.
 */
bool compare_email(const string email1, const string email2)
{
	int retValue = 0;
	
	vector<string> email1_parts = split_string(email1, '@');
	vector<string> email2_parts = split_string(email2, '@');
	
	
	retValue = email1_parts[1].compare(email2_parts[1]); 

	if(retValue == 0)
	{
		retValue = email1_parts[0].compare(email2_parts[0]); 
	}
	
	return retValue < 0;
}

/* flags */
static int print_flag = 0;

/* checks emails for validation */
int main(int argc, char * argv[])
{
    string line;
    list<string> selected_lines;

	/*
	// looks better for more options, but not supporting windows

	int option_index = 0;

	// define options and assign them to flags or variables
	static struct option long_options[] =
	{
		{"print-valid", no_argument, &print_flag, 0},
		{"print-invalid", no_argument, &print_flag, 1},
		{0, 0, 0, 0}
	};

	getopt_long (argc, argv, "", long_options, &option_index);
    */

	if(argc == 2 && strcmp(argv[1], "--print-invalid") == 0)
	{
		print_flag = 1;
	}

    // read lines by mode into list
    while (cin >> line)
    {
        {
            if(print_flag == 0)
			{
				// add valid emails
              	if(valid_email(line))
                {
                	selected_lines.push_back(line);
                }
			}
			else
			{
				// add non emails
            	if(!valid_email(line))
                {
                	selected_lines.push_back(line);
				}
            }
        }
    }
	
	// sort if emails selected from lines
	if(print_flag == 0)
	{
		selected_lines.sort(compare_email); 
	}

	// output emails or non emails on console
	list<string>::iterator it = selected_lines.begin();
	while(it != selected_lines.end())
	{
		cout << *it++ << endl;
	}
	
	return 0;
}
