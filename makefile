CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

bin/c_compiler :
	mkdir -p bin
	cd c_translator && $(MAKE) bin/c_compiler
	cd c_compiler && $(MAKE) bin/c_compiler

clean : 
	rm bin/*
	cd c_translator && $(MAKE) clean
	cd c_compiler && $(MAKE) clean
	
