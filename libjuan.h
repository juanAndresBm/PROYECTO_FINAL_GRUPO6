// Materia: Programación I, Paralelo 4
// Grupo: 6
// Autor: Juan
// Fecha creación: 19-06-2026
// Nombre del PROYECTO FINAL: Sistema de Gestion Surtidor Volcan 
#ifndef LIBJUAN_H
#define LIBJUAN_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

struct TanquePrincipal {
    int tipoCombustible;
    double capacidadMaxima;
    double stockActual;
};

struct BombaDispensadora {
    int numeroBomba;
    double stockGasolina;
    double stockDiesel;
    double capacidadBomba;
};

struct ProveedorYPFB {
    char nombrePlanta[50];
    char ciudad[30];
};

struct RecepcionCisterna {
    char placaCisterna[15];
    char nombreChofer[50];
    double litrosDescargados;
    int tipoCombustible;
    char fechaLlegada[12];
    char plantaOrigen[50];
    char ciudadOrigen[30];
};

void libjuan_guardar(TanquePrincipal tanques[], int totalTanques, BombaDispensadora bombas[], int totalBombas, ProveedorYPFB proveedores[], int totalProveedores, RecepcionCisterna cisternas[], int totalCisternas) {
    ofstream arch("logistica.txt");
    if (!arch) return;

    arch << totalTanques << endl;
    for(int i = 0; i < totalTanques; i++) {
        arch << tanques[i].tipoCombustible << endl << tanques[i].capacidadMaxima << endl << tanques[i].stockActual << endl;
    }

    arch << totalBombas << endl;
    for(int i = 0; i < totalBombas; i++) {
        arch << bombas[i].numeroBomba << endl << bombas[i].stockGasolina << endl << bombas[i].stockDiesel << endl << bombas[i].capacidadBomba << endl;
    }

    arch << totalProveedores << endl;
    for(int i = 0; i < totalProveedores; i++) {
        arch << proveedores[i].nombrePlanta << endl << proveedores[i].ciudad << endl;
    }

    arch << totalCisternas << endl;
    for(int i = 0; i < totalCisternas; i++) {
        arch << cisternas[i].placaCisterna << endl 
             << cisternas[i].nombreChofer << endl 
             << cisternas[i].litrosDescargados << endl 
             << cisternas[i].tipoCombustible << endl
             << cisternas[i].fechaLlegada << endl
             << cisternas[i].plantaOrigen << endl
             << cisternas[i].ciudadOrigen << endl;
    }
    arch.close();
}

void libjuan_cargar(TanquePrincipal tanques[], int& totalTanques, BombaDispensadora bombas[], int& totalBombas, ProveedorYPFB proveedores[], int& totalProveedores, RecepcionCisterna cisternas[], int& totalCisternas) {
    ifstream arch("logistica.txt");
    if (!arch) return;

    arch >> totalTanques;
    for(int i = 0; i < totalTanques; i++) {
        arch >> tanques[i].tipoCombustible >> tanques[i].capacidadMaxima >> tanques[i].stockActual;
    }

    arch >> totalBombas;
    for(int i = 0; i < totalBombas; i++) {
        arch >> bombas[i].numeroBomba >> bombas[i].stockGasolina >> bombas[i].stockDiesel >> bombas[i].capacidadBomba;
    }

    arch >> totalProveedores;
    arch.ignore();
    for(int i = 0; i < totalProveedores; i++) {
        arch.getline(proveedores[i].nombrePlanta, 50);
        arch.getline(proveedores[i].ciudad, 30);
    }

    arch >> totalCisternas;
    for(int i = 0; i < totalCisternas; i++) {
        arch >> cisternas[i].placaCisterna;
        arch.ignore();
        arch.getline(cisternas[i].nombreChofer, 50);
        arch >> cisternas[i].litrosDescargados >> cisternas[i].tipoCombustible >> cisternas[i].fechaLlegada;
        arch.ignore();
        arch.getline(cisternas[i].plantaOrigen, 50);
        arch.getline(cisternas[i].ciudadOrigen, 30);
    }
    arch.close();
}

