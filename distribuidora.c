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

Nodo *crear_nodo(char *descripcion, int duracion, int incremento);
Nodo *crear_lista_vacia();

void insertar_inicio_nodo(Nodo **start, Nodo *nodo);
void insertar_final_nodo(Nodo **start, Nodo *nodo);

Nodo *quitar_nodo_x_palabra(Nodo **star, char *palabra_buscado);
Nodo *quitar_nodo_x_id(Nodo **star, int id_buscado);

void eliminar_nodo(Nodo **nodo);
void liberar_lista_tareas(Nodo **start);

void mostrar_tareas(Nodo ** start, int pendiente_o_realizada);

int main()
{
    srand(time(NULL));

    int incremento = 1000;
    char descripcion[150];
    int duracion = 0;
    int condicion = 1;
    int eleccion = 0;

    Nodo *start_tareas_pendientes = crear_lista_vacia();
    Nodo *start_tareas_realizadas = crear_lista_vacia();

    printf("-----------------------------------------\\\\\\\\|||BIENVENIDO A LA LISTA DE TAREAS|||////////-----------------------------------------");
    do
    {
        printf("\nIngrese la descripcion de la tarea: ");
        scanf(" %149[^\n]", descripcion);

        printf("\nIngrese la duracion de la tarea: ");
        scanf("%d", &duracion);

        insertar_final_nodo(&start_tareas_pendientes, crear_nodo(descripcion, duracion, incremento++));
        mostrar_tareas(&start_tareas_pendientes, 0);

        printf("\nTermino alguna tarea?\n           0 = NO\n           otra cosa = SI \nPonga su decision:");
        scanf("%d", &eleccion);

        while (eleccion != 0)
        {
            printf("++Que tarea termino, diga el id de la tarea que termino: ");
            scanf("%d", &eleccion);
            
            Nodo *nodo_mover = quitar_nodo_x_id(&start_tareas_pendientes, eleccion);

            if(nodo_mover != NULL)
            {
                insertar_final_nodo(&start_tareas_realizadas, nodo_mover);
                printf("\n--****---Se completo la tarea--****---");
            }
            else
            {
                printf("\nNo se encontro una tarea con ID %d.\n", eleccion);
            }   
            printf("\n\n++Quiere salir de la papelera de las tareas realizadas:\n           0 = SI\n           otra cosa = NO \nPonga su decision:");
            scanf("%d", &eleccion);
        }

        fflush(stdin);
        printf("\n\nSi quiere finalizar la carga presione '0' (en caso negativo presione cualquier tecla o numero y presione ENTER): ");
        scanf("%d", &condicion);
    } 
    while (condicion);
    mostrar_tareas(&start_tareas_pendientes, 0);
    printf("\n------------------");
    mostrar_tareas(&start_tareas_realizadas, 1);

    liberar_lista_tareas(&start_tareas_pendientes);
    liberar_lista_tareas(&start_tareas_realizadas);
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

Nodo *quitar_nodo_x_palabra(Nodo **star, char *palabra_buscado)
{
    Nodo **aux = star;

    while (*aux != NULL && strstr((*aux)->Tarea.Descripcion, palabra_buscado) == NULL)
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

void mostrar_tareas(Nodo ** start, int pendiente_o_realizada)
{
    Nodo *aux = *start;
    if (aux == NULL)
        printf("\n NO hay tareas :/");
    
    char *frase = (pendiente_o_realizada == 0) ? "PENDIENDTES" : "REALIZADAS";

    printf("\n\n---------------------------LISTADO DE TAREAS %s ", frase);
    while (aux)
    {
        printf("\n-----Datos de la Tarea:");
        printf("\n  Descripcion: %s", aux->Tarea.Descripcion);
        printf("\n  Duracion: %d", aux->Tarea.Duracion);
        printf("\n  Id de la Tarea: %d", aux->Tarea.TareaID);
        aux = aux->Siguiente;
    }
}
void liberar_lista_tareas(Nodo **start)
{
    Nodo *actual = *start;
    while (actual)
    {
        Nodo *temp = actual;
        actual = actual->Siguiente;
        
        free(temp->Tarea.Descripcion);
        free(temp);
    }

    *start = NULL;
}
