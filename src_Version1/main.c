#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definimos String como tipo *char
//typedef char* String;
//-----prototipos

	//protipos generales
char *new_string();
String concatenar(String a,String b);
int cadenaIdentica(char *a,char *b);
//prototipos de base
void crearDB();
void mostrarDB();
int existeBase(String base);
void usarDB(String sel);
void eliminarDB(String dbsel);

//prototipos de tabla
void crearTabla(String sel);

//prototipo de menu
void menu();
//----inicio de funciones----
int main()
{
	menu();	
return 0;
}
//-----------------funciones de uso general
char *new_string()
{
	char *cad=malloc(sizeof(char)*100),a;
	int i=0;
	getchar();
	while((a=getchar())!='\n')cad[i++]=a;

return cad;
}

String concatenar(String a,String b)
{
	int i=0,j=0;
	String c=calloc(sizeof(char),strlen(a)+strlen(b));
	for(i=0;i<(strlen(a)+strlen(b));i++)
	{
		if(i<strlen(a))c[i]=a[i];
		else c[i]=b[j++];
	}
return c;
}

int cadenaIdentica(char *a,char *b)
{
	int i;
	if(strlen(a)!=strlen(b))return 0;
	for(i=0;i<strlen(a);i++)
		if(a[i]!=b[i])return 0;
return 1;
}

//---------------------------funciones DB

void crearDB()
{
	String cad,base_leida=malloc(sizeof(char)*100);
	FILE *pf;
	int cant=0;
	pf=fopen("DB/cant_db.txt","r");
	fscanf(pf,"%d",&cant);
	fclose(pf);

	printf("Ingrese el nombre de la db\n");
	cad=new_string();
	int i,existe=0;
	pf=fopen("DB/nombre_bases.txt","r");
	for(i=0;i<cant;i++)
	{	fscanf(pf,"%s",base_leida);
		if(cadenaIdentica(base_leida,cad))
		{
			printf("-------La base de datos ya existe-----\n");
			existe=1;
			break;
		}
	}
	if(existe)return;
	system(concatenar("mkdir DB/",cad));
	//pf=fopen(concatenar("DB/",concatenar(cad,".txt")),"w");

	pf=fopen("DB/nombre_bases.txt","a");
	fprintf(pf, "%s\n",cad);
	fclose(pf);

	pf=fopen("DB/cant_db.txt","w");
	fprintf(pf,"%d",++cant);
	fclose(pf);
	printf("-------------Base de datos creada satisfactoriamente---------\n");
}

void mostrarDB()
{
	FILE *pf;
	int i,cant=0;
	String dbnames=malloc(sizeof(char)*100);

	pf=fopen("DB/cant_db.txt","r");
	fscanf(pf,"%d",&cant);
	fclose(pf);
	printf("%d\n",cant );
	if(cant==0)
	{
		printf("No hay db creadas:\n");
		return;
	}
	fopen("DB/nombre_bases.txt","r");
	printf("--------------------------------------\n");
	for(i=0;i<cant;i++)
	{
		fscanf(pf,"%s",dbnames);
		printf("%d-%s\n",i+1,dbnames);
	}
	printf("---------------%d Bases creadas---------------\n", cant);
	fclose(pf);

}

int existeBase(String base)
{
	int i,cd;
	FILE *pf=fopen(concatenar("DB/",concatenar("cant_db",".txt")),"r");
	fscanf(pf,"%d",&cd),i;
	fclose(pf);
	char *base_ext=malloc(sizeof(char)*100);
	pf=fopen("DB/nombre_bases.txt","r");
	for(i=0;i<cd;i++)
	{
		fscanf(pf,"%s",base_ext);
		if(cadenaIdentica(base_ext,base))
			return 1;
	}
	fclose(pf);
return 0;
}
void usarDB(String sel)
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

void eliminarDB(String dbsel)
{
	if(!existeBase(dbsel))
	{
		printf("---------No existe base con ese nombre----------\n");
		return;
	}
	int cant=0,i,k=0;
	String nbase=malloc(sizeof(char)*100),bases[100];
	FILE *pf=fopen("DB/cant_db.txt","r");
	fscanf(pf,"%d",&cant);
	fclose(pf);
	char a;
	pf=fopen("DB/nombre_bases.txt","r");
	for(i=0;i<cant;i++)
	{
		fscanf(pf,"%s",nbase);
		if(!cadenaIdentica(nbase,dbsel))
			bases[k++]=nbase;
	}
	fclose(pf);
	pf=fopen("DB/nombre_bases.txt","w");
	for(i=0;i<k;i++)
	{
		fprintf(pf, "%s\n",bases[i] );
		printf("%s\n",bases[i] );
	}
	fclose(pf);
	pf=fopen("DB/cant_db.txt","w");
	fprintf(pf, "%d\n",k );
	fclose(pf);
	system(concatenar("rm -fr DB/",dbsel));
	printf("%s\n",concatenar("rm -fr DB/",dbsel) );
	printf("---------La base de datos se ha eliminado satisfactoriamente-------\n");


}

//-------------------------funciones tabla
void crearTabla(String sel)
{
	FILE *pf;
	int cant=0,cant_c=0;

	printf("Ingrese el nombre de la tabla\n");
	String tabla=new_string();
	system(concatenar("mkdir DB/",concatenar(sel,concatenar("/",tabla))));
	//----------cant tablas no tiene extension
	pf=fopen(concatenar("DB/",concatenar(sel, concatenar("/cant_tablas","")) ),"a+");
	fscanf(pf,"%d",&cant);
	fprintf(pf, "%d", ++cant);
	fclose(pf);

	pf=fopen(concatenar("DB/",concatenar(sel, concatenar("/nombre_tablas",".txt")) ),"a");
	fprintf(pf,	"%s\n", tabla);
	fclose(pf);
	String ruta=concatenar("DB/",concatenar(sel,concatenar("/",tabla)));

	printf("Ingrese la cantidad de campos de la tabla:\n");
	scanf("%d",&cant_c);
	pf=fopen(concatenar(ruta,"/cant_campos.txt"),"w");
	fprintf(pf, "%d", cant_c);
	fclose(pf);


	pf=fopen(concatenar(ruta,"/campos.txt") ,"a");
	int i,t;
	String nom;
	for(i=0;i<cant_c;i++)
	{
		printf("1) int\n2)float\n3) string\n");
		printf("Ingrese el nombre y tipo del campo %d\n",i+1 );
		nom=new_string();
		scanf("%d",&t);
		fprintf(pf, "%s %d\n",nom, t);
	}
	printf("------tabla creada correctamente-----\n");
	fclose(pf);
}

//--------------------funcion general
void menu()
{
	int op;
	do
	{
		printf("1)Crear db\n2)mostrar db\n3)usar\n4)eliminar db\n5)Salir\n");
		scanf("%d",&op);
 		String db;
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