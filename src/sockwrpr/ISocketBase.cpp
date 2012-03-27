/**
 * ISocketBase implementation.
 * @author awidegreen
 */

#include "ISocketBase.hh"

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

namespace
{
  const int MAXRECV = 500;
}

namespace sockwrpr
{
  ISocketBase::ISocketBase() :
    mSocketNumber(-1)
  {
      memset( &mSocketAddress, 0, sizeof(mSocketAddress) );
  }

/*
 ******************************************************************************************************
 */

  ISocketBase::~ISocketBase()
  {
    if ( isValid() )
    { // close socket if valid.
      ::close(mSocketNumber);
    }
  }

/*
 ******************************************************************************************************
 */

  bool
  ISocketBase::create()
  {
    mSocketNumber = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if ( !isValid() )
      return false;


    // TIME_WAIT - argh
    int on = 1;
    if ( setsockopt(mSocketNumber,
                    SOL_SOCKET,
                    SO_REUSEADDR,
                    (const char*)&on,
                    sizeof(on)) == -1 )
      return false;


    return true;
  }

/*
 ******************************************************************************************************
 */
  bool 
  ISocketBase::send(const std::string data) const
  {
      int status = ::send(mSocketNumber, data.c_str(), data.size(), MSG_NOSIGNAL);
      if ( status == -1 )
      {
        return false;
      }
      else
      {
        return true;
      }
  }

/*
 ******************************************************************************************************
 */
  int
  ISocketBase::receive(std::string& data) const
  {
    char buf [MAXRECV + 1];

    data.clear();

    memset(buf, 0, MAXRECV + 1);

    int status = ::recv(mSocketNumber, buf, MAXRECV, 0);

    if ( status == -1 )
    {
      std::cout << "status == -1   errno == " << errno << "  in Socket::receive" << std::endl;
      return 0;
    }
    else if ( status == 0 )
    {
      return 0;
    }
    else
    {
      data = buf;
      return status;
    }
  }

/*
 ******************************************************************************************************
 */

  void
  ISocketBase::setNonBlocking(const bool blocking)
  {
    int opts;
    
    opts = fcntl(mSocketNumber, F_GETFL );

    if ( opts < 0 )
    {
      return;
    }

    if ( blocking )
      opts = ( opts | O_NONBLOCK );
    else
      opts = ( opts & ~O_NONBLOCK );
    
    fcntl(mSocketNumber, F_SETFL, opts);
  }

/*
 ******************************************************************************************************
 */

} // end namespace
