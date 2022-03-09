NAME		=	ft_containers

SRCS		=	main2.cpp
INCS		=	vector.hpp iterator.hpp type_traits.hpp
CXXFLAGS	=	-Wall -Wextra -Wpedantic -Wfloat-conversion -Wsign-conversion -Wshadow -std=c++98 -fno-limit-debug-info -g
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
