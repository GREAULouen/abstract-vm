CPP		 =	c++
CPPFLAGS =	-Wall -Wextra -Werror -std=c++11

SRC_DIR  =	src
OBJ_DIR  =	obj

NAME	 =	abstract-vm
SRC		 =	main.cpp				\
			Token.cpp				\
			Lexer.cpp

SUB_DIR =	$(SRC_DIR)					\
			$(SRC_DIR)/lexer			\
			$(SRC_DIR)/token

vpath %.cpp $(SUB_DIR)

OBJ		 =	$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))



all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp | ${OBJ_DIR}
	$(CPP) $(CPPFLAGS) -c $< -o $@

${OBJ_DIR} :
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re