CC     = g++
CFLAGS += -g -Wall -std=c++11
SRC    = $(wildcard *.cc)
#OBJS   = $(SRC:.cc=.o)
BINS   = $(SRC:.cc=)
LIBS   = 

all:$(BINS)

# bin files depend on *.cc files
%:%.cc
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f *.o $(BINS)
