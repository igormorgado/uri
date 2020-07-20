TARGET=main
CC = gcc
CFLAGS = -g --pedantic -Wall --std=c99 
LIBS = -lm

$(TARGET):
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

run:
	./$(TARGET) < entrada.txt > saida.txt 

test:
	@echo Running tests...
	@paste saida.txt esperado.txt | awk -v FS='\t' -v OFS='\t' -f test.awk

debug: clean main
	./$(TARGET) < entrada.txt

all: clean main run test

clean:
	rm -rf $(TARGET)
