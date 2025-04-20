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

//----------------Fucion para liberar la memoria----------------------------

void liberarMemoria(Nodo *Cabecera);

int main()
{
    srand(time(NULL));
    Nodo *Cabecera = (Nodo *)malloc(sizeof(Nodo));

    Cabecera->Siguiente = NULL;

    cargaTareas(Cabecera);

    liberarMemoria(Cabecera);
    free(Cabecera);

    return 0;
}

void cargaTareas(Nodo *anterior)
{
    int r = 1;
    while (r == 1)
    {
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