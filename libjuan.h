// Materia: Programación I, Paralelo 4
// Grupo: 6
// Autor: Juan
// Fecha creación: 23-06-2026
// Nombre del miniproyecto: Sistema Surtidor Volcan - Modulo Administracion

#ifndef LIBJUAN_H
#define LIBJUAN_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Tanque {
    int idTanque;
    char tipoCombustible[30];
    double capacidadTotal;
    double nivelActual;
    bool activo;
};

struct Cisterna {
    char placaCisterna[15];
    char empresaProveedora[40];
    char fechaIngreso[15];
    double litrosDescargados;
    int idTanqueDestino;
    bool activo;
};

struct Empleado {
    char ci[15];
    char nombreCompleto[50];
    char cargo[30];
    char contrasenia[20];
    bool activo;
};

bool ExisteTanque(string archivoTanques, int idBuscar) {
    ifstream archivo;
    Tanque t;
    bool encontrado = false;

    archivo.open(archivoTanques, ios::binary);
    if (archivo.is_open()) {
        while (!encontrado && archivo.read((char*)&t, sizeof(Tanque))) {
            if (t.idTanque == idBuscar && t.activo) {
                encontrado = true;
            }
        }
        archivo.close();
    }
    return encontrado;
}

bool ExisteEmpleado(string archivoEmpleados, const char* ciBuscar) {
    ifstream archivo;
    Empleado e;
    bool encontrado = false;

    archivo.open(archivoEmpleados, ios::binary);
    if (archivo.is_open()) {
        while (!encontrado && archivo.read((char*)&e, sizeof(Empleado))) {
            if (strcmp(e.ci, ciBuscar) == 0 && e.activo) {
                encontrado = true;
            }
        }
        archivo.close();
    }
    return encontrado;
}

void RegistrarDescargaCisterna(string archivoCisternas, string archivoTanques) {
    ofstream archCis;
    fstream archTan;
    Cisterna nuevaCisterna;
    Tanque t;
    bool tanqueEncontrado = false;

    system("cls");
    cout << "==================== REGISTRO DE DESCARGA DE CISTERNAS ====================" << endl;
    cout << "Ingrese Placa de la Cisterna: ";
    cin.getline(nuevaCisterna.placaCisterna, 15);
    cout << "Ingrese Empresa Proveedora: ";
    cin.getline(nuevaCisterna.empresaProveedora, 40);
    cout << "Ingrese Fecha de Ingreso (DD-MM-AAAA): ";
    cin.getline(nuevaCisterna.fechaIngreso, 15);
    cout << "Ingrese ID del Tanque Destino: ";
    cin >> nuevaCisterna.idTanqueDestino;
    cout << "Ingrese Litros a Descargar: ";
    cin >> nuevaCisterna.litrosDescargados;
    cin.ignore();

    archTan.open(archivoTanques, ios::in | ios::out | ios::binary);
    if (archTan.is_open()) {
        while (!tanqueEncontrado && archTan.read((char*)&t, sizeof(Tanque))) {
            if (t.idTanque == nuevaCisterna.idTanqueDestino && t.activo) {
                tanqueEncontrado = true;
                if (t.nivelActual + nuevaCisterna.litrosDescargados <= t.capacidadTotal) {
                    t.nivelActual = t.nivelActual + nuevaCisterna.litrosDescargados;
                    archTan.seekp(-sizeof(Tanque), ios::cur);
                    archTan.write((char*)&t, sizeof(Tanque));
                    
                    nuevaCisterna.activo = true;
                    archCis.open(archivoCisternas, ios::binary | ios::app);
                    if (archCis.is_open()) {
                        archCis.write((char*)&nuevaCisterna, sizeof(Cisterna));
                        archCis.close();
                    }
                    cout << "\nDescarga procesada y stock de tanque actualizado con exito." << endl;
                } else {
                    cout << "\nError: La descarga excede la capacidad maxima del tanque." << endl;
                }
            }
        }
        archTan.close();
        if (!tanqueEncontrado) {
            cout << "\nError: El tanque destino no existe o no esta activo." << endl;
        }
    } else {
        cout << "\nError: No se pudo acceder a la base de datos de tanques." << endl;
    }
}

