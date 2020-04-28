#!/bin/bash


start=`date +%s`
for i in $(seq 1 1 100)
do
   	curl -i -X GET http://127.0.0.1:8888/index.html
done
end=`date +%s` 
dif=$[ end - start ] 
echo -e "\n\n\n time: $dif s"
