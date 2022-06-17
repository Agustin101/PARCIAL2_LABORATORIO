#include <stdio.h>
#include <stdlib.h>
#include "inc/LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "bibliotecaESDeDatos.h"
#include "controller.h"

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int retorna -1 si falla y 0 si funciona
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger){
	FILE* pFile = NULL;
	int retorno = -1;

	printf("antes del if");
	if(path != NULL && pArrayListPassenger != NULL){
		printf("post del if");
		pFile = fopen(path, "r");
		if(pFile != NULL && !parser_PassengerFromText(pFile, pArrayListPassenger)){
			printf("antes del if");
				retorno = 0;
		}
	}
	fclose(pFile);
    return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int retorna -1 si falla y 0 si sale bien.
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger){
	FILE* pFile = NULL;
	int retorno = -1;

	if(path != NULL && pArrayListPassenger != NULL){
		pFile = fopen(path, "rb");
		if(pFile != NULL && !parser_PassengerFromBinary(pFile, pArrayListPassenger)){
				retorno = 0;
		}
	}
	fclose(pFile);
    return retorno;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return -1 si falla, 0 si puede dar de alta.
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger){
    int retorno = -1;
	int  bufferId;
	char bufferName[50];
	char bufferLastName[50];
	float bufferPrice;
	char bufferFlyCode[10];
	int bufferTypePassenger;
	char bufferStatusFlight[50];
	FILE * pFile = NULL;
	Passenger * pPasajero = NULL;

	pFile = fopen(ARCHIVO_IDS, "r");

   if(pArrayListPassenger != NULL && pFile != NULL){
	   if(getString(bufferName, "Ingrese el nombre del pasajero:\n", "Error, pruebe con un caracter valido\n", 2)== 0 && getString(bufferLastName, "Ingrese el apellido del pasajero:\n", "Error, pruebe con un caracter valido\n", 2)== 0 &&
		  utnGetFloat(&bufferPrice, "Ingrese el precio del viaje", "Error ingrese un numero valido", 0, 10000000, 2) == 0 && utn_getFlyCode(bufferFlyCode, "Ingrese el codigo de vuelo:\n", "Error solo caracteres alfanumericos", 2) == 0 &&
		  utn_getInt(&bufferTypePassenger, "Ingrese el tipo de pasajero: \n1)FIRSTCLASS\n2)EXECUTIVECLASS\n3)ECONOMYCLASS\n", "Error ingrese una opcion valida.", 1, 3, 2) == 0 &&
		  getFlightStatus(bufferStatusFlight, "Ingrese el estado del vuelo 'En vuelo' 'En Horario' 'Aterrizado' 'Demorado':\n", "Error, debe ser una cadena de caracteres valida respetando minusculas y mayusculas.\n", 2)== 0){
		  pPasajero = Passenger_new();
		  bufferId = parser_idsFromText(pFile);
		  bufferId++;
		  	  if(pPasajero != NULL && bufferId > 0){
		  		  if(Passenger_setId(pPasajero, bufferId) == -1 || Passenger_setPrecio(pPasajero, bufferPrice) == -1 || Passenger_setTipoPasajero(pPasajero, bufferTypePassenger)	== -1 ||
		  		  Passenger_setNombre(pPasajero, bufferName) == -1 || Passenger_setApellido(pPasajero, bufferLastName) == -1 || Passenger_setCodigoVuelo(pPasajero, bufferFlyCode) ||
				  Passenger_setStatusFlight(pPasajero, bufferStatusFlight)==-1){
				  Passenger_delete(pPasajero);
				  pPasajero=NULL;
				}
				else{
					ll_add(pArrayListPassenger, pPasajero);
					retorno = 0;
					controller_saveIdAsText(ARCHIVO_IDS, bufferId);
				}
		   }else{
				Passenger_delete(pPasajero);
				pPasajero=NULL;
		   }
	   }
   }
   fclose(pFile);
   return retorno;
}

