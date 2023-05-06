SRC_DIR		= src
OBJ_DIR		= obj
SRCS		= main.cpp Server.cpp createServer.cpp signal.cpp sendMessage.cpp User.cpp createChannel.cpp kickChannel.cpp Channel.cpp utils.cpp topic.cpp mode.cpp
SRC			= $(addprefix src/, $(SRCS))
OBJS		= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
D_OBJS		= mkdir -p $(@D)
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98 -g
NAME		= ircserv
RM			= rm -rf

all:		$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
			@$(D_OBJS)
			@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "\033[1;92mMake succesfully executed\033[0m"

clean:
			@$(RM) $(OBJ_DIR)
			@echo "\033[1;93mClean succesfully executed\033[0m"

fclean:
			@$(RM) $(OBJ_DIR)
			@$(RM) $(NAME)
			@echo "\033[1;91mFclean succesfully executed\033[0m"

re:			fclean all

.PHONY:		all clean fclean re