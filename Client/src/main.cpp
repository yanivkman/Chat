#include <stdio.h>
#include <string.h>

#include "argh.h"

#include <iostream> // TODO: remove after debug..

#include "client.h"

int main(int argc, char* argv[])
{
    char server_ip[IP_MAX_LENGTH] = {0}; // Make sure to put string terminator

    uint16_t port; // port is at max 65535..

    argh::parser cmdl({"-h", "--help", "-server_ip", "-port"}); // batch pre-register multiple params: name + value
    cmdl.parse(argc, argv);

    std::cout << "cmdl[{'-h', '--help'}]" << cmdl[{"-h", "--help"}] << std::endl;

    if (cmdl[{"-h", "--help"}])
    {
        printf("Please enter parameters in format:\n./client -server_ip=SERVER_IP_ADDRESS -port=PORT_NUM\n");
        printf("Where 'client' is the name of your binary\nSERVER_IP_ADDRESS is the ip of the server itself\n");
        printf("PORT_NUM is the number of the port the client will use, it should be between 1024 and 65535\n");

        return EXIT_SUCCESS;
    }
    else if (argc != NUMBER_OF_ARGS_CLIENT || !cmdl("--server_ip") || !cmdl("--port"))
    {
        printf("Must provide exactly two parameters to main.\n");
        printf("The format is: ./client server_ip=SERVER_IP_ADDRESS port=PORT_NUM\n");
        printf("for more help please enter -h or --help :)\n");

        return EXIT_FAILURE;
    }
    else
    {
        size_t input_ip_length = cmdl("server_ip").str().length();
        if (input_ip_length > sizeof(server_ip) - 1) // The -1 is to save spare space for terminator!
        {
            printf("IP length is not valid.\n");

            return EXIT_FAILURE;
        }
         
        strncpy(server_ip, (cmdl("server_ip").str()).c_str(), input_ip_length);

        EipErrors ip_err;
        if(!is_valid_ip_address(server_ip, input_ip_length, ip_err))
        {
            print_ip_error(ip_err);
            
            return EXIT_FAILURE;
        }

        port = stoi(cmdl("port").str());

        EportErrors port_err;
        if (!(is_valid_port(port, port_err)))
        {
            print_port_error(port_err);

            return EXIT_FAILURE;
        }
        
    }
    
    printf("Trying to connect to server at ip address %s at port %d\n", server_ip, port);
    //send_connect_message();

    return EXIT_SUCCESS;
}