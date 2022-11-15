# Magical Sockets

controla y usa los sockets con facilidad, captura o lanza peticiones a direcciones IP o en localhost!  transmite informacion con facilidad por la red

<hr/>

control and use sockets with ease, capture or launch requests to IP addresses or localhost! transmit information with ease over the network

![example](https://user-images.githubusercontent.com/52190352/201794656-4da648f1-87ff-42c7-a22d-3c2d2ee235f8.png)


<hr/>

## How to

### compile 
    
```    
   ├── Makefile
    └── src
       ├── client.cpp
       └── server.cpp



      
      make file=server route=folder_server
      
      or
      
      make file=client route=folder_client
      
```      
      
### use

 
```
    result


   ── folder_server
   ├── app
   └── objects
       ├── mgsockets.d
       ├── mgsockets.o
       ├── server.d
       └── server.o
     
     
     
     
   ── folder_client
   ├── app
   └── objects
       ├── client.d
       ├── client.o
       ├── mgsockets.d
       └── mgsockets.o
       
       
       
      
      RUN
      
      ./server/app
      ./client/apo
       
    
    
    
       
```
    
    
    
    
    