void libjuan_mostrarEstado(TanquePrincipal tanques[], int totalTanques, BombaDispensadora bombas[], int totalBombas) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "       ESTADO DE TANQUES Y BOMBAS        " << endl;
    cout << "=========================================" << endl;
    cout << "--- DEPOSITOS GRANDES PRINCIPALES ---" << endl;
    if (totalTanques >= 2) {
        cout << "Tanque Mayor [GASOLINA]: " << tanques[0].stockActual << " / " << tanques[0].capacidadMaxima << " Lts." << endl;
        cout << "Tanque Mayor [DIESEL]:   " << tanques[1].stockActual << " / " << tanques[1].capacidadMaxima << " Lts." << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "--- DEPOSITOS PEQUENOS (BOMBAS) ---" << endl;
    for (int i = 0; i < totalBombas; i++) {
        cout << "Bomba Nro " << bombas[i].numeroBomba << " -> Gasolina: " << bombas[i].stockGasolina << " Lts | Diesel: " << bombas[i].stockDiesel << " Lts" << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa;
    cin >> pausa;
}

void libjuan_registrarProveedor(ProveedorYPFB proveedores[], int& totalProveedores, TanquePrincipal tanques[], int totalTanques, BombaDispensadora bombas[], int totalBombas, RecepcionCisterna cisternas[], int totalCisternas) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "         REGISTRAR PROVEEDOR YPFB        " << endl;
    cout << "=========================================" << endl;
    if (totalProveedores < 100) {
        cout << "Seleccione la Planta o Refineria de Origen:" << endl << endl;
        cout << "--- REFINERIAS TRADICIONALES ---" << endl;
        cout << "1. Refineria Gualberto Villarroel (Cochabamba)" << endl;
        cout << "2. Refineria Guillermo Elder Bell (Santa Cruz)" << endl;
        cout << "3. Refineria Oro Negro (Santa Cruz)" << endl << endl;
        cout << "--- PLANTAS DE BIODIESEL ---" << endl;
        cout << "4. Planta de Biodiesel I - Palmasola (Santa Cruz)" << endl;
        cout << "5. Planta de Biodiesel II - Heroes de Senkata (La Paz)" << endl;
        cout << "Ingrese opcion (1-5): ";
        int opcionOrigen;
        cin >> opcionOrigen;

        switch (opcionOrigen) {
            case 1: strcpy(proveedores[totalProveedores].nombrePlanta, "Refineria Gualberto Villarroel"); strcpy(proveedores[totalProveedores].ciudad, "Cochabamba"); break;
            case 2: strcpy(proveedores[totalProveedores].nombrePlanta, "Refineria Guillermo Elder Bell"); strcpy(proveedores[totalProveedores].ciudad, "Santa Cruz"); break;
            case 3: strcpy(proveedores[totalProveedores].nombrePlanta, "Refineria Oro Negro"); strcpy(proveedores[totalProveedores].ciudad, "Santa Cruz"); break;
            case 4: strcpy(proveedores[totalProveedores].nombrePlanta, "Planta de Biodiesel I"); strcpy(proveedores[totalProveedores].ciudad, "Santa Cruz"); break;
            case 5: strcpy(proveedores[totalProveedores].nombrePlanta, "Planta de Biodiesel II"); strcpy(proveedores[totalProveedores].ciudad, "La Paz"); break;
            default: strcpy(proveedores[totalProveedores].nombrePlanta, "Origen Desconocido"); strcpy(proveedores[totalProveedores].ciudad, "No Especificado"); break;
        }

        totalProveedores = totalProveedores + 1;
        libjuan_guardar(tanques, totalTanques, bombas, totalBombas, proveedores, totalProveedores, cisternas, totalCisternas);
        cout << "-----------------------------------------" << endl;
        cout << "Proveedor registrado exitosamente." << endl;
    } else {
        cout << "Error: Limite maximo de almacenamiento alcanzado." << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa;
    cin >> pausa;
}

void libjuan_modificarProveedor(ProveedorYPFB proveedores[], int totalProveedores, TanquePrincipal tanques[], int totalTanques, BombaDispensadora bombas[], int totalBombas, RecepcionCisterna cisternas[], int totalCisternas) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "         MODIFICAR PLANTA PROVEEDORA     " << endl;
    cout << "=========================================" << endl;
    if (totalProveedores == 0) {
        cout << "No existen plantas proveedoras registradas." << endl;
    } else {
        cout << "Seleccione la planta a modificar:" << endl;
        for(int i = 0; i < totalProveedores; i++) {
            cout << i + 1 << ". " << proveedores[i].nombrePlanta << " (" << proveedores[i].ciudad << ")" << endl;
        }
        cout << "Ingrese opcion: ";
        int idx;
        cin >> idx;
        idx--;

        if (idx >= 0 && idx < totalProveedores) {
            cout << "Seleccione la nueva Planta asignada para esta posicion:" << endl << endl;
            cout << "1. Refineria Gualberto Villarroel (Cochabamba)" << endl;
            cout << "2. Refineria Guillermo Elder Bell (Santa Cruz)" << endl;
            cout << "3. Refineria Oro Negro (Santa Cruz)" << endl;
            cout << "4. Planta de Biodiesel I - Palmasola (Santa Cruz)" << endl;
            cout << "5. Planta de Biodiesel II - Heroes de Senkata (La Paz)" << endl;
            cout << "Ingrese numero (1-5): ";
            int nuevaOpc;
            cin >> nuevaOpc;

            switch (nuevaOpc) {
                case 1: strcpy(proveedores[idx].nombrePlanta, "Refineria Gualberto Villarroel"); strcpy(proveedores[idx].ciudad, "Cochabamba"); break;
                case 2: strcpy(proveedores[idx].nombrePlanta, "Refineria Guillermo Elder Bell"); strcpy(proveedores[idx].ciudad, "Santa Cruz"); break;
                case 3: strcpy(proveedores[idx].nombrePlanta, "Refineria Oro Negro"); strcpy(proveedores[idx].ciudad, "Santa Cruz"); break;
                case 4: strcpy(proveedores[idx].nombrePlanta, "Planta de Biodiesel I"); strcpy(proveedores[idx].ciudad, "Santa Cruz"); break;
                case 5: strcpy(proveedores[idx].nombrePlanta, "Planta de Biodiesel II"); strcpy(proveedores[idx].ciudad, "La Paz"); break;
                default: strcpy(proveedores[idx].nombrePlanta, "Modificacion Desconocida"); strcpy(proveedores[idx].ciudad, "No Especificado"); break;
            }
            
            libjuan_guardar(tanques, totalTanques, bombas, totalBombas, proveedores, totalProveedores, cisternas, totalCisternas);
            cout << "-----------------------------------------" << endl;
            cout << "Datos de la planta modificados con exito." << endl;
        } else {
            cout << "Opcion no valida." << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa;
    cin >> pausa;
}

void libjuan_eliminarProveedor(ProveedorYPFB proveedores[], int& totalProveedores, TanquePrincipal tanques[], int totalTanques, BombaDispensadora bombas[], int totalBombas, RecepcionCisterna cisternas[], int totalCisternas) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "         ELIMINAR PLANTA PROVEEDORA      " << endl;
    cout << "=========================================" << endl;
    if (totalProveedores == 0) {
        cout << "No existen plantas proveedoras registradas." << endl;
    } else {
        cout << "Seleccione la planta que desea eliminar de la lista:" << endl;
        for (int i = 0; i < totalProveedores; i++) {
            cout << i + 1 << ". " << proveedores[i].nombrePlanta << " (" << proveedores[i].ciudad << ")" << endl;
        }
        cout << "Ingrese numero de opcion (o 0 para cancelar): ";
        int opc;
        cin >> opc;

        if (opc > 0 && opc <= totalProveedores) {
            int idxEliminar = opc - 1;
            
            for (int i = idxEliminar; i < totalProveedores - 1; i++) {
                proveedores[i] = proveedores[i + 1];
            }
            totalProveedores--;

            libjuan_guardar(tanques, totalTanques, bombas, totalBombas, proveedores, totalProveedores, cisternas, totalCisternas);
            cout << "-----------------------------------------" << endl;
            cout << "Planta proveedora eliminada correctamente." << endl;
        } else {
            cout << "Operacion cancelada o entrada no valida." << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa;
    cin >> pausa;
}

void libjuan_recibirCisterna(RecepcionCisterna cisternas[], int& totalCisternas, BombaDispensadora bombas[], int totalBombas, TanquePrincipal tanques[], ProveedorYPFB proveedores[], int totalProveedores) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "        RECEPCION DE CISTERNA YPFB       " << endl;
    cout << "=========================================" << endl;
    
    if (totalCisternas >= 50) {
        cout << "Error: Limite de recepciones alcanzado." << endl;
        cout << "Presione cualquier tecla y ENTER para continuar: ";
        char pausaLim; cin >> pausaLim;
        return;
    }

    cout << "Seleccione la Planta o Refineria de Origen:" << endl << endl;
    cout << "--- REFINERIAS TRADICIONALES ---" << endl;
    cout << "1. Refineria Gualberto Villarroel (Cochabamba)" << endl;
    cout << "2. Refineria Guillermo Elder Bell (Santa Cruz)" << endl;
    cout << "3. Refineria Oro Negro (Santa Cruz)" << endl << endl;
    cout << "--- PLANTAS DE BIODIESEL ---" << endl;
    cout << "4. Planta de Biodiesel I - Palmasola (Santa Cruz)" << endl;
    cout << "5. Planta de Biodiesel II - Heroes de Senkata (La Paz)" << endl;
    cout << "Ingrese opcion (1-5): ";
    int opcionOrigen;
    cin >> opcionOrigen;

    char plantaSel[50];
    char ciudadSel[30];

    switch (opcionOrigen) {
        case 1: strcpy(plantaSel, "Refineria Gualberto Villarroel"); strcpy(ciudadSel, "Cochabamba"); break;
        case 2: strcpy(plantaSel, "Refineria Guillermo Elder Bell"); strcpy(ciudadSel, "Santa Cruz"); break;
        case 3: strcpy(plantaSel, "Refineria Oro Negro"); strcpy(ciudadSel, "Santa Cruz"); break;
        case 4: strcpy(plantaSel, "Planta de Biodiesel I"); strcpy(ciudadSel, "Santa Cruz"); break;
        case 5: strcpy(plantaSel, "Planta de Biodiesel II"); strcpy(ciudadSel, "La Paz"); break;
        default: strcpy(plantaSel, "Origen Desconocido"); strcpy(ciudadSel, "No Especificado"); break;
    }

    system("cls");
    cout << "=========================================" << endl;
    cout << "         DATOS DE CONTROL DE ARRIBO      " << endl;
    cout << "=========================================" << endl;
    cout << "Origen seleccionado: " << plantaSel << " (" << ciudadSel << ")" << endl;
    cout << "Ingrese la fecha de arribo (DD/MM/AAAA): ";
    cin >> cisternas[totalCisternas].fechaLlegada;
    cout << "Ingrese placa de la cisterna: ";
    cin >> cisternas[totalCisternas].placaCisterna;
    
    cout << "Ingrese el nombre completo del Chofer (Permite espacios): ";
    cin.ignore(100, '\n');
    cin.getline(cisternas[totalCisternas].nombreChofer, 50);
    
    system("cls");
    cout << "=========================================" << endl;
    cout << "         CARGAMENTO DE COMBUSTIBLE       " << endl;
    cout << "=========================================" << endl;
    cout << "Seleccione tipo combustible:" << endl;
    cout << "1. Gasolina" << endl;
    cout << "2. Diesel" << endl;
    cout << "Ingrese opcion (1-2): ";
    cin >> cisternas[totalCisternas].tipoCombustible;
    cout << "Ingrese litros descargados de la cisterna: ";
    cin >> cisternas[totalCisternas].litrosDescargados;
    
    int tIdx = (cisternas[totalCisternas].tipoCombustible == 1) ? 0 : 1;
    double stockActualTanque = tanques[tIdx].stockActual;
    double capacidadMaxTanque = tanques[tIdx].capacidadMaxima;
    double intentoTotal = stockActualTanque + cisternas[totalCisternas].litrosDescargados;

    if (intentoTotal > capacidadMaxTanque) {
        system("cls");
        cout << "=========================================" << endl;
        cout << "      ALERTA DE SEGURIDAD: REBALSE       " << endl;
        cout << "=========================================" << endl;
        cout << "ERROR: La descarga supera la capacidad del tanque." << endl << endl;
        cout << "-> Capacidad Maxima:   " << capacidadMaxTanque << " Lts." << endl;
        cout << "-> Stock Actual:       " << stockActualTanque << " Lts." << endl;
        cout << "[X] OPERACION RECHAZADA: Exceso detectado." << endl;
    } else {
        double porBomba = cisternas[totalCisternas].litrosDescargados / 3.0;
        tanques[tIdx].stockActual = intentoTotal;

        if (tIdx == 0) {
            bombas[0].stockGasolina += porBomba;
            bombas[1].stockGasolina += porBomba;
            bombas[2].stockGasolina += porBomba;
        } else {
            bombas[0].stockDiesel += porBomba;
            bombas[1].stockDiesel += porBomba;
            bombas[2].stockDiesel += porBomba;
        }
        
        strcpy(cisternas[totalCisternas].plantaOrigen, plantaSel);
        strcpy(cisternas[totalCisternas].ciudadOrigen, ciudadSel);
        
        totalCisternas = totalCisternas + 1;
        libjuan_guardar(tanques, 2, bombas, totalBombas, proveedores, totalProveedores, cisternas, totalCisternas);
        
        system("cls");
        cout << "=========================================" << endl;
        cout << "         DESCARGA Y DISTRIBUCION         " << endl;
        cout << "=========================================" << endl;
        cout << "Descarga completada con exito y guardada." << endl;
    }

    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa;
    cin >> pausa;
}

void libjuan_verHistorialCisternas(RecepcionCisterna cisternas[], int totalCisternas) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "       HISTORIAL DE CISTERNAS RECIBIDAS  " << endl;
    cout << "=========================================" << endl;
    if (totalCisternas == 0) {
        cout << "No se registran descargas de cisternas aun." << endl;
    } else {
        cout << "FECHA      | CHOFER               | PLACA   | LITROS   | ORIGEN" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        for (int i = 0; i < totalCisternas; i++) {
            cout << cisternas[i].fechaLlegada << " | "
                 << cisternas[i].nombreChofer << " | "
                 << cisternas[i].placaCisterna << " | "
                 << cisternas[i].litrosDescargados << " | "
                 << cisternas[i].plantaOrigen << " (" << cisternas[i].ciudadOrigen << ")" << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para regresar: ";
    char pausa;
    cin >> pausa;
}

void libjuan_menuLogistica(TanquePrincipal tanques[], int totalTanques, BombaDispensadora bombas[], int totalBombas, ProveedorYPFB proveedores[], int& totalProveedores, RecepcionCisterna cisternas[], int& totalCisternas) {
    bool enMenuJuan = true;
    int opcionJuan = 0;
    while (enMenuJuan) {
        system("cls");
        cout << "=========================================" << endl;
        cout << "       MODULO DE LOGISTICA (JUAN)        " << endl;
        cout << "=========================================" << endl;
        cout << "1. Ver Estado de Tanques y Bombas" << endl;
        cout << "2. Registrar Planta Proveedora YPFB" << endl;
        cout << "3. Modificar Planta Proveedora" << endl;
        cout << "4. Eliminar Planta Proveedora" << endl;
        cout << "5. Registrar Recepcion de Cisterna" << endl;
        cout << "6. Ver Historial de Cisternas" << endl;
        cout << "7. Volver al Menu Principal" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcionJuan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            opcionJuan = 0;
        }

        switch (opcionJuan) {
            case 1: libjuan_mostrarEstado(tanques, totalTanques, bombas, totalBombas); break;
            case 2: libjuan_registrarProveedor(proveedores, totalProveedores, tanques, totalTanques, bombas, totalBombas, cisternas, totalCisternas); break;
            case 3: libjuan_modificarProveedor(proveedores, totalProveedores, tanques, totalTanques, bombas, totalBombas, cisternas, totalCisternas); break;
            case 4: libjuan_eliminarProveedor(proveedores, totalProveedores, tanques, totalTanques, bombas, totalBombas, cisternas, totalCisternas); break;
            case 5: libjuan_recibirCisterna(cisternas, totalCisternas, bombas, totalBombas, tanques, proveedores, totalProveedores); break;
            case 6: libjuan_verHistorialCisternas(cisternas, totalCisternas); break;
            case 7: enMenuJuan = false; break;
            default: break;
        }
    }
}

#endif
