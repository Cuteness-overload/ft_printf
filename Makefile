NAME =	libftprintf.a

SRCS =	ft_printf.c \
		parser.c \
		render.c \
		render_str.c \
		render_int.c \
		utils.c \
		str_utils.c \
		int_utils.c

HFILES = ft_printf.h

SDIR = ./srcs/
IDIR = ./includes/

SFILES = $(addprefix $(SDIR),$(SRCS))
OFILES = $(SFILES:.c=.o)

LFT_NAME = libft.a
LFT_PATH = ./libft

CC = cc
CFLAGS += -Wall -Wextra -Werror -fPIE
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
			cd libft && $(MAKE) all && cd ..

$(NAME)	:	$(LFT_PATH)/$(LFT_NAME) $(OFILES)
			cp $(LFT_PATH)/$(LFT_NAME) $(NAME)
			$(AR) $(ARFLAGS) $(NAME) $(OFILES)

bonus	: all

clean	:
			cd libft && $(MAKE) clean && cd ..
			@rm -f $(OFILES)

fclean	: clean
			cd libft && $(MAKE) fclean && cd ..
			@rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re bonus
