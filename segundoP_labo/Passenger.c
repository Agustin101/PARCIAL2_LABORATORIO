#include "Passenger.h"

/// @brief  asigna espacio de memoria para un nuevo pasajero
///
/// @return Devuelve el puntero a memoria
Passenger* Passenger_new(){
	Passenger * pasajeroAux = NULL;
	pasajeroAux = (Passenger *)malloc(sizeof(Passenger));
	if(pasajeroAux != NULL){
		 Passenger_setId(pasajeroAux,0);
		 Passenger_setNombre(pasajeroAux," ");
		 Passenger_setApellido(pasajeroAux," ");
		 Passenger_setPrecio(pasajeroAux,0);
		 Passenger_setTipoPasajero(pasajeroAux,0);
		 Passenger_setCodigoVuelo(pasajeroAux," ");
		 Passenger_setStatusFlight(pasajeroAux," ");
	}
	else{
		Passenger_delete(pasajeroAux);
	}
	return pasajeroAux;
}

/// @brief Carga un pasajero con los parametros recibidos.
///
/// @param idStr
/// @param nombreStr
/// @param apellidoStr
/// @param precioStr
/// @param tipoPasajeroStr
/// @param codigoVueloStr
/// @param estadoDeVueloStr
/// @return retorna un puntero a NULL si falla o el puntero del pasajero si lo puede cargar sin errores.
Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char * apellidoStr, char * precioStr, char* tipoPasajeroStr, char* codigoVueloStr,char*estadoDeVueloStr){
	Passenger * this = NULL;
	int idAux;
	float precioAux;
	int tipoPasajeroAux;

	this = Passenger_new();
	tipoPasajeroAux = Passenger_tipoPasajero(this,tipoPasajeroStr);

	if(this != NULL && tipoPasajeroAux != -1 && idStr != NULL && nombreStr !=NULL && apellidoStr!=NULL && precioStr!=NULL && tipoPasajeroStr!=NULL && codigoVueloStr!= NULL && estadoDeVueloStr != NULL){
		idAux = atoi(idStr);
		precioAux = atof(precioStr);
		if(Passenger_setId(this, idAux) == -1 || Passenger_setPrecio(this, precioAux) == -1 || Passenger_setTipoPasajero(this, tipoPasajeroAux)	== -1 ||
			Passenger_setNombre(this, nombreStr) == -1 || Passenger_setApellido(this, apellidoStr) == -1 || Passenger_setCodigoVuelo(this, codigoVueloStr) ||
			Passenger_setStatusFlight(this, estadoDeVueloStr)==-1){
			Passenger_delete(this);
			this=NULL;
		}
	}
	return this;
}

/// @brief Borra un puntero a pasajero y libera el espacio de memoria.
///
/// @param Passenger * this
void Passenger_delete(Passenger * this){
	if(this != NULL){
		free(this);
	}
}

/// @brief asigna el id al campo del pasajero
///
/// @param Passenger* this
/// @param int id
/// @return int retorno -1 si falla 0 si puede
int Passenger_setId(Passenger* this,int id){
	int retorno = -1;

	if(this != NULL && id >0){
			this->id = id;
			retorno = 0;
	}
	return retorno;
}


/// @brief obtiene el id del campo del pasajero
///
/// @param Passenger* this
/// @param int* id
/// @return int retorno -1 si falla 0 si puede
int Passenger_getId(Passenger* this,int* id){
	int retorno = -1;
	if(this != NULL && id != NULL){
		*id = this->id;
		retorno = 0;
	}
	return retorno;
}

/// @brief asigna el nombre al campo del pasajero
///
/// @param Passenger* this
/// @param char* nombre
/// @return int retorno -1 si falla 0 si puede
int Passenger_setNombre(Passenger* this,char* nombre){
	int retorno = -1;
	if(this != NULL && nombre != NULL){
		if(esNombre(nombre)){
			strcpy(this->nombre,nombre);
			retorno = 0;
		}
	}
	return retorno;
}
/// @brief obtiene el nombre del campo del pasajero
///
/// @param Passenger* this
/// @param char* nombre
/// @return int retorno -1 si falla 0 si puede
int Passenger_getNombre(Passenger* this,char* nombre){
	int retorno = -1;
	if(this != NULL && nombre != NULL){
		retorno = 0;
		strcpy(nombre,this->nombre);
	}
	return retorno;
}

