/* ------------------------------
   $Id: pipe.c,v 1.2 2005/03/29 09:46:52 marquet Exp $
   ------------------------------------------------------------

   mshell - a job manager
   
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#include "cmd.h"
#include "common.h"
#include "pipe.h"
#include "jobs.h"




/*

nbcmd : le nombre de commande sur la ligne de commande
bg : background
*/
void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {

  if (nbcmd==2){
    pid_t pid1;
    int pipeFd[2];
    
    /* creation du tube */
    if (pipe(pipeFd)==-1){
      perror("Création du tube");
      exit(2);
    }
    /*creation du processus fils pour la commande 1 */
    pid1 = fork();
    /* Fermeture du descripteur par le fils1, redirection sur STDOUT, execution de la commande 1*/
    switch(pid1){
    case -1: 
      perror("fork() fils1 error ");
      exit(2);
      break;
    case  0: /* le processus Fils1 exécutera la premiere commande */
      /* Redirection de la sortie standard STDOUT sur la lecture du tube */
      dup2(pipeFd[1],STDOUT_FILENO);
      /* Fermeture du descripteur en sortie par le fils1 qui ne lira pas dans le tube */
      close(pipeFd[0]);
      /* Execution de la commande 1 */
      execvp(*cmds[0],cmds[0]);
      /* On quitte sur un echec si la commande 1 ne s'est pas executée */
      perror("execvp(cmd1)");
      exit(EXIT_FAILURE);
      break;
    default :  /* Ici on a que 2 commande donc le processus Pere executera la seconde */
      /* Si on est en mode Background */
      if (bg){
	/* ajout de commande1 dans la table des jobs */      
	jobs_addjob(pid1,BG,cmds[1][1]);
        /* entrée standard redirigée sur le tube */
	dup2(pipeFd[0],STDIN_FILENO);
        /* Fermeture du descripteur en entrée car ici le pere est lecteur, on doit plus avoir de redacteur sur le tube sinon DEADLOCK */
        close(pipeFd[1]);
        /* Execution de la commande 2 */
	execvp(*cmds[1],cmds[1]);
	/* On quitte sur un echec si la commande 2 ne s'est pas executée */
      perror("execvp(cmd2)");
      exit(EXIT_FAILURE);
      break;
      }
      /* Sinon on est en avant plan */
      else{
	/* ajout de commande1 dans la table des jobs en FG */      
	jobs_addjob(pid1,FG,cmds[1][1]);
        /*idem*/
	dup2(pipeFd[0],STDIN_FILENO);
        close(pipeFd[1]);
	execvp(*cmds[1],cmds[1]);
	perror("execvp(cmd2)");
	exit(EXIT_FAILURE);
      }
      break;
    }
  return;
  }
}
