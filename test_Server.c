#include <unistd.h>		
#include <stdio.h>		
#include <stdlib.h>		
#include <pthread.h>
#include <semaphore.h>

#define P sem_wait
#define V sem_post

sem_t sInteg, sProd, sBackup, smettreEnPause;
pthread_t integ, backup, prod;
int serveur;


void initServer();

void testServer();

void *serverIntegration(void *arg);

void *serverBackup(void *arg);

void *serverProduction(void *arg);

int donne_valeur_random(int a, int b);
	

int main(int nbarg, char* argv[]) {
	sem_init(&sInteg, 0, 0);
	sem_init(&sProd, 0, 0);
	sem_init(&sBackup, 0, 0);
	sem_init(&smettreEnPause, 0, 0);

	pthread_create(&integ, NULL, serverIntegration, NULL);
	pthread_create(&backup, NULL, serverBackup, NULL);
	pthread_create(&prod, NULL, serverProduction, NULL);
	
	pthread_join(integ, NULL);
	
	sem_destroy(&sInteg);
	sem_destroy(&sProd);
	sem_destroy(&sBackup);

}


void initServer() {
	int semVal=donne_valeur_random(0, 1);

	printf("\nRecherche d'un serveur disponible...\n");
	sleep(3);
	switch(semVal){
	    case 0: 
	            printf("\n**Serveur production disponible.\n");
	        	sleep(3);
		        serveur = 1;
		        printf("*****Redirection vers le serveur production...\n");
		        break;
		default:
		        printf("\n**Serveur production non disponible.\n");
	        	sleep(3);
	        	serveur = 2;
	        	printf("*****Redirection vers son serveur backup...\n");
	        	break;
		        
	}
	 
	if (serveur == 1) {
	    
		V(&sProd);
		
	} else {
		V(&sBackup);
	}
	
}

void testServer() {
    int vlsp,vlsb;
    sem_getvalue(&sProd, &vlsp);
    sem_getvalue(&sBackup,&vlsb);
    if(vlsp==1 && vlsb==0){
         printf("\nTest server => Le serveur courrant est le server de production \n");
    }else{
         if(vlsp==0 && vlsb==1){
                 printf("\nTest server => Le serveur courrant est le server backup \n");
         }else{
              printf("\nTest server => Il y'a une erreur \n");
         }
    }
   
	V(&smettreEnPause);
}

void *serverIntegration(void *arg) {
    
	int choix;
	char r;
	
	printf("Initialisation du serveur d'integration....  \n");
	sleep(3);
	printf("\t********* Bienvenue sur le serveur d'integration. *********\n");
    initServer();
    

	do
    {
       	printf("\n+ Vous voulez connaitre le serveur courrant ? (O,N) : ");
       	scanf( "%c", &r );
       	
    } while ( r!='O' && r!='N' && r!='o' && r!='n');
    
    if (r=='O' || r=='o'){
        testServer();
    }

    V(&smettreEnPause);
	
	 
	P(&sInteg);
	
	return NULL;
	
}

void *serverBackup(void *arg) {
    
    P(&smettreEnPause);
	while (1) {
	
		P(&sBackup);
		sleep(3);
		printf("\n********Le serveur backup vient d'effectuer la commande.\n");

		V(&sInteg);
	}
	return NULL;
	
}


void *serverProduction(void *arg) {
    
    P(&smettreEnPause);
	while (1) {
		P(&sProd);
		sleep(3);
		printf("\n********Le serveur production vient d'effectuer la commande.\n");
		V(&sInteg);
	}
	return NULL;
	
}

int donne_valeur_random(int a, int b)
{
    return rand()%(b+1 - a) + a;
}




