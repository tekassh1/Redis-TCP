#ifndef COMMANDS
#define COMMANDS

#include "Command.h"

class Put : public Command {
public:
    void execute(std::shared_ptr<ConnectionInfo> connection_info, std::vector<std::string> args) override;
};

class Get : public Command {
public:
    void execute(std::shared_ptr<ConnectionInfo> connection_info, std::vector<std::string> args) override;
};

class Del : public Command {
public:
    void execute(std::shared_ptr<ConnectionInfo> connection_info, std::vector<std::string> args) override;
};

class Count : public Command {
public:
    void execute(std::shared_ptr<ConnectionInfo> connection_info, std::vector<std::string> args) override;
};

class Dump : public Command {
    void execute(std::shared_ptr<ConnectionInfo> connection_info, std::vector<std::string> args) override;
};

class Load : public Command {
    void execute(std::shared_ptr<ConnectionInfo> connection_info, std::vector<std::string> args) override;
};

#endif