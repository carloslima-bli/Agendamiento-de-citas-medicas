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

void registrar_cita(Cita citas[], int *num_citas, Doctor doctores[], int num_doctores);
void listar_citas(Cita citas[], int num_citas);
void buscar_cita(Cita citas[], int num_citas);
void eliminar_cita(Cita citas[], int *num_citas);
void guardar_citas(Cita citas[], int num_citas);
void cargar_citas(Cita citas[], int *num_citas);
int buscar_indice(Cita citas[], int num_citas, char codigo[]);
int horario_ocupado(Cita citas[], int num_citas, char fecha[], char hora[]);
void generar_codigo(Cita citas[], int num_citas, char letra, char codigo[]);