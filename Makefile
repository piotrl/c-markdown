PROG = markdown

FILES = markdown.o main.o stack.o

$(PROG) : $(FILES)
	gcc -Wall -std=c99 $(FILES) -o $(PROG)

markdown.o : config.h markdown.h stack.h
main.o : config.h markdown.h stack.h
stack.o : stack.h

clean :
	rm -f *~
	rm -f *.o
