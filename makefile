main:clean
	gcc main.c server.c client.c net.c thread.c display.c -o main
clean:
	rm -f client server main
