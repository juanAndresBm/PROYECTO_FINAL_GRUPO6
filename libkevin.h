// Materia: Programación I, Paralelo 4
// Grupo: 6
// Autor: KEVIN
// Fecha creación: 19-06-2026
// Nombre del PROYECTO FINAL: Sistema de Gestion Surtidor Volcan 
#ifndef LIBKEVIN_H
#define LIBKEVIN_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>


using namespace std;

struct Operador {
    char usuario[30];
    char clave[20];
    bool esAdministrador;
    bool activo;
    int bombaAsignada;
};

struct ControlAsistencia {
    char usuario[30];
    char fecha[12];
    char horaEntrada[8];
    char horaSalida[8];
};

struct AsignacionBomba {
    char usuario[30];
    int numeroBomba;
    bool activa;
};

struct CierreTurno {
    char usuario[30];
    double dineroEstimado;
    double dineroReal;
    double diferencia;
};

void libkevin_guardarAsistencias(ControlAsistencia asistencias[], int totalAsistencias) {
    ofstream arch("asistencias.txt");
    if (!arch) return;
    arch << totalAsistencias << endl;
    for (int i = 0; i < totalAsistencias; i++) {
        arch << asistencias[i].usuario << endl << asistencias[i].fecha << endl << asistencias[i].horaEntrada << endl << asistencias[i].horaSalida << endl;
    }
    arch.close();
}

void libkevin_cargarAsistencias(ControlAsistencia asistencias[], int& totalAsistencias) {
    ifstream arch("asistencias.txt");
    if (!arch) return;
    arch >> totalAsistencias;
    for (int i = 0; i < totalAsistencias; i++) {
        arch >> asistencias[i].usuario >> asistencias[i].fecha >> asistencias[i].horaEntrada >> asistencias[i].horaSalida;
    }
    arch.close();
}

void libkevin_guardarCierres(CierreTurno cierres[], int totalCierres) {
    ofstream arch("cierres.txt");
    if (!arch) return;
    arch << totalCierres << endl;
    for (int i = 0; i < totalCierres; i++) {
        arch << cierres[i].usuario << endl << cierres[i].dineroEstimado << endl << cierres[i].dineroReal << endl << cierres[i].diferencia << endl;
    }
    arch.close();
}

void libkevin_cargarCierres(CierreTurno cierres[], int& totalCierres) {
    ifstream arch("cierres.txt");
    if (!arch) return;
    arch >> totalCierres;
    for (int i = 0; i < totalCierres; i++) {
        arch >> cierres[i].usuario >> cierres[i].dineroEstimado >> cierres[i].dineroReal >> cierres[i].diferencia;
    }
    arch.close();
}

void libkevin_guardarOperadores(Operador operadores[], int totalOperadores) {
    ofstream arch("operadores.txt");
    if (!arch) return;
    arch << totalOperadores << endl;
    for (int i = 0; i < totalOperadores; i++) {
        arch << operadores[i].usuario << endl << operadores[i].clave << endl << operadores[i].esAdministrador << endl << operadores[i].activo << endl << operadores[i].bombaAsignada << endl;
    }
    arch.close();
}

void libkevin_cargarOperadores(Operador operadores[], int& totalOperadores) {
    ifstream arch("operadores.txt");
    if (!arch) return;
    arch >> totalOperadores;
    for (int i = 0; i < totalOperadores; i++) {
        arch >> operadores[i].usuario >> operadores[i].clave >> operadores[i].esAdministrador >> operadores[i].activo >> operadores[i].bombaAsignada;
    }
    arch.close();
}

