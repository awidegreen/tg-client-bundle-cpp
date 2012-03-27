#include "sockwrpr/ClientSocket.hh"
#include "sockwrpr/SocketException.hh"
#include "strtk/strtk.hpp"

#include <string>
#include <iostream>

int main(int argc, char **argv)
{
   std::string cmdToSend = "register awidegreen";

   try
   {
      std::string host = "130.100.97.29";
//      host = "127.0.0.1";
      int port = 50001;

      sockwrpr::ClientSocket csock(host, port);

      std::string reply;

      csock << cmdToSend;
      csock >> reply;

      std::cout << "the reply from the server was: " << reply << std::endl;
      
      std::string respCode;
      std::string respParam;
      
      if ( strtk::parse(reply, " ", respCode, respParam) )
      {
        std::cout << "respCode: " << respCode
                  << " ; respParam: " << respParam
                  << std::endl;
      }
      else
      {
        std::cerr << "I was unable to parse the received string." << std::endl;
        return 1;
      }
   }
   catch ( sockwrpr::SocketException& e )
   {
      std::cout << "SocketExpection caught: " << e.description() << std::endl;
      return 1;
   }

   return 0;
}
