int controller_loadFromText(char* path , LinkedList* pArrayListPassenger);
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger);
int controller_addPassenger(LinkedList* pArrayListPassenger);
int controller_editPassenger(LinkedList* pArrayListPassenger);
int controller_removePassenger(LinkedList* pArrayListPassenger);
int controller_ListPassenger(LinkedList* pArrayListPassenger);
int controller_sortPassenger(LinkedList* pArrayListPassenger);
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger);
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger);
int controller_saveIdAsText(char *path, int ultimoId);



int controller_menuInformes(LinkedList *pArrayListPassenger);
int controller_ListPassengerMillas(LinkedList* pArrayListPassenger);


#define ARCHIVO_BIN "data.bin"
#define ARCHIVO_TXT "data.csv"
#define ARCHIVO_IDS "dataId.csv"
#define ARCHIVO_TXTFILTRO "dataFilter.csv"




