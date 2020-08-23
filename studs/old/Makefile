TARGETS = subset_backtrack subset_recursive permut_backtrack permut_recursive knight_tour
CC = gcc
CFLAGS = -g -Wno-unused-function --pedantic -Wall --std=c99 
LIBS = -lm

all: clean $(TARGETS)

$(TARGETS):
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)


clean:
	@rm -rf $(TARGETS) *.o
