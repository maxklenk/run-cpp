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
    std::ofstream myfile(filename);
    // myfile.exceptions...

    // myfile << showpoint; // for integral floats show ".0" always
    // myfile << boolalpha; // for bool values print as true/false instead of 0/1

    // each line contains the key-value pair
    auto header = content.header();
    for (auto const &line: header) {
        myfile << line.first << "=" << parseValue(line.second) << std::endl;
    }

    // One empty line marks the beginning of the raw data section.
    myfile << std::endl; // \n instead

    // body
    for (const auto &data: content.body()) {
        myfile << data; // binary data shorter than hex
        // text file: 0-Byte, 26-Byte, ... will be handled as EOF which is wrong
    }

    myfile.close();
}

FileContent readText(const std::string &filename, bool skipHeader) {
    std::string line;
    std::ifstream myfile(filename);
    FileContent fileContent = FileContent();
    FileContent::Body body;

    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            auto length = line.length();
            if (length == 0) {
                skipHeader = true;
                break;
            }
            if (!skipHeader) {
                auto index = line.find("=");

                const std::string key = line.substr(0, index);
                const std::string valueString = line.substr(index + 1, length);

                switch (valueString[0]) {
                    case '"':
                        fileContent.addHeaderItem(key, Value(valueString.substr(1, valueString.length() - 2)));
                        break;
                    case 'f':
                        fileContent.addHeaderItem(key, Value(false));
                        break;
                    case 't':
                        fileContent.addHeaderItem(key, Value(true));
                        break;
                    default :
                        if (valueString.find(".") != std::string::npos) {
                            // contains dot
                            float num = std::stod(valueString); // stdof instead
                            fileContent.addHeaderItem(key, Value(num));
                        } else {
                            // or int
                            int num = std::stoi(valueString);
                            fileContent.addHeaderItem(key, Value(num));
                        }
                }
            }
        }
        char c;
        while(myfile.get(c)){ // get data by checking size whithout while
            body.push_back(c);
        }
        fileContent.setBody(body);

        myfile.close();
    }

    return fileContent;
}
