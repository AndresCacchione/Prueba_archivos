#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <rlutil.h>
using namespace std;
using namespace rlutil;
#include "funciones.h"


int main()
{
    int op;

    do{

        op=menu();

        switch(op)
        {
        case 1:
            {
                cargar_registro();
            }break;
        case 2:
            {
                leer_registro();
            }break;
        case 3:
            {
                modificar_registro();
            }break;
        case 4:
            {
                eliminar_registro();
            }break;
        case 5:
            {
                listar_registros();
            }break;
        case 0: {}break;
        default:
            {
                cout<<"Opcion invalida, intente nuevamente"<<endl;
            }break;
        }
        anykey();
    }while(op!=0);
return 0;
}
