#include "mgsocket.h"

Engine::Engine(uint16_t _xport)  {
     PORT = make_shared<uint16_t> (_xport);
}

int Engine::create(){
try {

   if(socket_id = make_shared<int>(
                                socket(DOMAIN, TYPE, PROTOCOL)
                              )){
           return MG_ERROR;
     } 
   return MG_OK;
}
catch(const std::exception& e) {
     std::cerr << e.what() << '\n';
     return MG_CONFUSED;
}
}


int Engine::close() {
     try {
        if(shutdown(*socket_id, SHUT_RDWR)){
          return MG_ERROR;
        }
        return MG_OK;
     }
     catch(const std::exception& e)
     {
          std::cerr << e.what() << '\n';
          return MG_CONFUSED;
     }
}

int Engine::setPort(uint16_t xPort){
      try {
          PORT.reset( new uint16_t(std::move(xPort)));
          return MG_OK;
      }
      catch(const std::exception& e)
      {
          std::cerr << e.what() << '\n';
          return MG_ERROR;
      }
} 

int Engine::setHeapLimit(int _max){
     try {
          if(heap_limit == nullptr) {
               heap_limit = make_shared<int>(std::move(_max));
               return MG_CONFUSED;
          } 
          heap_limit.reset(new int(std::move(_max)));
          return MG_OK;
     }
     catch(const std::exception& e){
          std::cerr << e.what() << '\n';
          return MG_ERROR;
     }
}

int Engine::getHeapLimit(){
     try {
          if(*heap_limit > 0) {
               return *heap_limit;
          }  else{
               heap_limit = make_shared<int>(DEF_HEAP_LIMIT);
               return *heap_limit;
          }
     }
     catch(const std::exception& e) {
          std::cerr << e.what() << '\n';
          return MG_ERROR;
     }
}


int Engine::getPort() {
     try {
          if(*PORT > 0) {
               return *PORT;
          } else{
               MG_ERROR;
          }
     }
     catch(const std::exception& e)
     {
          std::cerr << e.what() << '\n';
     }
     return MG_CONFUSED;
}


int Engine::setBuffer(int _tamx) {
     try {
           if(buffer_size == nullptr) {
                buffer_size = make_shared<int>(std::move(_tamx));
                return MG_CONFUSED;
           }
           buffer_size.reset(new int(std::move(_tamx)));
           return MG_OK;
     }
     catch(const std::exception& e) {
          std::cerr << e.what() << '\n';
          return MG_ERROR;
     }
}


void Server::setSessions(int max) {
 try {
     if(static_sessions == nullptr){
          static_sessions = make_shared<int>(std::move(max));
          return;
     } 
     static_sessions.reset(new int(std::move(max)));
 }
 catch(const std::exception& e) {
     std::cerr << e.what() << '\n';
 }
}



int Server::on() {
     try {

          if( setsockopt(*socket_id,
                        SOL_SOCKET, 
                        SO_REUSEADDR | 
                        SO_REUSEPORT, 
                        &*option_mame, 
                        sizeof(*option_mame)) != 0 )
                        {
                         return MG_ERROR;
                        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(*PORT);

      if(bind(*socket_id, (struct sockaddr *)&address, sizeof(address)) < 0) {
           return MG_ERROR;
        }

        if(listen(*socket_id, *static_sessions) < 0) {
          return MG_ERROR;
        }

     if((new_socket = make_shared<int>(
                                        accept(*socket_id,
                                               (struct sockaddr *)&address,  
                                               (socklen_t *)&address_len))) < 0) {
                                                       return MG_ERROR;
                                               }
          return MG_OK;
     }
     catch(const std::exception& e)
     {
          std::cerr << e.what() << '\n';
          return MG_CONFUSED;
     } 
}



string Server::getResponse() {
char _A = '?';
char* forbiden =& _A;
try {

     string receptor{};
     vector<char> buffer = {0};
     buffer.reserve(*buffer_size);
     read(*new_socket, buffer.data(), *buffer_size);

     for (int it = 0; it <= *buffer_size-(*heap_limit); it++) {
          receptor += buffer[it];
     }
     return receptor;

}
catch(const std::exception& e) {
     std::cerr << e.what() << '\n';
     return forbiden;
}
}


int Client::on(){
     try {
               if( setsockopt(*socket_id,
                        SOL_SOCKET, 
                        SO_REUSEADDR | 
                        SO_REUSEPORT, 
                        &*option_mame, 
                        sizeof(*option_mame)) != 0 )
                        {
                         return MG_ERROR;
                        }
          
        address.sin_family = AF_INET;
        address.sin_port = htons(*PORT);

        if(inet_pton(AF_INET,  "127.0.0.1", & address.sin_addr ) <= 0 ){
          throw "error, invalid address";
        }
        if(make_shared<int>(connect(*socket_id, (struct sockaddr*)&address, sizeof(address)))){
               throw "error, fail connect";
        }
        send(*socket_id, *message, std::strlen(*message), 0);
        return MG_OK;
     }
     catch(const std::exception& e) {
          std::cerr << e.what() << '\n';
          return MG_ERROR;
     }
}
 
string Client::getResponse(){
char _A = '?';
char* forbiden =& _A;
try {
     string recept{};
     vector<char> buffer = {0};
     buffer.reserve(*buffer_size);
     read(*new_socket, buffer.data(), *buffer_size);

     for (int it = 0; it <= *buffer_size-(*heap_limit); it++) {
          recept += buffer[it];
     }
     return recept;
}
catch(const std::exception& e) {
     std::cerr << e.what() << '\n';
     return forbiden;
}
}

void Client::setMessage()