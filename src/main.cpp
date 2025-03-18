#include <iostream>
#include "server.hpp"

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }
        run_server(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
