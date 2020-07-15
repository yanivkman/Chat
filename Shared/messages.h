#include "defines.h"

enum EmessageType
{
    Connect,
    ConnectResponse,
    Outgoing,
    Incoming
};

struct MessageHeader
{
    EmessageType type;
};

struct ConnectMessage
{
    MessageHeader header;
};

struct ConnectResponseMessage
{
    MessageHeader header;
    client_id_t clientId;
};

struct OutgoingMessage
{
    MessageHeader header;
    uint32_t textLength;
    char text[MAX_TEXT_SIZE];
};

struct IncomingMessage
{
    MessageHeader header;
    uint32_t textLength;
    char text[MAX_TEXT_SIZE];
    client_id_t author;
};


union ChatMessage
{
    MessageHeader header;
    ConnectMessage connect;
    ConnectResponseMessage connectResponse;
    OutgoingMessage outgoing;
    IncomingMessage incoming;
};
