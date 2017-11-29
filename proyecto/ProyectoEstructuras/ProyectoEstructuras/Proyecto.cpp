#include <iostream>
#include <conio.h>
#include <string>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "qrcodegen.h"
#define Tam 11
#define vabTam 20
using namespace std;

//DEFINICION DE ESTRUCTURAS
struct Producto { //muestra produtos
	char  nombre[20];
	float precio = 0;
	float pUnidad = 0;
	int   stock = 0;
};

struct DatosCliente {
	char nombre[15];
	char apellido[15];
	int  cedula;
};

struct ListaDatosCliente
{
	DatosCliente datosCliente;
	float total = 0.0f;
	ListaDatosCliente *ant, *sig;
};

struct ListaProducto {
	Producto producto;
	ListaProducto *sig;
	ListaProducto *ant;
}listita;

struct Factura {
	ListaProducto compra;
	DatosCliente  datos;
	float total;
};



typedef ListaProducto *Lista;
typedef Factura *fact;
typedef ListaDatosCliente *ListaCliente;

//PROTOTIPOS DE FUNCIONES
int validaCedula();
void menuCompra(int opcion);
void compra(Lista &, Lista &, int);
void mostrarProductos(Lista);
void inicializarProductos(Lista &, char *, float, int, int);
int validarProducto(Lista &, char *, int);
void validarPrecio(Lista &, Lista);
void validarStock(Lista &);
void facturar(Lista &, fact &);
void ingresoDatos(fact &, Lista &);
void nuevaCompra(Lista &);
void gotoxy(int x, int y);
void barraCarga();
void seleccionarProducto(Lista lista);
int menuTeclas(Lista &);
void backgroundcolor(int color);
void guardar(ListaCliente &listaCliente, fact &factura, char *archivo, int contador);
bool esNumerico(string);
int validarIngresoNumeros(char *);
char *validarCaracteres(char *);
int menuDireccion();
void modificarListaCompra(Lista &, Lista &, Lista &);
void inicio();
void  generarQr(char *);
static void generarQrBasico(char dato1[]);
static void printQr(const uint8_t qrcode[]);

