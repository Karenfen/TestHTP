#include <server.h>

#define PORT 55665

int main()
{
    Server serv(PORT);
    bool res = false;

    if (serv.Init())
    {
        res = serv.Start();
    }

    return !res;
}