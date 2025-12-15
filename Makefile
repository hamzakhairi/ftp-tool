CXX = c++
CXXFLAGS = -Wall -Wextra -Werror
SRC = ftp.cpp FUZZ.cpp
OBJ = $(SRC:.cpp=.o)
NAME = ft_ftp
INCLUDE = -I./include

all: $(NAME) clean
# 	./$(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -lcurl -o  $(NAME)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
