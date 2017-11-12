# @authors AYAR & NOUFLI
# @version 13 Janvier 2011
# Makefile pour ./mdu

CC      = gcc
CFLAGS = -Wall -Werror -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

mdu: mdu.c
		gcc $(CFLAGS) -o $@ $?
clean :
	rm *.o 

#@ cible
#? sources