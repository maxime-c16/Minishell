# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 11:45:51 by mcauchy           #+#    #+#              #
#    Updated: 2022/11/21 16:15:18 by mcauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES 			=	main.c singleton.c free.c parsing.c exec.c \
					path.c ft_split.c init.c data_struct.c utils.c \
					env_parsing.c env_manipulating.c redirections.c \
					redir_utils.c utils2.c utils3.c heredocs.c \
					heredocs_utils.c builtins.c builtins_exec.c \
					exec_utils.c refacto_token.c refacto_utils.c \
					env_parsing.c env_manipulating.c  ft_unquoting.c \
					env_var.c display_env.c unset_env.c ft_unquoting2.c \
					signals.c split_utils.c lcd_better_split.c exit_cmd.c\
					builtins_exec_utils.c utils4.c env_var2.c exec_utils2.c \

SRC_DIR 		=	srcs

DIR_OBJ 		=	.objs

LIBFT_DIR 	=	libft

SRCS 				=	$(addprefix $(SRC_DIR)/, $(FILES))

OBJS 				=	$(addprefix $(DIR_OBJ)/, $(notdir $(SRCS:.c=.o)))

CC 				=	gcc

CFLAGS 			=	-Wall -Wextra -Werror -g3

NAME 			=	minishell

HEADER  		=	includes/minishell.h

all				: 	MK_LIBFT $(NAME)

$(NAME) 		: 	$(OBJS)
					@clear
					@echo "Linking $(NAME)..."
					@$(CC) $(CFLAGS) $^ $(LIBFT_DIR)/libft.a -o $@ -lreadline
					@clear
					@echo "Compilation done."
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

$(DIR_OBJ)/%.o	:	$(SRC_DIR)/%.c $(HEADER)
									@mkdir -p $(@D)
									@echo "Compiling $(notdir $<)..."
									@$(CC) $(CFLAGS) -o $@ -c $<

MK_LIBFT				:
									@make -C $(LIBFT_DIR)
									@make -C $(LIBFT_DIR) bonus

clean						:
									@/bin/rm -f $(OBJS)
									@/bin/rm -rf $(DIR_OBJ)
									@make -C $(LIBFT_DIR) clean
									@clear
									@echo "Cleaned."

fclean					:	clean
									@clear
									@/bin/rm -f $(NAME)
									make -C $(LIBFT_DIR) fclean
									@clear
									@echo "Fully cleaned."

re							:	fclean  all

.PHONY  				: 	all clean fclean fclean re
