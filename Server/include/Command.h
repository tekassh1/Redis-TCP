#ifndef COMMAND
#define COMMAND

#include <string>
#include <vector>
#include <memory>

struct ConnectionInfo;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(std::shared_ptr<ConnectionInfo> connection_info, std::vector<std::string> args) = 0;
};

#endif