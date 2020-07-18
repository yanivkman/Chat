#include <iostream>
#include "argh.h"

#include "server.h"

int main(int argc, char* argv[])
{
    // port=PORT_NUM
    argh::parser cmdl(argv);

    if (cmdl[{ "-v", "--verbose" }])
        std::cout << "Verbose, I am.\n";

    return EXIT_SUCCESS;
}