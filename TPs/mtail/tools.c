#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 /* Termine l'execution du programme sur une erreur fatale.

    Si assert est faux, affiche le message sur la sortie d'erreur
    et termine en retournant la valeur status à l'environnement.
*/
extern
void
fatal
(int assert, const char* message, int status) {
    if (assert == 0 ) {
       fprintf(stderr,"%s", message);
       exit(status);
    }
}

