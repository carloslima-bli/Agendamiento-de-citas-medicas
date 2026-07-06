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
printf("Ingrese el anio de la cita: ");
    scanf("%d", &anio);
    while(anio < 2024 || anio > 2100)
    {
        printf("Anio no valido, debe estar entre 2024 y 2100\n");
        printf("Ingrese el anio de la cita: ");
        scanf("%d", &anio);
    }

    sprintf(fecha, "%02d/%02d/%04d", dia, mes, anio);

    printf("Ingrese la hora de la cita (9-20, horario de 9am a 8pm): ");
    scanf("%d", &hora);
    while(hora < 9 || hora > 20)
    {
        printf("Hora no valida, el consultorio atiende de 9am a 8pm (9-20)\n");
        printf("Ingrese la hora de la cita (9-20): ");
        scanf("%d", &hora);
    }

    printf("Ingrese los minutos de la cita (0-59): ");
    scanf("%d", &minutos);
    while(minutos < 0 || minutos > 59)
    {
        printf("Minutos no validos, deben estar entre 0 y 59\n");
        printf("Ingrese los minutos de la cita (0-59): ");
        scanf("%d", &minutos);
    }

    /* si la hora es exactamente las 8pm, solo se permite la hora en punto */
    if(hora == 20 && minutos > 0)
    {
        printf("El ultimo horario disponible es a las 8:00pm en punto\n");
        return;
    }

    sprintf(hora_texto, "%02d:%02d", hora, minutos);

    if(horario_ocupado(citas, *num_citas, fecha, hora_texto))
    {
        printf("Ya existe una cita en esa fecha y hora\n");
        return;
    }

    printf("\nLista de doctores:\n");
    for(i = 0; i < num_doctores; i++)
    {
        printf("%d. %s - %s\n", i + 1, doctores[i].nombre, doctores[i].especialidad);
    }

    printf("Seleccione el numero del doctor: ");
    scanf("%d", &doctor_seleccionado);

    while(doctor_seleccionado < 1 || doctor_seleccionado > num_doctores)
    {
        printf("Doctor no valido\n");
        printf("Seleccione el numero del doctor: ");
        scanf("%d", &doctor_seleccionado);
    }

    generar_codigo(citas, *num_citas, doctores[doctor_seleccionado - 1].letra, codigo);

    strcpy(citas[*num_citas].codigo, codigo);
    strcpy(citas[*num_citas].fecha, fecha);
    strcpy(citas[*num_citas].hora, hora_texto);
    strcpy(citas[*num_citas].medico, doctores[doctor_seleccionado - 1].nombre);
    strcpy(citas[*num_citas].especialidad, doctores[doctor_seleccionado - 1].especialidad);

    (*num_citas)++;

    printf("Cita registrada correctamente con el codigo %s\n", codigo);

    guardar_citas(citas, *num_citas);
}
    void listar_citas(Cita citas[], int num_citas)
{
    int i;

    if(num_citas == 0)
    {
        printf("\nNo hay citas registradas\n");
        return;
    }

    printf("\n%-8s %-20s %-18s %-12s %-6s %-20s\n",
           "Codigo", "Paciente", "Especialidad", "Fecha", "Hora", "Medico");

    for(i = 0; i < num_citas; i++)
    {
        printf("%-8s %-20s %-18s %-12s %-6s %-20s\n",
               citas[i].codigo, citas[i].paciente, citas[i].especialidad,
               citas[i].fecha, citas[i].hora, citas[i].medico);
    }
}

void buscar_cita(Cita citas[], int num_citas)
{
    char texto[50];
    int i, encontrado = 0;

    printf("\nIngrese el codigo o parte del nombre del paciente: ");
    scanf(" %49[^\n]", texto);

    for(i = 0; i < num_citas; i++)
    {
        if(strcmp(citas[i].codigo, texto) == 0 || strstr(citas[i].paciente, texto) != NULL)
        {
            printf("%s %s %s %s %s %s\n",
                   citas[i].codigo, citas[i].paciente, citas[i].especialidad,
                   citas[i].fecha, citas[i].hora, citas[i].medico);
            encontrado = 1;
        }
    }

    if(encontrado == 0)
    {
        printf("No se encontraron coincidencias\n");
    }
}

void eliminar_cita(Cita citas[], int *num_citas)
{
    char codigo[16];
    char confirmar;
    int indice, i;

    printf("\nIngrese el codigo de la cita a eliminar: ");
    scanf("%15s", codigo);

    indice = buscar_indice(citas, *num_citas, codigo);

    if(indice == -1)
    {
        printf("No existe una cita con ese codigo\n");
        return;
    }

    printf("Esta seguro que desea eliminarla? (s/n): ");
    scanf(" %c", &confirmar);

    if(confirmar != 's' && confirmar != 'S')
    {
        printf("Eliminacion cancelada\n");
        return;
    }

    for(i = indice; i < *num_citas - 1; i++)
    {
        citas[i] = citas[i + 1];
    }

    (*num_citas)--;
    printf("Cita eliminada correctamente\n");

    guardar_citas(citas, *num_citas);
}

void guardar_citas(Cita citas[], int num_citas)
{
    FILE *archivo;
    int i;

    archivo = fopen("citas.csv", "w");

    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo citas.csv\n");
        return;
    }

    fprintf(archivo, "codigo_cita,nombre_paciente,especialidad,fecha,hora,medico\n");

    for(i = 0; i < num_citas; i++)
    {
        fprintf(archivo, "%s,%s,%s,%s,%s,%s\n",
                citas[i].codigo, citas[i].paciente, citas[i].especialidad,
                citas[i].fecha, citas[i].hora, citas[i].medico);
    }

    fclose(archivo);
    printf("Datos guardados en citas.csv\n");
}

void cargar_citas(Cita citas[], int *num_citas)
{
    FILE *archivo;
    char linea[200];
    char *token;
    int lineas_leidas = 0;
    int lineas_ignoradas = 0;

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