void libkevin_registrarEntrada(ControlAsistencia asistencias[], int& totalAsistencias, char usuarioActivo[]) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "         REGISTRAR ENTRADA DE TURNO      " << endl;
    cout << "=========================================" << endl;
    if (totalAsistencias < 100) {
        strcpy(asistencias[totalAsistencias].usuario, usuarioActivo);
        cout << "Ingrese la fecha actual (DD/MM/AAAA): ";
        cin >> asistencias[totalAsistencias].fecha;
        cout << "Ingrese hora de ENTRADA (HH:MM): ";
        cin >> asistencias[totalAsistencias].horaEntrada;
        strcpy(asistencias[totalAsistencias].horaSalida, "00:00");
        totalAsistencias = totalAsistencias + 1;
        
        libkevin_guardarAsistencias(asistencias, totalAsistencias);
        cout << "Entrada registrada y guardada permanentemente." << endl;
    } else {
        cout << "Error: Limite de asistencias alcanzado." << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa; cin >> pausa;
}

void libkevin_registrarSalida(ControlAsistencia asistencias[], int totalAsistencias, char usuarioActivo[]) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "          REGISTRAR SALIDA DE TURNO      " << endl;
    cout << "=========================================" << endl;
    
    int i = totalAsistencias - 1;
    int indiceEncontrado = -1;
    bool encontrado = false;
    
    while (i >= 0 && !encontrado) {
        if (strcmp(asistencias[i].usuario, usuarioActivo) == 0 && strcmp(asistencias[i].horaSalida, "00:00") == 0) {
            encontrado = true;
            indiceEncontrado = i;
        }
        i = i - 1;
    }
    
    if (encontrado) {
        cout << "Usuario Activo:     " << usuarioActivo << endl;
        cout << "Fecha de Ingreso:   " << asistencias[indiceEncontrado].fecha << endl;
        cout << "Hora de Entrada:    " << asistencias[indiceEncontrado].horaEntrada << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Ingrese hora de SALIDA (HH:MM): ";
        cin >> asistencias[indiceEncontrado].horaSalida;
        
        libkevin_guardarAsistencias(asistencias, totalAsistencias);
        cout << "Salida grabada exitosamente." << endl;
    } else {
        cout << "Error: No se encontro entrada activa para su usuario." << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa; cin >> pausa;
}

