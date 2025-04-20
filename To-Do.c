#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define tama 100

struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
};
typedef struct Tarea Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
};
typedef struct Nodo Nodo;

//--------------------Declaracion de Funciones-------------------------

void cargaTareas(Nodo *anterior);

void tareaRealizada(Nodo *realizada, Nodo *pendiente);

void listarTareas(Nodo *pendiente, Nodo *realizadas);

void buscarTareas(Nodo *pendiente, Nodo *realizadas);

void liberarMemoria(Nodo *Cabecera);

//---------------------Main---------------------------------

int main()
{
    srand(time(NULL));
    Nodo *Cabecera = (Nodo *)malloc(sizeof(Nodo));   // Puntero a la lista de tareas pendientes
    Nodo *realizadas = (Nodo *)malloc(sizeof(Nodo)); // Puntero a la lista de tareas realizadas

    Cabecera->Siguiente = NULL;
    realizadas->Siguiente = NULL;

    cargaTareas(Cabecera);

    tareaRealizada(realizadas, Cabecera);

    listarTareas(Cabecera, realizadas);

    buscarTareas(Cabecera, realizadas);

    // Libero memoria

    liberarMemoria(Cabecera);
    liberarMemoria(realizadas);
    free(realizadas);
    free(Cabecera);

    return 0;
}

//----------------Fucion para Cargar Tareas----------------------------

void cargaTareas(Nodo *anterior)
{
    int r = 1;
    Nodo *aux = anterior;
    while (r == 1)
    {
        printf("\nIngrese la Tarea pendiente:\n");
        Nodo *pNodo = (Nodo *)malloc(sizeof(Nodo));
        char *descripcion = (char *)malloc(tama * sizeof(char));
        pNodo->T.Descripcion = descripcion;
        if (aux->Siguiente == NULL)
        {
            pNodo->T.TareaID = 1000;
        }
        else
        {
            pNodo->T.TareaID = anterior->T.TareaID + 1;
        }

        pNodo->Siguiente = anterior->Siguiente;
        anterior->Siguiente = pNodo;
        anterior = pNodo;

        printf("\nIngrese descripcion de la tarea: ");
        gets(pNodo->T.Descripcion);

        do
        {
            printf("\nIngrese la duracion (Entre 10 a 100): ");
            scanf("%d", &pNodo->T.Duracion);
            fflush(stdin);

        } while (pNodo->T.Duracion > 100 || pNodo->T.Duracion < 10);

        printf("\nDesea ingresar otra tarea? (1 = SI, 0 = NO)\n");
        scanf("%d", &r);
        fflush(stdin);
    }
}

//----------------Fucion para liberar la memoria----------------------------

void liberarMemoria(Nodo *Cabecera)
{
    while (Cabecera->Siguiente != NULL)
    {
        Nodo *aux;
        aux = Cabecera->Siguiente;
        Cabecera->Siguiente = Cabecera->Siguiente->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}

//----------------Fucion para marcar tareas como realizadas----------------------------

void tareaRealizada(Nodo *realizada, Nodo *pendiente)
{
    int r = 1, id;
    Nodo *aux1, *aux2;

    do
    {
        aux2 = NULL;

        if (pendiente->Siguiente == NULL)
        {
            printf("\nNo hay tareas pendientes\n");
            break;
        }

        printf("\nIngrese el ID de la tarea que esta realizada: ");
        scanf("%d", &id);
        aux1 = pendiente;

        while (aux1->Siguiente != NULL)
        {
            if (aux1->Siguiente->T.TareaID == id)
            {
                aux2 = aux1->Siguiente;
                aux1->Siguiente = aux2->Siguiente;
                aux2->Siguiente = realizada->Siguiente;
                realizada->Siguiente = aux2;
                break;
            }
            aux1 = aux1->Siguiente;
        }
        if (aux2 == NULL)
        {
            printf("\nNo se encontro ninguna tarea con esa ID\n");
        }

        printf("\nDesea marcar como realizada otra tarea? (1=SI, 2=NO)\n");
        scanf("%d", &r);

    } while (r == 1);
}

//----------------Fucion para listar tareas----------------------------

void listarTareas(Nodo *pendiente, Nodo *realizadas)
{
    Nodo *aux = pendiente->Siguiente;

    printf("\n----------------------------TAREAS PENDIENTES----------------------------");

    if (aux == NULL)
    {
        printf("\n\tNo hay tareas pendientes.\n");
    }

    while (aux != NULL)
    {
        printf("\n\t\tTarea %d", aux->T.TareaID);
        printf("\n\t\tDescripcion: %s", aux->T.Descripcion);
        printf("\n\t\tDuracion: %d horas", aux->T.Duracion);
        printf("\n--------------------------------------------");
        aux = aux->Siguiente;
    }

    aux = realizadas->Siguiente;

    printf("\n----------------------------TAREAS REALIZADAS----------------------------");

    if (aux == NULL)
    {
        printf("\n\tNo hay tareas realizadas.\n");
    }

    while (aux != NULL)
    {
        printf("\n\t\tTarea %d", aux->T.TareaID);
        printf("\n\t\tDescripcion: %s", aux->T.Descripcion);
        printf("\n\t\tDuracion: %d horas", aux->T.Duracion);
        printf("\n--------------------------------------------");
        aux = aux->Siguiente;
    }
}

//----------------Fucion para buscar tareas----------------------------

void buscarTareas(Nodo *pendiente, Nodo *realizadas)
{
    int r;
    do
    {
        Nodo *aux = pendiente->Siguiente;
        int id, eleccion, encontrada = 0;
        char palabra[20];

        printf("\nDesea buscar por ID(1) o palabra clave(2)?\n");
        scanf("%d", &eleccion);

        if (eleccion == 1)
        {
            fflush(stdin);
            printf("\nIngrese la ID de la tarea que desea buscar: ");
            scanf("%d", &id);
        }
        else
        {
            fflush(stdin);
            printf("\nIngrese la palabra clave: ");
            gets(palabra);
        }

        for (int i = 0; i < 2; i++)
        {
            while (aux != NULL)
            {
                if (aux->T.TareaID == id || strstr(aux->T.Descripcion, palabra) != NULL)
                {
                    if (i == 0)
                    {
                        printf("\n\t---------La Tarea esta pendiente--------");
                    }
                    else
                    {
                        printf("\n\t---------La Tarea esta realizada--------");
                    }
                    printf("\n\t\tTarea %d", aux->T.TareaID);
                    printf("\n\t\tDescripcion: %s", aux->T.Descripcion);
                    printf("\n\t\tDuracion: %d horas", aux->T.Duracion);
                    printf("\n--------------------------------------------");
                    encontrada = 1;
                    break;
                }
                aux = aux->Siguiente;
            }
            aux = realizadas->Siguiente;
            if (encontrada == 1)
            {
                break;
            }
        }
        if (encontrada == 0)
        {
            printf("\nTarea no encontrada");
        }
        printf("\nDesea buscar otra tarea? (SI = 1, NO = 2)");
        scanf("%d", &r);
    } while (r == 1);
}
