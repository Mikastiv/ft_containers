NAME		=	ft_containers

SRCS		=	main2.cpp
TEST_SRCS	=	vector_tests.cpp
INCS		=	vector.hpp iterator.hpp type_traits.hpp
CXXFLAGS	=	-Wall -Wextra -Wpedantic -Wfloat-conversion -Wsign-conversion -Wshadow -std=c++98 -I.
DEBUG_FLAGS	=	-fno-limit-debug-info -g
CXX			=	clang++

RELEASE		?=	0
ifeq (RELEASE, 0)
	CXXFLAGS += DEBUG_FLAGS
endif

OBJS		=	$(SRCS:.cpp=.o)
TEST_OBJS	=	$(TEST_SRCS:.cpp=.o)

VPATH		=	tests

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(OBJS) -o $(NAME)

clean:
			@rm -rf $(OBJS) $(TEST_OBJS)

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

fmt:
			@clang-format -i $(SRCS) $(INCS) $(TEST_SRCS)

.PHONY:		all clean fclean re fmt
