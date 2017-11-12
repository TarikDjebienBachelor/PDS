#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int
main()
{
int i,j;
pid_t  pid;
/* le processus crée 10 processus fils avec la commande fork*/
for (i=1;i<11;i++){
		switch (fork()){
			case -1 : ;
			case  0 : 
				for(j=0;j<5000000;j++);	
				printf("%d   :[ %d ] je suis le processus fils a mi-parcours\n",i,getpid());
				for(j=0;j<5000000;j++);	
				exit(EXIT_SUCCESS);
			
			default:;
		}
	}	
/*  */
printf("\n--------------- -  classement  ----------------\n\n");
for (i=1;i<11;i++){
	pid = wait( (int *) 0);
	printf("%d    :[%d] processus fils \n",i,(int) pid);
	}
return 0;
}
