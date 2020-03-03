all: SimpleToolKit

SimpleToolKit: main.o crypto.o employee_directory.o
	gcc main.o crypto.o employee_directory.o -o SimpleToolKit
	sudo chown root:root SimpleToolKit
	sudo chmod 4555 SimpleToolKit
	sudo chmod 600 ./password.txt


main.o: main.c
	gcc -g -c main.c

crypto.o: crypto.c
	gcc -g -c crypto.c

employee_directory.o: employee_directory.c
	gcc -g -c employee_directory.c

clean:
	rm -rf *.o SimpleToolKit
