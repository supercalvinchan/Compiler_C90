CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

all : bin/print_canonical bin/eval_expr

src/maths_parser.tab.cpp src/maths_parser.tab.hpp : src/maths_parser.y
	bison -v -d src/maths_parser.y -o src/maths_parser.tab.cpp

src/maths_lexer.yy.cpp : src/maths_lexer.flex src/maths_parser.tab.hpp
	flex -o src/maths_lexer.yy.cpp  src/maths_lexer.flex

include/ast/ast_variable.o : include/ast/ast_variable.cpp include/ast/ast_variable.hpp
	g++ -g -c  include/ast/ast_variable.cpp -o include/ast/ast_variable.o

include/ast/ast_expression.o : include/ast/ast_expression.cpp include/ast/ast_expression.hpp
	g++ -g -c include/ast/ast_expression.cpp -o include/ast/ast_expression.o

include/ast/ast_declarations.o : include/ast/ast_declarations.cpp include/ast/ast_declarations.hpp
	g++ -g -c include/ast/ast_declarations.cpp -o include/ast/ast_declarations.o

include/ast/ast_statements.o : include/ast/ast_statements.cpp include/ast/ast_statements.hpp
	g++ -g -c include/ast/ast_statements.cpp -o include/ast/ast_statements.o

include/ast/ast_parameters.o : include/ast/ast_parameters.cpp include/ast/ast_parameters.hpp
	g++ -g -c include/ast/ast_parameters.cpp -o include/ast/ast_parameters.o

include/ast/ast_functions.o : include/ast/ast_functions.cpp include/ast/ast_functions.hpp
	g++ -g -c include/ast/ast_functions.cpp -o include/ast/ast_functions.o

include/ast/ast_operators.o : include/ast/ast_operators.cpp include/ast/ast_operators.hpp
	g++ -g -c include/ast/ast_operators.cpp -o include/ast/ast_operators.o

include/ast/ast_primitives.o : include/ast/ast_primitives.cpp include/ast/ast_primitives.hpp
	g++ -g -c include/ast/ast_primitives.cpp -o include/ast/ast_primitives.o



bin/c_compiler : include/ast/ast_variable.o include/ast/ast_expression.o include/ast/ast_primitives.o include/ast/ast_operators.o include/ast/ast_statements.o include/ast/ast_declarations.o include/ast/ast_parameters.o  include/ast/ast_functions.o src/print_canonical.o src/maths_parser.tab.o src/maths_lexer.yy.o src/maths_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -g -o ../bin/c_compiler $^


clean :
	rm src/*.o
	rm src/*.tab.cpp
	rm src/*.yy.cpp
	rm include/ast/*.o
