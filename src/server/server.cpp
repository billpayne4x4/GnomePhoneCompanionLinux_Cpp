#include "server.h"
#include "../config.h"
#include "../tools/debug.tpp"
#include <giomm/inetsocketaddress.h>
#include <chrono>

server::server() : jsonQueue(), buffer()
{
    serverDispatcher.connect(sigc::mem_fun(*this, &server::received));
}

server::~server()
{
    // dtor
    delete serverThread;
}

bool server::isRunning()
{
    return serverRunning;
}

void server::start()
{
    debug(config::logLevel::INFO) << "Starting server...";
    serverRunning = true;
    serverThread = new std::thread(&server::serverLoop, this);
    serverThread->detach();
}

void server::stop()
{
    debug(config::logLevel::INFO) << "Stopping server...";
    serverRunning = false;
    cancellable->cancel();
}

void server::serverLoop()
{
    if (socket)
        socket.reset();

    if (cancellable)
        cancellable.reset();

    try
    {
        cancellable = Gio::Cancellable::create();
        socket = Gio::Socket::create(Gio::SocketFamily::IPV4, Gio::Socket::Type::STREAM, Gio::Socket::Protocol::TCP);
        debug(config::logLevel::INFO) << "Socket created.";

        if (config::bind == "0.0.0.0")
            socket->bind(Gio::InetSocketAddress::create(Gio::InetAddress::create_any(Gio::SocketFamily::IPV4), config::port), false);
        else
            socket->bind(Gio::InetSocketAddress::create(Gio::InetAddress::create(config::bind), config::port), false);
        debug(config::logLevel::INFO) << "Bind to address: " << config::bind << ":" << config::port;
    }
    catch (const std::exception &e)
    {
        debug(config::logLevel::ERROR) << e.what();
    }

    while (serverRunning)
    {
        Glib::RefPtr<Gio::Socket> clientSocket;

        try
        {
            debug(config::logLevel::INFO) << "Waiting for client...";
            socket->listen();
            clientSocket = socket->accept(cancellable);
            debug(config::logLevel::INFO) << "Client connected.";
        }
        catch (const std::exception &e)
        {
            debug(config::logLevel::ERROR) << e.what();
        }

        while (clientSocket->is_connected())
        {
            gchar recivedBuffer[4096] = {};

            try
            {
                clientSocket->receive(recivedBuffer, sizeof(buffer), cancellable);
                if (recivedBuffer[0] == '\0')
                    clientSocket->close();
            }
            catch (const std::exception &e)
            {
                debug(config::logLevel::ERROR) << e.what();
            }

            std::string receivedString(recivedBuffer);

            while (receivedString != "" && serverRunning)
            {
                int originaJsonDepth = jsonDepth;
                char c = receivedString[0];
                receivedString.erase(0, 1);

                switch (c)
                {
                case '{':
                    jsonDepth++;
                    break;
                case '}':
                    jsonDepth--;
                    break;
                }

                if (jsonDepth > 0 || c == '{' || c == '}')
                    buffer += c;

                if (originaJsonDepth == 1 && jsonDepth == 0)
                {
                    jsonQueue.push(buffer);
                    buffer.clear();
                    serverDispatcher();
                }
            }
        }
        debug(config::logLevel::INFO) << "Client disconnected.";
    }
    debug(config::logLevel::INFO) << "Server ended.";
}

void server::received()
{
    while (!jsonQueue.empty())
    {
        std::string json = jsonQueue.front();
        debug(config::logLevel::INFO) << "JSON:" << '\n'
                                      << json;
        jsonQueue.pop();
    }
}

void server::test()
{
    std::cout << "TEST!" << std::endl;
}