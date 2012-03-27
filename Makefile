# This makefile is used to setup and run the thegame client and the corresponding tests.

# general
UNZIP 	      = unzip

# directories
OBJS_DIR      = ./obj
SRC_DIR       = ./src
SOCKWRPR_DIR  = $(SRC_DIR)/sockwrpr
TEST_DIR      = ./test
FILES_DIR     = ./files
GTEST_DIR     = ./gtest
LIB_DIR       = ./lib

# compiler
CXXFLAGS     += -g -Wall -Wno-long-long -I$(SRC_DIR)

# google testframework
GTEST_PKG     = $(FILES_DIR)/gtest-1.6.0.zip
GTEST_INC     = $(GTEST_DIR)/include
GTEST_LIB     = libgtest.a
TEST_CXXFLAGS = $(CXXFLAGS) -I$(GTEST_INC) -L$(LIB_DIR)

#vpath
VPATH 	      = $(SRC_DIR) $(SOCKWRPR_DIR) $(TEST_DIR)

# objs and srcs
EXE           = tg_client
TEST_EXE      = tg_client_test   
SRC_EXT       = cpp
### hint tg_client.o and tg_client_test.o are NOT INCLUDED here, see specific targets.
OBJECTS       = ClientSocket.o ISocketBase.o
TEST_OBJECTS  =  # add your o-files for the classes that should be tested.

# strtk options
STRTK_OPTIONS = -Dstrtk_no_tr1_or_boost -lstdc++

all: tg_client test

tg_client: $(addprefix $(OBJS_DIR)/,$(OBJECTS)) $(OBJS_DIR)/$(EXE).o
	$(CXX) $(CXXFLAGS) -o $(EXE) $^

$(OBJS_DIR)/%.o:%.$(SRC_EXT)
	test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
	$(CXX) -c $(CXXFLAGS) $(STRTK_OPTIONS) $< -o $@

setup: gtest_setup
	test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)

gtest_setup:
	test -d $(GTEST_DIR) || $(MAKE) gtest_install

gtest_install: 
	$(UNZIP) $(GTEST_PKG)
	mv gtest-* $(GTEST_DIR)
	cd $(GTEST_DIR); \
	$(CXX) -I./include -I. -c ./src/gtest-all.cc; \
	ar -rv $(GTEST_LIB) gtest-all.o
	test -d $(LIB_DIR) || mkdir $(LIB_DIR)
	mv $(GTEST_DIR)/$(GTEST_LIB) $(LIB_DIR)

test: $(addprefix $(OBJS_DIR)/,$(TEST_OBJECTS)) $(OBJS_DIR)/tg_client_test.o
	$(CXX) $(TEST_CXXFLAGS) -lpthread -lgtest -o $(TEST_EXE) $^ $(LIB_DIR)/$(GTEST_LIB)

test_run: test
	./tg_client_test

$(OBJS_DIR)/tg_client_test.o: tg_client_test.$(SRC_EXT)
	$(CXX) -c $(STRTK_OPTIONS) $(TEST_CXXFLAGS) $< -o $@

.PHONY: clean cleaner cleanest

clean:
	$(RM) -fr $(OBJS_DIR)

cleaner: clean
	$(RM) $(EXE) $(TEST_EXE)

cleanest: cleaner
	$(RM) -fr $(GTEST_DIR) $(LIB_DIR)