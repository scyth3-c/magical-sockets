#include <mgsocket.h>


int main(int argc, char const *argv[]) {
 

    Server mg;

    mg.create();
    mg.setPort(8080);
    mg.setBuffer(2048);
    mg.setSessions(1);



    mg.on();
   
    std::cout <<  mg.getResponse();



    mg.close();


    return 0;
}
