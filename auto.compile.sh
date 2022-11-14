#!/bin/bash
#compile-server-client

rm -rf server ;
rm -rf client ;

make file=server route=server ;
make file=client route=client ;

./server/app ;