int main() {
	char nombreArchivo[12] = "factura.txt";
	int i = 1, j = 0, contador = 0;
	char opcion;
	char *lista[vabTam] = { "Sprite 200ml","Coca-Cola","ChocoWonka","Caramelos",
						"V220 bebida","Nueces 1kg","Pretzels","Chocolate",
						"Te Verde","Queso Fresco","Frutaris","Harina 1kg",
						"Helado 1L","Nescafe","Doritos","Powerade","Pilsener 1L",
						"Yogurt 1L","Colcafe","Atun Real"};
	float precios[vabTam] = { 1.00,1.00,2.30,2.4,2.90,3.00,2.00,1.50,1.50,2.30,0.25,2.00,2.00,1.75,1.00,2.30,2.4,2.90,3.00,2.00 };
	int stock[vabTam] = { 5,5,2,2,2,6,5,6,7,8,1,1,1,1,1,2,6,5,6,7 };
	Lista listaCompra, lisProductos, lisAuxiliar;
	ListaCliente listaCliente;
	fact factura;
	factura = new (struct Factura);
	listaCliente = new ListaDatosCliente();
	listaCompra = NULL;
	lisProductos = NULL;
	lisAuxiliar = NULL;
	listaCliente = NULL;
	//Inicializa los productos disponibles
	do {
		inicializarProductos(lisProductos, lista[j], precios[j], stock[j], j);
		inicializarProductos(lisAuxiliar, lista[j], precios[j], stock[j], j);
		j++;
	} while (j<vabTam);
	inicio();
	barraCarga();
	//Muestra el menu hasta que se elija "Salir".
	do {
		menuCompra(i);
		while ((opcion = getch()) != 13) {
			if (opcion == 72) {
				if (i == 1) {
					i = 6;
				}
				else {
					i--;
				}
			}
			if (opcion == 80) {
				if (i == 6) {
					i = 1;
				}
				else {
					i++;
				}
			}
			menuCompra(i);
		}
		switch (i) {
		case 1:
			if (lisProductos == NULL) {
				printf("No puede comprar mas productos");
				i = 6;
				exit(1);
			}
			else {
				int opc;
				system("cls");
				opc = menuTeclas(lisProductos);
				compra(listaCompra, lisProductos, opc);
				validarStock(lisProductos);
			}
			system("pause");
			break;
		case 2:
			system("cls");
			modificarListaCompra(listaCompra, lisProductos, lisAuxiliar);
			printf("\n\n");
			mostrarProductos(listaCompra);
			system("pause");
			break;
		case 3:
			system("cls");
			if (listaCompra != NULL) {
				contador++;
				printf("\n\n\tFACTURACION\n\n");
				ingresoDatos(factura, listaCompra);
				nuevaCompra(listaCompra);
				guardar(listaCliente, factura, nombreArchivo, contador);

				printf("\n\n    SU COMPRA HA FINALIZADO CON EXITO\!\n\n");
				system("pause");
				system("cls");
				barraCarga();
			}
			else {
				printf("\n\n\n\t*******************************************");
				printf("\n\n\t    No ha seleccionado ningun producto\n");
				printf("\n\n\t*******************************************\n");
				Sleep(700);
				//system("pause");
			}
			break;
		case 4:
			system("cls");
			printf("Abriendo archivo ayuda...\n");
			ShellExecute(NULL, L"open", L"C://Users/Administrador1/Desktop/proyecto/ManualdeUsuario.chm", NULL, NULL, SW_SHOWNORMAL);
			system("pause");
			break;
		case 5:
			system("cls");
			printf("SOBRE NOSOTROS\n\n");
			
		/*	char lista[300] = "";
			strcpy(lista, "https://scontent.fuio7-1.fna.fbcdn.net/v/t34.0-12/24203566_2162297370462812_645498074_n.jpg?oh=5ba57cf8ae52e28be8fcec13a863d333&oe=5A213C96");*/
			//generarQr(lista);

			system("pause");
			break;
		case 6:
			system("cls");
			printf("\n\n\t*******************************************\n");
			printf("\t\tGracias por usar este software!\n");
			printf("\n\t*******************************************\n");
			system("Start C:/Users/Administrador1/Desktop/proyecto/ProyectoEstructuras/ProyectoEstructuras/PDFg.jar");
			system("pause");//Sleep(2000);
			break;
		default:;
		}
	} while (i != 6);
	return 0;
}

void backgroundcolor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void inicio() {
	system("color 0A");
	gotoxy(0, 0);
	backgroundcolor(7);
	while (!kbhit()) {
		gotoxy(20, 28); printf("||");
		gotoxy(20, 29); printf("||");
		gotoxy(20, 30); printf("||");
		gotoxy(20, 31); printf("||");
		gotoxy(20, 32); printf("||");
		gotoxy(20, 33); printf("||");
		gotoxy(20, 34); printf("||");
		gotoxy(20, 35); printf("||");
		gotoxy(20, 36); printf("||");
		gotoxy(20, 37); printf("||");
		gotoxy(20, 38); printf("||");
		gotoxy(20, 39); printf("||");

		gotoxy(78, 28); printf("||");
		gotoxy(78, 29); printf("||");
		gotoxy(78, 30); printf("||");
		gotoxy(78, 31); printf("||");
		gotoxy(78, 32); printf("||");
		gotoxy(78, 33); printf("||");
		gotoxy(78, 34); printf("||");
		gotoxy(78, 35); printf("||");
		gotoxy(78, 36); printf("||");
		gotoxy(78, 37); printf("||");
		gotoxy(78, 38); printf("||");
		gotoxy(78, 39); printf("||");

		gotoxy(22, 26); printf("********************************************************");
		gotoxy(29, 28); printf("UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE");
		gotoxy(38, 30); printf("ESTRUCTURA DE DATOS");
		gotoxy(25, 32); printf("INTEGRANTES:");
		gotoxy(38, 34); printf("Carvajal Abigail");
		gotoxy(38, 35); printf("Corral Daniel");
		gotoxy(40, 37); printf("TEMA PROYECTO:");
		gotoxy(25, 39); printf("TIENDA VIRTUAL CON LISTAS DOBLEMENTE ENLAZADAS");
		gotoxy(22, 41); printf("********************************************************");
		gotoxy(25, 42); printf("\n");
		gotoxy(25, 43); printf("\n");
		gotoxy(25, 44); printf("\n");
		gotoxy(25, 45); printf("\n");
		gotoxy(25, 46); printf("\n");
		gotoxy(25, 47); printf("\n");
		gotoxy(25, 48); printf("\n");
		gotoxy(25, 49); printf("\n");
		gotoxy(25, 50); printf("\n");
		gotoxy(25, 51); printf("\n");
	}
	system("cls");
}


