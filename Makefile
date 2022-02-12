NAME = computor
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -O0 -g
SRCDIR = src
OBJDIR = obj
TESTDIR = test

DEPS = inc/Domain/Token.h \
	   inc/Domain/Expression.h \
	   inc/Domain/Solution.h \
	   inc/DomainServices/Parser.h \
	   inc/DomainServices/Lexer.h \
	   inc/DomainServices/Solver.h \
	   inc/DomainServices/Extractors/TokenExtractor.h \
	   inc/DomainServices/Extractors/UnknownTokenExtractor.h \
	   inc/DomainServices/Extractors/OperationTokenExtractor.h \
	   inc/DomainServices/Extractors/NumberTokenExtractor.h \
	   inc/Presenters/SolutionPresenter.h \
	   inc/Presenters/ExpressionPresenter.h \
	   inc/Presenters/CLISolutionPresenter.h \
	   inc/Presenters/CLIExpressionPresenter.h

INC = -I inc \
	  -I inc/Domain \
	  -I inc/Presenters \
	  -I inc/DomainServices \

SRC = main.cpp \
	  Token.cpp \
	  Expression.cpp \
	  Solution.cpp \
	  Parser.cpp \
	  Lexer.cpp \
	  Solver.cpp \
	  TokenExtractor.cpp \
	  UnknownTokenExtractor.cpp \
	  OperationTokenExtractor.cpp \
	  NumberTokenExtractor.cpp \
	  SolutionPresenter.cpp \
	  ExpressionPresenter.cpp \
	  CLISolutionPresenter.cpp \
	  CLIExpressionPresenter.cpp \

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

RED = "\033[0;31m"
YELLOW = "\033[33m"
GREEN = "\033[0;32m"
NOCOLOR = "\033[0m"

all: $(NAME)

$(NAME): $(DEPS) $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ)
	@echo ${GREEN}$(NAME) has compiled successfully!${NOCOLOR}

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@echo ${YELLOW}Compiling $<${NOCOLOR}
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean: clean_test
	@echo ${YELLOW}Cleaning $(OBJDIR)/*.o ${NOCOLOR}
	@echo ${YELLOW}Cleaning $(TESTDIR)/*.{in,out} ${NOCOLOR}
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: all gen_test_cases
	./$(TESTDIR)/run.sh $(NAME) $(TESTDIR)/expressions.in $(TESTDIR)/expressions.out

gen_test_cases:
	python3 $(TESTDIR)/ExpressionsCreator.py $(TESTDIR)/expressions.in

clean_test:
	@rm -f $(TESTDIR)/expressions.in $(TESTDIR)/expressions.out

.PHONY: all clean fclean re test gen_test_cases clean_test

