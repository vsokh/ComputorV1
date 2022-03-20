NAME = computor

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -O2 -g

OBJDIR = obj
TESTDIR = test

SRC = main.cpp \
	  Solver/Solver.cpp \
	  Utils/Exceptions.cpp \
	  Presetner/ExpressionPresenter.cpp \
	  Presenter/SolutionPresenter.cpp \
	  Parser/FormulaParser.cpp \
	  Parser/ExpressionParser.cpp

INC = -I Parser -I Solver -I Presenter -I Utils -I Model

HEADER_DEPS = Model/Expression.hpp \
 			  Model/Solution.hpp \
			  Parser/FormulaParser.hpp \
			  Parser/ExpressionParser.hpp \
 			  Solver/Solver.hpp \
 			  Utils/Exceptions.hpp \
 			  Presenter/ExpressionPresenter.hpp \
 			  Presenter/SolutionPresenter.hpp

CPP_DEPS = $(patsubst %.cpp, %.d, $(notdir $(SRC)))
OBJ = $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

VPATH = $(dir $(SRC))

RED = "\033[0;31m"
YELLOW = "\033[33m"
GREEN = "\033[0;32m"
NOCOLOR = "\033[0m"

all: $(NAME)

run: $(NAME)
	./$(NAME)

$(CPP_TEST): $(OBJ) $(HEADER_DEPS)
	$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ)
	@echo ${GREEN}$(TEST_TARGET) has compiled successfully!${NOCOLOR}

$(NAME): $(OBJ) $(HEADER_DEPS)
	$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ)
	@echo ${GREEN}$(NAME) has compiled successfully!${NOCOLOR}

$(OBJDIR)/%.o: %.cpp $(HEADER_DEPS)
	@echo ${YELLOW}Compiling $<${NOCOLOR}
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $< -MD

include $(wildcard $(CPP_DEPS))

clean: clean_test
	@echo ${YELLOW}Cleaning $(OBJDIR)/*.o ${NOCOLOR}
	@echo ${YELLOW}Cleaning $(TESTDIR)/*.{in,out} ${NOCOLOR}
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(CPP_TEST)

re: fclean all

test: all gen_test_cases
	./$(TESTDIR)/run.sh $(NAME) $(TESTDIR)/expressions.in $(TESTDIR)/expressions.out

gen_test_cases:
	python3 $(TESTDIR)/PolynomialsCreator.py $(TESTDIR)/expressions.in

clean_test:
	@rm -f $(TESTDIR)/expressions.in $(TESTDIR)/expressions.out

.PHONY: all clean fclean re test gen_test_cases clean_test
