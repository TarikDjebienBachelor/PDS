#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

typedef void (*func_t) (void *);

/* fonction qui executera le travail de type func_t */
void
f
(void * arg)
{
  sleep(1); /* on utilise un sleep() pour attendre le temps necessaire à la mort du fils */
  if (getppid()==1) /* Si le processus est orphelin alor init de pid 1 le recupere*/
            printf("Le petit fils de PID [%d] est Orphelin, il fait donc son travail en appelant f().\nSon nouveau pere est init de PID [%d]\n",getpid(),getppid());
}

/* fonction double fork */
void
forkfork
(func_t f, void *arg)
{
  /* le PID du fils */
  pid_t pidFils;
  /* le PID du petit fils */
  pid_t pidPetitFils;
  
  /* Affichage du pere et du processus racine */
  printf("Je suis forkfork de PID [%d] du pere de PID [%d]\n",getpid(),getppid());
  
  /* creation du premier processus fils */
  pidFils=fork();
  
  /* test sur la valeur de retour de fork() */
  switch(pidFils){
  /* -1 si la creation a echoué */
  case -1 : printf("creation du fils echoué.\n");
            exit(EXIT_FAILURE);
  /* la creation du processus fils n'a pas eu de probleme donc le fils recupere la valeur 0 par fork() */
  case  0 : printf("Je suis le fils de PID [%d] du père de PID [%d]\n",getpid(),getppid());
            /* le fils va creer a son tour un petit fils par un second appel de fork() */
            pidPetitFils=fork();
            /* on teste encore une fois la valeur de retour */
            switch(pidPetitFils){
            /* -1 creation du petit fils a echoué */
            case -1 : printf("creation du petit fils a echoue \n");
                      exit(EXIT_FAILURE);
            /* 0 le petits fils a bien été crée celui ci fera alors son travail par la fonction f() */
            case 0 : printf("Je suis le petit fils de PID [%d] du fils de PID [%d]\n",getpid(),getppid());
                     f(arg);
                     exit(EXIT_SUCCESS);
            /* le fils termine pour rendre le petits fils orphelin */         
            default :  exit(EXIT_SUCCESS);
            }
           
  /* le pere recupere le PID du fils creer et attends que celui ci termine son travail */
  default : printf("Attente de la terminaison du fils\n");
            wait(NULL);
            printf("Le fils a ete arrete\n");
            exit(EXIT_SUCCESS);
  }          
}


