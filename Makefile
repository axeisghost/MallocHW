CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror -lm
#OPTFLAG = -O2
DEBUGFLAG = -g

# This is the name of the static archive to produce
# Don't change this line
LIBRARY = malloc

# The C and H files
# Your test file SHOULD NOT be in this line
CFILES = my_malloc.c my_sbrk.c
HFILES = my_malloc.h

PROGRAM = hw11

# Targets:
# test -- runs your test program
# clean -- removes compiled code from the directory
 

#test: CFLAGS += $(OPTFLAG) 
test: $(PROGRAM)-test
	./$(PROGRAM)-test

$(PROGRAM)-test: lib$(LIBRARY).a test.c
	$(CC) $(CFLAGS) $(DEBUGFLAG) test.c -L . -l$(LIBRARY) -o $@

OFILES = $(patsubst %.c,%.o,$(CFILES))

lib$(LIBRARY).a: $(OFILES)
	ar -cr lib$(LIBRARY).a $(OFILES)
%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) $(DEBUGFLAG) -c $<

clean:
	rm -rf lib$(LIBRARY).a $(PROGRAM)-test $(OFILES)
