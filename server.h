#include <buffer.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
private:
    int port;
    Buffer buffer;
    int server_fd;
    struct sockaddr_in address;
    int addrlen;
    int client_socket;

public:
    Server(int port_) : port(port_), buffer(Buffer(BUFFER_SIZE)) {}
    ~Server()
    {
        close(server_fd);
        close(client_socket);
    }
    bool Init()
    {
        int opt = 1;
        addrlen = sizeof(address);

        if ((server_fd = socket(AF_INET, SOCK_STREAM)) == 0)
        {
            std::cerr << "socket failed!\n";
            return false;
        }

        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        {
            std::cerr << "setsockopt\n";
            return false;
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            std::cerr << "bind fails\n";
            return false;
        }

        return true;
    }

    bool Start()
    {
        if (listen(server_fd, 3) < 0)
        {
            std::cerr << "listening failed\n";
            false;
        }

        std::cout << "Server listening on port: " << port << std::endl;

        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            std::cerr << "accept failed\n";
            return false;
        }

        std::cout << "Connection accepted" << std::endl;

        size_t valread;
        while ((valread = read(client_socket, cicleBuf.buf[cicleBuf.current_index], BUFFER_SIZE - cicleBuf.current_index)) > 0)
        {
            cicleBuf.MoveIndex(valread);
        }

        if (valread == -1)
        {
            std::cerr << "read failed\n";
            return false;
        }

        char *answer = "Success";

        if (write(client_socket, answer, strlen(answer)) < 0)
        {
            std::cerr << "send failed\n";
            return false;
        }

        close(client_socket);
    }
};