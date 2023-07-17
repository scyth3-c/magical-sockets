#ifndef MAGICAL_SOCKETS_HPP
#define MAGICAL_SOCKETS_HPP


#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdexcept>


#include <memory>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <functional>

#include <iostream>
#include <vector>

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::function;

constexpr const char* LOCALHOST = "127.0.0.1";
constexpr uint16_t DEFAULT_PORT = 3000;

constexpr int DOMAIN = AF_INET;
constexpr int TYPE = SOCK_STREAM;
constexpr int PROTOCOL = 0;

constexpr int MG_ERROR = -1;
constexpr int MG_OK = 0;
constexpr int MG_CONFUSED = 1;

constexpr int DEF_HEAP_LIMIT = 512;
constexpr int DEF_BUFFER_SIZE = 2048;


constexpr int UnCATCH_ERROR_CH = -66;


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
        int 
             setBuffer(int),
             setPort(uint16_t),
             getPort();

          void* _cache;
        
        virtual void getResponseProcessing() = 0;
        virtual int on(function<void(string*)>optional = [](string*)->void{}) = 0;
        virtual int Close() = 0;
        virtual string getResponse() const = 0;
};



class Server : public Engine {
  private:
     shared_ptr
               <string> buffereOd_data = nullptr;
     shared_ptr
               <int> static_sessions = make_shared<int>(1);



  public:
     
     Server(uint16_t Port) : Engine(Port){}
     Server() : Engine(DEFAULT_PORT){}
     ~Server(){}

     int on(function<void(string* clust)>optional = [](string*)->void{}) override;
     int Close() override;
     void setSessions(int);
     void sendResponse(string);
     void getResponseProcessing() override;
     inline string getResponse() const override {std::string base = *buffereOd_data;  return base;  }
};


class Client : public Engine {

     private: 
        shared_ptr
                    <string> message = make_shared<string>();
        shared_ptr
                    <int> socket_fd = make_shared<int>();
        shared_ptr
                    <string> IP_ADDRRESS = make_shared<string>();
        shared_ptr
                    <string> buffereOd_data = nullptr;

     public:
          Client(uint16_t Port) : Engine(Port){}
          Client() : Engine(DEFAULT_PORT){}
          ~Client(){}

     int on(function<void(string*)>optional = [](string*)->void{}) override;
     int Close() override;
     void setMessage(string);
     void setIP(string ip = LOCALHOST);
     void getResponseProcessing() override;
     inline string getResponse() const  override { return  *buffereOd_data; }
};



constexpr auto HTML = "text/html; charset=utf-8 ";
constexpr auto JSON = "application/json ";

struct WEB {

     WEB(){}

     static string json(string _txt, string status="200 OK") {
      return       "HTTP/1.1 "+status+"\n"
                   "Server: Magical/0.5\n"
                   "Content-Type: "+ JSON  +"\n"
                   "Content-Length: " + std::to_string(_txt.length()) + "\n"
                   "Accept-Ranges: bytes\n" +
                   "Connection: close\n"
                   "\n" +
                   _txt;
     }
     

     static string custom(string _txt, string type, string headers,  string status="200 OK"){
           return  "HTTP/1.1 "+status+"\n"
                   "Server: Magical/0.5\n"
                   "Content-Type: "+type+"\n"
                   "Content-Length: " + std::to_string(_txt.length()) + "\n"
                   "Accept-Ranges: bytes\n" +
                    headers
                    +
                   "Connection: close\n"
                   "\n" +
                   _txt;
     }     
};

template<class...P>
struct HEADERS_MG {
    HEADERS_MG(){}
    HEADERS_MG(std::initializer_list<P...>list): body(list) {}
    vector<string> body;
    string generate(){
        string response{""};
        for (auto &it : body) {
            response += it + "\n";
        }
        return response;
    }
};  

typedef HEADERS_MG<string> Headers;


constexpr auto HTTP_ERROR = "HTTP/1.1 400 BAD\n"
                           "Server: Magical/0.5\n"
                           "Content-Type: application/json\n"
                           "Content-Length: 25\n"
                           "Accept-Ranges: bytes\n"
                           "Connection: close\n"
                           "\n"
                           "error!";


#endif // !MAGICAL_SOCKETS_HPP
