Hi all

We are posting our grading suite of tests even in advance of your submission so that you can test your code and not be surprised by your eventual grade.  We may not do this for every HW since testing yourself is an important skill that we will want you to build.  However, here are the details for configuring, running, and debugging our grading tests.  They use the Google Test Suite and a compilation tool cmake. Please read the entire post to understand all the features.

How to Get and Use the Tests

Do a git pull in your homework-resources repo, which will download a folder hw1_tests.

Copy the hw1_tests folder from homework-resources to your hw-username/hw1 folder so that hw1_tests sits at the same level as all your source code (.cpp and .h files).

At the terminal (if you aren't already using the VM or Docker terminal), cd to the hw1_tests folder in your hw-username/hw1 folder

Initialize the test suite's CMake build system by running cmake .  <-- That period/dot is intentional and important.  It's not just  cmake, it is cmake .

note: CMake is a very useful program for compiling C++ code that will generate Makefiles and other scripts

Compile the test suite: make

Run the tests: ctest

You should now see a list of tests scrolling by. Hopefully they succeed, but if any fail, read below for how to debug them.



How to Debug Test Failures

or: How to Stop Panicking and Start Debugging

So, some of your tests are failing, which means there's a problem with your code. Don't worry, that's totally normal.

The first thing you'll want to ask yourself is, which homework problem is the issue occurring on: sum_pairs, tweet_parse, or str? There's a different subdirectory for each problem under the hw1_tests folder. Go into the appropriate subfolder and you should find an executable for the tests for that problem (e.g. str_tests, tweet_parse_tests, etc.). You may look at the source code of our tests to get an idea of what is happening.  You can also run that executable ./tweet_parse_tests and you should see output for each test that looks like:

[ RUN      ] TestTweetParse.NumTweets2
This test is executing your program with the following command line:
/usr/bin/valgrind --tool=memcheck -q --leak-check=yes --error-exitcode=113 /home/redekopp/cs104/su19/hw1_grading/ttrojan/hw1-test/tweet_parse_tests/hw1_tweet_parse /home/redekopp/cs104/su19/hw1_grading/ttrojan/hw1-test/tweet_parse_tests/testFiles/NumTweets2/input.txt /home/redekopp/cs104/su19/hw1_grading/ttrojan/hw1-test/tweet_parse_tests/testFiles/NumTweets2/output.txt
Your program's STDOUT was written to: /home/redekopp/cs104/su19/hw1_grading/ttrojan/hw1-test/tweet_parse_tests/testFiles/NumTweets2/stdout.txt

The key pieces of info here are the paths to the input and output files. input.txt mentioned here contains the input file that your program was run on, and output.txt contains the output that your program produced. Looking at those files, and running your program on them, should give you all the info you need to solve the problem.

USING GDB:  Also you can debug a particular test by using the command:   make debug-TEST_NAME where TEST_NAME is the test name shown in the output.  For example, make debug-TestTweetParse.NumTweets2 would start gdb on that test case and allow you to run, set breakpoints, etc.



