#!/bin/bash

if [ $# != 2 ] ; then
    echo "USAGE: ./stress_connection_server.sh ADDRESS PORT"
    exit 84
fi

ADDRESS=$1
PORT=$2

if [ ADDRESS == "localhost" ] ; then
    ADDRESS = "127.0.0.1"
fi

i=0

while [ ${i} -le 1040 ] ; do
    nc -C ${ADDRESS} ${PORT} &
    sleep 0.005
    ((i++))
done

exit 0