/// @brief asigna el apellido al campo del pasajero
///
/// @param Passenger* this
/// @param char* apellido
/// @return int retorno -1 si falla 0 si puede
int Passenger_setApellido(Passenger* this,char* apellido){
	int retorno = -1;
	if(this != NULL && apellido != NULL){
		if(esNombre(apellido)){
			strncpy(this->apellido,apellido,sizeof(this->apellido));
			retorno = 0;
		}
	}
	return retorno;
}

/// @brief obtiene el apellido del campo del pasajero
///
/// @param Passenger* this
/// @param char* apellido
/// @return int retorno -1 si falla 0 si puede
int Passenger_getApellido(Passenger* this,char* apellido){
	int retorno = -1;
	if(this != NULL && apellido != NULL){
		retorno = 0;
		strcpy(apellido,this->apellido);
	}
	return retorno;
}

/// @brief asigna el codigo al campo del pasajero
///
/// @param Passenger*this
/// @param char* codigoVuelo
/// @return int retorno -1 si falla 0 si puede
int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo){

	int retorno = -1;
	if(this != NULL && codigoVuelo != NULL){
		if(esCodigo(codigoVuelo)){
			strcpy(this->codigoVuelo,codigoVuelo);
			retorno = 0;
		}
	}
	return retorno;

}

/// @brief obtiene el codigo del campo del pasajero
///
/// @param Passenger*this
/// @param char* codigoVuelo
/// @return int retorno -1 si falla 0 si puede
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo){
	int retorno = -1;
	if(this != NULL && codigoVuelo != NULL){
		retorno = 0;
		strcpy(codigoVuelo,this->codigoVuelo);
	}
	return retorno;
}

/// @brief asigna el tipo al campo del pasajero
///
/// @param Passenger*this
/// @param int tipoPasajero
/// @return int retorno -1 si falla 0 si puede
int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero){
	int retorno = -1;

	if(this != NULL && tipoPasajero > 0){
			this->tipoPasajero = tipoPasajero;
			retorno = 0;
	}
	return retorno;
}

/// @brief Verifica el tipo de pasajero mediante la cadena ingresada y la transforma
/// en entero.
/// @param Passenger * this
/// @param char * tipoPasajeroStr
/// @return -1 si falla o el entero del tipo si pudo asignarlo correctamente.
int Passenger_tipoPasajero(Passenger * this, char * tipoPasajeroStr){
	int retorno = -1;

	if(this != NULL && tipoPasajeroStr != NULL){
		if(strcmp(tipoPasajeroStr, "FirstClass")==0){
			retorno = FIRSTCLASS;
		}
		else if(strcmp(tipoPasajeroStr, "ExecutiveClass")==0){
			retorno = EXECUTIVECLASS;
		}
		else if(strcmp(tipoPasajeroStr, "EconomyClass")==0){
			retorno = ECONOMYCLASS;
		}
	}
	return retorno;
}

/// @brief Convierte el tipo de pasajaero de entero a cadena de chars
///
/// @param this
/// @param tipoPasajeroInt
/// @param tipoPasajeroStr
/// @return	-1 si falla 0 si puede convertirlo
int Passenger_tipoPasajeroTxt(Passenger * this,int tipoPasajeroInt, char * tipoPasajeroStr){
	int retorno = -1;
	char bufferAux[50];

	if(this != NULL && tipoPasajeroStr != NULL){
		retorno = 0;
		if(tipoPasajeroInt == FIRSTCLASS){
			strcpy(bufferAux, "FirstClass");
			strcpy(tipoPasajeroStr,bufferAux);
		}
		else if(tipoPasajeroInt == EXECUTIVECLASS){
			strcpy(bufferAux, "ExecutiveClass");
			strcpy(tipoPasajeroStr,bufferAux);
		}
		else if(tipoPasajeroInt == ECONOMYCLASS){
			strcpy(bufferAux, "EconomyClass");
			strcpy(tipoPasajeroStr,bufferAux);
		}
	}
	return retorno;
}

/// @brief obtiene el tipo del campo del pasajero
///
/// @param Passenger* this
/// @param int* tipoPasajero
/// @return int retorno -1 si falla 0 si puede
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero){
	int retorno = -1;
	if(this != NULL && tipoPasajero != NULL){
		retorno = 0;
		*tipoPasajero = this->tipoPasajero;
	}
	return retorno;
}

