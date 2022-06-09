# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkamal <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 11:46:35 by bkamal            #+#    #+#              #
#    Updated: 2022/06/09 00:24:19 by bkamal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

SRCS	= pipex.c\
			utils.c\
			utils2.c\
			utils3.c

SRCB	= main_bonus.c\
			pipex_bonus.c\
			heredoc_bonus.c\
			utils_bonus.c\
			utils2_bonus.c\
			utils3_bonus.c\
			get_next_line.c\
			get_next_line_utils.c\
			
OBJS	= $(SRCS:.c=.o)

OBJB	= $(SRCB:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: ${NAME}

bonus: $(OBJB)
	$(CC) $(CFLAGS) $(OBJB) -o $(NAME)

clean:
		${RM} ${OBJS} ${OBJB}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
