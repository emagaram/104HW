# Some of the commands in here might be dependent on which command shell is used to
# execute it. For example, commands that delete and create files and folders are
# slightly different under the bash shell, PowerShell, and Windows command prompt.
# Also path separators are different in bash than in PowerShell and the Windows
# command prompt.

CC = g++
CC_FLAGS = -g -Wall -std=c++11 -ggdb
COMPILE_OBJ = $(CC) $(CC_FLAGS) -c
COMPILE_EXE = $(CC) $(CC_FLAGS)
OUT = obj
CREATE_DIR = mkdir -p
DELETE_FILE = rm -f


GTEST_LIB = ../../googletest/build/lib
GTEST_INCLUDE = ../../googletest/googletest/include/
COMPILE_GTEST_OBJ = $(CC) -std=c++17 -Wall -I h -I $(GTEST_INCLUDE) -c -ggdb -g
COMPILE_GTEST_EXE = $(CC) -std=c++17 -I h -pthread -ggdb -g

$(shell $(CREATE_DIR) $(OUT))

all: tests.exe deque.exe deque_test.exe

deque.exe: deque.h deque.cpp
	$(COMPILE_EXE) deque.h deque.cpp -o deque.exe

tests.exe: tests.cpp $(OUT)/rem_dup_lib.o
	$(COMPILE_EXE) tests.cpp $(OUT)/rem_dup_lib.o -o tests.exe

deque_test.exe: $(OUT)/deque_test.o $(OUT)/rem_dup_lib.o
	$(COMPILE_GTEST_EXE) $(OUT)/deque_test.o $(OUT)/rem_dup_lib.o $(GTEST_LIB)/libgtest_main.a $(GTEST_LIB)/libgtest.a -o deque_test.exe

$(OUT)/deque_test.o: deque_test.cpp
	$(COMPILE_GTEST_OBJ) deque_test.cpp -o $(OUT)/deque_test.o

$(OUT)/rem_dup_lib.o: rem_dup_lib.h rem_dup_lib.cpp
	$(COMPILE_OBJ) rem_dup_lib.cpp -o $(OUT)/rem_dup_lib.o

$(OUT)/deque.o: deque.h 
	$(COMPILE_OBJ) deque.h -o $(OUT)/deque.o

.PHONY:  clean

clean:
	$(DELETE_FILE) *.o
	$(DELETE_FILE) *.d	
	$(DELETE_FILE) *.exe
	$(DELETE_FILE) $(OUT)/*.o
	$(DELETE_FILE) $(OUT)/*.d
	$(DELETE_FILE) $(OUT)/*.exe
