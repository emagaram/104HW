# How to build

    make all

## Other notes

I finished every problem and tested them so everything should work. Ignore the deque.cpp file, I used it for testing. The tests.cpp file is also a test file I used but it runs doctest. It should work though just by compiling and doing ./tests. It should be ignored though  because it has some memory leaks that aren't reflective of actual issues with my code. I developed in vscode and changed some of the tasks.json and launch.json files which is why i pushed the .vscode folder. All .o files are put in the obj folder for neatness. Lastly, in my removeConsecutive function, I delete the consecutive items from the heap because although it goes against design principles since it's not technically "ours" to delete, it was the only way I could think of doing it. Also, in my rem_dup.cpp, I created a delete list function and even though it probably should have gone in my rem_dup_library, I wasn't sure if I was allowed to add in more public functions or destructors. Thanks!