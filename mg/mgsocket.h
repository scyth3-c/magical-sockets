#ifndef MGSOCKETY_HPP
#define MGSOCKETY_HPP


#include <netinet/in.h>
#include <sys/socket.h>

#include <memory>
#include <unistd.h>
#include <stdlib.h>
#include <string>

#include <iostream>

using std::string;
using std::shared_ptr;
using std::make_shared;


constexpr uint16_t DEFAULT_PORT = 3000;
constexpr int DOMAIN = AF_INET;
constexpr int TYPE = SOCK_STREAM;
constexpr int PROTOCOL = 0;

constexpr int MG_ERROR = -1;
constexpr int MG_OK = 0;
constexpr int MG_CONFUSED = 1;



class Engine {

   protected:
        
        struct sockaddr_in address;
        shared_ptr<uint16_t> PORT = nullptr;
        
        shared_ptr 
                   <int> 
                         socket_id = nullptr,
                         new_socket = nullptr,
                         state_receptor = nullptr,
                         address_len = make_shared<int>(sizeof(address)),
                         option_mame = make_shared<int>(1),
                         static_sessions = make_shared<int>(1),
                         buffer_size = make_shared<int>(2048);
    public:

        explicit Engine(uint16_t);
        virtual ~Engine() = default;

        int create();
        int close(),
             setBuffer(int),
             setPort(uint16_t),
             getPort();
        
        virtual char* getResponse() = 0;
        virtual void setSessions(int) = 0;
        virtual int on() = 0;

    
};


class Server : public Engine {
  
  private:
     shared_ptr
               <char> buffered_data = make_shared<char>();

  public:
     
     Server(uint16_t Port) : Engine(Port){}
     Server() : Engine(DEFAULT_PORT){}
     ~Server(){}

     int on();
     char* getResponse();
     void setSessions(int);

};



#endif // !MGSOCKETY_HPP