/** \brief Modificar datos de pasajero elegidos por el usuario
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return retorna -2  si la lista esta vacia, -1 si no encuentra el id, 0 si pudo modificar
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger){
	int retorno = -1;
	int opcion;
	int idAmodificar;
	Passenger * pPasajero = NULL;
	char nombreAux[50];
	char apellidoAux[50];
	float precioAux;
	char codigoDeVueloAux[8];
	int tipoPasajeroAux;
	char estadoDeVueloAux[50];
	int indiceRetornado;

	if(pArrayListPassenger != NULL && !ll_isEmpty(pArrayListPassenger)){
		controller_ListPassenger(pArrayListPassenger);
		if(!utn_getInt(&idAmodificar, "Ingrese el id del pasajero que desea modificar:\n", "Ingrese un numero en el rango.\n", 1, 10000, 2) && !findPassengerById(pArrayListPassenger, idAmodificar, &indiceRetornado)){
				pPasajero = (Passenger*)ll_get(pArrayListPassenger, indiceRetornado);
				if(pPasajero != NULL){
					do{
						if(utn_getInt(&opcion, "Ingrese el campo que desea modificar:\n1)Nombre.\n2)Apellido.\n3)Precio.\n4)Codigo de vuelo.\n5)Tipo de pasajero\n6)Estado de vuelo.\n7)Volver al menu principal.", "Ingrese un numero en el rango.\n", 1, 7, 2)==0){
							switch(opcion){
							case 1:
								if(!getString(nombreAux, "Ingrese el nuevo nombre del pasajero: \n", "Ingrese un nombre valido", 2)){
									if(!Passenger_setNombre(pPasajero, nombreAux)){
										printf("El nombre fue actualizado con exito.\n");
										retorno = 0;
									}
									else{
										printf("Hubo un error en el cambio de nombre.\n");
									}
								}
								break;
							case 2:
								if(!getString(apellidoAux, "Ingrese el nuevo apellido del pasajero: \n", "Ingrese un apellido valido\n", 2)){
									if(!Passenger_setApellido(pPasajero, apellidoAux)){
										printf("Apellido modificado con exito\n");
										retorno = 0;
									}
								}
								break;
							case 3:
								if(!utnGetFloat(&precioAux, "Ingrese el nuevo precio del viaje:\n", "Por favor ingrese un valor valido.", 0, 1000000, 2)){
									if(!Passenger_setPrecio(pPasajero, precioAux)){
										printf("Precio actualizado con exito.\n");
										retorno = 0;
									}
								}
								break;
							case 4:
								if(!utn_getFlyCode(codigoDeVueloAux, "Ingrese el nuevo codigo de vuelo: \n", "Ingrese un codigo alfanumerico.\n", 2)){
									if(!Passenger_setCodigoVuelo(pPasajero, codigoDeVueloAux)){
										printf("Codigo de vuelo actualizado con exito.\n");
										retorno = 0;
									}
								}
								break;
							case 5:
								if(!utn_getInt(&tipoPasajeroAux, "Ingrese el nuevo tipo de pasajero: \n1)First Class\n2)Executive class\n3)Economy Class\n", "Ingrese una opcion valida.", 1, 3, 2)){
									if(!Passenger_setTipoPasajero(pPasajero, tipoPasajeroAux)){
										printf("Tipo de pasajero actualizado con exito.\n");
										retorno = 0;
									}
								}
								break;
							case 6:
								if(!getFlightStatus(estadoDeVueloAux, "Ingrese el estado del vuelo 'En vuelo' 'En Horario' 'Aterrizado' 'Demorado':\n", "Error, debe ser una cadena de caracteres valida respetando minusculas y mayusculas.\n", 2)){
									if(!Passenger_setStatusFlight(pPasajero, estadoDeVueloAux)){
										printf("Estado de vuelo actualizado con exito.\n");
										retorno = 0;
									}
								}
								break;
							case 7:
								break;
							}
						}
					}while(opcion != 7);
				}
				else{
					retorno = -1;
				}
		}
	}else{
		retorno = -2;
	}

    return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return retorna -2  si la lista esta vacia, -1 si no encuentra el id, 0 si pudo dar de baja
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger){
	int retorno = -2;
	int idAEliminar;
	int idAux;
	int indiceRetornado;
	Passenger * pAux = NULL;

	if(pArrayListPassenger != NULL && !ll_isEmpty(pArrayListPassenger)){
		controller_ListPassenger(pArrayListPassenger);
		if(utn_getInt(&idAEliminar, "Ingrese el id del pasajero a eliminar: \n", "Ingrese un id valido", 1, 10000, 2) == 0 && !findPassengerById(pArrayListPassenger, idAEliminar, &indiceRetornado)){
			pAux = (Passenger*)ll_get(pArrayListPassenger, indiceRetornado);
			Passenger_getId(pAux, &idAux);
			if(pAux != NULL && !ll_remove(pArrayListPassenger,indiceRetornado)){
				Passenger_delete(pAux);
				retorno = 0;
			}
		}
		else{
			retorno = -1;
		}
	}

    return retorno;;
}

/** \brief Listar pasajeros
 * \param pArrayListPassenger LinkedList*
 * \return int -1 si no hay ningun pasajero 0 si hay al menos 1
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger){
	Passenger * pPasajero = NULL;
	int retorno = -2;
	int cantidadElementos;
	int  bufferId;
	char bufferName[50];
	char bufferLastName[50];
	float bufferPrice;
	char bufferFlyCode[10];
	int bufferTypePassenger;
	char bufferStatusFlight[50];
	char bufferTypePassengerStr[50];

	if(pArrayListPassenger != NULL && !ll_isEmpty(pArrayListPassenger)){
		printf("ID   NOMBRE          APELLIDO        PRECIO     FLYCODE T.PASAJERO      FLIGHTSTATUS\n");
		cantidadElementos = ll_len(pArrayListPassenger);
		for(int i =0; i < cantidadElementos; i++){
			pPasajero = (Passenger*) ll_get(pArrayListPassenger, i);
			if(pPasajero != NULL && !Passenger_getApellido(pPasajero, bufferLastName) && !Passenger_getId(pPasajero, &bufferId)
					&& !Passenger_getNombre(pPasajero, bufferName) && !Passenger_getPrecio(pPasajero, &bufferPrice)
					&& !Passenger_getTipoPasajero(pPasajero, &bufferTypePassenger) && !Passenger_getCodigoVuelo(pPasajero, bufferFlyCode)
					&& !Passenger_getStatusFlight(pPasajero, bufferStatusFlight) && !Passenger_tipoPasajeroTxt(pPasajero,bufferTypePassenger, bufferTypePassengerStr)){
				printf("%-4d %-15s %-15s $%-9.2f %-7s %-15s %-15s\n",bufferId,bufferName, bufferLastName,bufferPrice,bufferFlyCode,bufferTypePassengerStr,bufferStatusFlight);
				retorno = 0;
			}
			else{
				retorno = -1;
			}
		}
	}
    return retorno;
}

/** \brief Ordenar pasajeros bajo el criterio seleccionado
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return -2 si no hay pasajeros, -1 si la seleccion sale mal, 0 si pudo ordenar.
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger){
	int retorno = -2;
	int opcion;
	int order;

	if(pArrayListPassenger != NULL && !ll_isEmpty(pArrayListPassenger)){
			retorno = -1;
			do{
				if(!utn_getInt(&opcion, "Indique la forma en que desea ordenar\n1)Ordenar por id.\n2)Por nombre\n3)Apellido\n4)Precio.\n5)Codigo de vuelo.\n6)Tipo de pasajero.\n7)Estado de vuelo.\n8)Volver al menu principal.", "Error ingrese una opcion valida", 1, 8, 2)){
				switch(opcion){
				case 1:
					if(!utn_getInt(&order, "Indique el orden para ordenar.\n0)Descendente.\n1)Ascendente.\n", "Indique una opcion valida.", 0, 1, 2)){
						printf("Ordenando, por favor espere\n");
						ll_sort(pArrayListPassenger,Passenger_sortById, order);
						retorno = 0;
					}
					break;
				case 2:
					if(!utn_getInt(&order, "Indique el orden para ordenar.\n0)Descendente.\n1)Ascendente.\n", "Indique una opcion valida.", 0, 1, 2)){
						printf("Ordenando, por favor espere\n");
						ll_sort(pArrayListPassenger,Passenger_sortByName, order);
						retorno = 0;
					}
					break;
				case 3:
					if(!utn_getInt(&order, "Indique el orden para ordenar.\n0)Descendente.\n1)Ascendente.\n", "Indique una opcion valida.", 0, 1, 2)){
						printf("Ordenando, por favor espere\n");
						ll_sort(pArrayListPassenger,Passenger_sortByLastName, order);
						retorno = 0;
					}
					break;
				case 4:
					if(!utn_getInt(&order, "Indique el orden para ordenar.\n0)Descendente.\n1)Ascendente.\n", "Indique una opcion valida.", 0, 1, 2)){
						printf("Ordenando, por favor espere\n");
						ll_sort(pArrayListPassenger,Passenger_sortByPrice, order);
						retorno = 0;
					}
					break;
				case 5:
					if(!utn_getInt(&order, "Indique el orden para ordenar.\n0)Descendente.\n1)Ascendente.\n", "Indique una opcion valida.", 0, 1, 2)){
						printf("Ordenando, por favor espere\n");
						ll_sort(pArrayListPassenger,Passenger_sortByFlyCode, order);
						retorno = 0;
					}
					break;
				case 6:
					if(!utn_getInt(&order, "Indique el orden para ordenar.\n0)Descendente.\n1)Ascendente.\n", "Indique una opcion valida.", 0, 1, 2)){
						printf("Ordenando, por favor espere\n");
						ll_sort(pArrayListPassenger,Passenger_sortByTypePassenger, order);
						retorno = 0;
					}
					break;
				case 7:
					if(!utn_getInt(&order, "Indique el orden para ordenar.\n0)Descendente.\n1)Ascendente.\n", "Indique una opcion valida.", 0, 1, 2)){
						printf("Ordenando, por favor espere\n");
						ll_sort(pArrayListPassenger,Passenger_sortByFlightStatus, order);
						retorno = 0;
					}
					break;
				case 8:
					break;
				}
			}
			}while(opcion!=8);
	}
    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int retorna -1 si falla y 0 si sale bien.
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger){
	Passenger * pPasajero = NULL;
	FILE * pFile = NULL;
	int retorno = -1;
	int cantidadElementos;
	int  bufferId;
	char bufferName[50];
	char bufferLastName[50];
	float bufferPrice;
	char bufferFlyCode[10];
	int bufferTypePassenger;
	char bufferStatusFlight[50];
	char bufferTypePassengerStr[50];

	if(path != NULL && pArrayListPassenger != NULL){
		pFile = fopen(path, "w");
		if(pFile != NULL){
		fprintf(pFile,"id,name,lastname,price,flycode,typePassenger,statusFlight\n");
			cantidadElementos = ll_len(pArrayListPassenger);
			for(int i = 0; i < cantidadElementos; i++){
				pPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
				if(pPasajero != NULL && !Passenger_getId(pPasajero, &bufferId) && !Passenger_getNombre(pPasajero, bufferName)&& !Passenger_getApellido(pPasajero, bufferLastName)&&
		    	   !Passenger_getPrecio(pPasajero, &bufferPrice) && !Passenger_getCodigoVuelo(pPasajero, bufferFlyCode) && !Passenger_getTipoPasajero(pPasajero, &bufferTypePassenger)
				   && !Passenger_tipoPasajeroTxt(pPasajero,bufferTypePassenger, bufferTypePassengerStr) && !Passenger_getStatusFlight(pPasajero, bufferStatusFlight)){
						fprintf(pFile,"%d,%s,%s,%.2f,%s,%s,%s\n",bufferId,bufferName, bufferLastName,bufferPrice,bufferFlyCode,bufferTypePassengerStr,bufferStatusFlight);
						retorno = 0;
				}
			}
		}
	}
	fclose(pFile);
    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int retorna  -1 si falla y 0 si sale bien
 *
 */
