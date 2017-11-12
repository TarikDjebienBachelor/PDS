#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "makeargv.h"





int
main
(int argc, char *argv[]){
  
  int i, status, positionLectureCurseur;
  
  /* Chaine représentant le mode utilisé et celui admis par default */
  char *valeurOption, *defaultOption="-and";
  
  /*************** GESTION DU BON USAGE DE LA COMMANDE PAR L'UTILISATEUR ***********************/
  if(argc==1) {
    fprintf(stderr,"entrer au minimum une commande à executer.\nUsage : ./do [-and|-or] command ...\n");
    exit(EXIT_FAILURE);
  } 
  if(strcmp(argv[1],"-and")==0||strcmp(argv[1],"-or")==0){
    if(argc<3)
      fprintf(stderr,"entrer au minimum une commande à executer.\nUsage : ./do [-and|-or] command ...\n");
    exit(EXIT_FAILURE);
  }
  
  /*************** GESTION DU MODE POUR LA VALEUR RETOUR DU STATUT FINAL DE DO *****************/     
  
  /* Si le premier argument est l'option -and */
  if (strcmp(argv[1],"-and")==0)
    /* alors le statut final sera issue de conjonction des statuts de chacune des commandes */
    strcpy(valeurOption,"-and");
  /* Si le premier argument est l'option -or */
  else if (strcmp(argv[1],"-or")==0)
    /* alors le statut final sera issue de disjonction des statuts de chacune des commandes */
    strcpy(valeurOption,"-or");
  /* sinon c'est le mode par default qui est attribué sur le statut final */
  else strcpy(valeurOption,defaultOption);
  
  /************** GESTION DE LA POSITION DU CURSEUR DE LECTURE POUR MAKEARGV() *****************/

  /* si on a un -and ou un -or */
  if(strcmp(argv[1],"-and")==0||strcmp(argv[1],"-or")==0)
    /*la fonction makeargv() scannera les commandes à partir de la 3eme case de argv[] */
    positionLectureCurseur = 3;
  else
    /*Sinon la fonction makeargv() scannera les commandes directement à partir de la 2eme case de argv[] */
    positionLectureCurseur = 2;

  /************** GESTION DE L'EXECUTION DES COMMANDES *****************************************/
  
  /* On va traiter chaque commandes se trouvant dans chaque case argv[i] */
  for (i=positionLectureCurseur; i<argc; i++) { 
    /* chaine contenant une commande à executer */
    char **cmdargv;
    /*char **arg;*/
    
    
    /* création de la commande issue de argv[i] dans la chaine cmdargv */
    status = makeargv(argv[i], " \t", &cmdargv);
    assert(status>0);
    
    /* EXECUTION DE CHACUNE DES COMMANDES PAR UN PROCESSUS FILS */
    pid_t pidFilsCourant;
    pidFilsCourant = fork();
    switch(pidFilsCourant){
    case -1 : exit(EXIT_FAILURE);
    case  0 : execvp(argv[i],cmdargv);exit(EXIT_FAILURE);
    default : 
    }

    /* test: affichage 
       fprintf(stderr, "[%s]\t%% ", *cmdargv);
       
       for (arg=cmdargv; *arg; arg++)
       fprintf(stderr, "%s ", *arg);
       
       fprintf(stderr, "\n");
	*/
    
    /* libération mémoire */
    freeargv(cmdargv);
  }
  
  exit(EXIT_SUCCESS);
  
  return 0;
}

