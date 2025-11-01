#ifndef OPTYPE_H
#define OPTYPE_H

#include <string>

using std::size_t;
using std::string;

enum class OpType { Insert, Delete, Replace};

struct Operation{
    OpType type;
    int pos;
    string oldValue;
    string newValue;
};

#endif // OPTYPE_H
