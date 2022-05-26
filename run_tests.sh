FILE=$1
server v4 5501 &
client 127.0.0.1 5501 <./tests/$FILE.in

server v6 5501 &
client ::1 5501 <./tests/$FILE.in
