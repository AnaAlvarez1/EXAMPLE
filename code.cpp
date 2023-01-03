/*ARCHIVO BINARIO DE NÚMEROS REALES

*Ejercicio 1:
Una empresa dedicada a las ventas de productos por mayor registra en un archivo binario solo los totales de ventas
que se van realizando durante el día. Las cargas de los datos se realizan en cualquier momento, por lo que el archivo
no debe perder la información con una nueva carga.

El dueño de la empresa solicita, al centro de cómputos, le confeccione un sistema qué por medio de un menú se pueda realizar
 lo siguiente:
 
"	Permitir registrar en cualquier momento los montos totales de venta.
"	Saber cuál es la mayor venta guardada y la cantidad de veces que se registró el mismo monto.
"	Visualizar los datos en pantallas, donde cada fila deberá tener 10 datos separados por un guion y visualizar 6 dígitos por cada valor. 
En caso de que la cantidad sea menor a 6 dígitos rellenar con ceros a la izquierda hasta completar los 6 dígitos.
"	Saber cuál es el monto total de las ventas realizadas en el momento de la consulta.
"	Permitir al final del día borrar el archivo.

NOTA:

    Utilizar para todas las opciones del menú funciones. Cada función deberá recibir cómo uno sus parámetros el archivo.
    El archivo debe ser abierto al inicio del programa y cerrarlo al final del programa.*/
    
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>


int Menu(); //funcion menu
void registrarVentas(FILE *archi, int fecha[3]); //funcion registro de ventas del dia
void ventaMayor(FILE *archi,int cantidad, float ventamayor, int fecha[3]); //funcion busqueda de la venta mayor y cantidad de veces registrada en el día
void mostrarVentas(FILE *archi, int fecha[3]);
float montoTotal(FILE *archi);
void borrarArchivo(FILE *archi);




