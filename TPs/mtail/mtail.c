#include <stdio.h>
#include "readl.h"
#include "tools.h"
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if (argc > 2)
	fatal(0,"entrer au minimum un argument. \n Usage : mtail [-n] < filename\n",EXIT_FAILURE);
	else if (argc == 1){
		/* la ligne courante */
		char ligneCourante[MAXLINE+1]="";
		/* et sa longueur */
		int longeurLigneCourante = 0;
		/* et le nombre de ligne du fichier */
		int nblignes = 0;
		/* compteur pour afficher les 10 dernieres lignes */
		int cpt = 0;
		/* statut de succés */
		int status;
		/* on recupere chaque ligne de l'entrée standard */
	    while ( (longeurLigneCourante = readl(ligneCourante)) != EOF){
	      nblignes++;
	    }
	    
	    status = lseek(STDIN_FILENO,0,SEEK_SET);
	    if ( status == -1){
	      fatal(0,"Non seekable file\n",EXIT_FAILURE);
	    }
	     while ( (longeurLigneCourante = readl(ligneCourante)) != EOF){
	      
	      if (cpt++ >= (nblignes - 10)){
		fprintf(stdout,"%s\n",ligneCourante);
	      }
	     }
	     exit(EXIT_SUCCESS);		
	}
	else if (argc == 2){
		/* la ligne courante */
		char ligneCourante[MAXLINE+1]="";
		/* et sa longueur */
		int longeurLigneCourante = 0;
		/* et le nombre de ligne du fichier */
		int nblignes = 0;
		/* compteur pour afficher les n dernieres lignes */
		int cpt = 0;
		/* statut de succés */
		int status;
		/* le nombre de n lignes à afficher */
		int n = atoi((argv[1])+1);
		/* on recupere chaque ligne de l'entrée standard */
	    while ( (longeurLigneCourante = readl(ligneCourante)) != EOF){
	      nblignes++;
	    }
	    
	    status = lseek(STDIN_FILENO,0,SEEK_SET);
	    if ( status == -1){
	      fatal(0,"Non seekable file\n",EXIT_FAILURE);
	    }
	     while ( (longeurLigneCourante = readl(ligneCourante)) != EOF){
	      
	      if (cpt++ >= (nblignes - n)){
		fprintf(stdout,"%s\n",ligneCourante);
	      }
	     }
	     exit(EXIT_SUCCESS);

	

	}
	else fatal(0,"entrer au maximum deux arguments. \n Usage : mtail [-n] < filename \n",EXIT_FAILURE);

	return 0;
}