int menuTeclas(Lista &lista) {
	system("color 07");
	system("cls");
	Lista aux, aux1;
	aux = lista;
	aux1 = lista;
	int cont = 0;
	while (aux != NULL) {
		cont++;
		aux = aux->sig;
	}
	int men[50] = {};
	string menNombre[50] = {};
	float precio[50] = {};
	for (int i = 0; i<cont; i++) {
		men[i] = aux1->producto.stock;
		menNombre[i] = aux1->producto.nombre;
		precio[i] = aux1->producto.precio;
		aux1 = aux1->sig;
	}
	int cursor = 0;
	char tecla;
	for (;;) {
		system("cls");
		backgroundcolor(7);
		printf("\n\n\t    PRODUCTOS DISPONIBLES\n\n");
		printf(" Producto\t\t   Precio\t  Stock\n");
		printf("---------------------------------------------------------\n");
		for (int i = 0; i < cont; i++) {
			if (cursor == i) {
				backgroundcolor(160);
				printf(" %s\t\t   %.2f\t\t   %d\n", menNombre[i].c_str(), precio[i], men[i]);
				backgroundcolor(7);
			}
			else {
				backgroundcolor(7);
				printf(" %s\t\t   %.2f\t\t   %d\n", menNombre[i].c_str(), precio[i], men[i]);
			}
		}
		for (;;) {
			tecla = _getch();
			if (tecla == 80) {
				cursor++;
				if (cursor == cont)
				{
					cursor = 0;
				}
				break;
			}
			if (tecla == 72) {
				cursor--;
				if (cursor == -1)
				{
					cursor = cont;
				}
				break;
			}
			if (tecla == 13) {
				cursor += 1;
				/*Dependiendo de donde el cursor de enter entra en el switch*/
				return cursor;
			}
		}
	}while (tecla != 13);
	//printf("%d",cursor);
	system("pause");
	return cursor;
}

//Esta función permite realizar nuevas compras/vacia la lista de compras
void nuevaCompra(Lista &lista) {
	if (lista != NULL) {
		Lista punteroAuxiliar;
		while (lista != NULL) {
			punteroAuxiliar = lista->sig;
			delete(lista);
			lista = punteroAuxiliar;
		}
	}
}
//Ingresa datos de Usuario... aqui se mete generacion de QR
void ingresoDatos(fact &factura, Lista &lisProductos) {
	fact aux = new(struct Factura);
	char nombre[50], apellido[50];
	int cedula;
	//Nombre
	strcpy(nombre, validarCaracteres("Ingrese su Nombre:  "));
	strcpy(aux->datos.nombre, nombre);
	//Apellido
	strcpy(apellido, validarCaracteres("Ingrese su Apellido:  "));
	strcpy(aux->datos.apellido, apellido);
	//Cedula
	fflush(stdin);
	cedula = validaCedula();
	aux->datos.cedula = cedula;


	factura = aux;
	facturar(lisProductos, aux);
}

