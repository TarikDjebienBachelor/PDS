/* ------------------------------
   $Id: makeargv.c,v 1.2 2005/03/14 08:50:35 marquet Exp $
   ------------------------------------------------------------

   Cuts command into argv pieces
   From  Robbins & Robbins: Unix Systems Programming

   Philippe Marquet, Mar 2005
   
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

int makeargv(const char *s, const char *delimiters, char ***argvp);

void freeargv(char **argv);
