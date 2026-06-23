// Materia: Programación I, Paralelo 4
// Grupo: 6
// Autor: Juan
// Fecha creación: 23-06-2026
// Nombre del miniproyecto: Sistema de Gestion Surtidor Volcan 


#include <iostream>
#include "libjuan.h"

using namespace std;

void MenuPrincipalGlobal(string archivoCisternas, string archivoTanques, string archivoEmpleados);

int main() {
    string archivoCisternas = "CISTERNAS.BIN";
    string archivoTanques = "TANQUES.BIN";
    string archivoEmpleados = "EMPLEADOS.BIN"; 
    
    system("chcp 65001");
    MenuPrincipalGlobal(archivoCisternas, archivoTanques, archivoEmpleados);
    return 0;
}

void MenuPrincipalGlobal(string archivoCisternas, string archivoTanques, string archivoEmpleados) {
    int opcion = 0;
    bool continuarGlobal = true;
    while (continuarGlobal) {
        system("cls");
        cout << "==================== SURTIDOR VOLCAN - CONTROL DE ACCESO GLOBAL ====================" << endl;
        cout << "1. Opcion 1: Autenticacion de Personal (Ingreso Restringido)" << endl;
        cout << "2. Opcion 2: Acceso Libre para Clientes / Consulta Externa" << endl;
        cout << "0. Opcion 3: Salir del Sistema" << endl;
        cout << "====================================================================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                AutenticarUsuario(archivoCisternas, archivoTanques, archivoEmpleados);
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "==================== MONITOR PUBLICO DE CONSULTA EXTERNA ====================" << endl;
                cout << "[Módulo de Solo Lectura para Clientes en construcción por sus compañeros de grupo]" << endl;
                cout << "=============================================================================" << endl;
                system("pause");
                break;
            case 0:
                continuarGlobal = false;
                break;
            default:
                cout << "Opcion no valida. Seleccione un numero de la lista." << endl;
                system("pause");
                break;
        }
    }
    system("cls");
    cout << "SISTEMA CERRADO CORRECTAMENTE - PERSISTENCIA DE DATOS ASEGURADA" << endl;
}