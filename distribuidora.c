#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//pruebaaaa
#define MAX_DESCRIPCION 150

typedef struct Tarea
{
    int TareaId;
    char *Descripcion;
    int Duracion;
}Tarea;

typedef struct Tnodo
{
    Tarea Task;
    struct Tnodo *Siguiente;
}Tnodo;

void menu_principal_ui();
void ingreso_datos(char *descripcion, int *duracion);
void mostrar_nodo(Tnodo *nodo, const char *origen);
void mostrar_lista(Tnodo *start);

Tnodo *crear_lista_vacia();
Tnodo *crear_nodo(char *descripcion, int duracion, int tarea_id);
Tnodo *busqueda_x_id(Tnodo *start, int tarea_id);
Tnodo *busqueda_x_palabra(Tnodo *start, char *descripcion);
Tnodo *quitar_nodo_x_id(Tnodo **start, int tarea_id);
Tnodo *quitar_nodo_x_palabra(Tnodo **start, char *descripcion);

void insertar_nodo_inicio(Tnodo **start, Tnodo *nuevo_nodo);
void insertar_nodo_final(Tnodo **start, Tnodo *nuevo_nodo);
void liberar_lista(Tnodo *start); 

int main()
{
    char descripcion[MAX_DESCRIPCION];
    int duracion; int tarea_id = 1000; int eleccion; 
    
    Tnodo *start_tareas_pendientes = crear_lista_vacia();
    Tnodo *start_tareas_realizadas = crear_lista_vacia();

    do
    {
        menu_principal_ui();
        printf("\nPonga su eleccion: ");
        scanf("%d", &eleccion);

        switch (eleccion)
        {
            case 1:
                ingreso_datos(descripcion, &duracion);
                insertar_nodo_inicio(&start_tareas_pendientes, crear_nodo(descripcion, duracion, tarea_id++));
                break;

            case 2:
                printf("\nPonga el Id de su tarea pendiente que termino:");
                scanf("%d", &tarea_id);
                insertar_nodo_final(&start_tareas_realizadas, quitar_nodo_x_id(&start_tareas_pendientes, tarea_id));
                break;

            case 3:
                mostrar_lista(start_tareas_pendientes);
                break;
                
            case 4:
                mostrar_lista(start_tareas_realizadas);
                break;

            case 5:
                printf("\n--------Tareas Pendientes");
                mostrar_lista(start_tareas_pendientes);
                printf("\n--------Tareas Realizadas");
                mostrar_lista(start_tareas_realizadas);
                break;

            case 6:
                printf("\nIngrese ID de tarea a buscar:");
                scanf("%d", &tarea_id);
                mostrar_nodo(busqueda_x_id(start_tareas_pendientes, tarea_id), "PENDIENTES");
                mostrar_nodo(busqueda_x_id(start_tareas_realizadas, tarea_id), "REALIZADAS");
                break;
                
            case 7:
                printf("\nIngrese palabra a buscar:");
                scanf("%s", descripcion);
                mostrar_nodo(busqueda_x_palabra(start_tareas_pendientes, descripcion), "PENDIENTES");
                mostrar_nodo(busqueda_x_palabra(start_tareas_realizadas, descripcion), "REALIZADAS");
                break;

            default:
                break;
        }
    } while (eleccion);
    
    liberar_lista(start_tareas_pendientes); 
    liberar_lista(start_tareas_realizadas);

    return 0;
}

