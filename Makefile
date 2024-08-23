# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kofujita <kofujita@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 15:17:38 by kofujita          #+#    #+#              #
#    Updated: 2024/06/11 19:31:36 by moco             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Wextra -Werror
SRCS := ./src/ft_printf_c.c ./src/ft_printf_characters.c ./src/ft_printf_d.c ./src/ft_printf_i.c ./src/ft_printf_info.c ./src/ft_printf_loop_character.c ./src/ft_printf_lx.c ./src/ft_printf_p.c ./src/ft_printf_s.c ./src/ft_printf_set_fps.c ./src/ft_printf_strlen.c ./src/ft_printf_sx.c ./src/ft_printf_u.c ./src/ft_printf_write_numeric.c ./ft_printf.c
OBJS := $(SRCS:%.c=%.o)

RM          := rm -rf
CP          := cp -r
MKDIR       := mkdir -p

NAME := libftprintf.a

INSTALL_DIR := /usr/local/bin

# Progress bar information
SRCS_COUNT := $(words $(SRCS))
PROGRESS := 0
BAR_LENGTH := 40

.PHONY :
	all clean fclean re install

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE_DIR) -o $@ -c $<
	@$(eval PROGRESS=$(shell echo $$(($(PROGRESS) + 1))))
	@PERCENTAGE=$$(($(PROGRESS) * 100 / $(SRCS_COUNT))) ; \
	BAR=$$(($(BAR_LENGTH) * $$PERCENTAGE / 100)) ; \
	SPACES=$$(($(BAR_LENGTH) - $$BAR)) ; \
	printf "\r\033[K" ; \
	printf "Progress: [" ; \
	for i in $$(seq 1 $$BAR); do printf "="; done ; \
	printf ">" ; \
	for i in $$(seq 1 $$SPACES); do printf " "; done ; \
	printf "] $$PERCENTAGE%% ($@)"

$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo 
	@echo Created $(NAME)

all : $(NAME)

clean :
	@$(RM) $(OBJS)
	@echo "Deleted OBJS"

fclean : clean
	@$(RM) $(NAME)
	@echo "Deleted NAME"

re : fclean all

install : all
	$(CP) $(NAME) $(INSTALL_DIR)