int controller_saveAsBinary(char *path, LinkedList *pArrayListPassenger) {
	int retorno = -1;
	int cantidadElementos;
	Passenger *pPasajero = NULL;
	FILE *pFile = NULL;

	if (path != NULL && pArrayListPassenger != NULL) {
		pFile = fopen(path, "wb");
		if (pFile != NULL) {
			cantidadElementos = ll_len(pArrayListPassenger);
			for (int i = 0; i < cantidadElementos; i++) {
				pPasajero = (Passenger*) ll_get(pArrayListPassenger, i);
				if (pPasajero != NULL) {
					fwrite(pPasajero, sizeof(Passenger), 1, pFile);
					retorno = 0;
				}
			}
		}
	}
	fclose(pFile);
	return retorno;
}

/// @brief Gaurda el ultimo id asignado en el archivo csv
///
/// @param path
/// @param ultimoId
/// @return -1 si falla 0 si sale bien
int controller_saveIdAsText(char *path, int ultimoId) {
	FILE *pFile = NULL;
	int retorno = -1;

	if(path != NULL && ultimoId > 0){
		pFile = fopen(path, "w");
		if (pFile != NULL) {
			fprintf(pFile, "%d,\n", ultimoId);
			retorno = 0;
		}
	}
	fclose(pFile);
	return retorno;
}
