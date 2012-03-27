#ifndef CLIENTSOCKET_HH_
#define CLIENTSOCKET_HH_

#include "ISocketBase.hh"

namespace sockwrpr
{
  class ServerSocket :
    public ISocketBase
  {
  private:
    /**
     * Used for binding a socket.
     */
    bool bind(const int port);

    /**
     * Listen for incoming connections.
     */
    bool listen() const;

    /**
     * Accepts incoming connections.
     */
    bool accept(ServerSocket& newSocket) const;
  public:
    /**
     * ctor
     */ 
    ServerSocket(const int port);
    /**
     * dtor
     */ 
    virtual ~ServerSocket();

    /**
     * Used to write data to the socket.
     */
    const ServerSocket& operator<<(const std::string& data) const;
    
    /**
     * Used to read to from the socket.
     */
    const ServerSocket& operator>>(std::string& data) const;
    
    /**
     * Interface for accepting a socket.
     */
    void acceptSocket(ServerSocket& socket);
    
  };
} // end namespace

#endif // CLIENTSOCKET_HH_

