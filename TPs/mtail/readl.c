#include "readl.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/*
Lit une ligne sur l'entree standard.
Cette ligne doit comporter moins de MAXLINE caracteres.
Le resultat est retourne dans line.
*/
extern
int
readl
/*
Le tableau line doit etre de taille au moins MAXLINE + 1.
*/
(char line[MAXLINE+1])
{
  /*
  Declarations des variables
  */
  char c;
  int compteur = 0;
  const char* message = "La chaine ne peut etre lue car elle contient plus de 80 caracteres.\n";
  /* Reinitialisation de notre chaine */
  int i;
  for (i=0;i<MAXLINE+1;i++)
      line[i]=0;
  /*On lit caractere par caractere tant que l'on a pa rencontre un \n */
  while ((c=getchar()) != '\n') {
   fatal (compteur < MAXLINE,message,EXIT_FAILURE);
   if (c == EOF) return EOF;
   line[compteur]= c;
   compteur++;
  }

  /*
  Un \0 est ecrit en fin de la chaine.
  */
  line = strcat(line,"\0");

  /*
  On Retourne le nombre de caracteres lu, non compris le \0 final.
  */
  return(strlen(line));

}/* end readl */
