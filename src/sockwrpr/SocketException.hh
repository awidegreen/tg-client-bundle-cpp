#ifndef SOCKETEXCEPTION_HH_
#define SOCKETEXCEPTION_HH_
/**
 * Implements a socket exception which is thrown
 * when an error in the socket init/communication
 * occurs.
 * @author awidegreen
 */

#include <string>

namespace sockwrpr
{

  class SocketException
  {
  public:
    SocketException( std::string msg ) : mMsg ( msg )
      {}
    ~SocketException()
      {}

    std::string description()
      { return mMsg; }

  private:
    std::string mMsg;

  };
} // end namespace

#endif // SOCKETEXCEPTION_HH_
