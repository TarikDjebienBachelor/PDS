NAME	=	mcut

SRC	=	mcut.c readl.c tools.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Werror -pedantic -ansi

RM	=	rm -f

all	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)
clean	:
		$(RM) *~ *\# \#*
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
