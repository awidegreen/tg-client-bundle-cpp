/**
 * ClientSocket implementation
 * @author awidegreen
 */ 

#include "ClientSocket.hh"

#include "SocketException.hh"

#include <arpa/inet.h>
#include <errno.h>
#include <iostream>

namespace sockwrpr
{

/*
 ******************************************************************************************************
 */
  ClientSocket::ClientSocket(std::string host, int port)
  {
    if ( !create() )
    {
      throw SocketException("Could not create client socket.");
    }
    
    if ( !connect(host, port) )
    {
      throw SocketException("Could not connect to host/port");
    }
  }

/*
 ******************************************************************************************************
 */

  bool
  ClientSocket::connect(const std::string host, int port)
  {
    if ( !isValid() )
      return false;

    std::cout << "Try to connect to " << host << " on port " << port << std::endl;

    mSocketAddress.sin_family = AF_INET;
    // sets the port
    mSocketAddress.sin_port = htons(port);
    // ip addr
    //mSocketAddress.sin_addr.s_addr = inet_addr(host.c_str());

    // converts string to ip-addr
    int status = inet_pton(AF_INET, host.c_str(), &mSocketAddress.sin_addr);

    //std::cout << "connect with mSocketNumber: " << mSocketNumber << std::endl;
    status = ::connect(mSocketNumber,
                       reinterpret_cast<sockaddr*>(&mSocketAddress),
                       sizeof(mSocketAddress));

    
    if ( errno == EAFNOSUPPORT )
    {
       return false;
    }

    if ( status == 0 )
       return true;
    else
    {
       std::cout << "connect status return: " << status
                 << " errno: " << errno << std::endl;
       return false;
    }
  }
  
/*
 ******************************************************************************************************
 */

  const ClientSocket&
  ClientSocket::operator<<( const std::string& data ) const
  {
    if ( !send(data) )
    {
      throw SocketException ( "Could not write to socket." );
    }

    return *this;
  }
  
/*
 ******************************************************************************************************
 */

  const ClientSocket&
  ClientSocket::operator>>(std::string& data) const
  {
    if ( !receive(data) )
    {
      throw SocketException ( "Could not read from socket." );
    }

    return *this;
  }

/*
 ******************************************************************************************************
 */

  void
  ClientSocket::sendData(const std::string& data)
  {
    *this << data;
  }
  
/*
 ******************************************************************************************************
 */

  void
  ClientSocket::receiveData(std::string& data)
  {
    *this >> data;
  }
  
/*
 ******************************************************************************************************
 */
  
  
}
