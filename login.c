/* Usuario ingresa su nombre y password ... Loguea si es correcto */
/*
Usuario logueados:
  nombre		password
1.	grupo8		demonios
2.	renato		4549114
3. 	sofia		3961996
4. 	miguel		4551822
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <hash.h>

/* El archivo del password */
#define FILEUSER "/etc/daemon8.users.acl"

#define BUFLEN 512 

int main (void){
	
	int fopen;
	char readfile[BUFLEN];
	int len;
	
	/*Lectura del archivo*/
	if ((fopen= open(FILEUSER, O_RDONLY)) < 0){
		perror("error en open FILEUSER");
		exit(EXIT_FAILURE);
	}else{
		if((len = read(fopen, readfile, BUFLEN)) < 0) {
			perror("error en read FILEUSER");
			exit(EXIT_FAILURE);
		}
		readfile[len]= '\0';
	}	
	if(close(fopen) < 0) {
            perror("error en close FILEUSER");
            exit(EXIT_FAILURE);
  	}      	

	char *userinput, *passwordinput;
	char *buscar;
	int lenu, lenp, intentos=0;
	userinput= (char *) malloc(10*sizeof(char));
	passwordinput= (char *) malloc(15*sizeof(char));

	do{
		printf("Ingrese su nombre de usuario->\t");
		scanf("%s", userinput);
		printf("Ingrese su contraseña->\t");
		scanf("%s", passwordinput);
		lenu= strlen(userinput);
		lenp= strlen(passwordinput);
		
    /*el trabajo interesante */
		if ( (buscar= strstr(readfile, hash(userinput))) != NULL ){//si encuentra el usuario en readfile
			buscar+= lenu;
			if ( buscar == strstr(buscar, "::") ){
				buscar+=2;
				if (buscar == strstr(buscar, hash(passwordinput))) break;
			}
		}
		
		intentos++;
		if (intentos==3){
			perror("error: Login sin éxito");
			exit(EXIT_FAILURE);
		}else if (intentos==2){
			printf ("Ultimo intento. ¡Asegúrese de ingresar correctamente!\n");
		}else{
			printf("Nombre de usuario o contraseña incorrectas. ¡Por favor ingrese correctamente!\n");
		}
	}while(1);
			
	printf("\n:::LOGIN EXITOSO::: ¡BIENVENIDO!\n");
	exit(EXIT_SUCCESS);

}
