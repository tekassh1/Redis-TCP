#ifndef SERIALIZATION_MANAGER
#define SERIALIZATION_MANAGER

#include "ConnectionManager.h"

class SerializationManager {

public:
    static void SerializeResponse(const ConnectionStatus& status, char* buffer) {
        memcpy(buffer, &status, sizeof(ConnectionStatus));
    }
};

#endif