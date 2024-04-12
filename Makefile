run: main
	./main

main: screen
	gcc -o main main.c screen.o line.o point.o utils.o -lm

screen: line
	gcc -c screen.c

line: point
	gcc -c line.c

point: utils
	gcc -c point.c

utils:
	gcc -c utils.c

clean:
	rm -f *.o
	rm main