/// @brief asigna el precio al campo del pasajero
///
/// @param Passenger* this
/// @param float precio
/// @return int retorno -1 si falla 0 si puede
int Passenger_setPrecio(Passenger* this,float precio){
	int retorno = -1;

	if(this != NULL && precio > 0){
			this->precio = precio;
			retorno = 0;
	}
	return retorno;
}

/// @brief obtiene el precio del campo del pasajero
///
/// @param Passenger* this
/// @param float* precio
/// @return int retorno -1 si falla 0 si puede
int Passenger_getPrecio(Passenger* this,float* precio){
	int retorno = -1;
	if(this != NULL && precio != NULL){
		retorno = 0;
		*precio = this->precio;
	}
	return retorno;
}

/// @brief asigna el estado de vuelo al campo del pasajero
///
/// @param Passenger* this
/// @param char* estadoDeVueloStr
/// @return int retorno -1 si falla 0 si puede
int Passenger_setStatusFlight(Passenger* this,char*estadoDeVueloStr){
	int retorno = -1;
	if(this != NULL && estadoDeVueloStr != NULL){
		if(esNombre(estadoDeVueloStr)){
			strcpy(this->statusFlight,estadoDeVueloStr);
			retorno = 0;
		}
	}
	return retorno;
}

/// @brief obtiene el estado de vuelo del campo del pasajero
///
/// @param Passenger* this
/// @param estadoDeVueloStr
/// @return int retorno -1 si falla 0 si puede
int Passenger_getStatusFlight(Passenger* this,char*estadoDeVueloStr){
	int retorno = -1;
	if(this != NULL && estadoDeVueloStr != NULL){
		retorno = 0;
		strcpy(estadoDeVueloStr,this->statusFlight);
	}
	return retorno;
}

/// @brief ordena por id
///
/// @param primerElemento
/// @param segundoElemento
/// @return el resultado de la comparacion de los id
int Passenger_sortById(void* primerElemento, void* segundoElemento){
	int retorno = 0;
	int idPrimerElemento;
	int idSegundoElemento;

	Passenger * pPrimElem;
	Passenger * pSegElem;

	if(primerElemento != NULL && segundoElemento != NULL){
		pPrimElem = (Passenger *) primerElemento;
		pSegElem = (Passenger *) segundoElemento;

		Passenger_getId(pPrimElem, &idPrimerElemento);
		Passenger_getId(pSegElem, &idSegundoElemento);

		if(idPrimerElemento > idSegundoElemento){
			retorno = 1;
		}
		else if (idPrimerElemento < idSegundoElemento){
			retorno = -1;
		}

	}
	return retorno;
}

/// @brief ordena por estado de vuelo
///
/// @param primerElemento
/// @param segundoElemento
/// @return el resultado de la comparacion del estado de vuelo
int Passenger_sortByFlightStatus(void* primerElemento, void* segundoElemento){
	int retorno = -1;
	char estadoUno[50];
	char estadoDos[50];

	Passenger * primElem;
	Passenger * SegElem;

	if(primerElemento != NULL && segundoElemento != NULL){
		primElem = (Passenger *) primerElemento;
		SegElem = (Passenger *) segundoElemento;

		Passenger_getStatusFlight(primElem, estadoUno);
		Passenger_getStatusFlight(SegElem, estadoDos);
		retorno = strcmp(estadoUno,estadoDos);
	}

	return retorno;
}

/// @brief ordena por el tipo de pasajero
///
/// @param primerElemento
/// @param segundoElemento
/// @return el resultado de la comparacion del tipo de pasajero
int Passenger_sortByTypePassenger(void* primerElemento, void* segundoElemento){
	int retorno = 0;
	int tipoPrimerElemento;
	int tipoSegundoElemento;

	Passenger * primElem;
	Passenger * SegElem;

	if(primerElemento != NULL && segundoElemento != NULL){
		primElem = (Passenger *) primerElemento;
		SegElem = (Passenger *) segundoElemento;
		Passenger_getTipoPasajero(primElem, &tipoPrimerElemento);
		Passenger_getTipoPasajero(SegElem, &tipoSegundoElemento);
		if(tipoPrimerElemento > tipoSegundoElemento){
			retorno = 1;
		}
		else if (tipoPrimerElemento < tipoSegundoElemento){
			retorno = -1;
		}
	}
	return retorno;
}

