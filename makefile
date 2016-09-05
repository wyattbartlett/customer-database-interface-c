#makefile	for project1
DB.o: DB.c
		cc	-c	DB.c

UI.o: UI.c
		cc	-c	UI.c

iofunctions.o: iofunctions.c
		cc	-c	iofunctions.c

project1:	DB.o	UI.o	iofunctions.o
		cc	-o	project1	DB.o	UI.o iofunctions.o