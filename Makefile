CXX = g++
CXXFLAGS = -g -std=c++20 -Wall -Wextra

all: game game_set

game: main.o card.o card_list.o
	$(CXX) $(CXXFLAGS) -o game main.o card.o card_list.o

game_set: main_set.o card.o
	$(CXX) $(CXXFLAGS) -o game_set main_set.o card.o

tests: tests.o card.o card_list.o
	$(CXX) $(CXXFLAGS) -o tests tests.o card.o card_list.o
	./tests

main.o: main.cpp card.h card_list.h
	$(CXX) $(CXXFLAGS) -c main.cpp

main_set.o: main_set.cpp card.h
	$(CXX) $(CXXFLAGS) -c main_set.cpp

tests.o: tests.cpp card.h card_list.h
	$(CXX) $(CXXFLAGS) -c tests.cpp

card.o: card.cpp card.h
	$(CXX) $(CXXFLAGS) -c card.cpp

card_list.o: card_list.cpp card_list.h card.h
	$(CXX) $(CXXFLAGS) -c card_list.cpp

clean:
	rm -f *.o game game_set tests
