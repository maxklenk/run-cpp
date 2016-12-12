
#pragma once

#include <sstream>
#include <vector>
#include <string>
#include <iostream>

class tree_streambuf : public std::streambuf
{

private:

    // TODO Ensure that no data can be read from the buffer (write-only).

    std::vector<std::streambuf *> streams;


protected:
    using std::streambuf::overflow;
    virtual tree_streambuf::int_type overflow(tree_streambuf::int_type ch);

public:
    tree_streambuf();

    void add_sink(std::streambuf *streambuf);

};
