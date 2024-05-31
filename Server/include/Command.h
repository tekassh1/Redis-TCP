#ifndef COMMAND
#define COMMAND

#include <string>
#include <vector>
#include <memory>

struct ConnectionInfo;

using namespace std;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(shared_ptr<ConnectionInfo> connection_info, vector<string> args) = 0;
};

#endif