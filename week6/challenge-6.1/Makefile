.PHONY: clean pristine

prog: adder.o main.o
	gcc -o main $^              

clean:
	rm -f *.o

pristine:
	rm -f *.o main

main.o: main.c
	gcc -Wall -Wextra -c $<

adder.o: adder.c
	gcc -Wall -Wextra -c $<