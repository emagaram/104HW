BINDIR := bin

CXX := g++
CXXFLAGS := -g -Wall -std=c++11

VALGRIND := valgrind --tool=memcheck

GTEST_CXXFLAGS := -I /usr/include/gtest/
GTEST_LDFLAGS := -l gtest_main -l gtest -pthread

all: test

# Create binary dir
$(BINDIR)/.dirstamp:
	mkdir -p $(BINDIR)
	touch $(BINDIR)/.dirstamp

# provided test executable
piazza-tests: $(BINDIR)/piazza-tests.o $(BINDIR)/piazza.o 
	$(CXX) $(CXXFLAGS) $^ $(GTEST_LDFLAGS) -o $@

# $(BINDIR)/piazza-test-functions.o

# grading test executable
piazza-grading-tests: $(BINDIR)/piazza-grading-tests.o $(BINDIR)/piazza.o 
	$(CXX) $(CXXFLAGS) $^ $(GTEST_LDFLAGS) -o $@

#$(BINDIR)/piazza-test-functions.o

# provided test using solution executable
piazza-tests-sol: $(BINDIR)/piazza-tests.o $(BINDIR)/piazza-sol.o 
	$(CXX) $(CXXFLAGS) $^ $(GTEST_LDFLAGS) -o $@

#$(BINDIR)/piazza-test-functions.o

# grading test using solution executable
piazza-grading-sol: $(BINDIR)/piazza-grading-tests.o $(BINDIR)/piazza-sol.o 
	$(CXX) $(CXXFLAGS) $^ $(GTEST_LDFLAGS) -o $@

# $(BINDIR)/piazza-test-functions.o

# generic rule for .cpp files
$(BINDIR)/%.o : %.cpp $(BINDIR)/.dirstamp
	$(CXX) -c $(CXXFLAGS) $(GTEST_CXXFLAGS) $< -o $@

# student test target
test: piazza-tests
	$(VALGRIND) ./piazza-tests

# grading test target
grade: piazza-grading-tests
	$(VALGRIND) ./piazza-grading-tests

# header dependencies
$(BINDIR)/piazza-tests.o:  piazza.h
$(BINDIR)/piazza-grading-tests.o:  piazza.h
$(BINDIR)/piazza.o: piazza.h
$(BINDIR)/piazza-sol.o: piazza.h
#$(BINDIR)/piazza-test-functions.o: piazza-test-functio.h piazza.h

# clean
clean:
	rm -rf $(BINDIR) piazza-tests piazza-grading piazza-tests-sol piazza-grading-sol

.PHONY: test grade clean
