/*
 * utn.h
 *
 *  Created on: 3 abr. 2022
 *      Author: Agustin
 */


#ifndef BIBLIOTECAESDEDATOS_H_
#define BIBLIOTECAESDEDATOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int menuPrincipal(void);
int utn_getInt(int * pResultado, char*pMensaje, char*pMensajeError, int minimo, int maximo, int reintentos);
int getInt(int* pResultado);
int esNumerica(char* cadena);
int myGets(char* cadena, int longitud);
int utnGetFloat(float * pResultado, char*pMensaje, char*pMensajeError, int minimo, int maximo, int reintentos);
int getFloat(float* pResultado);
int esNumericaDecimal(char* cadena);
int utn_getFlyCode(char retString[], char * pMensaje, char *pMensajeError,  int reintentos);
int esCodigo(char* cadena);
int mensajeGenerico(char * mensaje);
int getString(char cadena[],char mensaje[], char mensajeError[], int reintentos);
int esNombre(char* cadena);
int utn_getString(char string[], int len);
int getFlightStatus(char cadena[],char mensaje[], char mensajeError[], int reintentos);
int itsFlightStatus(char* cadena);
#endif /* BIBLIOTECAESDEDATOS_H_ */
