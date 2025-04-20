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

struct { 
    Tarea T;  
    Nodo *Siguiente;  
}typedef Nodo; 

Nodo *crear_lista_vacia();
Nodo *crear_nodo(Tarea);
void insertar_inicio_nodo(Nodo **, Nodo *);
void insertar_final_nodo(Nodo **, Nodo *);
Nodo *buscar_nodo(Nodo **, char *);
void eliminar_nodo(Nodo **);
void quitar_nodo(Nodo **, char *);

int main()
{
    Nodo *Star = crear_lista_vacia();
    
    return 0;
}

Nodo *crear_lista_vacia()
{
    return NULL;
}
Nodo *crear_nodo(Tarea T)
{
    Nodo *new_nodo = (Nodo*)malloc(sizeof(Nodo));

    printf("Ponga la descripcion de la tarea:");
    scanf("%s", &new_nodo->T.Descripcion);

    int duracion_tarea = rand()% (100 - 10 + 1) + 10;
    printf("Ponga la duracion de la tarea: %d", duracion_tarea);

    return new_nodo;
}
void insertar_inicio_nodo(Nodo **start, Nodo *nodo)
{
    nodo->Siguiente = *start;
    *start = nodo;
}
void insertar_final_nodo(Nodo **start, Nodo *nodo)
{
    Nodo *new_nodo = crear_nodo(nodo->T);
    Nodo *aux = start;

    while (aux->Siguiente)
    {
        aux = aux->Siguiente; 
    }

    aux->Siguiente = new_nodo;
}
Nodo *buscar_nodo(Nodo **start, char *buscado)
{
    Nodo *aux = start;
    while (aux && aux->T.Descripcion != buscado)
    {
        aux = aux->Siguiente;
    }
    return aux;
}
void eliminar_nodo(Nodo **nodo)
{
    if(nodo)
        free(nodo);
}
void quitar_nodo(Nodo **star, char *buscado)
{
    Nodo **aux = star;

    while (*aux != NULL && (*aux)->T.Descripcion != buscado)
    {
        aux = &(*aux)->Siguiente;
    }

    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        eliminar_nodo(temp);
    }
}