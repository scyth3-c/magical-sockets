#include "mgsockets.h"

using std::cout;


int main() {
   
   // in http://localhost:8080

    Server server; 

    server.create();
    server.setPort(8080);
    server.setBuffer(2048);

    string token = "123";

    auto func = [&](string* data) {

            std::cout << *data;  // *data is the client message 

            token = *data + "-trick!";
            
    };


    server.on(func);
    server.sendResponse(token); // sent the same response to client +  "-trick!""
    server.Close();


    return 0;
}