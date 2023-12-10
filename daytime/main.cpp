#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
using namespace std;
int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        close(s);
        return 8080;
    }

    unique_ptr <sockaddr_in> serv_addr(new sockaddr_in);
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(13);
    serv_addr->sin_addr.s_addr = inet_addr("172.16.40.1");

    int rc = 0;

    rc = connect(s, (sockaddr*) serv_addr.get(),
                 sizeof(sockaddr_in));
    if (rc == -1) {
        std::cerr << "Ошибка при подключении" << std::endl;
        close(s);
        return 8180;
    }
    string message(" ");
    size_t rb = send(s, message.c_str(), message.length(), 0);
    char buffer[256];
    rc = recv(s, buffer, sizeof buffer, 0);
    if (rc = -1) {
        std::cerr << "Ошибка при получении данных" << std::endl;
        close(s);
        return 8081;
    }
    buffer[rc] = '\0';
    cout << "Текущее время: " << buffer << endl;
    rc = close(s);
    return 0;
}
