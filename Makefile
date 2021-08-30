NAME = computor
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++14 -O2
SRCDIR = src
OBJDIR = obj
DEPS = inc/
INC = -I inc
SRC = main.cpp
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

clean:
	@echo ${YELLOW}Cleaning $(OBJDIR)/*.o ${NOCOLOR}
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

gen_test_cases:
	python3 test/expr_generator.py

test: all
	./test/run.sh $(NAME) test/expressions.in test/expressions.out

.PHONY: all clean fclean re test

