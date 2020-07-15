#include "defines.h"

enum EmessageType
{
    Connect,
    ConnectResponse
};

struct MessageHeader
{
    EmessageType type;
};

struct ConnectMessage
{
    MessageHeader header;
}

struct ConnectResponseMessage
{
    MessageHeader header;
    client_id_t clientId;
};



union ChatMessage
{
    MessageHeader header;
    ConnectMessage connect;
    ConnectResponseMessage connectResponse;
};


