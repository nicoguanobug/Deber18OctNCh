/*
 * ISWZ1102 - PROGRAMACION 1
 * Taller 3 - Gestion de calificaciones
 * Autor: Nicolas
 *
 * Programa que gestiona las calificaciones de 5 estudiantes en 3 asignaturas
 * (Matematicas, Lenguaje y Programacion). Permite registrar estudiantes con
 * sus notas, mostrar promedios, mostrar la calificacion mas alta y mas baja
 * por materia y ver los estudiantes aprobados/reprobados.
 */
#include <stdio.h>
#include <string.h>

#define MAX_EST 5   // Numero maximo de estudiantes que maneja el programa

// Prototipos de las funciones de validacion de entradas
float validarFlotanteRango(float min, float max);
int leerEntero(void);



int main (int argc, char *argv[]) {

    // nombres: nombre de cada estudiante | matSimp: abreviatura de cada materia
    // aprep: texto Aprobado/Reprobado de las 3 materias de un estudiante
    char nombres[MAX_EST][20], matSimp[3][20]={"Mat","Len","Prog"}, aprep[3][20];
    // m1, m2, m3: notas de Matematicas, Lenguaje y Programacion por estudiante
    // maxminC: minimo (columna 0) y maximo (columna 1) de cada materia
    float m1[MAX_EST], m2[MAX_EST], m3[MAX_EST], maxminC[3][2];

    int opc, opc1;      // opc: opcion del menu | opc1: 1 = continuar, 2 = salir
    int contE=0;        // cantidad de estudiantes registrados
    // promE: promedio de un estudiante | promM: promedio de cada materia
    float promE=0 , promM[3]={0}, min, max;

    do
    {
        // Menu principal
        printf("Seleccione una opcion\n");
        printf("1.Registro estudiante (incluye ingreso de calificaciones)\n");
        printf("2.Mostrar promedios (por materia y estudiante)\n");
        printf("3.Mostrar calificaciones mas alta y mas baja (por materia)\n");
        printf("4.Estudiantes aprobados/reprobados\n");
        printf("5.Salir\n");
        printf(">> ");

        // Se valida que la opcion sea un numero (si no lo es, devuelve -1)
        opc = leerEntero();

        switch (opc)
        {
        case 1:
            // Opcion 1: registrar un estudiante y sus 3 calificaciones
            // No se permite registrar mas estudiantes que el tamano de los arreglos
            if (contE >= MAX_EST){
                printf("Error: ya se registraron los %d estudiantes permitidos\n", MAX_EST);
                break;
            }

            printf("Ingrese los datos del estudiante %d:\n",contE);
            printf("Nombre: ");
            scanf("%19s",nombres[contE]);       // maximo 19 caracteres + '\0'
            while((getchar())!='\n');           // limpia el buffer de entrada

            // Las tres notas deben estar en el rango de 0 a 10
            printf("Matematicas: ");
            m1[contE] = validarFlotanteRango(0,10);

            printf("Lenguaje: ");
            m2[contE] = validarFlotanteRango(0,10);

            printf("Programacion: ");
            m3[contE] = validarFlotanteRango(0,10);

            contE++;
            break;
        case 2:
            // Opcion 2: promedio por estudiante y por materia
            // Sin estudiantes no se puede promediar (evita dividir para 0)
            if (contE == 0){
                printf("No hay estudiantes registrados\n");
                break;
            }

            // Se reinician los acumuladores para no sumar consultas anteriores
            promM[0]=0;
            promM[1]=0;
            promM[2]=0;

            printf("#\t\tNombre\t\tMat\t\tLen\t\tProg\t\tPromE\n");
            for (int i = 0; i < contE; i++)
            {
                promE = (m1[i] + m2[i] + m3[i])/3;   // promedio del estudiante i
                promM[0]+=m1[i];                     // se acumula la nota de cada materia
                promM[1]+=m2[i];
                promM[2]+=m3[i];
                printf("%d\t\t%s\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",i,nombres[i],m1[i],m2[i],m3[i],promE);
            }
            // Promedio de cada materia = suma de notas / cantidad de estudiantes
            promM[0]/=contE;
            promM[1]/=contE;
            promM[2]/=contE;
            printf("\tPromediosM\t\t%.2f\t\t%.2f\t\t%.2f\n",promM[0],promM[1],promM[2]);
            break;

        case 3:
            // Opcion 3: calificacion mas baja y mas alta de cada materia
            // Se inicia min en 10 y max en 0 (limites del rango de notas)

            // Matematicas
            min = 10;
            max = 0;
            for (int i = 0; i < contE; i++)
            {
                if (m1[i]<=min){
                    min = m1[i];
                }
                if (m1[i]>max){
                    max = m1[i];
                }
            }
            maxminC[0][0]=min;
            maxminC[0][1]=max;

            // Lenguaje
            min = 10;
            max = 0;
            for (int i = 0; i < contE; i++)
            {
                if (m2[i]<=min){
                    min = m2[i];
                }
                if (m2[i]>max){
                    max = m2[i];
                }
            }
            maxminC[1][0]=min;
            maxminC[1][1]=max;

            // Programacion
            min = 10;
            max = 0;
            for (int i = 0; i < contE; i++)
            {
                if (m3[i]<=min){
                    min = m3[i];
                }
                if (m3[i]>max){
                    max = m3[i];
                }
            }
            maxminC[2][0]=min;
            maxminC[2][1]=max;

            printf("Mats\t\tMin\t\tMax\n");

            for (int i = 0; i < 3; i++)
            {
                printf("%s\t\t%.2f\t\t%.2f\n",matSimp[i],maxminC[i][0],maxminC[i][1]);
            }

            break;
        case 4:
            // Opcion 4: estado de cada estudiante en cada materia (aprueba con 6 o mas)
            printf("#\t\tNombre\t\tMatematicas\t\tLenguaje\t\tProgramacion\n");
            for (int i = 0; i < contE; i++)
            {
                if (m1[i]>=6){
                    strcpy(aprep[0],"Aprobado");
                }else{
                    strcpy(aprep[0],"Reprobado");
                }

                if (m2[i]>=6){
                    strcpy(aprep[1],"Aprobado");
                }else{
                    strcpy(aprep[1],"Reprobado");
                }

                if (m3[i]>=6){
                    strcpy(aprep[2],"Aprobado");
                }else{
                    strcpy(aprep[2],"Reprobado");
                }

                printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\n",i,nombres[i],aprep[0],aprep[1],aprep[2]);
            }
            break;
        case 5:
            // Opcion 5: termina el programa
            return 0;

        default:
            // Opcion fuera del menu o que no es un numero
            printf("Error: opcion invalida, ingrese un numero del 1 al 5\n");
            break;
        }

        // Se pregunta si desea continuar; solo se acepta 1 o 2
        do
        {
            printf("Desea seleccionar otra opcion 1.Si/2.No: ");
            opc1 = leerEntero();
            if (opc1 != 1 && opc1 != 2)
            {
                printf("Error: ingrese 1 o 2\n");
            }
        } while (opc1 != 1 && opc1 != 2);
    } while (opc1==1);




    return 0;
}


// Lee un numero flotante y lo repite hasta que sea numerico y este entre min y max
float validarFlotanteRango(float min, float max){
    int val = 0;
    float aux = 0;
    do{
        val = scanf("%f",&aux);
        while((getchar())!='\n');   // limpia el buffer de entrada
        if (aux < min || aux > max || val != 1)
        {
            printf("Error: Valor ingresado incorrecto\n");
        }
    }while(aux < min || aux > max || val != 1);
    return aux;
}

// Lee un numero entero; si lo ingresado no es un numero devuelve -1
int leerEntero(void){
    int val = 0;
    int aux = 0;
    val = scanf("%d",&aux);
    while((getchar())!='\n');       // limpia el buffer de entrada
    if (val != 1)
    {
        return -1;
    }
    return aux;
}
