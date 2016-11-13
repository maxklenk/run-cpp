#include <iostream>
#include <fstream>
#include <string>

#include "textfileformat.h"

std::string parseValue(const Value value) {
    switch (value.type()) {
        case ValueType::BOOL:
            return std::string(value.asBool() ? "true" : "false");
        case ValueType::INTEGER:
            return std::to_string(value.asInt());
        case ValueType::FLOAT:
            return std::to_string(value.asFloat());
        case ValueType::STRING:
            return "\"" + value.asString() + "\"";
    }
}

void writeText(const FileContent &content, const std::string &filename) {
    std::ofstream myfile;
    myfile.open(filename);

    // One empty line marks the beginning of the raw data section.
    myfile << "\n";

    // each line contains the key-value pair
    auto header = content.header();
    for (auto const &line: header) {
        myfile << line.first << "=" << parseValue(line.second) << "\n";
    }

    // body
    auto body = content.body();
    for (auto const &line: body) {
        myfile << line << "\n";
    }

    myfile.close();
}

FileContent readText(const std::string &filename, bool skipHeader) {
    std::string line;
    std::ifstream myfile(filename);
    FileContent fileContent = FileContent();
    std::vector<char> body = {};
    bool first = true;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            auto length = line.length();
            if (length > 1) {
                auto index = line.find("=");

                const std::string key = line.substr(0, index);
                const std::string valueString = line.substr(index + 1, length);

                switch (valueString[0]) {
                    case '"':
                        fileContent.addHeaderItem(key, Value(valueString.substr(1, valueString.length()-2)));
                        break;
                    case 'f':
                        fileContent.addHeaderItem(key, Value(false));
                        break;
                    case 't':
                        fileContent.addHeaderItem(key, Value(true));
                        break;
                    default :
                        if (valueString.find(".") !=std::string::npos) {
                            // contains dot
                            float num = std::stod(valueString);
                            fileContent.addHeaderItem(key, Value(num));
                        } else {
                            // or int
                            int num = std::stoi(valueString);
                            fileContent.addHeaderItem(key, Value(num));
                        }
                }
            } else {
                if (first) {
                    first = false;
                } else {
                    // TODO: body parsing does not work
                    body.push_back(line[0]);
                }
            }
        }
        myfile.close();
    }

    fileContent.setBody(body);
    return fileContent;
}