main()
{
	setlocale(LC_CTYPE, "Spanish"); //llamada funcion caracteres especiales español
	FILE *archivo; //variable de tipo puntero

	int cantidad,ultimaPosicion;
	float ventamayor,total=0.0;
	int fecha[3],opc=0;
	float ventas;



	archivo = fopen("ventasDelDia.dat","r+b"); //apertura de archivo que existe (lectura + escritura)
	
	    if(archivo == NULL)
	    {
	    	archivo = fopen("ventasDelDia.dat","w+b"); //crea archivo, ya que no existe (y lo escribe) o  si existe, lo abre lo borra y lo deja vacio.
		
		    if(archivo == NULL)
		    {
			    printf("\a*Error! No se puede crear el archivo");
			    system("PAUSE");
			    exit(1);
	    	}
	    }
	    
	
	

	
	int opcion=0;
	
	do
	{
		
		system("cls");
		opcion=Menu();
		system("cls");
		
		
		switch(opcion)
		{
			case 1: {
				       printf("\n\t\t\tVENTAS DEL DÍA\n");
				       
				       registrarVentas(archivo, fecha);
				       
				       break;
			        }
			case 2: {
				       printf("\n\t\t\tMAYOR VENTA REGISTRADA Y CANTIDAD DE VECES INGRESADAS\n");
				       
				       
				       ventaMayor(archivo,cantidad, ventamayor, fecha);
				       
				       
				
				       break;
			        }
			case 3: {
				       printf("\n\t\t\tDATOS REGISTRADOS");
				       
				       mostrarVentas(archivo, fecha);
				       
				       break;
			        }
			case 4: {
				       printf("\n\t\t\tMONTO TOTAL\n");
				       
				       total = montoTotal(archivo);
				       
				       printf("\n El monto total es:$ %.2f",total);
				
				       break;
			        }
			case 5: {
				       printf("\n\a*¿Desea Borrar archivo?");
				       printf("\nsi => 1 | no => 2\n");
				       opc=getch();
				       
				       if(opc==1)
				       {
				       	    remove("ventasDelDia.dat");
					   }
					   if(opc==2)
					   {
					   	system("PAUSE");
					   	    exit(1);
					   }
				       break;
			        }
			case 0: {
				       printf("\nCerrando programa...");
				       
				
				       break;
			        }
			default: {
                        printf("\n\n\n");
                        printf("\t\t_________________________________");
				        printf("\n\t\t\a|###|ERROR!Opcion incorrecta|###|\n");
				        printf("\t\t¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
				
				        break;
			         }
		};
		
		printf("\n\n");
		system("pause");
		
	
	}while(opcion!=0);
	
	
	
}

int Menu()
{
	system("cls");
	int selet=0;
	
	printf("########################################################################################################################\n");
	printf("\t\t\t\t\tEMPRESA XXXX  S.A");
	printf("\n\n########################################################################################################################\n");
	printf("|*|MENÚ");
	printf("\n|1|Ventas del día");
	printf("\n|2|Mayor venta registrada y cantidad de veces ingresada");
	printf("\n|3|Datos registrados");
	printf("\n|4|Monto total registrado hasta el momento");
	printf("\n|5|Borrar archivo");
	printf("\n|0|Salír");
	printf("\n########################################################################################################################\n");
	printf("\t\t\t\t\t");
	printf("\n*Su opcion: ");
	scanf("%d",&selet);

	return (selet);
}

void registrarVentas(FILE *archi,int fecha[3])
{


	float ventas;
	int opc=1;
	bool borrado;

	printf("\n*Por favor ingrese el día(dd), mes(mm) y año(aaaa) de la venta:\n");
	printf("\n\tDía: ");
	fflush(stdin); //limpia el buffer
	scanf("%d", &fecha[0]);
	printf("\n\tMes:");
	fflush(stdin);
	scanf("%d", &fecha[1]);
	printf("\n\tAño: ");
	fflush(stdin);
	scanf("%d", &fecha[2]);
	fflush(stdin);
	
	
	do
	{
		printf("\n\n*Por favor ingrese el monto de la venta: $ ");
		fflush(stdin);
		scanf("%f", &ventas);
		
		fwrite(&ventas,sizeof(float),1,archi); //funcion para ecribir en el archivo
		
		printf("\n*¿Desea agregar otra venta?");
		printf("\n s/n");
		printf("\n");
		opc=getch();
		
	}while(opc != 'n');
	
	fclose(archi);


	
}

void ventaMayor(FILE *archi,int cantidad, float ventamayor, int fecha[3])
{
    archi = fopen("ventasDelDia.dat","r+b");
    
	float ventas;
	
	fread(&ventas, sizeof(float), 1, archi);//funcion para leer el archivo

	ventamayor = 0.0;

	cantidad = 0;
	float comparacion=0.0;

	while(!feof(archi))
	{
		if(ventas > ventamayor )
		{
			ventamayor = ventas;
		}

		fread(&ventas, sizeof(float), 1, archi);//funcion para leer el archivo
	}
	
	rewind(archi); //revobino ubicando el puntero al inicio
	fread(&ventas, sizeof(float), 1, archi);//funcion para leer el archivo
	while(!feof(archi))
	{
		if(ventamayor==ventas)
		{
			cantidad++;
		}
		fread(&ventas, sizeof(float), 1, archi);
	}
	
	printf("#####################################################################################\n");
	printf("\nFecha de ingreso de datos: %d/%d/%d \n", fecha[0], fecha[1], fecha[2]);
	
	printf("\n La venta mayor fue $ %.2f , ingresada %d ves/veces en el día. ", ventamayor, cantidad);
	printf("\n####################################################################################\n");
	

	fclose(archi);

	
}

void mostrarVentas(FILE *archi, int fecha[3])
{
	archi = fopen("ventasDelDia.dat","rb");
	
	float ventas;
	int i=0;

	fread(&ventas,sizeof(float),1,archi);
	
	printf("\n\t\tVENTAS %d/%d/%d \n",fecha[0],fecha[1],fecha[2]);

	while(!feof(archi))
	{
		printf("\n|%d|Ventas: %f",i+1,ventas);
	
	    fread(&ventas,sizeof(float),1,archi);
	}
	
	fclose(archi);

}

float montoTotal(FILE *archi)
{
	archi = fopen("ventasDelDia.dat","r+b");
	
	
	float ventas,suma=0.0;
	
	fread(&ventas,sizeof(float),1,archi);
	
	while(!feof(archi))
	{
		suma = suma + ventas;
		fread(&ventas,sizeof(float),1,archi);
		
	}
	return suma;
	
	fclose(archi);

}