/// @brief ordena por el codigo de vuelo
///
/// @param primerElemento
/// @param segundoElemento
/// @return el resultado de la comparacion del codigo de vuelo
int Passenger_sortByFlyCode(void* primerElemento, void* segundoElemento){
	int retorno = -1;
	char codigoUno[50];
	char codigoDos[50];

	Passenger * primElem;
	Passenger * SegElem;

	if(primerElemento != NULL && segundoElemento != NULL){
		primElem = (Passenger *) primerElemento;
		SegElem = (Passenger *) segundoElemento;

		Passenger_getCodigoVuelo(primElem, codigoUno);
		Passenger_getCodigoVuelo(SegElem, codigoDos);
		retorno = strcmp(codigoUno,codigoDos);
	}

	return retorno;
}


/// @brief ordena por el precio de pasajero
///
/// @param primerElemento
/// @param segundoElemento
/// @return el resultado de la comparacion del precio del pasajero
int Passenger_sortByPrice(void* primerElemento, void* segundoElemento){
	int retorno = 0;
	float precioPrimerElemento;
	float precioSegundoElemento;

	Passenger * primElem;
	Passenger * SegElem;

	if(primerElemento != NULL && segundoElemento != NULL){
		primElem = (Passenger *) primerElemento;
		SegElem = (Passenger *) segundoElemento;

		Passenger_getPrecio(primElem, &precioPrimerElemento);
		Passenger_getPrecio(SegElem, &precioSegundoElemento);

		if(precioPrimerElemento > precioSegundoElemento){
			retorno = 1;
		}
		else if (precioPrimerElemento < precioSegundoElemento){
			retorno = -1;
		}

	}
	return retorno;
}

/// @brief ordena por el apellido del pasajero
///
/// @param primerElemento
/// @param segundoElemento
/// @return el resultado de la comparacion del apellido del pasajero
int Passenger_sortByLastName(void* primerElemento, void* segundoElemento){
	int retorno = -1;
	char apellidoUno[50];
	char apellidoDos[50];

	Passenger * primElem;
	Passenger * SegElem;

	if(primerElemento != NULL && segundoElemento != NULL){
		primElem = (Passenger *) primerElemento;
		SegElem = (Passenger *) segundoElemento;

		Passenger_getApellido(primElem, apellidoUno);
		Passenger_getApellido(SegElem, apellidoDos);
		retorno = strcmp(apellidoUno,apellidoDos);
	}

	return retorno;
}

/// @brief ordena por el nombre del pasajero
///
/// @param primerElemento
/// @param segundoElemento
/// @return el resultado de la comparacion del nombre del pasajero
int Passenger_sortByName(void* primerElemento, void* segundoElemento){
	int retorno = -1;
	char nombreUno[50];
	char nombreDos[50];

	Passenger * primElem;
	Passenger * SegElem;

	if(primerElemento != NULL && segundoElemento != NULL){
		primElem = (Passenger *) primerElemento;
		SegElem = (Passenger *) segundoElemento;

		Passenger_getNombre(primElem, nombreUno);
		Passenger_getNombre(SegElem, nombreDos);

		retorno = strcmp(nombreUno,nombreDos);
	}

	return retorno;
}

/// @brief Busca una id en la lista de pasajeros
///
/// @param pArrayListPassenger
/// @param idBuscado
/// @return -1 si falla o 0 si sale bien
int findPassengerById(LinkedList* pArrayListPassenger, int idBuscado, int * indice) {
	int retorno;
	retorno = -1;
	int cantidadElementos;
	int idAux;
	Passenger * pAux = NULL;

	if (pArrayListPassenger != NULL && idBuscado > 0 && indice != NULL) {
		cantidadElementos = ll_len(pArrayListPassenger);
		for (int i = 0; i < cantidadElementos; i++) {
			pAux = (Passenger *)ll_get(pArrayListPassenger, i);
			Passenger_getId(pAux, &idAux);
			if ( pAux != NULL && idAux == idBuscado ) {
				*indice = i;
				 retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
























