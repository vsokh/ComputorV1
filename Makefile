NAME = computor
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -O0 -g
SRCDIR = src
OBJDIR = obj
TESTDIR = test

DEPS = inc/Lexer.h \
	   inc/Token.h \
	   inc/TokenExtractor.h \
	   inc/UnknownTokenExtractor.h \
	   inc/OperationTokenExtractor.h \
	   inc/NumberTokenExtractor.h

INC = -I inc
SRC = main.cpp \
	  Lexer.cpp \
	  Token.cpp \
	  TokenExtractor.cpp \
	  UnknownTokenExtractor.cpp \
	  OperationTokenExtractor.cpp \
	  NumberTokenExtractor.cpp

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

test: all gen_test_cases
	./$(TESTDIR)/run.sh $(NAME) $(TESTDIR)/expressions.in $(TESTDIR)/expressions.out

gen_test_cases:
	python3 $(TESTDIR)/expr_generator.py $(TESTDIR)/expressions.in

clean_test:
	@rm -f $(TESTDIR)/expressions.in $(TESTDIR)/expressions.out

.PHONY: all clean fclean re test

