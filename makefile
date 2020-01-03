all:	control.c main.c
		gcc -c control.c
		gcc -c main.c
		gcc -o control control.o
		gcc -o write main.o