char *validarCaracteres(char *mensaje) {
	int i = 0;
	bool esCadena = false;
	char cadena[50];
	do
	{
		i = 0;
		fflush(stdin);
		printf("%s", mensaje);
		
		scanf("%s", &cadena);
		while (cadena[i] != NULL)
		{
			if (cadena[i] > 64 && cadena[i] < 91)
			{
				esCadena = true;
			}
			if (cadena[i] > 96 && cadena[i] < 123)
			{
				esCadena = true;
			}
			i++;
		}
		if (esCadena == false) printf("Ingreso no valido.\n");
	} while (esCadena == false);
	return cadena;
}

void facturar(Lista &lisProductos, fact &factura) {
	float total = 0;
	Lista aux = new(struct ListaProducto);
	aux = lisProductos;

	char espacio[2] = "\t";
	char fin[30] = "";

	while (aux != NULL) {
		aux->producto.pUnidad += aux->producto.precio;//*aux->producto.stock;
		total += aux->producto.precio;//*aux->producto.stock;
		aux = aux->sig;
	}
	factura->total = total;
	system("cls");
	printf("\n\t|**********************************************************|");
	printf("\n\t|\t\t\t  FACTURA                          |");
	printf("\n\t|    Usuario: %s %s                     ", factura->datos.nombre, factura->datos.apellido);
	printf("\n\t|    ID: %d                             ", factura->datos.cedula);
	printf("\n\t|--------------------------------------------------------- |\n");
	printf("\n\t|  Producto\t\t   Precio\t  Cantidad         |\n");
	printf("\t|--------------------------------------------------------- |\n");
	mostrarProductos(lisProductos);
	printf("\t  \t\t  Total = %.2f\n", factura->total);
	printf("\t|--------------------------------------------------------- |\n");

	strcat(fin , factura->datos.nombre);
	strcat(fin, espacio);
	strcat(fin, factura->datos.apellido);

	generarQr(fin);
}

//PARA INICIALIZAR LOS PRODUCTOS DISPONIBLES
void inicializarProductos(Lista &lisProductos, char *lista, float precios, int stock, int i) {
	if (lisProductos == NULL) {
		Lista aux, aux1;
		aux = new (struct ListaProducto);
		strcpy(aux->producto.nombre, lista);
		aux->producto.precio = precios;
		aux->producto.stock = stock;
		aux->sig = aux->ant = NULL;
		lisProductos = aux;
	}
	if (lisProductos != NULL) {
		Lista aux, aux1;
		aux = new (struct ListaProducto);
		strcpy(aux->producto.nombre, lista);
		aux->producto.precio = precios;
		aux->producto.stock = stock;
		aux1 = lisProductos;
		aux->sig = aux1;
		aux->ant = aux1->ant;
		aux1->ant = aux;
		lisProductos = aux;
	}

}

void mostrarProductos(Lista lista) {

	if (lista == NULL) {
		printf("No existen elementos en la lista. \n");
	}
	else {
		int i = 1;
		while (lista != NULL) {
			//SetConsoleTextAttribute ( salida, FOREGROUND_GREEN | BACKGROUND_BLUE );
			printf("\t| %s\t\t   %.2f\t\t   %d               |\n", lista->producto.nombre, lista->producto.precio, lista->producto.stock);
			//SetConsoleTextAttribute ( salida, coloresOriginales);
			printf("\t|--------------------------------------------------------- |\n");
			lista = lista->sig;
			i++;
		}
		printf("\n");
	}
}

