CC = g++
CC_FLAGS = -g -Wall -std=c++11 -ggdb
COMPILE_OBJ = $(CC) $(CC_FLAGS) -c
COMPILE_EXE = $(CC) $(CC_FLAGS)
OUT = obj
CREATE_DIR = mkdir -p
DELETE_FILE = rm -f

GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

$(shell $(CREATE_DIR) $(OUT))

all: tests laundry remdup deque_test stack_test

remdup: rem_dup.cpp $(OUT)/rem_dup_lib.o
	$(COMPILE_EXE) rem_dup.cpp $(OUT)/rem_dup_lib.o -o remdup

laundry: laundry.cpp stack.h
	$(COMPILE_EXE) laundry.cpp stack.h -o laundry

tests: tests.cpp $(OUT)/rem_dup_lib.o
	$(COMPILE_EXE) tests.cpp $(OUT)/rem_dup_lib.o -o tests

deque_test: $(OUT)/deque_test.o $(OUT)/rem_dup_lib.o
	$(COMPILE_EXE) $(OUT)/deque_test.o $(OUT)/rem_dup_lib.o $(GTEST_LL) -o deque_test

stack_test: $(OUT)/stack_test.o
	$(COMPILE_EXE) $(OUT)/stack_test.o $(GTEST_LL) -o stack_test

$(OUT)/stack_test.o: stack_test.cpp
	$(COMPILE_OBJ) stack_test.cpp -o $(OUT)/stack_test.o

$(OUT)/deque_test.o: deque_test.cpp
	$(COMPILE_OBJ) deque_test.cpp -o $(OUT)/deque_test.o

$(OUT)/rem_dup_lib.o: rem_dup_lib.h rem_dup_lib.cpp
	$(COMPILE_OBJ) rem_dup_lib.cpp -o $(OUT)/rem_dup_lib.o

.PHONY:  clean

clean:
	$(DELETE_FILE) *.o
	$(DELETE_FILE) *.d	
	$(DELETE_FILE) *.exe
	$(DELETE_FILE) $(OUT)/*.o
	$(DELETE_FILE) $(OUT)/*.d
	$(DELETE_FILE) $(OUT)/*.exe
