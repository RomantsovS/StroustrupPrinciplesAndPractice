#
# This is a common Makefile for code examples from the book
# "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
#

#
# Usage:
#     make        - Build all examples
#     make clean  - Clean all examples
#     make test   - Run the test suite
#
LIBS     = -lstdc++
MYLIBS = main.o
CXXFLAGS = $(INCLUDES) -Wall -time -O0 -g

# NOTE: If under Cygwin you get an error that uname command is not found,
#       make sure there are no folders with space in their names that preceed
#       the path to the Cygwin's bin folder inside your PATH variable.
ifeq ($(shell uname -o),Cygwin)
  OS=Cygwin
else
  OS=$(shell uname)
endif

.SUFFIXES: .cpp .o

# Create a list of source files.
SOURCES  = $(shell ls *.cpp)
# Create a list of object files from the source file lists.
OBJECTS = ${SOURCES:.cpp=.o}     
# Create a list of targets.
TARGETS = main.exe

# Build all targets by default
all: 	$(TARGETS)

# Files with extension .no-link.cpp are not intended for linking
%.no-link.exe: %.no-link.o
	@echo Linking skipped for $@
	@echo ================================================================================
	@echo Done building $@
	@echo ================================================================================
	@echo
	@echo

# A rule to build .exe file out of a .o file
main.exe: $(MYLIBS)
	$(CXX) -o $@ $(MYLIBS) $(LIBS)
	@echo ================================================================================
	@echo Done building $@
	@echo ================================================================================
	@echo
	@echo

# A rule to build .o file out of a .cpp file
%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo ================================================================================
	@echo Done compiling $@
	@echo ================================================================================
	@echo
	@echo

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo ================================================================================
	@echo Done compiling $@
	@echo ================================================================================
	@echo
	@echo

# A rule to clean all the intermediates and targets
clean:	
	rm -rf $(TARGETS) $(OBJECTS) *.out *.stackdump

# A rule to run set of tests
test:
	@for file in *.exe; do \
	    name=`basename $$file .exe` ; \
	    name=`basename $$name .crash` ; \
	    if (ls $$name.crash.exe >/dev/null 2>&1) ; then \
	        continue ; \
	    fi ; \
	    echo ======================================== [ $$file ] ; \
	    if (ls $$name.*in >/dev/null 2>&1) ; then \
	        for f in $$name.*in; do \
	            echo ; \
	            echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ { "$$f" } ; \
	            cat "$$f" ; \
	            echo ; \
	            echo ---------------------------------------- ; \
	            ./$$file < "$$f" ; \
	        done ; \
	    else \
	      ./$$file ; \
	    fi \
	done ; \
	echo -n 