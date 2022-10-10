CC = gcc
OBJ = main.o admin.o menu.o student.o teacher.o S_manage.o
BIN = S_manage.bin
STD = -std=gnu99
FLAG = -Werror -Wall #-DDEBUG

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ) && ./$(BIN)

main.o:main.c
	$(CC) $(STD) $(FLAG) -c main.c

admin.o:admin.c admin.h
	$(CC) $(STD) $(FLAG) -c admin.c

menu.o:menu.c menu.h
	$(CC) $(STD) $(FLAG) -c menu.c

teacher.o:teacher.c teacher.h
	$(CC) $(STD) $(FLAG) -c teacher.c

student.o:student.c student.h
	$(CC) $(STD) $(FLAG) -c student.c

admin.o:admin.c admin.h
	$(CC) $(STD) $(FLAG) -c admin.c

clean:
	rm -rf $(BIN) $(OBJ)

