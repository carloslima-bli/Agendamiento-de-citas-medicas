#include <stdio.h>
#include <string.h>
#include "funciones.h"




void registrar_cita(Cita citas[], int *num_citas, Doctor doctores[], int num_doctores);
void listar_citas(Cita citas[], int num_citas);
void buscar_cita(Cita citas[], int num_citas);
void eliminar_cita(Cita citas[], int *num_citas);
void guardar_citas(Cita citas[], int num_citas);
void cargar_citas(Cita citas[], int *num_citas);
int buscar_indice(Cita citas[], int num_citas, char codigo[]);
int horario_ocupado(Cita citas[], int num_citas, char fecha[], char hora[]);
void generar_codigo(Cita citas[], int num_citas, char letra, char codigo[]);

int main()
{
    Cita citas[100];
    int num_citas = 0;
    int opcion;

    Doctor doctores[5] = {
        {"Dra. Torres", "Medicina General", 'M'},
        {"Dr. Garcia", "Pediatria", 'P'},
        {"Dra. Sanchez", "Cardiologia", 'C'},
        {"Dr. Martinez", "Dermatologia", 'D'},
        {"Dra. Lopez", "Ginecologia", 'G'}
    };

    cargar_citas(citas, &num_citas);

    do
    {
        
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
                registrar_cita(citas, &num_citas, doctores, 5);
                break;
            case 2:
                listar_citas(citas, num_citas);
                break;
            case 3:
                buscar_cita(citas, num_citas);
                break;
            case 4:
                eliminar_cita(citas, &num_citas);
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
