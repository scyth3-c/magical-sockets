#ifndef MGSOCKETY_HPP
#define MGSOCKETY_HPP


#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <memory>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <cstring>

#include <iostream>
#include <vector>

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;

constexpr uint16_t DEFAULT_PORT = 3000;
constexpr int DOMAIN = AF_INET;
constexpr int TYPE = SOCK_STREAM;
constexpr int PROTOCOL = 0;

constexpr int MG_ERROR = -1;
constexpr int MG_OK = 0;
constexpr int MG_CONFUSED = 1;

constexpr int DEF_HEAP_LIMIT = 1024;
constexpr int DEF_BUFFER_SIZE = 3072;

class Engine {

   protected:
         
        struct sockaddr_in address;
        shared_ptr<uint16_t> PORT = nullptr;
        
        shared_ptr 
                   <int> 
                         socket_id = nullptr,
                         new_socket = nullptr,
                         state_receptor = nullptr,
                         heap_limit = make_shared<int>(DEF_HEAP_LIMIT),
                         address_len = make_shared<int>(sizeof(address)),
                         option_mame = make_shared<int>(1),
                         buffer_size = make_shared<int>(DEF_BUFFER_SIZE);
    public:

        explicit Engine(uint16_t);
        virtual ~Engine() = default;

        int create();
        int close(),
             setBuffer(int),
             setHeapLimit(int),
             getHeapLimit(),
             setPort(uint16_t),
             getPort();
        
        virtual string getResponse() = 0;
        virtual int on() = 0;
};



class Server : public Engine {
  private:
     shared_ptr
               <char> buffered_data = make_shared<char>();

     shared_ptr
               <int> static_sessions = make_shared<int>(1);
  public:
     
     Server(uint16_t Port) : Engine(Port){}
     Server() : Engine(DEFAULT_PORT){}
     ~Server(){}

     int on();
     string getResponse();
     void setSessions(int);
};


class Client : public Engine {

     private: 
        shared_ptr<const char*> message = make_shared<const char*>();
     
     public:
          Client(uint16_t Port) : Engine(Port){}
          Client() : Engine(DEFAULT_PORT){}
          ~Client(){}

     int on();
     void setMessage();
     string getResponse();
};



#endif // !MGSOCKETY_HPP