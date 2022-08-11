# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 11:45:51 by mcauchy           #+#    #+#              #
#    Updated: 2022/08/06 08:46:26 by mcauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES 			=	main.c singleton.c free.c parsing.c exec.c \
					path.c ft_split.c init.c data_struct.c env_parsing.c \
					env_manipulating.c

SRC_DIR 		=	srcs

DIR_OBJ 		=	.objs

LIBFT_DIR 		=	libft

SRCS 			=	$(addprefix $(SRC_DIR)/, $(FILES))

OBJS 			=	$(addprefix $(DIR_OBJ)/, $(notdir $(SRCS:.c=.o)))

CC 				=	gcc

CFLAGS 			=	-Wall -Wextra -Werror -g3 #-fsanitize=address

NAME 			=	minishell

HEADER  		=	includes/minishell.h

all				: 	$(NAME)

$(NAME) 		: 	$(OBJS)
					clear
					@echo "Linking $(NAME)..."
					@make -C $(LIBFT_DIR)
					@make -C $(LIBFT_DIR) bonus
					@$(CC) $(CFLAGS) $^ -lreadline $(LIBFT_DIR)/libft.a -o $@
					@clear
					@echo "Compilation done."
					@sleep 1
					@clear
					@echo "        :::   :::   ::::::::::: ::::    ::: ::::::::::: ::::::::  :::    ::: :::::::::: :::        :::  ";
					@echo "      :+:+: :+:+:      :+:     :+:+:   :+:     :+:    :+:    :+: :+:    :+: :+:        :+:        :+:   ";
					@echo "    +:+ +:+:+ +:+     +:+     :+:+:+  +:+     +:+    +:+        +:+    +:+ +:+        +:+        +:+    ";
					@echo "   +#+  +:+  +#+     +#+     +#+ +:+ +#+     +#+    +#++:++#++ +#++:++#++ +#++:++#   +#+        +#+     ";
					@echo "  +#+       +#+     +#+     +#+  +#+#+#     +#+           +#+ +#+    +#+ +#+        +#+        +#+      ";
					@echo " #+#       #+#     #+#     #+#   #+#+#     #+#    #+#    #+# #+#    #+# #+#        #+#        #+#       ";
					@echo "###       ### ########### ###    #### ########### ########  ###    ### ########## ########## ########## ";
					@echo "                                                                                                      ";
					@echo "|_      _ _  _ _     _|_     ()      _ _|_  _  _ _ _ ";
					@echo "|_)\/  | | |(_(_||_|(_| |\/  (_X  \/_\(_| |(/_(_| (_)";
					@echo "   /                     /        /                  ";
					@./$(NAME)

$(DIR_OBJ)/%.o	:	$(SRC_DIR)/%.c $(HEADER)
					@mkdir -p $(@D)
					@echo "Compiling $(notdir $<)..."
					@$(CC) $(CFLAGS) -o $@ -c $<

clean			:
					@/bin/rm -f $(OBJS)
					@/bin/rm -rf $(DIR_OBJ)
					@make -C $(LIBFT_DIR) clean
					@clear
					@echo "Cleaned."

fclean			:	clean
					@clear
					@/bin/rm -f $(NAME)
					@make -C $(LIBFT_DIR) fclean
					@clear
					@echo "Fully cleaned."

re				:	fclean  all

.PHONY  		: 	all clean fclean fclean re
