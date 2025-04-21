#----------------------------------->COLORS<-----------------------------------#
DEF_COLOR = \033[1;39m
WHITE = \033[1m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PINK = \033[1;35m
CIAN = \033[1;36m

#------------------------------------>NAME<------------------------------------#
NAME = libft.a

#----------------------------------->HEADER<-----------------------------------#
HEADER = libft.h

#------------------------------------->SRC<----–-------------------------------#
SOURCES_DIRECTORY = ./src/
SRCS =	$(wildcard $(SOURCES_DIRECTORY)*.c)

#------------------------------------>OBJ<-------------------------------------#
OBJS_DIR = ./objs/

OBJS = $(addprefix $(OBJS_DIR), $(subst .c,.o,$(SRCS)))

DEP = $(addsuffix .d, $(basename $(OBJS)))

#----------------------------------->COMANDS<----------------------------------#
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MDP = mkdir -p
AR = ar rcs
INCLUDE = -I ./

#------------------------------------>RULES<-----------------------------------#
$(OBJS_DIR)%.o: %.c Makefile
	@$(MDP) $(dir $@)
	@printf "$(PINK)      \rCompiling: $(YELLOW)$<...$(DEF_COLOR)      \r"
	@$(CC) -MT $@ $(CFLAGS) -MMD -MP $(INCLUDE) -c $< -o $@

all			: 
	@echo ""
	@$(MAKE) $(NAME)

$(NAME)		:	$(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@printf "\n$(GREEN)LIBRARY: '$(subst .a,,$@)' has been created.$(DEF_COLOR)\n"

#$(NAME)		:
#	@echo "$(YELLOW)Nothing to be done for '$(subst .a,,$(NAME))'$(DEF_COLOR)"

clean:
	@$(RM) -r $(OBJS_DIR)

fclean		:
	@$(MAKE) clean
	@$(RM) $(NAME)
	@echo "$(RED)LIBRARY: '$(subst .a,,$(NAME))' has been removed.$(DEF_COLOR)"

re			:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "$(CIAN)LIBRARY: '$(subst .a,,$(NAME))' has been remake$(DEF_COLOR)"
	@echo ""

.PHONY: all bonus clean fclean re bonus

-include $(DEP)