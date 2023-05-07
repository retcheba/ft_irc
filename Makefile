SRC_DIR		= src
OBJ_DIR		= obj
SRCS		= main.cpp \
				Create_Server/createServer.cpp Create_Server/checkPassword.cpp Create_Server/getInput.cpp \
				Create_Server/ignoreMessage.cpp Create_Server/launchServer.cpp Create_Server/setNickname.cpp Create_Server/setUsername.cpp \
				Channel/Channel.cpp Channel/add.cpp Channel/delete.cpp Channel/find.cpp \
				Channel/getter.cpp Channel/modeGetter.cpp Channel/modeRemove.cpp Channel/modeSet.cpp \
				Server/Server.cpp \
				User/User.cpp \
				SEND/channelMessage.cpp SEND/privateMessage.cpp \
				JOIN/createChannel.cpp \
				KICK/kickChannel.cpp \
				TOPIC/topic.cpp \
				MODE/mode.cpp  MODE/inviteMode.cpp MODE/limitsMode.cpp \
				MODE/operatorMode.cpp MODE/passwordMode.cpp MODE/topicMode.cpp \
				INVITE/invite.cpp \
				Signal/signal.cpp \
				Utils/utils.cpp Utils/check.cpp Utils/clean.cpp Utils/findIterator.cpp
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