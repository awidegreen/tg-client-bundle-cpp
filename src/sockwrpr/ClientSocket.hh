#ifndef CLIENTSOCKET_HH_
#define CLIENTSOCKET_HH_

/**
 * ClientSocket is used to connect to a socket, opened by a
 * server. The class should be used a classmember in a
 * client implementation.
 * @author awidegreen
 */ 

#include "ISocketBase.hh"

#include <string>

namespace sockwrpr
{
  class ClientSocket :
    public ISocketBase
  {
  private:
    /**
     * Connects to a socket server.
     */ 
    bool connect(const std::string host, const int port);
    
  public:
    /**
     * ctor
     */
    ClientSocket(std::string host, int port );
    /**
     * dtor
     */ 
    virtual ~ClientSocket() { }

    /**
     * Used for sending data to socket.
     */ 
    const ClientSocket& operator<< (const std::string& data) const;

    /**
     * Used for reading data from socket.
     */
    const ClientSocket& operator>> (std::string& data) const;

    /**
     * Used to sending data to socket.
     */
    void sendData(const std::string& data);

    /**
     * Used for reading data from socket.
     */
    void receiveData(std::string& data);
    
  };
}

#endif // CLIENTSOCKET_HH_
