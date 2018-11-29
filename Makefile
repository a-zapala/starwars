CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -lstdc++
CLANG = clang
.PHONY: all
all: starwars_example

starwars_example: zadanie/starwars_example.o src/rebelfleet.h src/imperialfleet.h src/battle.h.
	$(CLANG) $^ $(CXXFLAGS) -o $@

zadanie/%: CXXFLAGS += -I src


%.o: %.cc
	$(CLANG) $< $(CXXFLAGS) -c -o $@
	
clean:
	rm -f starwars_example
	find zadanie src -type f -name '*.o' | xargs rm -f
