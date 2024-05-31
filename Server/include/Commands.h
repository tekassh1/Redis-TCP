#ifndef COMMANDS
#define COMMANDS

#include "Command.h"

class Put : public Command {
public:
    void execute(shared_ptr<ConnectionInfo> connection_info, vector<string> args) override;
};

class Get : public Command {
public:
    void execute(shared_ptr<ConnectionInfo> connection_info, vector<string> args) override;
};

class Del : public Command {
public:
    void execute(shared_ptr<ConnectionInfo> connection_info, vector<string> args) override;
};

class Count : public Command {
public:
    void execute(shared_ptr<ConnectionInfo> connection_info, vector<string> args) override;
};

#endif