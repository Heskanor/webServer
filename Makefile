NAME =		webserver

#CXXFLAGS +=	-Wall -Wextra -Werror -std=c++98
 CXXFLAGS +=	-Wall -Wextra -Werror -std=c++98 -g
CXX =		clang++

SRCS =		$(wildcard *.cpp)

OBJS =		$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			clean fclean all

.PHONY: 	all clean fclean re
