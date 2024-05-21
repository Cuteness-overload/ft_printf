NAME =	libftprintf.a

SRCS =	ft_printf.c \
		parser.c \
		render.c \
		render_str.c \
		render_int.c \
		utils.c \
		str_utils.c \

HFILES = ft_printf.h

B_SRCS = ./

SDIR = ./srcs/
IDIR = ./includes/

SFILES = $(addprefix $(SDIR), $(SRCS))
OFILES = $(SFILES:.c=.o)

BSFILES = $(addprefix $(SDIR), $(B_SRCS))
BOFILES = $(BSFILES:.c=.o)

LFT_NAME = libft.a
LFT_PATH = ./libft

ifdef DO_BONUS
	OFILES += $(BOFILES)
endif

CC = cc
CFLAGS += -Wall -Wextra -Werror
#CFLAGS +=    -g3
#CFLAGS +=    -fsanitize=address
#CFLAGS +=    -arch x86_64
CFLAGS += -I$(IDIR) -I$(LFT_PATH)

AR = ar
ARFLAGS = -rcs

%.o:%.c $(IDIR)$(HFILES)
			$(CC) -c $(CFLAGS) -o $@ $<

all	:	$(NAME)

$(LFT_PATH)/$(LFT_NAME)	:
			@$(MAKE) -j -C $(LFT_PATH)

$(NAME)	:	$(LFT_PATH)/$(LFT_NAME) $(OFILES)
			@cp $(LFT_PATH)/$(LFT_NAME) $(NAME)
			@$(AR) $(ARFLAGS) $(NAME) $(OFILES)

bonus	:
			@$(MAKE) -j DO_BONUS=1

clean	:
			@rm -f $(OFILES)

fclean	: clean
			@$(MAKE) -C $(LFT_PATH) fclean
			@rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re bonus
