NAME = computor
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -O2 -g
OBJDIR = obj
TESTDIR = test

INC = -I
SRC =  main.cpp

HEADER_DEPS =

CPP_DEPS = $(patsubst %.cpp, %.d, $(notdir $(SRC)))
OBJ = $(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)))

VPATH = $(dir $(SRC))

RED = "\033[0;31m"
YELLOW = "\033[33m"
GREEN = "\033[0;32m"
NOCOLOR = "\033[0m"

all: $(NAME)

$(NAME): $(OBJ) #$(HEADER_DEPS)
	$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ)
	@echo ${GREEN}$(NAME) has compiled successfully!${NOCOLOR}

$(OBJDIR)/%.o: %.cpp #$(HEADER_DEPS)
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

re: clean all

test: all gen_test_cases
	./$(TESTDIR)/run.sh $(NAME) $(TESTDIR)/expressions.in $(TESTDIR)/expressions.out

gen_test_cases:
	python3 $(TESTDIR)/ExpressionsCreator.py $(TESTDIR)/expressions.in

clean_test:
	@rm -f $(TESTDIR)/expressions.in $(TESTDIR)/expressions.out

.PHONY: all clean fclean re test gen_test_cases clean_test
