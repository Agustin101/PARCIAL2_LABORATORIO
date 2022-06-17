#include <stdio.h>
#include <stdlib.h>
#include "inc/LinkedList.h"
#include "Passenger.h"
#include "Controller.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int retorna -1 si reciba un archivo o lista nula y 0 si puede cargar al menos a un pasajero.
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger){
	int retorno = -1;
	Passenger * pPasajeroAux = NULL;
	char bufferId[50];
	char bufferName[50];
	char bufferLastName[50];
	char bufferPrice[50];
	char bufferFlyCode[10];
	char bufferTypePassenger[50];
	char bufferStatusFlight[50];
	char ghostHeader[250];
	int cantidadCampos;

	if(pFile != NULL && pArrayListPassenger != NULL){
		fscanf(pFile, "%s\n", ghostHeader);
		while(!feof(pFile)){
			cantidadCampos = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferLastName,bufferPrice,bufferFlyCode,bufferTypePassenger,bufferStatusFlight);
			if(cantidadCampos == 7){
				pPasajeroAux = Passenger_newParametros(bufferId, bufferName, bufferLastName, bufferPrice, bufferTypePassenger, bufferFlyCode, bufferStatusFlight);
				if(pPasajeroAux != NULL){
					ll_add(pArrayListPassenger, pPasajeroAux);
					retorno = 0;
				}
				else{
					Passenger_delete(pPasajeroAux);
				}
			}
		}
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int -1 si falla 0 si sale bien
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger){
	int retorno = -1;
	int cantidad;
    int id;
    char name[50];
    char lastName[50];
    float price;
    int typePassenger;
    char flyCode[10];
    char flightStatus[50];
	Passenger * pAux = NULL;

	if(pFile != NULL && pArrayListPassenger != NULL){
		while(!feof(pFile)){
			pAux=Passenger_new();
			cantidad = fread(pAux, sizeof(Passenger),1,pFile);
			if(pAux != NULL && cantidad == 1){
				if(!Passenger_getApellido(pAux, lastName) && !Passenger_getId(pAux, &id)
						&& !Passenger_getNombre(pAux, name) && !Passenger_getPrecio(pAux, &price)
						&& !Passenger_getTipoPasajero(pAux, &typePassenger) && !Passenger_getCodigoVuelo(pAux, flyCode)
						&& !Passenger_getStatusFlight(pAux, flightStatus)){
					ll_add(pArrayListPassenger, pAux);
					retorno = 0;
				}
				else{
					Passenger_delete(pAux);
				}
			}
		}
	}
    return retorno;
}

///** \brief Obtiene el ultimo id asignado desde el archivo data.csv (modo texto).
///
///\param path char*
/// \param pArrayListPassenger LinkedList*
///\return int retorna -1 si reciba un archivo o lista nula y 0 si puede cargar al menos un id.
int parser_idsFromText(FILE* pFile){
	int retorno = -1;
	int cantidadCampos;
	char bufferId[50];
	int idAnterior;

	if(pFile != NULL){
		while(!feof(pFile)){
			cantidadCampos = fscanf(pFile, "%[^\n]\n",bufferId);
			if(cantidadCampos == 1){
				idAnterior = atoi(bufferId);
			}
		}
		retorno = idAnterior;
	}
    return retorno;
}





