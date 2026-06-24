#include <iostream>
#include <cstdlib>
#include <cstring>
#include "libkevin.h"
#include "libjuan.h"
#include "libpedro.h"

using namespace std;

int main() {
    Operador operadores[10];
    int totalOperadores = 0;

    ControlAsistencia asistencias[100];
    int totalAsistencias = 0;

    AsignacionBomba asignaciones[10];
    int totalAsignaciones = 0;

    CierreTurno cierres[50];
    int totalCierres = 0;

    TanquePrincipal tanques[2];
    int totalTanques = 0;

    BombaDispensadora bombas[3];
    int totalBombas = 0;

    ProveedorYPFB proveedores[100];
    int totalProveedores = 0;

    RecepcionCisterna cisternas[50];
    int totalCisternas = 0;

    ClienteBSISA clientes[100];
    int totalClientes = 0;

    Vehiculo vehiculos[100];
    int totalVehiculos = 0;

    Transaccion transacciones[200];
    int totalTransacciones = 0;

    FacturaEmitida facturas[200];
    int totalFacturas = 0;

    libkevin_cargarOperadores(operadores, totalOperadores);
    libkevin_cargarAsistencias(asistencias, totalAsistencias);
    libkevin_cargarCierres(cierres, totalCierres);
    libjuan_cargar(tanques, totalTanques, bombas, totalBombas, proveedores, totalProveedores, cisternas, totalCisternas);
    libpedro_cargar(clientes, totalClientes, vehiculos, totalVehiculos, transacciones, totalTransacciones, facturas, totalFacturas);

    bool sistemaActivo = true;

    while (sistemaActivo) {
        system("cls");
        cout << "=========================================" << endl;
        cout << "        SURTIDOR VOLCAN - BIENVENIDA     " << endl;
        cout << "=========================================" << endl;
        cout << "1. Iniciar Sesion" << endl;
        cout << "2. Registrarse (Nuevos Operadores / Personal)" << endl;
        cout << "3. Salir del Programa" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        int opcBienvenida;
        cin >> opcBienvenida;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            opcBienvenida = 0;
        }

        switch (opcBienvenida) {
            case 1:
                if (totalOperadores == 0) {
                    system("cls");
                    cout << "=========================================" << endl;
                    cout << "          ALERTA DE SEGURIDAD            " << endl;
                    cout << "=========================================" << endl;
                    cout << "Error: No existe ningun usuario registrado." << endl << endl;
                    cout << "Por favor, primero seleccione la opcion 2" << endl;
                    cout << "en el menu de bienvenida para registrarse." << endl;
                    cout << "-----------------------------------------" << endl;
                    cout << "Presione cualquier tecla y ENTER para volver: ";
                    char pausaAlerta;
                    cin >> pausaAlerta;
                } else {
                    system("cls");
                    cout << "=========================================" << endl;
                    cout << "       SURTIDOR VOLCAN - INICIO SESION   " << endl;
                    cout << "=========================================" << endl;
                    char usuarioLogin[30];
                    char claveLogin[20];
                    cout << "Usuario: ";
                    cin >> usuarioLogin;
                    cout << "Clave: ";
                    cin >> claveLogin;

                    int i = 0;
                    int indiceUsuarioActivo = -1;
                    bool encontrado = false;
                    while (i < totalOperadores && !encontrado) {
                        if (strcmp(operadores[i].usuario, usuarioLogin) == 0 && strcmp(operadores[i].clave, claveLogin) == 0) {
                            encontrado = true;
                            indiceUsuarioActivo = i;
                        }
                        i = i + 1;
                    }

                    if (encontrado) {
                        bool sesionActiva = true;
                        int opcionMenu = 0;

                        while (sesionActiva) {
                            system("cls");
                            cout << "=========================================" << endl;
                            cout << "        SURTIDOR VOLCAN - BOLIVIA        " << endl;
                            cout << "=========================================" << endl;
                            cout << "Usuario activo: " << operadores[indiceUsuarioActivo].usuario;
                            cout << " (Bomba " << operadores[indiceUsuarioActivo].bombaAsignada << ")";
                            if(operadores[indiceUsuarioActivo].esAdministrador) cout << " [ADMIN]";
                            cout << endl;
                            cout << "-----------------------------------------" << endl;
                            cout << "1. Modulo de Personal (Kevin)" << endl;
                            cout << "2. Modulo de Logistica y Tanques (Juan)" << endl;
                            cout << "3. Modulo de Ventas y B-SISA (Pedro)" << endl;
                            cout << "4. Cerrar Sesion" << endl;
                            cout << "5. Salir del Programa" << endl;
                            cout << "-----------------------------------------" << endl;
                            cout << "Ingrese una opcion: ";
                            cin >> opcionMenu;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(100, '\n');
                                opcionMenu = 0;
                            }

                            switch (opcionMenu) {
                                case 1:
                                    libkevin_menuPersonal(operadores, totalOperadores, asistencias, totalAsistencias, asignaciones, totalAsignaciones, cierres, totalCierres, operadores[indiceUsuarioActivo].usuario, facturas, totalFacturas, transacciones, totalTransacciones);
                                    break;
                                case 2:
                                    libjuan_menuLogistica(tanques, totalTanques, bombas, totalBombas, proveedores, totalProveedores, cisternas, totalCisternas);
                                    break;
                                case 3:
                                    libpedro_menuVentas(clientes, totalClientes, vehiculos, totalVehiculos, transacciones, totalTransacciones, facturas, totalFacturas, bombas, totalBombas, operadores[indiceUsuarioActivo].bombaAsignada, operadores[indiceUsuarioActivo].usuario);
                                    break;
                                case 4:
                                    sesionActiva = false;
                                    break;
                                case 5:
                                    sesionActiva = false;
                                    sistemaActivo = false;
                                    break;
                                default:
                                    break;
                            }

                            libkevin_guardarOperadores(operadores, totalOperadores);
                            libkevin_guardarAsistencias(asistencias, totalAsistencias);
                            libkevin_guardarCierres(cierres, totalCierres);
                            libjuan_guardar(tanques, totalTanques, bombas, totalBombas, proveedores, totalProveedores, cisternas, totalCisternas);
                            libpedro_guardar(clientes, totalClientes, vehiculos, totalVehiculos, transacciones, totalTransacciones, facturas, totalFacturas);
                        }
                    } else {
                        cout << "-----------------------------------------" << endl;
                        cout << "Credenciales incorrectas. Intente de nuevo." << endl;
                        cout << "Presione cualquier tecla y ENTER para continuar: ";
                        char pausaLoginErr;
                        cin >> pausaLoginErr;
                    }
                }
                break;

            case 2:
                if (totalOperadores >= 10) {
                    system("cls");
                    cout << "=========================================" << endl;
                    cout << "          LIMITE ALCANZADO               " << endl;
                    cout << "=========================================" << endl;
                    cout << "ERROR: Se ha alcanzado el limite maximo de 10 operadores." << endl;
                    cout << "-----------------------------------------" << endl;
                    cout << "Presione cualquier tecla y ENTER para volver: ";
                    char pausaRest;
                    cin >> pausaRest;
                } else {
                    system("cls");
                    cout << "=========================================" << endl;
                    if (totalOperadores == 0) {
                        cout << "   SURTIDOR VOLCAN - CONFIGURACION INICIAL" << endl;
                    } else {
                        cout << "   SURTIDOR VOLCAN - REGISTRO DE OPERADOR " << endl;
                    }
                    cout << "=========================================" << endl;
                    cout << "Ingrese el nombre de usuario: ";
                    cin >> operadores[totalOperadores].usuario;
                    cout << "Ingrese la clave de acceso: ";
                    cin >> operadores[totalOperadores].clave;
                    
                    int bombaAux;
                    while (true) {
                        cout << "Seleccione su Bomba de cargo (1-3): ";
                        cin >> bombaAux;
                        if (cin.fail() || bombaAux < 1 || bombaAux > 3) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "No elegiste una opcion valida. Vuelve a elegir la bomba." << endl;
                        } else {
                            break;
                        }
                    }
                    operadores[totalOperadores].bombaAsignada = bombaAux;
                    operadores[totalOperadores].activo = true;

                    if (totalOperadores == 0) {
                        operadores[totalOperadores].esAdministrador = true;
                        
                        tanques[0].tipoCombustible = 1;
                        tanques[0].capacidadMaxima = 20000.0;
                        tanques[0].stockActual = 0.0;

                        tanques[1].tipoCombustible = 2;
                        tanques[1].capacidadMaxima = 20000.0;
                        tanques[1].stockActual = 0.0;
                        totalTanques = 2;

                        bombas[0].numeroBomba = 1;
                        bombas[0].stockGasolina = 0.0;
                        bombas[0].stockDiesel = 0.0;
                        bombas[0].capacidadBomba = 3000.0;

                        bombas[1].numeroBomba = 2;
                        bombas[1].stockGasolina = 0.0;
                        bombas[1].stockDiesel = 0.0;
                        bombas[1].capacidadBomba = 3000.0;

                        bombas[2].numeroBomba = 3;
                        bombas[2].stockGasolina = 0.0;
                        bombas[2].stockDiesel = 0.0;
                        bombas[2].capacidadBomba = 3000.0;
                        totalBombas = 3;

                        cout << endl << "Administrador y Base de control creados con exito." << endl;
                    } else {
                        operadores[totalOperadores].esAdministrador = false;
                        cout << endl << "Nuevo Operador registrado de forma exitosa." << endl;
                    }

                    totalOperadores = totalOperadores + 1;

                    libkevin_guardarOperadores(operadores, totalOperadores);
                    libjuan_guardar(tanques, totalTanques, bombas, totalBombas, proveedores, totalProveedores, cisternas, totalCisternas);

                    cout << "-----------------------------------------" << endl;
                    cout << "Presione cualquier tecla y ENTER para continuar: ";
                    char pausaConf;
                    cin >> pausaConf;
                }
                break;

            case 3:
                sistemaActivo = false;
                break;

            default:
                break;
        }
    }

    return 0;
}
