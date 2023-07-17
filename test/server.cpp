#include "mgsockets.h"

using std::cout; //show in terminal



int main() {
 

    Server server;  //create


    //configure
    server.create();
    server.setPort(8080);
    server.setBuffer(2048);


   //use
    server.on();


    string response = server.getResponse();
    std::cout << response;    
    server.sendResponse("OK response= "+response);


    server.Close();


    return 0;
}