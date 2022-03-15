NAME = computor
CPP_TEST = cpp_test

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -O2 -g

OBJDIR = obj
TESTDIR = test

SRC = src/main.cpp src/Parser.cpp src/Exceptions.cpp src/ExpressionPresenter.cpp
INC = -I inc

HEADER_DEPS = inc/Expression.hpp inc/Parser.hpp inc/Exceptions.hpp inc/ExpressionPresenter.hpp

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

run_test: $(CPP_TEST)
	./$(CPP_TEST)

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
	python3 $(TESTDIR)/ExpressionsCreator.py $(TESTDIR)/expressions.in

clean_test:
	@rm -f $(TESTDIR)/expressions.in $(TESTDIR)/expressions.out

.PHONY: all clean fclean re test gen_test_cases clean_test