Tnodo *crear_lista_vacia()
{
    return NULL;
}
Tnodo *crear_nodo(char *descripcion, int duracion, int tarea_id)
{
    Tnodo *nuevo_nodo = (Tnodo*)malloc(sizeof(Tnodo));
    
    nuevo_nodo->Task.Descripcion = malloc(strlen(descripcion)+1); 
    strcpy(nuevo_nodo->Task.Descripcion, descripcion);
    
    nuevo_nodo->Task.TareaId = tarea_id;
    nuevo_nodo->Task.Duracion = duracion;
    nuevo_nodo->Siguiente = NULL;
    
    return nuevo_nodo;
}
Tnodo *busqueda_x_id(Tnodo *start, int tarea_id)
{
    Tnodo *aux = start;
    while (aux && aux->Task.TareaId != tarea_id)
    {
        aux = aux->Siguiente;
    }
    return aux;
}
Tnodo *busqueda_x_palabra(Tnodo *start, char *descripcion)
{
    Tnodo *aux = start;
    while (aux)
    {
        if (strstr(aux->Task.Descripcion, descripcion) != NULL)
            return aux;
        aux = aux->Siguiente;
    }
    return NULL;
}
Tnodo *quitar_nodo_x_id(Tnodo **start, int tarea_id)
{
    Tnodo **aux = start;

    while (*aux && (*aux)->Task.TareaId != tarea_id)
    {
        aux = &(*aux)->Siguiente;
    }

    if(*aux)
    {
        Tnodo *quitado = *aux;
        *aux = (*aux)->Siguiente;
        quitado->Siguiente = NULL;

        return quitado;  
    }

    return NULL;
}
Tnodo *quitar_nodo_x_palabra(Tnodo **start, char *descripcion)
{
    Tnodo **aux = start;

    while (*aux && strstr((*aux)->Task.Descripcion, descripcion) == NULL)
    {
        aux = &(*aux)->Siguiente;
    }
    
    if (*aux)
    {
        Tnodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }
    
    return NULL;
}

void menu_principal_ui()
{
    printf("\n----------------------------BIENVENIDO A LA LISTA DE TAREAS-------------------------------------------------");
    printf("\n[0]--Salir");
    printf("\n[1]--Carga de tareas pendientes");
    printf("\n[2]--Mover tareas pendientes a tareas realizadas");
    printf("\n[3]--Mostrar tareas pendientes");
    printf("\n[4]--Mostrar tareas realizadas");
    printf("\n[5]--Mostrar tareas pendientes y tareas realizadas");
    printf("\n[6]--Buscador de tareas por id");
    printf("\n[7]--Buscador de tareas por palabra");
}
void insertar_nodo_inicio(Tnodo **start, Tnodo *nuevo_nodo)
{
    nuevo_nodo->Siguiente = *start;
    *start = nuevo_nodo;
}
void insertar_nodo_final(Tnodo **start, Tnodo *nuevo_nodo)
{
    if (*start == NULL)
    {
        // Si la lista está vacía, el nuevo nodo es el primer nodo
        *start = nuevo_nodo;
    }
    else
    {
        Tnodo *aux = *start;
        while (aux->Siguiente)
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = nuevo_nodo;
    }
}
void ingreso_datos(char *descripcion, int *duracion)
{
    getchar(); // consumir el salto de línea pendiente
    printf("\n\nIngrese la descripcion de la Tarea: ");
    fgets(descripcion, MAX_DESCRIPCION, stdin);
    descripcion[strcspn(descripcion, "\n")] = 0; // eliminar salto de línea

    printf("Ingrese la duracion de la Tarea: ");
    scanf("%d", duracion);
}
void mostrar_lista(Tnodo *start)
{
    if (start == NULL)
    { 
        printf("\nLa lista está vacía");
        return;
    }
    Tnodo *aux = start;
    
    while (aux)
    {
        printf("\n\nDescripcion de Tarea: %s", aux->Task.Descripcion);
        printf("\nDuracion de Tarea: %d", aux->Task.Duracion);
        printf("\nId de Tarea: %d", aux->Task.TareaId);

        aux = aux->Siguiente;
    }
}
void mostrar_nodo(Tnodo *nodo, const char *origen) 
{
    if (nodo == NULL) return;
    
    printf("\n--- Tarea encontrada en %s ---\n", origen);
    printf("  Descripcion: %s\n", nodo->Task.Descripcion);
    printf("  Duracion: %d\n", nodo->Task.Duracion);
    printf("  ID: %d\n", nodo->Task.TareaId);
}
void liberar_lista(Tnodo *start)
{
    Tnodo *aux;
    while (start)
    {
        aux = start;
        start = start->Siguiente;
        free(aux->Task.Descripcion);
        free(aux);
    }
}