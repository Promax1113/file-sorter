main: main.c
	gcc main.c -o a

clean:
	ls | grep -v "\." | grep -v Makefile | xargs rm
