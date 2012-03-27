#ifndef ISOCKETBASE_HH_
#define ISOCKETBASE_HH_

/**
 * Base Socket class interface for implementing the
 * client and the server.
 *
 * @author awidegreen
 */

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

namespace sockwrpr
{
  class ISocketBase
  {
  protected:
    /**
     * ctor.
     */
    ISocketBase();

    /**
     * dtor.
     */
    virtual ~ISocketBase();

    //--- common socket methods.
    /**
     * Used to create a Socket.
     */
    bool create();

    /**
     * Used for data transmission, sending dta.
     */
    bool send(const std::string data) const;

    /**
     * Used for data transmission, receiving data.
     */
    int receive(std::string& data) const;

    /**
     * Indicates if the Socket is valid.
     */
    bool isValid() const
    {
      return ( mSocketNumber != -1 );
    }
     
    /**
     * Set the socket to nonblocking.
     */
    void setNonBlocking(const bool blocking);
    //-----

    int mSocketNumber;
    sockaddr_in mSocketAddress;
  private:
    
  };
} // end namespace 

#endif // ISOCKETBASE_HH_
