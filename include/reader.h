#ifndef _READER_H_
#define _READER_H_

#include <string>
#include <vector>
#include "operation.h"

class IReader {
public:
    IReader();
    virtual ~IReader();
    virtual std::vector<std::vector<Operation>> *Read() = 0;
    virtual std::vector<std::vector<Operation>> *Read(const std::string &path) = 0;

};

class FileReader : public IReader {
    virtual std::vector<std::vector<Operation>> *Read();
    virtual std::vector<std::vector<Operation>> *Read(const std::string &path);
};

class ConsoleReader : public IReader {

};

#endif // !_READER_H_
