#ifndef COMMAND
#define COMMAND

#include <string>
#include <vector>

struct ConnectionInfo;

using namespace std;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(ConnectionInfo* connection_info, vector<string> args) = 0;
};

#endif