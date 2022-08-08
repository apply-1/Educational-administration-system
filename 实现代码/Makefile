CC=gcc
BIN=system.bin
OBJ=main.o chief.o admin.o admin_chief.o admin_tools.o student.o student_tools.o teacher.o teacher_tools.o student_chief.o teacher_chief.o tools.o
FLAG=-Wall -Werror -DDEBUG
STD=-std=gnu99

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ)
main.o:main.c chief.h
	$(CC) $(STD) $(FLAG) -c main.c
chief.o:chief.c admin.h student.h teacher.h tools.h
	$(CC) $(STD) $(FLAG) -c chief.c
tools.o:tools.c
	$(CC) $(STD) $(FLAG) -c tools.c
admin.o:admin.c chief.h admin_tools.h admin_chief.h tools.h
	$(CC) $(STD) $(FLAG) -c admin.c
admin_chief.o:admin_chief.c chief.h tools.h
	$(CC) $(STD) $(FLAG) -c admin_chief.c
admin_tools.o:admin_tools.c chief.h tools.h
	$(CC) $(STD) $(FLAG) -c admin_tools.c
student.o:student.c chief.h student_tools.h student_chief.h
	$(CC) $(STD) $(FLAG) -c student.c
student_chief.o:student_chief.c student_tools.h chief.h tools.h
	$(CC) $(STD) $(FLAG) -c student_chief.c
student_tools.o:student_tools.c chief.h tools.h
	$(CC) $(STD) $(FLAG) -c student_tools.c
teacher.o:teacher.c chief.h teacher_tools.h teacher_chief.h
	$(CC) $(STD) $(FLAG) -c teacher.c
teacher_chief.o:teacher_chief.c chief.h tools.h
	$(CC) $(STD) $(FLAG) -c teacher_chief.c
teacher_tools.o:teacher_tools.c chief.h tools.h
	$(CC) $(STD) $(FLAG) -c teacher_tools.c
clean:
	rm -rf $(BIN) $(OBJ)

