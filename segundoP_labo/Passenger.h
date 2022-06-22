/*
 * Passenger.h
 *
 *  Created on: 19 may. 2022
 *
 */

#ifndef PASSENGER_H_
#define PASSENGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Controller.h"
#include "bibliotecaESDeDatos.h"

#define FIRSTCLASS 1
#define EXECUTIVECLASS 2
#define ECONOMYCLASS 3

typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	float precio;
	char codigoVuelo[10];
	int tipoPasajero;
	char statusFlight[50];
}Passenger;

Passenger* Passenger_new();
Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char * apellidoStr, char * precioStr, char* tipoPasajeroStr, char* codigoVueloStr,char*estadoDeVueloStr);
void Passenger_delete(Passenger * this);

int Passenger_setId(Passenger* this,int id);
int Passenger_getId(Passenger* this,int* id);

int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);

int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);

int Passenger_setPrecio(Passenger* this,float precio);
int Passenger_getPrecio(Passenger* this,float* precio);

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);
int Passenger_tipoPasajero(Passenger * this, char * tipoPasajeroStr);
int Passenger_tipoPasajeroTxt(Passenger * this,int tipoPasajeroInt, char * tipoPasajeroStr);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);

int Passenger_setStatusFlight(Passenger* this,char*estadoDeVueloStr);
int Passenger_getStatusFlight(Passenger* this,char*estadoDeVueloStr);

int Passenger_sortById(void* primerElemento, void* segundoElemento);
int Passenger_sortByFlightStatus(void* primerElemento, void* segundoElemento);
int Passenger_sortByTypePassenger(void* primerElemento, void* segundoElemento);
int Passenger_sortByFlyCode(void* primerElemento, void* segundoElemento);
int Passenger_sortByPrice(void* primerElemento, void* segundoElemento);
int Passenger_sortByLastName(void* primerElemento, void* segundoElemento);
int Passenger_sortByName(void* primerElemento, void* segundoElemento);


int findPassengerById(LinkedList* pArrayListPassenger, int idBuscado, int * indice);

#endif /* PASSENGER_H_ */
