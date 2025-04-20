#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea
{ 
    int TareaID;//Numérico autoincremental comenzando en 1000 
    char *Descripcion;  //       
    int Duracion; // entre 10 – 100  
}typedef Tarea;  

typedef struct Nodo {
    Tarea Tarea;  
    struct Nodo *Siguiente;  
} Nodo;

Nodo *crear_lista_vacia();
Nodo *crear_nodo(char *descripcion, int duracion, int incremento);

void insertar_inicio_nodo(Nodo **start, Nodo *nodo);
void insertar_final_nodo(Nodo **start, Nodo *nodo);
Nodo *buscar_nodo(Nodo **start, char *buscado);

void eliminar_nodo(Nodo **nodo);
Nodo *quitar_nodo_x_palabra(Nodo **star, char *buscado);
Nodo *quitar_nodo_x_id(Nodo **star, int id_buscado);

void mostrar_tareas(Nodo ** start);

int main()
{
    srand(time(NULL));

    int incremento = 1000;
    char descripcion[150];
    int condicion = 1;

    Nodo *start_tareas_pendientes = crear_lista_vacia();
    Nodo *start_tareas_realizadas = crear_lista_vacia();

    printf("-----------------------------------------°°°BIENVENIDO A LA LISTA DE TAREAS°°°-----------------------------------------");
    do
    {
        printf("\nIngrese la descripcion de la tarea: ");
        scanf("%s", descripcion);

        insertar_final_nodo(&start_tareas_pendientes, crear_nodo(descripcion, 10, incremento++));
        insertar_final_nodo(&start_tareas_pendientes, crear_nodo(descripcion, rand()% (100 - 10 + 1) + 10, incremento++));
        insertar_final_nodo(&start_tareas_pendientes, crear_nodo(descripcion, rand()% (100 - 10 + 1) + 10, incremento++));
        mostrar_tareas(&start_tareas_pendientes);

        //Nodo *nodo_a_eliminar = quitar_nodo_x_palabra(&start_tareas_pendientes, "io");
        //eliminar_nodo(&nodo_a_eliminar);

        mostrar_tareas(&start_tareas_pendientes);
        printf("\nSi quiere salir presione '0' en caso negativo presione 1");
        scanf("%d", &condicion);
    } 
    while (condicion);

    return 0;
}

Nodo *crear_lista_vacia()
{
    return NULL;
}
Nodo *crear_nodo(char *descripcion, int duracion, int incremento)
{
    Nodo *new_nodo = (Nodo*)malloc(sizeof(Nodo));

    new_nodo->Tarea.TareaID = incremento;
    new_nodo->Tarea.Duracion = duracion;

    new_nodo->Tarea.Descripcion = malloc(strlen(descripcion)+1);
    strcpy(new_nodo->Tarea.Descripcion, descripcion);
    new_nodo->Siguiente = NULL;

    return new_nodo;
}
void insertar_inicio_nodo(Nodo **start, Nodo *nodo)
{
    nodo->Siguiente = *start;
    *start = nodo;
}
void insertar_final_nodo(Nodo **start, Nodo *nodo)
{
    if (*start == NULL) 
    {
        *start = nodo;
    } 
    else 
    {
        Nodo *aux = *start;
        while (aux->Siguiente) 
        {
            aux = aux->Siguiente; 
        }
        aux->Siguiente = nodo;
    }
}
Nodo *buscar_nodo(Nodo **start, char *buscado)
{
    Nodo *aux = *start;
    while (aux && strcmp(aux->Tarea.Descripcion, buscado) != 0)
    {
        aux = aux->Siguiente;
    }
    return aux;
}
Nodo *quitar_nodo_x_palabra(Nodo **star, char *buscado)
{
    Nodo **aux = star;

    while (*aux != NULL && strstr((*aux)->Tarea.Descripcion, buscado) == NULL)
    {
        aux = &(*aux)->Siguiente;
    }

    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }

    return NULL;
}
Nodo *quitar_nodo_x_id(Nodo **star, int id_buscado)
{
    Nodo **aux = star;

    while (*aux != NULL && (*aux)->Tarea.TareaID != id_buscado)
    {
        aux = &(*aux)->Siguiente;
    }

    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }

    return NULL;
}
void eliminar_nodo(Nodo **nodo)
{
    if(*nodo)
    {
        free((*nodo)->Tarea.Descripcion);
        free(*nodo);
        *nodo = NULL;
    }
}
void mostrar_tareas(Nodo ** start)
{
    Nodo *aux = *start;
    if (aux == NULL)
    {
        printf("\n NO hay tareas :/");
    }
    
    printf("\n\n--------------------LISTADO DE NODOS");
    while (aux)
    {
        printf("\n---Datos del nodo");
        printf("\n  Descripcion: %s", aux->Tarea.Descripcion);
        printf("\n  Duracion: %d", aux->Tarea.Duracion);
        printf("\n  Id de la Tarea: %d", aux->Tarea.TareaID);
        aux = aux->Siguiente;
    }
}