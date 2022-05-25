CFLAGS = -g

all:
	gcc $(CFLAGS) client.c -o client
	gcc $(CFLAGS) server.c -o server

test:
	@bash run_tests.sh 0
	@bash run_tests.sh 1