void libkevin_verHistorialAsistencia(ControlAsistencia asistencias[], int totalAsistencias) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "     HISTORIAL DE ASISTENCIA GENERAL     " << endl;
    cout << "=========================================" << endl;
    if (totalAsistencias == 0) {
        cout << "No existen registros de asistencia aun." << endl;
    } else {
        cout << "OPERADOR     | FECHA      | ENTRADA | SALIDA" << endl;
        cout << "-----------------------------------------" << endl;
        for (int i = 0; i < totalAsistencias; i++) {
            cout << asistencias[i].usuario << " \t | " << asistencias[i].fecha << " | " << asistencias[i].horaEntrada << "   | " << asistencias[i].horaSalida << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para regresar: ";
    char pausa; cin >> pausa;
}

void libkevin_cerrarTurno(CierreTurno cierres[], int& totalCierres, char usuarioActivo[], FacturaEmitida facturas[], int totalFacturas, Transaccion transacciones[], int totalTransacciones, Operador operadores[], int totalOperadores) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "         CIERRE DE TURNO Y ARQUEO        " << endl;
    cout << "=========================================" << endl;
    if (totalCierres < 50) {
        strcpy(cierres[totalCierres].usuario, usuarioActivo);
        
        int bombaAsig = 1;
        int o = 0;
        bool encontradoOp = false;
        while (o < totalOperadores && !encontradoOp) {
            if (strcmp(operadores[o].usuario, usuarioActivo) == 0) {
                bombaAsig = operadores[o].bombaAsignada;
                encontradoOp = true;
            }
            o = o + 1;
        }
        
        double sumaVentasBomba = 0.0;
        for (int f = 0; f < totalFacturas; f++) {
            int idTrans = facturas[f].idTransaccion;
            int t = 0;
            bool encontradoTrans = false;
            while (t < totalTransacciones && !encontradoTrans) {
                if (transacciones[t].idTransaccion == idTrans) {
                    if (transacciones[t].numeroBomba == bombaAsig) {
                        sumaVentasBomba = sumaVentasBomba + facturas[f].totalBolivianos;
                    }
                    encontradoTrans = true;
                }
                t = t + 1;
            }
        }
        
        cierres[totalCierres].dineroEstimado = sumaVentasBomba;
        
        cout << "Usuario Activo: " << usuarioActivo << " (Encargado Bomba " << bombaAsig << ")" << endl;
        cout << "Dinero Estimado (Ventas de su Bomba): " << cierres[totalCierres].dineroEstimado << " Bs." << endl;
        cout << "Ingrese el dinero REAL fisico en caja (Bs): ";
        cin >> cierres[totalCierres].dineroReal;
        
        cierres[totalCierres].diferencia = cierres[totalCierres].dineroReal - cierres[totalCierres].dineroEstimado;
        
        system("cls");
        cout << "=========================================" << endl;
        cout << "         ARQUEO DE CAJA GENERADO         " << endl;
        cout << "=========================================" << endl;
        cout << "Monto Estimado: " << cierres[totalCierres].dineroEstimado << " Bs." << endl;
        cout << "Monto Real:     " << cierres[totalCierres].dineroReal << " Bs." << endl;
        cout << "Diferencia:     " << cierres[totalCierres].diferencia << " Bs." << endl;
        
        totalCierres = totalCierres + 1;
        libkevin_guardarCierres(cierres, totalCierres);
    } else {
        cout << "Error: Limite de cierres alcanzado." << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa; cin >> pausa;
}

void libkevin_verHistorialCierres(CierreTurno cierres[], int totalCierres) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "       HISTORIAL DE CIERRES DE TURNO     " << endl;
    cout << "=========================================" << endl;
    if (totalCierres == 0) {
        cout << "No existen cierres de turno registrados." << endl;
    } else {
        cout << "OPERADOR     | ESTIMADO  | REAL      | DIFERENCIA" << endl;
        cout << "-----------------------------------------" << endl;
        for (int i = 0; i < totalCierres; i++) {
            cout << cierres[i].usuario << " \t | " << cierres[i].dineroEstimado << " \t | " << cierres[i].dineroReal << " \t | " << cierres[i].diferencia << " Bs." << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para regresar: ";
    char pausa; cin >> pausa;
}

void libkevin_menuPersonal(Operador operadores[], int& totalOperadores, ControlAsistencia asistencias[], int& totalAsistencias, AsignacionBomba asignaciones[], int& totalAsignaciones, CierreTurno cierres[], int& totalCierres, char usuarioActivo[], FacturaEmitida facturas[], int totalFacturas, Transaccion transacciones[], int totalTransacciones) {
    bool enMenuKevin = true;
    int opcionKevin = 0;
    while (enMenuKevin) {
        system("cls");
        cout << "=========================================" << endl;
        cout << "        MODULO DE PERSONAL (KEVIN)       " << endl;
        cout << "=========================================" << endl;
        cout << "1. Registrar Entrada de Turno" << endl;
        cout << "2. Registrar Salida de Turno" << endl;
        cout << "3. Ver Historial de Asistencias" << endl;
        cout << "4. Realizar Cierre de Turno" << endl;
        cout << "5. Ver Historial de Cierres de Caja" << endl;
        cout << "6. Volver al Menu Principal" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcionKevin;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            opcionKevin = 0;
        }

        switch (opcionKevin) {
            case 1: libkevin_registrarEntrada(asistencias, totalAsistencias, usuarioActivo); break;
            case 2: libkevin_registrarSalida(asistencias, totalAsistencias, usuarioActivo); break;
            case 3: libkevin_verHistorialAsistencia(asistencias, totalAsistencias); break;
            case 4: libkevin_cerrarTurno(cierres, totalCierres, usuarioActivo, facturas, totalFacturas, transacciones, totalTransacciones, operadores, totalOperadores); break;
            case 5: libkevin_verHistorialCierres(cierres, totalCierres); break;
            case 6: enMenuKevin = false; break;
            default: break;
        }
    }
}

#endif
