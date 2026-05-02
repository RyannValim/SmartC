all: avl.o evento.o metricas.o menu.o main.o
	gcc avl.o evento.o metricas.o menu.o main.o -o SmartC

avl.o: avl.c avl.h
	gcc -c avl.c

evento.o: evento.c evento.h
	gcc -c evento.c

metricas.o: metricas.c metricas.h
	gcc -c metricas.c

menu.o: menu.c menu.h
	gcc -c menu.c

clean:
	rm -f *.o

run:
	./SmartC