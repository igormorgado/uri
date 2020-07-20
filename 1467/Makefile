
main:
	gcc -g --pedantic -Wall --std=c99 -o main main.c  -lm

run:
	./main < entrada.txt > saida.txt 

check:
	paste saida.txt esperado.txt | awk -v FS='\t' -v OFS='\t' -f check.awk

all: clean main run check

clean:
	rm -rf main