//MENU CON CURSORES
void menuCompra(int opcion) {
	HANDLE salida = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD coloresOriginales;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(salida, &csbiInfo);
	coloresOriginales = csbiInfo.wAttributes;
	switch (opcion) {
	case 1:
		system("cls");
		printf("\t\t----------------------\n");
		printf("\t\t   CYBER-MARKET\n");
		printf("\t\t----------------------\n\n");
		SetConsoleTextAttribute(salida, FOREGROUND_GREEN | BACKGROUND_BLUE);
		printf("\t Iniciar compra                            \n");
		SetConsoleTextAttribute(salida, coloresOriginales);
		printf("\t Eliminar de lista de productos              \n");
		printf("\t Finalizar Compra             \n");
		printf("\t Ayuda\n");
		printf("\t Sobre Nosotros                                       \n");
		printf("\t Salir.                                                                 \n\n");
		break;
	case 2:
		system("cls");
		printf("\t\t----------------------\n");
		printf("\t\t   CYBER-MARKET\n");
		printf("\t\t----------------------\n\n");
		printf("\t Iniciar compra.                               \n");
		SetConsoleTextAttribute(salida, FOREGROUND_GREEN | BACKGROUND_BLUE);
		printf("\t Eliminar de lista de productos              \n");
		SetConsoleTextAttribute(salida, coloresOriginales);
		printf("\t Finalizar Compra             \n");
		printf("\t Ayuda\n");
		printf("\t Sobre Nosotros                                       \n");
		printf("\t Salir.                                                               \n\n");
		break;
	case 3:
		system("cls");
		printf("\t\t----------------------\n");
		printf("\t\t   CYBER-MARKET\n");
		printf("\t\t----------------------\n\n");
		printf("\t Iniciar compra                            \n");
		printf("\t Eliminar de lista de productos              \n");
		SetConsoleTextAttribute(salida, FOREGROUND_GREEN | BACKGROUND_BLUE);
		printf("\t Finalizar Compra              \n");
		SetConsoleTextAttribute(salida, coloresOriginales);
		printf("\t Ayuda\n");
		printf("\t Sobre Nosotros                                       \n");
		printf("\t Salir.                                                               \n\n");
		break;
	case 4:
		system("cls");
		printf("\t\t----------------------\n");
		printf("\t\t   CYBER-MARKET\n");
		printf("\t\t----------------------\n\n");
		printf("\t Iniciar compra                            \n");
		printf("\t Eliminar de lista de productos              \n");
		printf("\t Finalizar Compra              \n");
		SetConsoleTextAttribute(salida, FOREGROUND_GREEN | BACKGROUND_BLUE);
		printf("\t Ayuda\n");
		SetConsoleTextAttribute(salida, coloresOriginales);
		printf("\t Sobre Nosotros                                       \n");
		printf("\t Salir.                                                                \n\n");
		break;
	case 5:
		system("cls");
		printf("\t\t----------------------\n");
		printf("\t\t   CYBER-MARKET\n");
		printf("\t\t----------------------\n\n");
		printf("\t Iniciar compra                            \n");
		printf("\t Eliminar de lista de productos              \n");
		printf("\t Finalizar Compra               \n");
		printf("\t Ayuda\n");
		SetConsoleTextAttribute(salida, FOREGROUND_GREEN | BACKGROUND_BLUE);
		printf("\t  Sobre Nosotros                                       \n");
		SetConsoleTextAttribute(salida, coloresOriginales);
		printf("\t Salir.                                                                 \n\n");
		break;
	case 6:
		system("cls");
		printf("\t\t----------------------\n");
		printf("\t\t   CYBER-MARKET\n");
		printf("\t\t----------------------\n\n");
		printf("\t Iniciar compra                            \n");
		printf("\t Eliminar de lista de productos               \n");
		printf("\t Finalizar Compra               \n");
		printf("\t Ayuda\n");
		printf("\t Sobre Nosotros                                       \n");
		SetConsoleTextAttribute(salida, FOREGROUND_GREEN | BACKGROUND_BLUE);
		printf("\t Salir.                                                                 \n\n");
		SetConsoleTextAttribute(salida, coloresOriginales);
		break;
	default:;
	}
}

