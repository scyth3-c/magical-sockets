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

        if( bind(*socket_id, (struct sockaddr *)&address, sizeof(address)) < 0) {
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


char* Server::getResponse() {

char _A = 'E';
char* forbiden =& _A;

try {
     
     char* buffer = new char[5000];
     read(*new_socket, buffer, *buffer_size);
     return buffer;
}
catch(const std::exception& e) {
     std::cerr << e.what() << '\n';
     return forbiden;
}
}
