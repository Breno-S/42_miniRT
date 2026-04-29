NAME := miniRT

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS = $(addprefix -I,$(INCLUDES))

LIB_DIRS = $(PATH_LIBFT)/bin

LIBFT := ./libs/libft/bin/libft.a
MINILIBX := ./libs/minilibx-linux/libmlx.a
MINILIBX_LIN := ./libs/minilibx-linux/libmlx_Linux.a

SRCS_LIBFT := ./libs/libft/build/

PATH_LIBFT := ./libs/libft
PATH_MINILIBX := ./libs/minilibx-linux
PATH_BIN := ./
PATH_OBJT := ./build/

INCLUDES := include libs/libft/include libs/minilibx-linux
PATH_MANDATORY := ./srcs
VEC_MATH_SRC_DIR := vec_math
PARSER_SRC_DIR := parser
RENDERER_SRC_DIR := renderer

SRCS_MANDATORY_COMMON := \
	main.c

SRCS_MANDATORY_PARSER := \
	parser.c \
	ft_rtlstadd_back.c \
	error.c \
	import_ent_i.c \
	import_ent_ii.c \
	import_ent_utils.c \
	import_file.c \
	verify_number.c \
	create_scene.c

SRCS_MANDATORY_VEC_MATH := \
	color.c \
	hit_cylinder.c \
	hit_plane.c \
	hit_sphere.c \
	hooks.c \
	mlx_env.c \
	ray.c \
	vec_math.c \
	vec_math_vec.c

SRCS_MANDATORY_RENDERER := \
	build_image.c \
	renderer.c

SRCS_MANDATORY := $(addprefix $(PATH_MANDATORY)/,$(SRCS_MANDATORY_COMMON))
SRCS_MANDATORY := $(SRCS_MANDATORY) $(addprefix $(PATH_MANDATORY)/$(PARSER_SRC_DIR)/,$(SRCS_MANDATORY_PARSER))
SRCS_MANDATORY := $(SRCS_MANDATORY) $(addprefix $(PATH_MANDATORY)/$(VEC_MATH_SRC_DIR)/,$(SRCS_MANDATORY_VEC_MATH))
SRCS_MANDATORY := $(SRCS_MANDATORY) $(addprefix $(PATH_MANDATORY)/$(RENDERER_SRC_DIR)/,$(SRCS_MANDATORY_RENDERER))

OBJTS := $(addprefix $(PATH_OBJT),$(SRCS_MANDATORY_COMMON))
OBJTS := $(OBJTS) $(addprefix $(PATH_OBJT),$(SRCS_MANDATORY_PARSER))
OBJTS := $(OBJTS) $(addprefix $(PATH_OBJT),$(SRCS_MANDATORY_VEC_MATH))
OBJTS := $(OBJTS) $(addprefix $(PATH_OBJT),$(SRCS_MANDATORY_RENDERER))

OBJTS             := $(OBJTS:.c=.o)
OBJTS_LIBFT = $(shell $(MAKE) -s -C $(PATH_LIBFT) get_var)
OBJTS_LIBFT := $(subst ./build/,$(SRCS_LIBFT),$(OBJTS_LIBFT))

LDLIBS := -lmlx -lXext -lX11 -lm -lft
LDFLAGS := $(addprefix -L, $(LIB_DIRS)) $(addprefix -L, $(PATH_MINILIBX))


# Cores ANSI
GREEN   = \033[0;32m
RED     = \033[0;31m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
L_GREEN = \033[1;32m
L_RED   = \033[1;31m
GRAY    = \033[0;90m
NC      = \033[0m

all: $(addprefix $(PATH_BIN),$(NAME))

# $(NAME)
$(addprefix $(PATH_BIN),$(NAME)): $(LIBFT) $(MINILIBX) $(subst $(PATH_MANDATORY),$(PATH_OBJT),$(OBJTS))
		@echo "$(YELLOW)+==========================================+"
		@echo "          Build $(NAME)          "
		@echo "+==========================================+$(NC)"

		@printf "$(L_GREEN)Build...$(NC) %-40s\n" $(NAME)
		@sleep 0.01
		$(CC) $(CFLAGS) $(CPPFLAGS) $(subst $(PATH_MANDATORY),$(PATH_OBJT),$(OBJTS)) -o $(addprefix $(PATH_BIN),$(NAME)) $(LDLIBS) $(LDFLAGS)

$(LIBFT): $(OBJTS_LIBFT)
		@echo "$(MAGENTA)+==========================================+"
		@echo "         Github: Breno-S | Norethx        "
		@echo "+==========================================+\n\n$(NC)"
		@echo "$(GREEN)	⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆"
		@echo "	⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿"
		@echo "	⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀"
		@echo "	⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉\n\n$(NC)"
		@echo "$(RED)+==========================================+"
		@echo "      Welcome to $(NAME) - Build libft       "
		@echo "+==========================================+$(NC)"
		@echo "Compilando código...\n"
		@make -C $(PATH_LIBFT) NAME="libft.a" all

$(MINILIBX):
		@git submodule update --init --recursive
		@make -C $(PATH_MINILIBX) NAME="libmlx.a" all

$(PATH_OBJT)%.o: $(PATH_MANDATORY)/$(PARSER_SRC_DIR)/%.c
		@mkdir -p build
		@printf "$(L_GREEN)Compiling...$(NC) %-40s\n" $<
		@sleep 0.01
		@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(subst srcs/,build/,$@)

$(PATH_OBJT)%.o: $(PATH_MANDATORY)/$(VEC_MATH_SRC_DIR)/%.c
		@mkdir -p build
		@printf "$(L_GREEN)Compiling...$(NC) %-40s\n" $<
		@sleep 0.01
		@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(subst srcs/,build/,$@)

$(PATH_OBJT)%.o: $(PATH_MANDATORY)/$(RENDERER_SRC_DIR)/%.c
		@mkdir -p build
		@printf "$(L_GREEN)Compiling...$(NC) %-40s\n" $<
		@sleep 0.01
		@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(subst srcs/,build/,$@)

$(PATH_OBJT)%.o: $(PATH_MANDATORY)/%.c
		@mkdir -p build
		@printf "$(L_GREEN)Compiling...$(NC) %-40s\n" $<
		@sleep 0.01
		@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(subst srcs/,build/,$@)

.PHONY: clean fclean re all bonus $(OBJTS_LIBFT) debug

debug: fclean
debug: CFLAGS = -g
debug: all

clean:
		@make -C $(PATH_LIBFT) clean
		@printf "$(L_GREEN)Removing objects...$(NC)\n"
		@rm -f $(subst $(PATH_MANDATORY),$(PATH_OBJT),$(OBJTS))
		@rm -rf $(PATH_OBJT)

fclean:
# 		@make -C $(PATH_LIBFT) fclean
# 		@printf "$(L_GREEN)Removing minilibx...$(NC)\n"
# 		@make -C $(PATH_MINILIBX) clean
# 		@printf "$(L_GREEN)Removing objects...$(NC)\n"
# 		@rm -f $(subst $(PATH_MANDATORY),$(PATH_OBJT),$(OBJTS))
		@rm -rf $(PATH_OBJT)
		@printf "$(L_GREEN)Removing executable...$(NC)\n"
		@rm -f $(addprefix $(PATH_BIN),$(NAME))

re: fclean all
