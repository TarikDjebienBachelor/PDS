/* Object  : Programme qui affiche sur la sortie standard la valeur de NAME_MAX et PATH_MAX sur la machine courante
  * Author : Djebien Tarik
  * Date    : 19/12/2010
  */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>


int
main
(int argc,char *argv[]){
  printf("longueur maximale d'un nom d'entrée dans le système de fichiers : %d \n",NAME_MAX);
  printf("longueur maximale d'un chemin dans le systeme de fichiers : %d \n",PATH_MAX);
  return 0;
}