void AltaTanque(string archivoTanques) {
    ofstream archivo;
    Tanque nuevoTanque;

    system("cls");
    cout << "==================== ALTA DE NUEVO TANQUE ====================" << endl;
    cout << "Ingrese ID del Tanque: ";
    cin >> nuevoTanque.idTanque;
    cin.ignore();

    if (ExisteTanque(archivoTanques, nuevoTanque.idTanque)) {
        cout << "Error: El ID de tanque ya se encuentra registrado." << endl;
    } else {
        cout << "Ingrese Tipo de Combustible: ";
        cin.getline(nuevoTanque.tipoCombustible, 30);
        cout << "Ingrese Capacidad Total (Litros): ";
        cin >> nuevoTanque.capacidadTotal;
        cout << "Ingrese Nivel Actual (Litros): ";
        cin >> nuevoTanque.nivelActual;
        cin.ignore();
        nuevoTanque.activo = true;

        archivo.open(archivoTanques, ios::binary | ios::app);
        if (archivo.is_open()) {
            archivo.write((char*)&nuevoTanque, sizeof(Tanque));
            archivo.close();
            cout << "\nTanque creado exitosamente." << endl;
        }
    }
}

void BajaLogicaTanque(string archivoTanques) {
    fstream archivo;
    Tanque t;
    int idBuscar;
    bool modificado = false;

    system("cls");
    cout << "==================== BAJA LOGICA DE TANQUE ====================" << endl;
    cout << "Ingrese el ID del tanque a dar de baja: ";
    cin >> idBuscar;
    cin.ignore();

    archivo.open(archivoTanques, ios::in | ios::out | ios::binary);
    if (archivo.is_open()) {
        while (!modificado && archivo.read((char*)&t, sizeof(Tanque))) {
            if (t.idTanque == idBuscar && t.activo) {
                if (t.nivelActual == 0.0) {
                    t.activo = false;
                    archivo.seekp(-sizeof(Tanque), ios::cur);
                    archivo.write((char*)&t, sizeof(Tanque));
                    modificado = true;
                    cout << "\nTanque deshabilitado de manera logica en el sistema." << endl;
                } else {
                    modificado = true;
                    cout << "\nError: No se puede dar de baja un tanque con combustible almacenado." << endl;
                }
            }
        }
        archivo.close();
        if (!modificado) {
            cout << "\nTanque no encontrado o ya se encuentra inactivo." << endl;
        }
    }
}

void ModificarTanque(string archivoTanques) {
    fstream archivo;
    Tanque t;
    int idBuscar;
    bool modificado = false;

    system("cls");
    cout << "==================== MODIFICAR TANQUE ====================" << endl;
    cout << "Ingrese el ID del tanque a modificar: ";
    cin >> idBuscar;
    cin.ignore();

    archivo.open(archivoTanques, ios::in | ios::out | ios::binary);
    if (archivo.is_open()) {
        while (!modificado && archivo.read((char*)&t, sizeof(Tanque))) {
            if (t.idTanque == idBuscar && t.activo) {
                cout << "Ingrese Nuevo Tipo de Combustible: ";
                cin.getline(t.tipoCombustible, 30);
                cout << "Ingrese Nueva Capacidad Total: ";
                cin >> t.capacidadTotal;
                cin.ignore();

                archivo.seekp(-sizeof(Tanque), ios::cur);
                archivo.write((char*)&t, sizeof(Tanque));
                modificado = true;
                cout << "\nDatos del tanque actualizados correctamente." << endl;
            }
        }
        archivo.close();
        if (!modificado) {
            cout << "\nTanque activo con ese ID no fue localizado." << endl;
        }
    }
}

void AdministrarTanques(string archivoTanques) {
    int subOpcion = 0;
    bool continuarSub = true;
    while (continuarSub) {
        system("cls");
        cout << "==================== ABM DE TANQUES ====================" << endl;
        cout << "1. Alta de Tanque" << endl;
        cout << "2. Baja Logica de Tanque" << endl;
        cout << "3. Modificacion de Tanque" << endl;
        cout << "0. Volver al Menu de Administracion" << endl;
        cout << "========================================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> subOpcion;
        cin.ignore();

        switch (subOpcion) {
            case 1:
                AltaTanque(archivoTanques);
                system("pause");
                break;
            case 2:
                BajaLogicaTanque(archivoTanques);
                system("pause");
                break;
            case 3:
                ModificarTanque(archivoTanques);
                system("pause");
                break;
            case 0:
                continuarSub = false;
                break;
            default:
                cout << "Opcion incorrecta. Intente de nuevo." << endl;
                system("pause");
                break;
        }
    }
}