void compra(Lista &listaCompra, Lista &lisProductos, int opc) {
	printf("\n\n************************ \n");
	printf("\nEl producto escogido es: \n");
	int i = 0, cantidad;
	float total = 0;
	Lista auxprod = new (struct ListaProducto);
	auxprod = lisProductos;

	for (i = 0; i<opc - 1; i++)
	{
		auxprod = auxprod->sig;
	}
	printf("%s  \n", auxprod->producto.nombre);
	do {
		cantidad = validarIngresoNumeros("\nIngrese la cantidad del producto que desea:  ");
		if (cantidad > auxprod->producto.stock)
			printf("No disponemos de esa cantidad de productos.\n");
	} while (cantidad < 0 || cantidad > auxprod->producto.stock);
	auxprod->producto.stock = auxprod->producto.stock - cantidad;

	//Se añade el producto seleccionado a la lista de compras
	if (listaCompra != NULL) {
		Lista aux, aux1;
		aux = new (struct ListaProducto);
		if (validarProducto(listaCompra, auxprod->producto.nombre, cantidad) != 0) {
			strcpy(aux->producto.nombre, auxprod->producto.nombre);
			aux->producto.stock = cantidad;
			//aux->producto.precio = auxprod->producto.precio * cantidad;
			aux1 = listaCompra;
			aux->sig = aux1;
			aux->ant = aux1->ant;
			aux1->ant = aux;
			listaCompra = aux;
		}

	}
	else {
		Lista aux, aux1;
		aux = new (struct ListaProducto);
		strcpy(aux->producto.nombre, auxprod->producto.nombre);
		aux->producto.stock = cantidad;
		//aux->producto.precio = auxprod->producto.precio;
		aux->sig = aux->ant = NULL;
		listaCompra = aux;
	}
	validarPrecio(listaCompra, lisProductos);

	//Muestra la lista de compras antes de finalizar
	system("cls");
	printf("\n\tLa lista de compras es: \n\n");
	printf("\t Producto\t\t   Subtotal\t  Cantidad\n");
	printf("\t---------------------------------------------------------\n");
	mostrarProductos(listaCompra);

	auxprod = listaCompra;
	while (auxprod != NULL)
	{
		total = total + auxprod->producto.precio;
		auxprod = auxprod->sig;
	}
	printf("\t\t\t   Total = %.2f\n\n", total);
}

int validarProducto(Lista &lista, char *nombreproducto, int cantidad) {
	int band = 1;
	Lista aux = new(ListaProducto);
	aux = lista;
	while (aux != NULL)
	{
		band = strcmp(nombreproducto, aux->producto.nombre);
		if (band == 0)
		{
			aux->producto.stock = aux->producto.stock + cantidad;
			break;
		}
		aux = aux->sig;
	}
	return (band);
}

void barraCarga() {
	printf("\n \n\t\tPresione cualquier tecla para iniciar compra \n");
	getch();
	system("cls");
	int x, y, i, z, a;
	gotoxy(25, 10);
	printf("CARGANDO");
	for (i = 10; i<50; i++) {
		gotoxy(i, 13);
		printf("%c", 177);
		gotoxy(36, 10);
		printf("%d %c", i * 2, '%');
		for (x = 50; x<70; x++) {
			for (y = 1; y<70; y++) {
				gotoxy(y, 24);
			}
		}
	}
}

void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void validarStock(Lista &lista) {
	Lista aux = new(ListaProducto);
	aux = lista;
	if (aux != NULL) {
		while (aux != NULL)
		{
			if (aux->producto.stock == 0)
			{
				if (aux->ant == NULL&&aux->sig == NULL) {
					lista = NULL;
					break;
				}

				if (aux->ant == NULL)
				{
					aux->sig->ant = NULL;
					lista = aux->sig;
				}
				if (aux->sig == NULL)
				{
					aux->ant->sig = NULL;
				}
				if (aux->ant != NULL && aux->sig != NULL)
				{
					aux->ant->sig = aux->sig;
					aux->sig->ant = aux->ant;
				}
			}
			aux = aux->sig;
		}
	}
}

void guardar(ListaCliente &listacliente, fact &factura, char *archivo, int contador) {
	FILE *ptr;
	char nombre[30] = {""};

	ptr = fopen(archivo, "a"); //REALIZO LA APERTURA DEL ARCHIVO
	if (ptr == NULL)
	{
		printf("ERROR.\n");
	}
	else
	{
		strcpy(nombre, factura->datos.nombre);
		//fputs(nombre,ptr);
		fprintf(ptr, "Nombre: %s  Apellido: %s Cedula: %d \n", nombre, factura->datos.apellido, factura->datos.cedula);
		fclose(ptr);
	}
}

