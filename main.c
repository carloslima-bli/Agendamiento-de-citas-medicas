#include <stdio.h>
#include <string.h>

typedef struct
{
    char nombre[50];
    char especialidad[30];
    char letra;
} Doctor;
 
typedef struct
{
    char codigo[16];
    char paciente[50];
    char especialidad[30];
    char fecha[11];
    char hora[6];
    char medico[50];
} Cita;

int main()
{
    int opcion;
    Cita citas[100];
    int num_citas = 0;

    do{
     printf("\n Sistema de citas medicas \n\n");
    printf("1. Registrar cita\n");
    printf("2. Listar citas\n");
    printf("3. Buscar cita\n");
    printf("4. Eliminar cita\n");
    printf("5. Salir\n\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);

    switch(opcion)
        {
            case 1:
                //registar cita
                break;
            case 2:
                //lista de citas
                break;
            case 3:
                //buscar cita
                break;
            case 4:
                //eliminar cita
                break;
            case 5:
                printf("Gracias por usar el sistema de citas medicas\n");
                break;
            default:
                printf("Opcion no valida\n");
        }
 
    } while(opcion != 5);

    return 0;
}