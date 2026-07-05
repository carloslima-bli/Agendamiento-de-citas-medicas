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

void mostrar_menu();
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
        mostrar_menu();
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

void mostrar_menu()
{
    printf("\n=== Sistema de citas medicas ===\n\n");
    printf("1. Registrar cita\n");
    printf("2. Listar citas\n");
    printf("3. Buscar cita\n");
    printf("4. Eliminar cita\n");
    printf("5. Salir\n\n");
    printf("Ingrese una opcion: ");
}

/* Busca una cita por su codigo y devuelve la posicion en el arreglo.
   Si no la encuentra devuelve -1 */
int buscar_indice(Cita citas[], int num_citas, char codigo[])
{
    int i;
    for(i = 0; i < num_citas; i++)
    {
        if(strcmp(citas[i].codigo, codigo) == 0)
        {
            return i;
        }
    }
    return -1;
}

/* Devuelve 1 si ya hay una cita con esa fecha y hora, 0 si no */
int horario_ocupado(Cita citas[], int num_citas, char fecha[], char hora[])
{
    int i;
    for(i = 0; i < num_citas; i++)
    {
        if(strcmp(citas[i].fecha, fecha) == 0 && strcmp(citas[i].hora, hora) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/* Genera un codigo automatico para la especialidad, por ejemplo P001, P002, M001...
   Busca el numero mas alto ya usado con esa letra y le suma 1 */
void generar_codigo(Cita citas[], int num_citas, char letra, char codigo[])
{
    int i, numero, numero_mayor;

    numero_mayor = 0;

    for(i = 0; i < num_citas; i++)
    {
        if(citas[i].codigo[0] == letra)
        {
            sscanf(citas[i].codigo + 1, "%d", &numero);
            if(numero > numero_mayor)
            {
                numero_mayor = numero;
            }
        }
    }

    numero_mayor = numero_mayor + 1;
    sprintf(codigo, "%c%03d", letra, numero_mayor);
}

void registrar_cita(Cita citas[], int *num_citas, Doctor doctores[], int num_doctores)
{
    int dia, mes, anio, hora, minutos;
    int doctor_seleccionado, i;
    char codigo[16];
    char fecha[11];
    char hora_texto[6];

    printf("\nIngrese el nombre del paciente: ");
    scanf(" %49[^\n]", citas[*num_citas].paciente);

    printf("Ingrese el dia de la cita (1-31): ");
    scanf("%d", &dia);
    while(dia < 1 || dia > 31)
    {
        printf("Dia no valido, debe estar entre 1 y 31\n");
        printf("Ingrese el dia de la cita (1-31): ");
        scanf("%d", &dia);
    }

    printf("Ingrese el mes de la cita (1-12): ");
    scanf("%d", &mes);
    while(mes < 1 || mes > 12)
    {
        printf("Mes no valido, debe estar entre 1 y 12\n");
        printf("Ingrese el mes de la cita (1-12): ");
        scanf("%d", &mes);
    }

    