run: main
	./main

main: screen
	gcc -o main main.c screen.o line.o point.o double.o -lm

screen: line
	gcc -c screen.c

line: point
	gcc -c line.c

point: double
	gcc -c point.c

double:
	gcc -c double.c

clean:
	rm -f *.o
	rm main
