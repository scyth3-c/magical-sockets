#include "mgsockets.h"


int main() {
 

    Client client;

    client.create();


    client.setIP(LOCALHOST);
    client.setPort(8080);

    
    client.setBuffer(2048);
    client.setMessage("Hello");



    client.on();

        std::cout <<  client.getResponse();

    client.Close();


    return 0;
}
