GENERAL
=======
This bundle should be used as a starting point for the "TheGame" TDD-Excersice. It provides a wrapper implementation for using the linux sockets, string parser and a test-framework:

* sockwrpr
* strtk: http://www.codeproject.com/KB/recipes/Tokenizer.aspx?display=Mobile&fid=990812 and http://www.partow.net/programming/strtk/index.html
* google testframework: http://code.google.com/p/googletest/

Installation
============
Just download this repository and unpack it. See section *Makefile usage* for further details.

TestCases (tg_client_test)
==========================
Some example TestCases are already implemented under *test/tg_client_test.cpp*. The intention is, that every testcase should go into that file.

Hint
----
You have to add you Class under test to the TEST_OBJECTS list in the head of the *Makefile*, e.g.: `TEST_OBJECTS = TestClass.o`

Client (tg_client)
==================
An example implementation of the client is located in *src/tg_client.cpp*. It is recommended to use at least the file as an entry-point for the client implementation (int main() here).

Hint
----
* The Makefile implemented to use *.cpp as C++ file-extension.
* Add new classes to the OBJECTS list in the Makefile.


Makefile usage
==============
`make setup` will unpack and compile the googletest framework and create some mandatory folders.
After running the setup target your folder should look like this:
.
|- files  (gtest*.zip)
|- gtest/ (googletest framework including "include" dir)
|- src/   (source files, include tg_client.cpp, sockwrpr/.*, strtk/strtk.hpp)
|- lib/   (libgtest.a)
|- obj/   (obj-files dir)
|- test/  (test sources)
|- Makefile
|- <tg_client>
|- <thegclient_test>


`make [all]` will generate the tg_client, which has an example implementation of how to use the SocketWrapper package (*sockwrpr*). The following files will be generated:
* tg_client
* tg_client_test

`make test` will just compile test.

`make test_run` will call the target `test` and runs the tests after that.

`make clean` will remove *obj/*.

`make cleaner` uses clean and will also remove the executeables (*tg_client*, *tg_client_test*).

`make cleanest` uses cleaner and will also remove the googletest-framework directory *gtest/* and *lib/*

It is recommended to use `make test_run` to execute the TestCases.

Other
=====
This bundle does not use the boost library for *strtk* (disabled during compile process).

