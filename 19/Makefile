CFLAGS				=	-Wfatal-errors -std=c++23 -Wall -pedantic -Werror -O3

INCLUDE_PATH		=	-I../common
LIBS				=

all: 01 02 03
	
%: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE_PATH) $(LIBS) $< -o $@
	
clean:
	rm -f 01 02 03

run1: 01
	cat input0 | ./01
	
run2: 02
	cat input1 | ./02
	
run3: 03
	cat input2 | ./03
	
.PHONY: clean run1 run2 run3
