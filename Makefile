NAME      = cub3D

SRC_DIR   = src
OBJ_DIR   = obj
INC_DIR   = inc
LIBFT_DIR = libft
MLX_DIR   = mlx

SRC       = main.c \
			init.c \
			image.c \
			map.c \
			player.c \
			raycast.c \
			utils.c

OBJ       = $(SRC:%.c=$(OBJ_DIR)/%.o)
LIBFT     = $(LIBFT_DIR)/libft.a

UNAME_S  := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
     GMLX        = $(MLX_DIR)/minilibx_linux
     CMLX        = $(GMLX)/libmlx.a
     MLXFLAGS    = -L$(GMLX) -lmlx -lXext -lX11 -lm
     PLATFORM    = Linux
endif

ifeq ($(UNAME_S), Darwin)
     GMLX        = $(MLX_DIR)/minilibx_opengl
     CMLX        = $(GMLX)/libmlx.a
     MLXFLAGS    = -L$(GMLX) -lmlx -framework OpenGL -framework AppKit
     PLATFORM    = macOS
endif

CC        = cc
CFLAGS    = -Wall -Wextra -Werror
INCLUDES  = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(GMLX)
RM        = @rm -rf

all: $(NAME)
	 @echo "platform: $(PLATFORM) usage: $(GMLX)"

$(NAME): $(LIBFT) $(CMLX) $(OBJ)
	@echo "linking $(NAME)"
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft $(MLXFLAGS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "compiling libft"
	@$(MAKE) -C $(LIBFT_DIR)

$(CMLX):
	@echo "compiling minilibx"
	@$(MAKE) -C $(GMLX) 2>/dev/null 1>/dev/null

clean:
	@echo "clean object file"
	$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(GMLX) clean 1>/dev/null

fclean: clean
	@echo "super clean $(NAME)"
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
