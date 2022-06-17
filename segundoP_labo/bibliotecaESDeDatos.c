/*
 * utn.c
 *
 *  Created on: 3 abr. 2022
 *      Author: Agustin
 */
#include "bibliotecaESDeDatos.h"
/// @brief  Genera el menu principal del programa y pide la opcion.
///
/// @return -1 si falla, la opcion si sale bien.
int menuPrincipal(void){
	int opcion = -1;
	int reintentos = 2;

	do{

    printf("1)Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n");
    printf("2)Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).\n");
    printf("3)Alta de pasajero.\n");
    printf("4)Modificar datos de pasajero.\n");
    printf("5)Baja de pasajero.\n");
    printf("6)Listar pasajeros.\n");
    printf("7)Ordenar pasajeros.\n");
    printf("8)Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n");
    printf("9)Guardar los datos de los pasajeros en el archivo data.csv (modo binario).\n");
    printf("10)Salir.\n");
	utn_getInt(&opcion, "", "Error ingrese una opcion valida.", 1, 10, 2);
    reintentos--;
	}while(reintentos >=0);
	return opcion;
}


/// @brief Funcion que se utiliza para obtener un numero entero en un rango determinado por la misma.
///
/// @param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
/// @param pMensaje Es el mensaje a ser mostrado
/// @param pMensajeError Es el mensaje de error a ser mostrado
/// @param minimo El numero minimo a ser aceptado
/// @param maximo El numero maximo a ser aceptado
/// @param reintentos Parametro que determina la cantidad de reintentos antes de que la funcion
/// finalice.
/// @return  Retorna 0 si se obtuvo el numero y -1 si no
int utn_getInt(int * pResultado, char*pMensaje, char*pMensajeError, int minimo, int maximo, int reintentos){
	int retorno;
	int buffer;

	retorno = -1;

	if (pResultado != NULL && pMensaje != NULL && pMensajeError != NULL && minimo <= maximo && reintentos >= 0){
		while(reintentos>0){
			printf(pMensaje);
			if(getInt(&buffer)==1){
				if(buffer<=maximo && buffer>=minimo){
					break;
				}
			}
			fflush(stdin);
			reintentos--;
			printf(pMensajeError);
		}
		if(reintentos==0){
			retorno=-1;
		}
		else{
		retorno=0;
		*pResultado = buffer;
		}
	}
	return retorno;

}

/// @brief Verifica si la cadena ingresada es numerica
///
/// @param  pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
/// @return  Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no
int getInt(int* pResultado){
	int retorno;
	retorno = -1;
	char buffer[64];

	if(pResultado != NULL){
		if(myGets(buffer,sizeof(buffer)) ==0 && esNumerica(buffer)){
			*pResultado = atoi(buffer);
			retorno = 1;
		}
	}
	return retorno;
}

/// @brief  Verifica si la cadena ingresada es numerica
///
/// @param cadena Cadena de caracteres a ser analizada
/// @return  Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es
int esNumerica(char* cadena)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && strlen(cadena) > 0)
	{
		while(cadena[i] != '\0')
		{
			if(cadena[i] < '0' || cadena[i] > '9' )
			{
				retorno = 0;
				break;
			}
			i++;
		}
	}
	return retorno;
}
/// @brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
/// * un m�ximo de 'longitud - 1' caracteres.
///
///
/// @param cadena o Puntero al espacio de memoria donde se copiara la cadena obtenida
/// @param longitud Define el tama�o de cadena
/// @return  Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
int myGets(char* cadena, int longitud){
	int retorno;
	retorno =-1;
	if(cadena != NULL && longitud >0 && fgets(cadena,longitud,stdin)==cadena){
		fflush(stdin);
		if(cadena[strlen(cadena)-1] == '\n'){
			cadena[strlen(cadena)-1] = '\0';
		}
	retorno=0;
	}

return retorno;
}

/// @brief Funcion que se utiliza para obtener un numero decimal en un rango determinado por la misma.
///
/// @param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
/// @param pMensaje Es el mensaje a ser mostrado
/// @param pMensajeError Es el mensaje de error a ser mostrado
/// @param minimo El numero minimo a ser aceptado
/// @param maximo minimo El numero maximo a ser aceptado
/// @param reintentos Parametro que determina la cantidad de reintentos antes de que la funcion
/// finalice.
/// @return Retorna 0 si se obtuvo el numero y -1 si no
int utnGetFloat(float * pResultado, char*pMensaje, char*pMensajeError, int minimo, int maximo, int reintentos){
	int retorno;
	float buffer;

	retorno = -1;

	if (pResultado != NULL && pMensaje != NULL && pMensajeError != NULL && minimo <= maximo && reintentos >= 0){
		while(reintentos>0){
			printf(pMensaje);
			if(getFloat(&buffer)==1){
				if(buffer<=maximo && buffer>=minimo){
					break;
				}
			}
			fflush(stdin);
			reintentos--;
			printf(pMensajeError);
		}
		if(reintentos==0){
			retorno=-1;
		}
		else{
		retorno=0;
		*pResultado = buffer;
		}
	}
	return retorno;
}

/// @brief Verifica si la cadena ingresada es numerica decimal
///
/// @param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
/// @return   Retorna 1 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
int getFloat(float* pResultado){
	int retorno;
	retorno = -1;
	char buffer[64];

	if(pResultado != NULL){
		if(myGets(buffer,sizeof(buffer)) ==0 && esNumericaDecimal(buffer)==1){
			*pResultado = atof(buffer);
			retorno = 1;
		}
	}
	return retorno;
}

