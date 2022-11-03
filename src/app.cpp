#include <mgsocket.h>


int main(int argc, char const *argv[]) {
 
    Server mg;

    mg.create();
    mg.setPort(8080);
    mg.setSessions(3);
    mg.setBuffer(5000);


    mg.on();

    std::cout <<  mg.getResponse();

    mg.close();


    return 0;
}
