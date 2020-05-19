COMPILAR = gcc -c

LINKEAR  = gcc

MAIN 	 = main

OBJETOS  = main.o supersequence.o

.PHONY	 = all clean

all: $(MAIN)

clean:
	rm $(OBJETOS)
	rm $(MAIN)

supersequence.o: supersequence.c supersequence.h
	$(COMPILAR) supersequence.c -o supersequence.o

$(MAIN): main.c $(OBJETOS)
	$(COMPILAR) main.c -o main.o
	$(LINKEAR) $(OBJETOS) -o $(MAIN)