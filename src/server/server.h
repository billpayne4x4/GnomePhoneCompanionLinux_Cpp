#ifndef SERVER_H
#define SERVER_H

#include <giomm/socket.h>
#include <glibmm/dispatcher.h>
#include <thread>
#include <queue>
 
class server
{
public:
    server();
    virtual ~server();

    void start();
    void stop();
    bool isRunning();

protected:
private:
    Glib::RefPtr<Gio::Socket> socket;
    Glib::RefPtr<Gio::Cancellable> cancellable;
    std::thread *serverThread;
    Glib::Dispatcher serverDispatcher;
    
    GSocketAddress *address = NULL;

    void serverLoop();
    void received();
    void cancelLoop();
    void test();

    bool serverRunning = false;
    int jsonDepth = 0;
    std::queue<std::string> jsonQueue;
    std::string buffer = "";
};

#endif // SERVER_H