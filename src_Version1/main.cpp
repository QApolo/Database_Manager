#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
//definimos string como tipo *char
//typedef char* String;
//-----prototipos

	//protipos generales
string new_string();
string concatenar(string a,string b);
int cadenaIdentica(char *a,char *b);
//prototipos de base
void crearDB();
void mostrarDB();
int existeBase(string base);
void usarDB(string sel);
void eliminarDB(string dbsel);

//prototipos de tabla
void crearTabla(string sel);

//prototipo de menu
void menu();
//----inicio de funciones----


ifstream fin;
ofstream fout;

int main()
{
	menu();	
return 0;
}
//-----------------funciones de uso general

string concatenar(string a,string b)
{
	
return a+b;
}

int cadenaIdentica(string a,string b)
{
	int i;
	if((a).length()!=b.length())return 0;
	for(i=0;i<a.length();i++)
		if(a[i]!=b[i])return 0;
return 1;
}

string new_string()
{
	string a;
	cin >> a;
	return a;
}

//---------------------------funciones DB

void crearDB()
{

	string cad="",base_leida = "";
	
	int cant=0;
	//pf=fopen("DB/cant_db.txt","r");
	fin.open("DB/cant_db.txt");
	//fscanf(pf,"%d",&cant);
	fin >> cant;
	fin.close();

	printf("Ingrese el nombre de la db\n");
	cin >> cad;

	int i,existe=0;
	fin.open("DB/nombre_bases.txt");
	//pf=fopen("DB/nombre_bases.txt","r");
	for(i=0;i<cant;i++)
	{	
		//fscanf(pf,"%s",base_leida);
		fin >> base_leida;
		if(cadenaIdentica(base_leida,cad))
		{
			printf("-------La base de datos ya existe-----\n");
			existe=1;
			break;
		}
	}
	if(existe)return;
	system(concatenar("mkdir DB/",cad).c_str());
				//pf=fopen(concatenar("DB/",concatenar(cad,".txt")),"w");

	//pf.open("DB/nombre_bases.txt");
	fout.open("DB/nombre_bases.txt");
	//pf=fopen("DB/nombre_bases.txt","a");
	fout << cad <<endl;
	//fprintf(pf, "%s\n",cad);
	fout.close();

	//pf=fopen("DB/cant_db.txt","w");
	fout.open("DB/cant_db.txt");
	fout << ++cant;
	//fprintf(pf,"%d",++cant);
	fout.close();
	printf("-------------Base de datos creada satisfactoriamente---------\n");
}

void mostrarDB()
{
	
	int i,cant=0;
	string dbnames = "";

	//pf=fopen("DB/cant_db.txt","r");
	fin.open("DB/cant_db.txt");
	//fscanf(pf,"%d",&cant);
	fin >> cant;
	fin.close();
	printf("%d\n",cant );
	if(cant==0)
	{
		printf("No hay db creadas:\n");
		return;
	}
	//fopen("DB/nombre_bases.txt","r");
	fin.open("DB/nombre_bases.txt",ifstream::in);
	printf("--------------------------------------\n");
	for(i=0;i<cant;i++)
	{
		fin >> dbnames;
		//fscanf(pf,"%s",dbnames);
		//printf("%d-%s\n",i+1,dbnames);
	}
	printf("---------------%d Bases creadas---------------\n", cant);
	fin.close();

}

int existeBase(string base)
{
	int i,cd;
	//FILE *pf=fopen(concatenar("DB/",concatenar("cant_db",".txt")),"r");

	fin.open("DB/cant_db.txt");
	//fscanf(pf,"%d",&cd);
	fin >> cd;

	fin.close();


	string base_ext = "";
	//pf=fopen("DB/nombre_bases.txt","r");
	fin.open("DB/nombre_bases.txt");
	for(i=0;i<cd;i++)
	{
		fin >> base_ext; //fscanf(pf,"%s",base_ext);
		if(cadenaIdentica(base_ext,base))
			return 1;
	}
	fin.close();
return 0;
}
void usarDB(string sel)
{
	int op;
	if(!existeBase(sel))
	{
		printf("----------No existeBase la base de datos-------\n");
		return;
	}
	do
	{
		printf("1)Crear tabla\n2)Modificar tabla\n3)Eliminar tabla\n");
		scanf("%d",&op);

		switch(op)
		{
			case 1:
				crearTabla(sel);
			break;

			case 2:
			break;

			case 3:
			break;
		}
	}while(op!=5);
}

