#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <rlutil.h>
using namespace rlutil;

struct articulo;
int menu();
void cargar_registro();
void listar_registros();
void leer_registro();
void crear_registro(articulo *);
bool guardar_registro(articulo);
bool menu_reintentar();
void mostrar_articulo(articulo);
void modificar_registro();
void eliminar_registro();

const int tam=5;
char direc[]="articulos.dat";

struct articulo
{
    char nombre[tam];
    float precio;
    int stock;
    int stock_min;
    bool activo;
};

int menu()
{
    cls();
    int op;
    cout<<"------------   1  - Cargar registro      ----------"<<endl;
    cout<<"------------   2  - Leer registro        ----------"<<endl;
    cout<<"------------   3  - Modificar registro   ----------"<<endl;
    cout<<"------------   4  - Eliminar registro    ----------"<<endl;
    cout<<"------------   5  - Listar registros     ----------"<<endl;
    cout<<"------------   0  - Salir                ----------"<<endl<<endl;

    cout<<"Selecciones una opcion del menu: ";
    cin>>op;
    cls();
return op;
}

void eliminar_registro()
{
    articulo art;
    FILE *p;
    p = fopen(direc,"rb+");
    if(p==NULL)
    {
        cout<<"Error en apertura de archivo"<<endl;
        return;
    }
    char nombre[tam];
    cout<<"Ingrese el nombre del articulo a eliminar: ";
    cin>>nombre;

    while(fread(&art,sizeof (articulo),1,p))
    {
        if(!strcmp(art.nombre,nombre))
           {
                if(art.activo)
                {
                    fseek(p,(ftell(p)-sizeof(articulo)),0);
                    art.activo=false;
                    fwrite(&art,sizeof (articulo),1,p);
                    cout<<"Articulo dado de baja exitosamente"<<endl;
                }
                else
                {
                    cout<<"Articulo ya dado de baja"<<endl;
                }
                fclose(p);
                return;
           }
    }
    cout<<"Nombre de articulo inexistente o dado de baja"<<endl;
    fclose(p);
}

void modificar_registro()
{
    char nombre[tam];
    articulo art;
    FILE *p;
    p = fopen(direc,"rb+");
    if(p==NULL)
   {
        cout<<"Error de archivo. No se pudo leer el archivo"<<endl;
        return;
    }
    cout<<"Ingresar el nombre de articulo a modificar: ";
    cin>>nombre;
    while(fread(&art,sizeof (articulo),1,p))
    {
        if((!strcmp(nombre,art.nombre)) && art.activo)
        {
            fseek(p,ftell(p)-sizeof(articulo),0);
            cout<<"Articulo encontrado, proceder a modificar: "<<endl;
            crear_registro(&art);
            fwrite(&art,sizeof (articulo),1,p);
            fclose(p);
            return;
        }
    }
    cout<<"El articulo no existe"<<endl;
    fclose(p);
}

void leer_registro()
{
    char nombre[tam];
    articulo art;
    FILE *p;
    p = fopen(direc, "rb+");
    if(p==NULL)
    {
        cout<<"Error de archivo. No se pudo leer el archivo"<<endl;
        return;
    }
    cout<<"Ingresar el nombre de articulo a leer: ";
    cin>>nombre;

    while(fread(&art,sizeof (struct articulo),1,p)==1)
    {
        if(!strcmp(nombre, art.nombre)&& art.activo)
        {
            fseek(p,(ftell(p)-sizeof(articulo)),0);
            cout<<"Articulo encontrado!"<<endl;
            fread(&art, sizeof (articulo),1,p);
            mostrar_articulo(art);
            return;
        }
    }
    if(feof(p))
    {
        cout<<"El articulo no existe"<<endl;
    }
    fclose(p);
}

void mostrar_articulo(articulo art)
{
    cout<<"Nombre del articulo: "<< art.nombre<<endl;
    cout<<"Precio del articulo: "<< art.precio<<endl;
    cout<<"Stock del articulo: "<< art.stock<<endl;
    cout<<"Stock minimo del articulo: "<< art.stock_min<<endl;
    cout<< endl;
    Sleep(1000);
}


void listar_registros()
{
    articulo art;
    FILE *p;

    p = fopen(direc, "rb");
    if(p==NULL)
    {
        cout<<"No se pudo listar los articulos"<<endl;
        return;
    }
    while(fread(&art, sizeof (articulo), 1, p))
    {

        if(art.activo)
            {
                cout<<"Nombre del articulo: "<< art.nombre<<endl;
                cout<<"Precio del articulo: "<< art.precio<<endl;
                cout<<"Stock del articulo: "<< art.stock<<endl;
                cout<<"Stock minimo del articulo: "<< art.stock_min<<endl;
                cout<< endl;
                Sleep(1000);
            }
    }
    fclose(p);
}

void crear_registro(articulo *art)
{
    cout<<"Ingrese nombre del articulo: ";
    cin>>(*art).nombre;
    cout<<"Ingrese precio del articulo: ";
    cin>>(*art).precio;
    cout<<"Ingrese stock del articulo: ";
    cin>>(*art).stock;
    cout<<"Ingrese stock minimo del articulo: ";
    cin>>(*art).stock_min;
    (*art).activo=true;
}

void cargar_registro()
{
    articulo art={0};
    while(true)
    {
    crear_registro(&art);
    bool guardar = guardar_registro(art);
    if(guardar)
        {
            cout<<"Registro guardado exitosamente!"<<endl;
        }
        else
        {
            cout<<"Registro no se ha podido guardar"<<endl;
        }
    anykey();
    cls();
    bool reintentar = menu_reintentar();
    if(!reintentar)
    {
        break;
    }
    cls();
    }
}

bool guardar_registro(articulo art)
{
    FILE *p;
    p = fopen(direc, "ab");

    if(p==NULL)
    {
        return false;
    }

    if(fwrite(&art,sizeof (articulo),1,p)==1)
    {
        cout<<"Registro cargado exitosamente"<<endl;
    }
    else
    {
        fclose(p);
        return false;
    }
fclose(p);
return true;
}

bool menu_reintentar()
{
    bool op;
    cout<<"Continua cargando?"<<endl;
    cout<<" 1 - SI"<<endl;
    cout<<" 0 - NO"<<endl;
    cout<<"Ingrese una opcion: ";
    cin>>op;
    cls();
return op;
}

#endif // FUNCIONES_H_INCLUDED
