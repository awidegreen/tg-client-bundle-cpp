/**
 * ServerSocket implementation
 * @author awidegreen
 */ 

#include "ServerSocket.hh"

#include "SocketException.hh"

#include <arpa/inet.h>
#include <errno.h>

namespace
{
  const int MAXHOSTNAME = 200;
  const int MAXCONNECTIONS = 5;
}

namespace sockwrpr
{
/*
 ******************************************************************************************************
 */
  
  ServerSocket::ServerSocket(const int port)
  {
    if ( !create() )
    {
      throw SocketException("Could not create server socket.");
    }

    if ( !bind(port) )
    {
      throw SocketException("Could not bind to port.");
    }

    if ( !listen() )
    {
      throw SocketException("Could not listen to socket.");
    }
  }
  
/*
 ******************************************************************************************************
 */

  ServerSocket::~ServerSocket()
  {
  }

/*
 ******************************************************************************************************
 */

  bool
  ServerSocket::bind(const int port)
  {

    if ( !isValid() )
    {
      return false;
    }

    mSocketAddress.sin_family = AF_INET;
    mSocketAddress.sin_addr.s_addr = INADDR_ANY;
    mSocketAddress.sin_port = htons(port);

    int bind_return = ::bind(mSocketNumber,
                             (sockaddr*)&mSocketAddress,
                             sizeof(mSocketAddress) );

    if ( bind_return == -1 )
    {
      return false;
    }

    return true;
}

/*
 ******************************************************************************************************
 */

  bool
  ServerSocket::listen() const
  {
    if ( !isValid() )
    {
      return false;
    }

    int listen_return = ::listen(mSocketNumber, MAXCONNECTIONS);


    if ( listen_return == -1 )
    {
      return false;
    }
  
    return true;
  }

  
/*
 ******************************************************************************************************
 */

  bool
  ServerSocket::accept(ServerSocket& newSocket) const
  {
    int addrLength = sizeof(mSocketAddress);
    newSocket.mSocketNumber = ::accept(mSocketNumber,
                                       (sockaddr*)&mSocketAddress,
                                       (socklen_t*) &addrLength);

    if ( newSocket.isValid() )
      return false;
    else
      return true;
  }
  
/*
 ******************************************************************************************************
 */

  const ServerSocket&
  ServerSocket::operator<<( const std::string& data) const
  {
    if ( !send(data) )
    {
      throw SocketException("Could not write to socket.");
    }

    return *this;
  }

/*
 ******************************************************************************************************
 */
  
  const ServerSocket&
  ServerSocket::operator>>(std::string& data) const
  {
    if ( !receive(data) )
    {
      throw SocketException("Could not read from socket.");
    }

    return *this;
  }

/*
 ******************************************************************************************************
 */

  void
  ServerSocket::acceptSocket(ServerSocket& socket)
  {
    if ( !accept(socket) )
    {
      throw SocketException("Could not accept socket.");
    }
  }

/*
 ******************************************************************************************************
 */
}
