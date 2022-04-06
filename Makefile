# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lide <lide@student.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 14:18:05 by lide              #+#    #+#              #
#    Updated: 2022/04/06 12:59:04 by lide             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_SERVER		=	server_file/server.c\
					utils_file/utils.c

SRCS_CLIENT		=	client_file/client.c\
					utils_file/utils.c

NAME1			= server.a
NAME2			= client.a
EXEC1			= server
EXEC2			= client
OBJS_SERVER		= ${SRCS_SERVER:.c=.o}
OBJS_CLIENT		= ${SRCS_CLIENT:.c=.o}
CC				= @gcc
CFLAGS			= -Wall -Werror -Wextra

all: ${NAME1} ${NAME2}

${NAME1}:	${OBJS_SERVER}
				@ar -rc ${NAME1} ${OBJS_SERVER}
				@${CC} ${CFLAGS} ${NAME1} -o ${EXEC1}
				@echo "Server Created"

${NAME2}:	${OBJS_CLIENT}
				@ar -rc ${NAME2} ${OBJS_CLIENT}
				@${CC} ${CFLAGS} ${NAME2} -o ${EXEC2}
				@echo "Client Created"


server: ${NAME1}

client: ${NAME2}

clean:
		@rm -f ${OBJS_SERVER} ${OBJS_CLIENT}
		@echo "Clean Executed"

fclean:
		@rm -f ${OBJS_SERVER} ${OBJS_CLIENT}
		@rm -f ${NAME1} ${NAME2} ${EXEC1} ${EXEC2}
		@echo "Fclean Executed"

re: fclean all

.PHONY: all clean fclean re server client