//funcion para determinar el precio de la lisa de compras
void validarPrecio(Lista &listaCompra, Lista lisProductos) {
	Lista aux = new(ListaProducto);
	int band = 1;
	aux = listaCompra;
	while (aux != NULL)
	{
		while (lisProductos != NULL)
		{
			band = strcmp(lisProductos->producto.nombre, aux->producto.nombre);
			if (band == 0)
			{
				aux->producto.precio = lisProductos->producto.precio * aux->producto.stock;

			}
			lisProductos = lisProductos->sig;
		}
		aux = aux->sig;
	}
}

int validarIngresoNumeros(char *mensaje) {
	string linea;
	int numero;
	bool repite = true;

	do
	{
		//fflush(stdin);
		printf("%s", mensaje);
		fflush(stdin);
		getline(cin, linea);

		if (esNumerico(linea))
		{
			repite = false;
		}
		else
		{
			printf("Ingreso no valido.\n");
		}
	} while (repite);

	numero = atoi(linea.c_str());
	//cin.get();
	return numero;
}

bool esNumerico(string linea) {
	bool b = true;
	int longitud = linea.size();

	if (longitud == 0) //caundo el usuario pulsa enter
	{
		b = false;
	}
	else if (longitud == 1 && !isdigit(linea[0]))
	{
		b = false;
	}
	else
	{
		int i;
		if (linea[0] == '+' || linea[0] == '-')
			i = 1;
		else i = 0;

		while (i<longitud)
		{
			if (!isdigit(linea[i]))
			{
				b = false;
				break;
			}
			i++;
		}
	}
	return b;
}

int menuDireccion() {
	int cursor = 0;
	char tecla;
	char *opc[2] = { "SI","NO" };
	for (;;) {
		system("cls");
		printf("\n\n********************************************************\n");
		printf("\n\nEsta seguro que desea eliminar el producto seleccionado?\n\n");
		backgroundcolor(7);
		for (int i = 0; i < 2; i++) {
			if (cursor == i) {
				backgroundcolor(160);
				printf("     %s\t",opc[i]);
				backgroundcolor(7);
			}
			else {
				backgroundcolor(7);
				printf("     %s\t",opc[i] );
			}
		}
		for (;;) {
			tecla = _getch();
			if (tecla == 75) {
				cursor++;
				if (cursor == 2)
				{
					cursor = 0;
				}
				break;
			}
			if (tecla == 77) {
				cursor--;
				if (cursor == -1)
				{
					
					cursor = 2;
				}
				break;
			}
			if (tecla == 13) {
				cursor += 1;
				//printf("cursor = %d", cursor);
				/*Dependiendo de donde el cursor de enter entra en el switch*/
				return cursor;
			}
		}
	}while (tecla != 13);
	return cursor;
}

