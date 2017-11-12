NAME	=	mdu

SRC	=	mdu.c 

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Werror -pedantic -ansi
CFLAGS +=       -D_XOPEN_SOURCE=500

RM	=	rm -f

all	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)
clean	:
		$(RM) *~ *\# \#*
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
