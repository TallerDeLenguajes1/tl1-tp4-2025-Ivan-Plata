#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tama 100

struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} typedef Tarea;

struct Nodo
{
    Tarea T;
    Nodo *Siguiente;
} typedef Nodo;

void cargaTareas(Nodo *anterior);

void tareaRealizada(Nodo *realizada, Nodo *pendiente);

//----------------Fucion para liberar la memoria----------------------------

void liberarMemoria(Nodo *Cabecera);

int main()
{
    srand(time(NULL));
    Nodo *Cabecera = (Nodo *)malloc(sizeof(Nodo));   // Puntero a la lista de tareas pendientes
    Nodo *realizadas = (Nodo *)malloc(sizeof(Nodo)); // Puntero a la lista de tareas realizadas

    Cabecera->Siguiente = NULL;
    realizadas->Siguiente = NULL;

    cargaTareas(Cabecera);

    liberarMemoria(Cabecera);
    liberarMemoria(realizadas);
    free(realizadas);
    free(Cabecera);

    return 0;
}

void cargaTareas(Nodo *anterior)
{
    int r = 1;
    while (r == 1)
    {
        printf("\nIngrese la Tarea pendiente:\n");
        Nodo *pNodo = (Nodo *)malloc(sizeof(Nodo)), *aux;
        char *descripcion = (char *)malloc(tama * sizeof(char));
        pNodo->T.Descripcion = descripcion;
        if (anterior->Siguiente == NULL)
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

void tareaRealizada(Nodo *realizada, Nodo *pendiente)
{
    int r = 1, id;
    Nodo *aux1, *aux2 = NULL;

    do
    {

        if (pendiente->Siguiente == NULL)
        {
            printf("\nNo hay tareas pendientes\n");
            break;
        }

        printf("\nIngrese el ID de la tarea que está realizada: ");
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