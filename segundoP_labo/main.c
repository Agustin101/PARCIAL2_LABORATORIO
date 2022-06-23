#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "bibliotecaESDeDatos.h"

int main(){
	setbuf(stdout,NULL);
    int option = 0;
    int flagGuardado=0;
    int flagArchivo = 0;
    int retorno;
    int respuesta = 0;

    LinkedList* listaPasajeros = ll_newLinkedList();

    do{
    	if(!utn_getInt(&option, "1)Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n2)Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).\n3)Alta de pasajero.\n4)Modificar datos de pasajero.\n5)Baja de pasajero.\n6)Listar pasajeros.\n7)Ordenar pasajeros.\n8)Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n9)Guardar los datos de los pasajeros en el archivo data.csv (modo binario).\n10)Salir.\n", "Error ingrese una opcion valida.\n", 1, 10, 3)){
        switch(option){
           case 1:
            	if(flagArchivo == 0 && !controller_loadFromText("data.csv",listaPasajeros)){
    				printf("El archivo se pudo leer y cerrar correctamente.\n");
    				flagArchivo = 1;
            	}
            	else if(flagArchivo == 1){
            		printf("No puede cargar el archivo de pasajeros dos veces.\n");
            	}
            	else{
            		printf("Error al abrir el archivo.\n");
            	}
            break;
        	case 2:
        		if(flagArchivo == 0 && !controller_loadFromBinary(ARCHIVO_BIN,listaPasajeros)  ){
    				printf("\nEl archivo se pudo leer y cerrar correctamente.\n");
    				flagArchivo = 1;
        		}
        		else if(flagArchivo == 1){
            		printf("No puede cargar el archivo de pasajeros dos veces.\n");
        		}
        		else{
        			printf("Error al abrir el archivo.\n");
        		}
        	break;
        	case 3:
        		if(!controller_addPassenger(listaPasajeros)){
					printf("\nPasajero dado de alta con exito.\n");
        		}
        		else{
        			printf("Hubo un error durante la carga del pasajero.\n");
        		}
        	break;
        	case 4:
        		retorno = controller_editPassenger(listaPasajeros);
        		if(retorno == 0){
					printf("Los datos de los pasajeros modificados se guardaron con exito.\n");
        		}
        		else if(retorno==-1){
        			printf("No se realizaron cambios.\n");
        		}
        		else if (retorno==-2){
        			printf("El id ingresado no corresponde a ningun pasajero en la lista.\n");
        		}
        		else if (retorno==-3){
        			printf("Debe tener al menos un pasajero en la lista para poder modificar.\n");
        		}
        	break;
        	case 5:
        		retorno = controller_removePassenger(listaPasajeros);
        		if(retorno == 0){
					printf("Pasajero eliminado del sistema con exito.\n");
        		}
        		else if(retorno == -1){
    				printf("El id no coincide con ningun pasajero.\n");
        		}
        		else{
        			 printf("Debe tener al menos un pasajero en la lista para poder eliminar.\n");
        		 }
        	break;
        	case 6:
        		retorno = controller_ListPassenger(listaPasajeros);
        		if(retorno == 0){
					printf("Lista impresa correctamente.\n");
        		}
        		else if(retorno == -1){
    				printf("Hubo un error durante la impresion de uno de los pasajeros.\n");
        		}
        		else{
        			 printf("Debe tener al menos un pasajero en la lista para poder listar.\n");
        		 }
        	break;
        	case 7:
        		retorno = controller_sortPassenger(listaPasajeros);
        		if(retorno == 0){
        			printf("La lista fue ordenada con exito.\n");
        		}
        		else if(retorno==-1){
        			printf("Un error durante la seleccion del criterio de ordenamiento.\n");
        		}
        		else if(retorno == -2){
        			printf("Debe ingresar al menos un pasajero para ordenar la lista.\n");
        		}

        	break;
        	case 8:
        		if(flagArchivo == 1){
            		if(!controller_saveAsText(ARCHIVO_TXT,listaPasajeros) && !controller_saveAsBinary(ARCHIVO_BIN,listaPasajeros)){
            			printf("Archivo guardado correctamente.\n");
            			flagGuardado=1;
            		}
            		else{
            			printf("Hubo un problema en el guardado del archivo.\n");
            		}
        		}
        		else{
        			printf("debe cargar un archivo antes de guardar.\n");
        		}
        	break;
        	case 9:
        		if(flagArchivo == 1){
            		if( !controller_saveAsBinary(ARCHIVO_BIN,listaPasajeros) && !controller_saveAsText(ARCHIVO_TXT,listaPasajeros)){
            			printf("Archivo guardado correctamente.\n");
            			flagGuardado=1;
            		}
            		else{
            			printf("Hubo un problema en el guardado del archivo.\n");
            		}
        		}
        		else{
        			printf("debe cargar un archivo antes de guardar.\n");
        		}
        	break;
        	case 10:
        		if(flagGuardado == 1){
        			utn_getInt(&respuesta, "¿Esta seguro que desea salir?\n1)Si.\n2)No.", "Ingrese un numero entre los especificados.\n", 1, 2, 2);
        			if(respuesta == 1){
        				ll_deleteLinkedList(listaPasajeros);
        				printf("\nHasta la proxima!");
        			}
        		}
        		else{
        			printf("No puede salir sin guardar.\n");
        		}
        	break;
        	}
    	}
    }while(respuesta != 1);
    return 0;
}

