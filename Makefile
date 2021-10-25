CC=clang
		
target: main.o api.o input.o commands.o threads.o
	clang -g -o target.exe main.o api.o input.o commands.o threads.o -lcurl -lpthread

main.o: main.c
	gcc -g -c main.c 

input.o: IO/input.c
	gcc -g -c IO/input.c

commands.o: commands/commands.c
	gcc -g -c commands/commands.c

api.o: api/api.c
	gcc -g -c api/api.c

threads.o: threads/threads.c
	gcc -g -c threads/threads.c


clean:
	rm *.o
	rm *.exe



