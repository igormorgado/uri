TARGET=main
CC = gcc
CFLAGS = -ggdb --pedantic -Wall --std=c99 -O2
LIBS = -lm

$(TARGET):
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

run:
	./$(TARGET) < entrada.txt > saida.txt 

test:
	@echo Running tests...
	@paste saida.txt esperado.txt | awk -v FS='\t' -v OFS='\t' -f test.awk

all: clean main run test

debug: clean
	$(CC) -o $(TARGET) $(TARGET).c -g -DDEBUG $(CFLAGS) $(LIBS)
	./$(TARGET) < entrada.txt

submit: clean
	cpp -P $(TARGET).c > submit.c

clean:
	rm -rf $(TARGET) submit.c
