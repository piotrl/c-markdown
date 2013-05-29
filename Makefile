PROG = markdown

FILES = markdown.o main.o stack.o

$(PROG) : $(FILES)
	gcc -Wall -std=c99 $(FILES) -o $(PROG)

markdown.o : libs/config.h libs/markdown.h libs/stack.h
main.o : libs/config.h libs/markdown.h libs/stack.h
stack.o : libs/stack.h

clean :
	rm -f *~
	rm -f *.o
