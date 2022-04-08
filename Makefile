# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lide <lide@student.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 14:18:05 by lide              #+#    #+#              #
#    Updated: 2022/04/08 17:54:32 by lide             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_SERVER			=	server_file/server.c\
						utils_file/utils.c

SRCS_CLIENT			=	client_file/client.c\
						utils_file/utils.c

SRCS_SERVER_BONUS	=	server_file/server_bonus.c\
						utils_file/utils_bonus.c

SRCS_CLIENT_BONUS	=	client_file/client_bonus.c\
						utils_file/utils_bonus.c

NAME1				= server.a
NAME2				= client.a
EXEC1				= server
EXEC2				= client
OBJS_SERVER			= ${SRCS_SERVER:.c=.o}
OBJS_CLIENT			= ${SRCS_CLIENT:.c=.o}
NAME3				= server_bonus.a
NAME4				= client_bonus.a
EXEC3				= server_bonus
EXEC4				= client_bonus
OBJS_SERVER_BONUS	= ${SRCS_SERVER_BONUS:.c=.o}
OBJS_CLIENT_BONUS	= ${SRCS_CLIENT_BONUS:.c=.o}
CC					= @gcc
CFLAGS				= -Wall -Werror -Wextra

all: ${NAME1} ${NAME2}

${NAME1}:	${OBJS_SERVER}
				@ar -rc ${NAME1} ${OBJS_SERVER}
				@${CC} ${CFLAGS} ${NAME1} -o ${EXEC1}
				@echo "Server Created"

${NAME2}:	${OBJS_CLIENT}
				@ar -rc ${NAME2} ${OBJS_CLIENT}
				@${CC} ${CFLAGS} ${NAME2} -o ${EXEC2}
				@echo "Client Created"

${NAME3}:	${OBJS_SERVER_BONUS}
				@ar -rc ${NAME3} ${OBJS_SERVER_BONUS}
				@${CC} ${CFLAGS} ${NAME3} -o ${EXEC3}
				@echo "Server_bonus Created"

${NAME4}:	${OBJS_CLIENT_BONUS}
				@ar -rc ${NAME4} ${OBJS_CLIENT_BONUS}
				@${CC} ${CFLAGS} ${NAME4} -o ${EXEC4}
				@echo "Client_bonus Created"

server: ${NAME1}

client: ${NAME2}

server_bonus: ${NAME3}

client_bonus: ${NAME4}

bonus: ${NAME3} ${NAME4}

clean:
		@rm -f ${OBJS_SERVER} ${OBJS_CLIENT}
		@rm -f ${OBJS_SERVER_BONUS} ${OBJS_CLIENT_BONUS}
		@echo "Clean Executed"

fclean:
		@rm -f ${OBJS_SERVER} ${OBJS_CLIENT}
		@rm -f ${OBJS_SERVER_BONUS} ${OBJS_CLIENT_BONUS}
		@rm -f ${NAME1} ${NAME2} ${EXEC1} ${EXEC2}
		@rm -f ${NAME3} ${NAME4} ${EXEC3} ${EXEC4}
		@echo "Fclean Executed"

re: fclean all

.PHONY: all clean fclean re server client server_bonus client_bonus bonus
