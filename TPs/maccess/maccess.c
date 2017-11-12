/* Object  : Programme qui implemente notre propre version de l'appel système access UNIX
 * Author  : Djebien Tarik
 * Date    : 19/12/2010
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h> 

#define TRUE  1
#define FALSE 0

/* Termine l'execution du programme sur une erreur fatale.
   Si assert est faux, affiche le message sur la sortie d'erreur
   et termine en retournant la valeur status à l'environnement.
*/
void
fatal
(int assert, const char* message, int status){
  if (assert == FALSE ) {
    fprintf(stderr,"%s", message);
    exit(status);
  }
}

/* Affiche en cas d'echec de maccess, ce pourquoi l'accés est impossible */
int
verboseMode
(int num,int affichage){  
  switch(num){
    /* 1. Le droit d’acces demande au fichier n’est pas autorise */
  case EACCES : if (affichage==1)printf("the file is unable to access with this mode specified.\n");
    return 1; 
    break;
    /* 2. Le fichier n’existe pas */ 
  case ENOENT : if (affichage==1)printf("A component of pathname does not exist or is a dangling symbolic link.\n");
    return 2;
    break;
    /* 3. Une des composantes du nom de fichier n’est pas un repertoire */ 
  case ENOTDIR: if (affichage==1)printf("A component used as a directory in pathname is not, in fact, a directory.\n");
    return 3;
    break;
    /* 4. Une des composantes du nom du fichier est trop longue */
   
    /* 5. Le nom du fichier est trop long  */
  case ENAMETOOLONG:if (affichage==1)printf("pathname is too long.\n");
    return 5;
    break;
    /* 6. Le nom du fichier comporte trop de liens symboliques */
  case ELOOP : if (affichage==1)printf("Too many symbolic links were encountered in resolving pathname.\n");
    return 6;
    break;
    /* 7. Autre erreur */
  default : if (affichage==1)printf("Another error\n"); return 7;
    } 
}

/*
char*
droitAffichage
(char* mode){
  if (strcmp(mode,"-r")==0) return "R_OK";
  else if (strcmp(mode,"-x")==0) return "X_OK";
  else if (strcmp(mode,"-w")==0) return "W_OK";
  else return "F_OK";
}
*/

int
main
(int argc, char* argv[]){
  
  /* Declaration */
  char *option,*fichier;
  int   res;
  
  /* Initialisation */
  res = 0;
  errno = 0;
  
  /* Traitement */
  if (argc >= 3 && argc <=4){
    fichier = argv[2];
    if (strcmp(option = argv[1],"-r")==0){
      res = access(fichier,R_OK);
      if (res != 0){
	if (argc==4 && strcmp(argv[3],"-v")==0 && res==-1)
	  return verboseMode(errno,1);
	else 
	  return verboseMode(errno,0);
      }
    }
    else if (strcmp(option = argv[1],"-w")==0){
      res = access(fichier,W_OK);
      if (res != 0){
	if (argc==4 && strcmp(argv[3],"-v")==0 && res==-1)
	  return verboseMode(errno,1);
	else 
	  return verboseMode(errno,0);
	}
    }
    else if (strcmp(option = argv[1],"-x")==0){
      res = access(fichier,X_OK);
      if (res != 0){
	if (argc==4 && strcmp(argv[3],"-v")==0 && res==-1)
	  return verboseMode(errno,1);
	else 
	  return verboseMode(errno,0);
	}
    }
   else if (strcmp(option = argv[1],"-xw")==0||strcmp(option = argv[1],"-wx")==0){
      res = access(fichier,X_OK|W_OK);
      if (res != 0){
	if (argc==4 && strcmp(argv[3],"-v")==0 && res==-1)
	  return verboseMode(errno,1);
	else 
	  return verboseMode(errno,0);
	}
    }
   else if (strcmp(option = argv[1],"-wr")==0||strcmp(option = argv[1],"-rw")==0){
      res = access(fichier,R_OK|W_OK);
      if (res != 0){
	if (argc==4 && strcmp(argv[3],"-v")==0 && res==-1)
	  return verboseMode(errno,1);
	else 
	  return verboseMode(errno,0);
	}
    }
   else if (strcmp(option = argv[1],"-rx")==0||strcmp(option = argv[1],"-xr")==0){
      res = access(fichier,X_OK|R_OK);
      if (res != 0){
	if (argc==4 && strcmp(argv[3],"-v")==0 && res==-1)
	  return verboseMode(errno,1);
	else 
	  return verboseMode(errno,0);
	}
    }
   else if (strcmp(option = argv[1],"-xwr")==0||strcmp(option = argv[1],"-wrx")==0||strcmp(option = argv[1],"-rxw")==0||strcmp(option = argv[1],"-xrw")==0||strcmp(option = argv[1],"-wxr")==0||strcmp(option = argv[1],"-rwx")==0){
      res = access(fichier,X_OK|R_OK|W_OK);
      if (res != 0){
	if (argc==4 && strcmp(argv[3],"-v")==0 && res==-1)
	  return verboseMode(errno,1);
	else 
	  return verboseMode(errno,0);
	}
    }   
   else {
      res = access(fichier,F_OK);
      if (argc==4 && strcmp(argv[3],"-v")==0)
	  return verboseMode(errno,1);
	else 
	  return verboseMode(errno,0);
	
    }
    
  }
  else fatal(FALSE,"Usage : maccess [-r|-w|-x] [FILE] {-v} \n",EXIT_FAILURE);
  
  return res; 
}

