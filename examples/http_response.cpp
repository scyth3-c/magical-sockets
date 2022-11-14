#include "mgsockets.h"

using std::cout;


int main() {
   
   // in http://localhost:8080

    Server server; 

    server.create();
    server.setPort(8080);
    server.setBuffer(2048);

    string response = "123";




    auto web_verify = [&](string* data) {
        
            // *data is the client message  

            int len = data->length();

            if(len >= 250) {

                response = WEB::json("hola web!", "200 OK");  //generate a http response with type json 

             } else {   

                HEADERS test = { "test:", "true", "example:", "1" };
                response= WEB::custom("<h1>error!</h1>", HTML,  test.generate(),  "400 BAD");
         }
    };




    server.on(web_verify);
    server.sendResponse(response); // sent the processing response to client 
    server.Close();


    return 0;
}