void eliminarDB(string dbsel)
{
	if(!existeBase(dbsel))
	{
		printf("---------No existe base con ese nombre----------\n");
		return;
	}
	int cant=0,i,k=0;
	string nbase="",bases[100];
	//FILE *pf=fopen("DB/cant_db.txt","r");
	fin.open("DB/cant_db.txt");
	fin >> cant; //fscanf(pf,"%d",&cant);
	fin.close();
	char a;
	fin.open("DB/nombre_bases.txt");
	//pf=fopen("DB/nombre_bases.txt","r");
	for(i=0;i<cant;i++)
	{
		 //fscanf(pf,"%s",nbase);
		if(!cadenaIdentica(nbase,dbsel))
			bases[k++]=nbase;
	}
	fin.close();
	fout.open("DB/nombre_bases.txt");
	//pf=fopen("DB/nombre_bases.txt","w");
	for(i=0;i<k;i++)
	{
		fout << bases[i]<<endl;
		//fprintf(pf, "%s\n",bases[i] );
		printf("%s\n",bases[i].c_str() );
	}
	fout.close();
	fout.open("DB/cant_db.txt");
	//pf=fopen("DB/cant_db.txt","w");
	fout <<k<<endl; //fprintf(pf, "%d\n",k );
	fout.close();

	system(("rm -fr DB/"+dbsel).c_str());
	printf("%s\n",("rm -fr DB/"+dbsel).c_str() );
	printf("---------La base de datos se ha eliminado satisfactoriamente-------\n");


}

//-------------------------funciones tabla
void crearTabla(string sel)
{
	int cant=0,cant_c=0;

	printf("Ingrese el nombre de la tabla\n");
	string tabla;
	cin >> tabla;
	system(("mkdir DB/"+sel+"/"+tabla).c_str());
	//----------cant tablas no tiene extension
	//pf=fopen(concatenar("DB/",concatenar(sel, concatenar("/cant_tablas","")) ).c_str(),"a+");
	string aux ="DB/"+sel+"/cant_tablas"; 
	fin.open(aux.c_str());

	fin >> cant; //fscanf(pf,"%d",&cant);
	fin.close();

	fout.open(("DB/"+sel+"/cant_tablas").c_str());

	fout << ++cant;	//fprintf(pf, "%d", ++cant);
	fout.close();

	//pf=fopen(concatenar("DB/",concatenar(sel, concatenar("/nombre_tablas",".txt")) ),"a");
	fout.open(("DB/"+sel+"/nombre_tablas.txt").c_str());

	fout << tabla <<endl;//fprintf(pf,	"%s\n", tabla);
	fout.close();
	string ruta=concatenar("DB/",concatenar(sel,concatenar("/",tabla)));

	printf("Ingrese la cantidad de campos de la tabla:\n");
	scanf("%d",&cant_c);
	fout.open((ruta+"/cant_campos.txt").c_str()); //pf=fopen(concatenar(ruta,"/cant_campos.txt"),"w");
	fout << cant_c; //fprintf(pf, "%d", cant_c);
	fout.close();


	fout.open((ruta + "/campos.txt").c_str()); //pf=fopen(concatenar(ruta,"/campos.txt") ,"a");
	int i,t;
	string nom;
	for(i=0;i<cant_c;i++)
	{
		printf("1) int\n2)float\n3) string\n");
		printf("Ingrese el nombre y tipo del campo %d\n",i+1 );
		cin >> nom;
		scanf("%d",&t);
	 	 //fprintf(pf, "%s %d\n",nom, t);
	}
	printf("------tabla creada correctamente-----\n");
	fout.close();
}

//--------------------funcion general
void menu()
{
	int op;
	do
	{
		printf("1)Crear db\n2)mostrar db\n3)usar\n4)eliminar db\n5)Salir\n");
		scanf("%d",&op);
 		string db;
		switch(op)
		{
			case 1:
				crearDB();
			break;

			case 2:
				mostrarDB();
			break;

			case 3:
				printf("Ingrese la DB a usar\n");
				usarDB(new_string());
			break;

			case 4:
				printf("Ingrese la DB a eliminar\n");
				eliminarDB(new_string());
			break;

		}
	}while(op!=5);
	
}