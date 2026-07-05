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
void cargar_citas(Cita citas[], int *num_citas);

int main()
{
    int opcion;
    Cita citas[100];
    int num_citas = 0;

    Doctor doctores[5] = {
        {"Dra. Torres", "Medicina General", 'M'},
        {"Dr. Garcia", "Pediatria", 'P'},
        {"Dra. Sanchez", "Cardiologia", 'C'},
        {"Dr. Martinez", "Dermatologia", 'D'},
        {"Dra. Lopez", "Ginecologia", 'G'}
    };

    cargar_citas(citas, &num_citas);

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
void cargar_citas(Cita citas[], int *num_citas)
{
    FILE *archivo;
    char linea[200];
    char *token;
 
    archivo = fopen("citas.csv", "r");
 
    if(archivo == NULL)
    {
        printf("No existe el archivo citas.csv todavia\n");
        return;
    }
 
    fgets(linea, sizeof(linea), archivo); /* saltar la cabecera */
 
    *num_citas = 0;
    while(fgets(linea, sizeof(linea), archivo) != NULL)
    {
        token = strtok(linea, ",");
        strcpy(citas[*num_citas].codigo, token);
 
        token = strtok(NULL, ",");
        strcpy(citas[*num_citas].paciente, token);
 
        token = strtok(NULL, ",");
        strcpy(citas[*num_citas].especialidad, token);
 
        token = strtok(NULL, ",");
        strcpy(citas[*num_citas].fecha, token);
 
        token = strtok(NULL, ",");
        strcpy(citas[*num_citas].hora, token);
 
        token = strtok(NULL, "\n");
        strcpy(citas[*num_citas].medico, token);
 
        (*num_citas)++;
    }
 
    fclose(archivo);
    printf("Se cargaron %d cita(s) desde citas.csv\n", *num_citas);
}