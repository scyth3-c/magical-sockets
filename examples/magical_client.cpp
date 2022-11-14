#include "mgsockets.h"


int main(int argc, char const *argv[]) {
 

    Client client;

    client.create();


    client.setIP(LOCALHOST);
    client.setPort(8080);

    
    client.setBuffer(2048);
    client.setMessage("Hello");



    auto func = [&](string* data){

            *data = *data + "-truncado!!";   // data is the server response        
    };


    client.on(func);
    
            std::cout << client.getResponse();

    client.Close();
    

    return 0;
}
