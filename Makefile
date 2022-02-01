NAME		=	ft_containers

SRCS		=	main.cpp
INCS		=	vector.hpp
CXXFLAGS	=	-Wall -Wextra -Werror -Wpedantic -Wfloat-conversion -Wsign-conversion -Wshadow -std=c++98
CXX			=	clang++

OBJS		=	$(SRCS:.cpp=.o)

all:		CXXFLAGS += -g -fno-limit-debug-info
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(OBJS) -o $(NAME)

clean:
			@rm -rf $(OBJS)

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

fmt:
			@clang-format -i $(SRCS) $(INCS)

.PHONY:		all clean fclean re fmt