void GestionarPersonal(string archivoEmpleados) {
    ofstream archivo;
    Empleado nuevoEmp;

    system("cls");
    cout << "==================== ABM REGISTRO DE PERSONAL ====================" << endl;
    cout << "Ingrese CI del Empleado: ";
    cin.getline(nuevoEmp.ci, 15);

    if (ExisteEmpleado(archivoEmpleados, nuevoEmp.ci)) {
        cout << "Error: Un empleado con esa cedula de identidad ya existe." << endl;
    } else {
        cout << "Ingrese Nombre Completo: ";
        cin.getline(nuevoEmp.nombreCompleto, 50);
        cout << "Ingrese Cargo (Administrador / Operario de Bomba): ";
        cin.getline(nuevoEmp.cargo, 30);
        cout << "Ingrese Contraseña de Acceso: ";
        cin.getline(nuevoEmp.contrasenia, 20);
        nuevoEmp.activo = true;

        archivo.open(archivoEmpleados, ios::binary | ios::app);
        if (archivo.is_open()) {
            archivo.write((char*)&nuevoEmp, sizeof(Empleado));
            archivo.close();
            cout << "\nPersonal registrado exitosamente en el sistema." << endl;
        }
    }
}

void MenuAdministracion(string archivoCisternas, string archivoTanques, string archivoEmpleados) {
    int opcion = 0;
    bool continuarMenu = true;
    while (continuarMenu) {
        system("cls");
        cout << "==================== SUBMENU DE ADMINISTRACION E INVENTARIO ====================" << endl;
        cout << "1. Opcion 1: Registro de Descarga de Cisternas" << endl;
        cout << "2. Opcion 2: ABM de Tanques (Altas, Bajas, Modificaciones)" << endl;
        cout << "3. Opcion 3: Registro y Gestion de Personal (ABM Empleados)" << endl;
        cout << "0. Cierre de Sesion Seguro" << endl;
        cout << "================================================================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                RegistrarDescargaCisterna(archivoCisternas, archivoTanques);
                system("pause");
                break;
            case 2:
                AdministrarTanques(archivoTanques);
                break;
            case 3:
                GestionarPersonal(archivoEmpleados);
                system("pause");
                break;
            case 0:
                continuarMenu = false;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                system("pause");
                break;
        }
    }
}

void AutenticarUsuario(string archivoCisternas, string archivoTanques, string archivoEmpleados) {
    ifstream archivo;
    Empleado e;
    char ciIngresado[15];
    char passIngresada[20];
    bool encontrado = false;

    system("cls");
    cout << "==================== AUTENTICACION DE PERSONAL ====================" << endl;
    cout << "Ingrese su Cedula de Identidad (CI): ";
    cin.getline(ciIngresado, 15);
    cout << "Ingrese su Contraseña de Seguridad: ";
    cin.getline(passIngresada, 20);

    archivo.open(archivoEmpleados, ios::binary);
    if (archivo.is_open()) {
        while (!encontrado && archivo.read((char*)&e, sizeof(Empleado))) {
            if (strcmp(e.ci, ciIngresado) == 0 && strcmp(e.contrasenia, passIngresada) == 0 && e.activo) {
                encontrado = true;
                if (strcmp(e.cargo, "Administrador") == 0) {
                    MenuAdministracion(archivoCisternas, archivoTanques, archivoEmpleados);
                } else {
                    cout << "\nAcceso autorizado. Redirigiendo al Submenu de Playa y Ventas..." << endl;
                }
            }
        }
        archivo.close();
        if (!encontrado) {
            cout << "\nCredenciales incorrectas o usuario inactivo en el sistema." << endl;
        }
    } else {
        cout << "\nError: No existen empleados registrados en el sistema." << endl;
    }
}

#endif