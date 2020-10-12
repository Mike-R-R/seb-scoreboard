CXXFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter
OBJECTS=main.o ScoreboardController.o SnookerGame.o Player.o SnookerStack.o EnglishBilliardsGame.o Timer.o
BINARIES=main

# RGB Library resolution and flags
RGB_LIB_DISTRIBUTION=~/rpi-rgb-led-matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L $(RGB_LIBDIR) -l $(RGB_LIBRARY_NAME) -lrt -lm -lpthread -lncurses

all: $(BINARIES)

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

main: main.o ScoreboardController.o SnookerGame.o Player.o SnookerStack.o EnglishBilliardsGame.o Timer.o $(RGB_LIBRARY)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -I $(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(BINARIES)

FORCE:
.PHONY: FORCE

run:
	sudo ./main
