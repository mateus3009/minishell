# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 20:40:30 by msales-a          #+#    #+#              #
#    Updated: 2021/09/14 21:46:18 by msales-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

# CONFIG

DIRECTORY_SOURCE	:= src
DIRECTORY_HEADER	:= includes
DIRECTORY_TARGET	:= target

LIBRARIES_SYSTEM	:= -lreadline
LIBRARIES_COMPILED	:= ./libs/libft/libft.a

# PREPARE

LIBRARIES_FLAGS_UTIL		= -L$(dir $(library)) -l$(patsubst lib%.a,%, $(notdir $(library)))
LIBRARIES_COMPILED_FLAGS	:= $(foreach library, $(LIBRARIES_COMPILED), $(LIBRARIES_FLAGS_UTIL))
LIBRARIES_FLAGS				:= $(LIBRARIES_COMPILED_FLAGS) $(LIBRARIES_SYSTEM)

FILE_SOURCE	:= $(filter %.c, $(shell find $(DIRECTORY_SOURCE) -type f))

OBJECTS_SOURCE	:= $(addprefix $(DIRECTORY_TARGET)/, $(FILE_SOURCE:.c=.o))

COMPILER		:= clang
COMPILER_FLAGS	:= -Wall -Wextra -Werror -g

HANDLER = solver

ifeq ($(SANITIZE_A),true)
        COMPILER_FLAGS += -fsanitize=address
endif

ifeq ($(SANITIZE_L),true)
        COMPILER_FLAGS += -fsanitize=leak
endif

# RECIPES

.PHONY : all clean fclean make re

all : $(NAME)

clean :
	@rm -rf $(DIRECTORY_TARGET)

fclean : cleanlib
	@rm -f $(NAME)

re : all clean

$(NAME) : $(OBJECTS_SOURCE) $(LIBRARIES_COMPILED)
	@$(COMPILER) $(COMPILER_FLAGS) $(OBJECTS_SOURCE) $(LIBRARIES_FLAGS) -o $(NAME)

$(BONUS_NAME) : $(OBJECTS_SOURCE_BONUS) $(LIBRARIES_COMPILED)
	@$(COMPILER) $(COMPILER_FLAGS) $(OBJECTS_SOURCE_BONUS) $(LIBRARIES_FLAGS) -o $(BONUS_NAME)

$(DIRECTORY_TARGET)/%.o : %.c Makefile
	@mkdir -p $(@D)
	@$(COMPILER) -I$(DIRECTORY_HEADER) $(COMPILER_FLAGS) -c $< -o $@

$(LIBRARIES_COMPILED) :
	@$(MAKE) -C $(dir $@)

cleanlib : $(LIBRARIES_COMPILED)
	@$(MAKE) clean fclean -C $(dir $<)