/// @brief Verifica si la cadena ingresada es flotante
///
/// @param cadena Cadena de caracteres a ser analizada
/// @return Retorna 1 (vardadero) si la cadena es flotante y 0 (falso) si no lo es
int esNumericaDecimal(char* cadena)
{
	int i = 0;
	int retorno = 1;

	if(cadena != NULL){
		while(cadena[i]!='\0')
		{
			if((cadena[i] >= '0' && cadena[i] <= '9') || cadena[i] == ',')
			{
				if(cadena[i] == ','){
					cadena[i]= '.';
				}
				i++;
			}
			else{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/// @brief Obtiene un codigo de vuelo alfanumerico
///
/// @param retString Puntero al espacio de memoria donde se dejara el resultado de la funcion
/// @param pMensaje Es el mensaje a ser mostrado
/// @param pMensajeError Es el mensaje de error a ser mostrado
/// @param reintentos reintentos Parametro que determina la cantidad de reintentos antes de que la funcion
/// finalice.
/// @return Retorna 0 si se obtuvo el codigo y -1 si no
int utn_getFlyCode(char retString[], char * pMensaje, char *pMensajeError,  int reintentos){
	int retorno;
	char buffer[10];
	retorno = -1;

		if(retString != NULL && pMensaje != NULL && pMensajeError != NULL &&  reintentos > 0){
			printf("%s",pMensaje);
			fflush(stdin);
			do{
				if (myGets(buffer,sizeof(buffer)) ==0 && esCodigo(buffer) == 1){
					strcpy(retString, buffer);
					retorno = 0;
					break;
				}
				else{
					printf("%s",pMensajeError);
					reintentos--;
				}
			}while(reintentos >= 0);
		}
	return retorno;
}
/// @brief Imprime un mensaje generico
///
/// @param Es el mensaje a ser mostrado
/// @return 0 al mostrar el mensaje
int mensajeGenerico(char * mensaje){

	printf("%s",mensaje);
	return 0;
}
/// @brief Obtiene una cadena de caracteres valido conformado por letras o espacios.
///
/// @param cadena cadena
/// @param mensaje Es el mensaje a ser mostrado
/// @param mensajeError Es el mensaje de error a ser mostrado
/// @param reintentos Reintentos Parametro que determina la cantidad de reintentos antes de que la funcion
/// @return Retorna 0 si se obtuvo la cadena de caracteres y -1 si no
int getString(char cadena[],char mensaje[], char mensajeError[], int reintentos){
	int retorno = -1;
	char cadenaAux[51];
	if(mensaje != NULL && cadena != NULL && mensajeError != 0 && reintentos > 0){
		do{
		printf("%s", mensaje);
		if (myGets(cadenaAux,sizeof(cadenaAux)) ==0 && esNombre(cadenaAux) == 1){
			strcpy(cadena, cadenaAux);
			retorno = 0;
			break;
		}
		else{
			printf("%s",mensajeError);
			reintentos--;
			retorno = 1;
		}
		}while(reintentos >=0);

	}

	return retorno;
}

/// @brief Verifica si la cadena ingresada es un nombre(letras y espacios)
///
/// @param cadena cadena
/// @return Retorna 1 si es valida 0 si fallo alguna validacion.
int esNombre(char* cadena)
{
	int ret=1;
	int i=0;
	int esLetra;

	if(cadena!=NULL){
		while(cadena[i]!='\0'){
			esLetra = isalpha(cadena[i]);
			if(esLetra!=0 || cadena[i] == ' '){
				i++;
			}
			else{
				ret = 0;
				break;
			}
		}
	}

return ret;
}
/// @brief Verifica si la cadena ingresada es un codigo alfanumerico
///
/// @param cadena cadena
/// @return Retorna 1 si es valida 0 si fallo alguna validacion.
int esCodigo(char* cadena)
{
	int ret=1;
	int i=0;
	int esLetra;

	if(cadena!=NULL){
		while(cadena[i]!='\0'){
			esLetra = isalpha(cadena[i]);
			if(esLetra!=0 || cadena[i] == ' ' || isdigit(cadena[i])!=0 ){
				i++;
			}
			else{
				ret = 0;
				break;
			}
		}
	}
	return ret;
}


/// @brief Obtiene un estao de vuelo valido conformado por letras o espacios.
///
/// @param cadena cadena
/// @param mensaje Es el mensaje a ser mostrado
/// @param mensajeError Es el mensaje de error a ser mostrado
/// @param reintentos Reintentos Parametro que determina la cantidad de reintentos antes de que la funcion
/// @return Retorna 0 si se obtuvo el estado de vuelo -1 si no.
int getFlightStatus(char cadena[],char mensaje[], char mensajeError[], int reintentos){
	int retorno = -1;
	char cadenaAux[50];
	if(mensaje != NULL && cadena != NULL && mensajeError != 0 && reintentos > 0){
		do{
		printf("%s", mensaje);
		if (myGets(cadenaAux,sizeof(cadenaAux)) ==0 && !itsFlightStatus(cadenaAux)){
			strcpy(cadena, cadenaAux);
			retorno = 0;
			break;
		}
		else{
			printf("%s",mensajeError);
			reintentos--;
			retorno = 1;
		}
		}while(reintentos >=0);

	}

	return retorno;
}

/// @brief Verifica si la cadena es un estado de vuelo valido.
///
/// @param cadena
/// @return -1 si falla 0 si pudo validar la cadena ingresada.
int itsFlightStatus(char* cadena){
	int retorno=-1;

	if(cadena!=NULL){
		if(strcmp(cadena, "En vuelo") == 0 || strcmp(cadena, "En Horario") == 0 ||  strcmp(cadena, "Aterrizado") == 0 || strcmp(cadena, "Demorado") == 0){
			retorno = 0;
		}
	}
	return retorno;
}








