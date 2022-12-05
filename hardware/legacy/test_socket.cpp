#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <exception>
#include <string>

class Oscilloscope
{
public:
    using port_t = size_t;

    Oscilloscope(char *server_ip = "10.11.13.220", port_t server_port = 5024)
    {
        // setup a socket and connection tools
        struct hostent *host = gethostbyname(server_ip);

        sockaddr_in sendSockAddr;
        bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
        sendSockAddr.sin_family = AF_INET;
        sendSockAddr.sin_addr.s_addr =
            inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
        sendSockAddr.sin_port = htons(server_port);

        m_client_side = socket(AF_INET, SOCK_STREAM, 0);

        // try to connect...
        int status = connect(m_client_side,
                             (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));

        if (status < 0)
            throw std::runtime_error("Error connecting to oscilloscope!");

        std::cout << "Connected to the oscilloscope!" << std::endl;
    }

    size_t command(std::string const& comm)
    {
        return send(m_client_side, comm.c_str(), comm.length(), 0);
    }

    size_t request(char *buf, size_t buf_size)
    {
        return recv(m_client_side, buf, buf_size, 0);
    }

    void save_waveform()
    {
        
    }

    ~Oscilloscope()
    {
        close(m_client_side);
        std::cout << "Connection closed" << std::endl;
    }

private:
    int m_client_side;
};

// Client side
int main(int argc, char *argv[])
{
    // grab the IP address and port number
    char *serverIp = "10.11.13.220";
    int port = 5024;

    // pre message buffer
    const size_t pre_msg_size = 22;
    char *pre_msg = new char[pre_msg_size];

    // create a message buffer
    const size_t msg_size = 3e6;
    char *msg = new char[msg_size];

    // setup a socket and connection tools
    struct hostent *host = gethostbyname(serverIp);

    sockaddr_in sendSockAddr;
    bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
        inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);

    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    // try to connect...
    int status = connect(clientSd,
                         (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
                         
    if (status < 0)
    {
        std::cout << "Error connecting to socket!" << std::endl;
        return -1;
    }
    std::cout << "Connected to the server!" << std::endl;


    int bytesRead = 0;
    int bytesWritten = 0;

    bytesRead = recv(clientSd, msg, msg_size, 0);
    std::cout << msg << std::endl;

    // clear the buffer
    memset(msg, 0, msg_size);

    // send message
    std::string query = "C1:WF? DAT2";
    strcpy(msg, query.c_str());
    bytesWritten = send(clientSd, msg, strlen(msg), 0);

    // receive message
    bytesRead = 0;
    while (bytesRead < pre_msg_size) {
        bytesRead += recv(clientSd, std::next(msg, bytesRead), msg_size - bytesRead, 0);
        std::cout << bytesRead << std::endl;
    }

    std::cout << msg << std::endl;

    // clear the buffer
    memset(msg, 0, msg_size);

    // for (size_t i = 0; i < bytesRead; i++)
    //     printf("%d ", static_cast<int>(msg[i]));

    // std::cout << std::dec << std::endl;

    delete[] msg;

    // std::cout << std::hex << msg[0] << std::dec << std::endl;

    // std::ofstream out;
    // out.open("out.txt", std::ios_base::trunc | std::ios_base::binary | std::ios_base::out);

    // out.write(msg, sizeof(msg));
    // out.close();

    // memset(&msg, 0, sizeof(msg)); // clear the buffer
    // while (1)
    // {
    //     std::cout << ">";
    //     std::string data;
    //     getline(std::cin, data);

    //     memset(&msg, 0, sizeof(msg)); // clear the buffer
    //     strcpy(msg, data.c_str());

    //     if (data == "exit")
    //     {
    //         send(clientSd, (char *)&msg, strlen(msg), 0);
    //         break;
    //     }

    //     bytesWritten += send(clientSd, (char *)&msg, strlen(msg), 0);
    //     std::cout << "Awaiting server response..." << std::endl;
    //     memset(&msg, 0, sizeof(msg)); // clear the buffer
    //     bytesRead += recv(clientSd, (char *)&msg, sizeof(msg), 0);
    //     if (!strcmp(msg, "exit"))
    //     {
    //         std::cout << "Server has quit the session" << std::endl;
    //         break;
    //     }
    //     std::cout << "Server: " << msg << std::endl;
    // }
    
    close(clientSd);
    std::cout << "********Session********" << std::endl;
    std::cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << std::endl;
    std::cout << "Connection closed" << std::endl;
    
    return 0;
}
