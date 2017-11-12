/**
 * @authors AYAR & NOUFLI
 * @version 13 Janvier 2011
 *
 * LA COMMANDE ./mdu doit donner le même resultat que :
 *
 *	./mdu arg1 [arg2] .. [argN] = du -B 512 -s arg1 [arg2] .. [argN]
 *		avec  (-s --summarize display only a total for each argument
 *  		       -B --block-size=SIZE use SIZE-byte blocks)
 *
 *	./mdu -b arg1 [arg2] .. [argN] = du -s -b arg1 [arg2] .. [argN]
 *		avec 
 *	 		(-s --summarize display only a total for each argument
 *  			 -b --bytes equivalent to `--apparent-size --block-size=1')
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <dirent.h>
#include <string.h>

/** MAX_SYMB_LINKS represente le nombre max de liens symboliques a parcourir */
#define MAX_SYMB_LINKS 100

/* Variables */
static int opt_apparent_size = 0;
int compteur,len,i;
 

/**
 * Fonction valid_name
 * @param name
 * @return
 */
static int valid_name(const char * name){
    return ((strcmp(name,".."))&& (strcmp(name,".")));
}

/**
 * Fonction du_file
 * @param pathname
 * @return valeur indiquant le bon ou non bon deroulement de la commande
 */
static int du_file(const char * pathname){
  struct stat st;
  int status;

  status = lstat(pathname,&st);

  /** On choisi stat car on choisi pas par defaut les erreurs symboliques */
    assert(status == 0);

  if(S_ISREG(st.st_mode))
    return opt_apparent_size ? st.st_size:st.st_blocks;

  if(S_ISDIR(st.st_mode)){
    DIR *dirp;
    struct dirent *dp;
    int size;
    char entry_path[PATH_MAX+1];

    /** Taille de repertoire seul */
    size = opt_apparent_size ? st.st_size:st.st_blocks ;
    dirp = opendir(pathname);
    assert(dirp != NULL);
    while((dp = readdir(dirp)))
    {
      
     /** Si entrée non valide continuer */
      if(!valid_name(dp -> d_name))
	continue;

      /* Concatener /usr/bin avec X//R6 */
      snprintf(entry_path,PATH_MAX,"%s/%s",pathname,dp->d_name);
      size +=du_file(entry_path);

    }/*fermeture du while*/

    closedir(dirp);
    return size;

  }/* IS_DIR */

  if(S_ISLNK(st.st_mode))
  {
        int size;
        char entry_path[PATH_MAX+1];

        /** Taille du lien symbolique */
        size = opt_apparent_size ? st.st_size:st.st_blocks ;
        compteur++;

        if(compteur>=MAX_SYMB_LINKS)
        {
            fprintf(stdout,"Plus de %d liens symboliques dans une même branche",MAX_SYMB_LINKS);
            fprintf(stdout,"      %s\n",pathname);
            exit(0);
        }
        len = readlink(pathname, entry_path, PATH_MAX);
        if(len != -1)
            entry_path[len] = '\0';
            size += du_file(entry_path);

        return size;
  }
  fprintf(stderr,"entree%s de type ignorée\n",pathname);
  exit(EXIT_SUCCESS);
}

/**
 * Fonction main
 * @param argc designe le nombre de parametres
 * @param argv comporte la commande './mdu' et le fichier/repertoire a tester
 * @return la valeur de "exit success"
 */
int
main(int argc, char **argv){

    char* option ;
    option = argv[1];
    
    switch(argc)
    {
        case 1:printf("Utilsation : ./mdu [option]arg1 [arg2] .. [argN]\n");
            break;
        default:
            if (option[0]=='-')
            {
                opt_apparent_size = 1;
                for (i=2;i < argc;i++)
                {
                    fprintf(stdout,"%d     %s\n",du_file(argv[i]),argv[i]);
                }
            }else
                {
                    for (i=1;i < argc;i++)
                    {
                        fprintf(stdout,"%d     %s\n",du_file(argv[i]),argv[i]);
                    }
                }
    }
    exit(EXIT_SUCCESS);
}
