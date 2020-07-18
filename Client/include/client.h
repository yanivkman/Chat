#include "defines.h"

class Client
{    
public:
    Client();
    ~Client();
    bool connect();
    size_t send();
    void disconnect();
    void exit();

private:
    client_id_t m_id;
};

Client::Client(/* args */)
{
}

Client::~Client()
{
}