void modificarListaCompra(Lista &listaCompra, Lista &lisProductos, Lista &listAuxiliar)
{
	int opc, op;
	Lista aux2 = new (struct ListaProducto);
	Lista auxprod = new (struct ListaProducto);
	auxprod = listaCompra;
	aux2 = listAuxiliar;
	if (listaCompra == NULL)
	{
		printf("No existen productos disponibles.\n");
	}
	else {
		printf("       ELIMINAR DE LA LISTA DE COMPRAS   \n\n");
		printf("Escoja que producto desea modificar: \n");
		opc = menuTeclas(listaCompra);
		op = menuDireccion();

		//Elimnar el producto de la lsita de compras y aumentar en la lista de productos
		if (op == 1)
		{
			for (int i = 0; i<opc - 1; i++)
				auxprod = auxprod->sig;

			//Se añade el producto selecionado a la lista de productos
			if (lisProductos != NULL) {
				Lista aux, aux1;
				aux = new (struct ListaProducto);
				if (validarProducto(lisProductos, auxprod->producto.nombre, auxprod->producto.stock) != 0) {
					strcpy(aux->producto.nombre, auxprod->producto.nombre);
					aux->producto.stock = auxprod->producto.stock;
					aux->producto.precio = auxprod->producto.precio / aux->producto.stock;
					aux1 = lisProductos;
					aux->sig = aux1;
					aux->ant = aux1->ant;
					aux1->ant = aux;
					lisProductos = aux;
				}
			}
			else {
				Lista aux, aux1;
				aux = new (struct ListaProducto);
				strcpy(aux->producto.nombre, auxprod->producto.nombre);
				aux->producto.stock = auxprod->producto.stock;
				aux->producto.precio = auxprod->producto.precio / aux->producto.stock;
				aux->sig = aux->ant = NULL;
				lisProductos = aux;
			}

			//Se elimina el producto de la lista de compras
			if (auxprod->sig == NULL && auxprod->ant == NULL)
			{
				//printf("lista nula");
				nuevaCompra(listaCompra);
			}
			else if (auxprod->ant == NULL)
			{
				//printf("1");
				auxprod->sig->ant = NULL;
				listaCompra = auxprod->sig;
			}
			else if (auxprod->sig == NULL)
			{
				//printf("2");
				auxprod->ant->sig = NULL;
			}
			else if (auxprod->ant != NULL && auxprod->sig != NULL)
			{
				//printf("3");
				auxprod->ant->sig = auxprod->sig;
				auxprod->sig->ant = auxprod->ant;
			}
		}

		//Devolver una cantidad de productos
		if (op == 2)
		{
			printf("no");
			system("PAUSE");
		}
	}
}

int validaCedula() {
	//inicializacion de variables
	int A[Tam], num, j, i, coc, pares, impares, digito, suma, sumtotal, res;
	char opc;
	int comprueba = 0, cedula;
	do
	{
		i = 10;
		pares = 0;
		suma = 0;
		impares = 0;
		digito = 0;
		sumtotal = 0;
		num = validarIngresoNumeros("\nIngrese el numero de cedula:\t");
		//scanf("%d",&num);
		while ((num <= 1000000000) || (num >= 3000000000))
		{
			printf("Numero incorrecto. Ingrese cedula de nuevo:\t");
			scanf("%d", &num);
		}
		//Asignación de cada numero a una posición
		cedula = num;
		do
		{
			coc = num / 10;
			A[i] = num % 10;
			i--;
			num = coc;
		} while (coc != 0);
		pares += (A[2] + A[4] + A[6] + A[8]);
		//printf("pares %d\n",pares);
		for (j = 1; j<10; j++)
		{
			A[j] *= 2;
			if (j % 2 == 0)
				A[j] /= 2;
			else
			{
				if (A[j]>9)
					suma += A[j] - 9;
				else
					digito += A[j];
			}
		}
		impares = suma + digito;
		//printf("impares %d\n",impares);
		sumtotal += impares + pares;
		res = 10 - (sumtotal % 10);
		A[1] *= 10;
		A[0] = (A[1] / 2 + A[2]);
		//printf("%d",A[0]);
		if (res == 10)
			res = 0;
		if (res == A[10] && A[0] <= 24) {
			printf("\n\t\tLa cedula es valida\n\n");
			comprueba = 1;
		}
		else {
			printf("\t\tLa cedula es invalida\n\n");
			comprueba = 0;
		}

	} while ((comprueba == 0));

	return cedula;


}

void generarQrBasico(char dato1[]) {
	char *dato = dato1;  // User-supplied text
	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level

													   // Make and print the QR Code symbol
	uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(dato, tempBuffer, qrcode, errCorLvl,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (ok)
		printQr(qrcode);
}

static void printQr(const uint8_t qrcode[]) {
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "\333\333" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
}

static void generarQr(char *mensaje)
{
	printf("GENERADOR DE QR\n");
	generarQrBasico(mensaje);
	system("pause");
}