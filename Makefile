NAME   = cub3D

SRC_DIR  = src
OBJ_DIR  = obj
INC_DIR  = inc
LIBFT_DIR = libft
MLX_DIR  = mlx

SRC      = exit.c \
		   game.c \
		   image.c \
		   init.c \
		   keys.c \
		   main.c \
		   map.c \
		   move.c \
		   utils.c \

OBJ    = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT   = $(LIBFT_DIR)/libft.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
     GMLX    = $(MLX_DIR)/minilibx_linux
     CMLX    = $(GMLX)/libmlx.a
     MLXFLAGS  = -L$(GMLX) -lmlx -lXext -lX11 -lm
	 PLATFLAGS  = -D__LINUX__
     PLATFORM  = Linux
     endif
ifeq ($(UNAME_S), Darwin)
     GMLX    = $(MLX_DIR)/minilibx_opengl
     CMLX    = $(GMLX)/libmlx.a
     MLXFLAGS  = -L$(GMLX) -lmlx -framework OpenGL -framework AppKit
	 PLATFLAGS  = -D__MACOS__
     PLATFORM  = macOS
endif

CC    = cc
CFLAGS  = -Wall -Wextra -Werror $(PLATFLAGS)
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/inc -I$(GMLX)
RM    = @rm -rf

GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RED    = \033[0;31m
NC    = \033[0m

all: $(NAME)
	@echo "$(GREEN)✓ Platform: $(PLATFORM)$(NC)"
	@echo "$(GREEN)✓ Using MLX: $(GMLX)$(NC)"
	@echo "$(GREEN)✓ $(NAME) ready to use!$(NC)"

$(NAME): $(LIBFT) $(CMLX) $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR)

$(CMLX):
	@echo "$(YELLOW)Compiling minilibx for $(PLATFORM)...$(NC)"
ifeq ($(UNAME_S), Darwin)
	 @$(MAKE) -C $(GMLX) 2>/dev/null 1>/dev/null || (echo "$(RED)Error: minilibx_opengl compilation failed$(NC)" && exit 1)
else
	 @$(MAKE) -C $(GMLX) 2>/dev/null 1>dev/null || (echo "$(RED)Error: minilibx_linux compilation failed$(NC)" && exit 1)
endif

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(GMLX) clean 1>/dev/null

fclean: clean
	@echo "$(YELLOW)Deep cleaning $(NAME)...$(NC)"
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
