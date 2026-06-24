#ifndef LIBPEDRO_H
#define LIBPEDRO_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "libjuan.h"

using namespace std;

struct ClienteBSISA {
    char cedula[15];
    char nombrePropietario[60];
    char nitFactura[20];
};

struct Vehiculo {
    char placa[15];
    char cedulaPropietario[15];
    char modelo[30];
    int anio;
    char tipoVehiculo[30];
};

struct Transaccion {
    int idTransaccion;
    char placaVehiculo[15];
    int numeroBomba;
    double litrosDespachados;
    int tipoCombustible;
    char usuarioOperador[30];
};

struct FacturaEmitida {
    int numeroFactura;
    int idTransaccion;
    double totalBolivianos;
    bool adecuada;
};

void libpedro_guardar(ClienteBSISA clientes[], int totalClientes, Vehiculo vehiculos[], int totalVehiculos, Transaccion transacciones[], int totalTransacciones, FacturaEmitida facturas[], int totalFacturas) {
    ofstream arch("ventas.txt");
    if (!arch) return;

    arch << totalClientes << endl;
    for(int i = 0; i < totalClientes; i++) {
        arch << clientes[i].cedula << endl << clientes[i].nombrePropietario << endl << clientes[i].nitFactura << endl;
    }

    arch << totalVehiculos << endl;
    for(int i = 0; i < totalVehiculos; i++) {
        arch << vehiculos[i].placa << endl << vehiculos[i].cedulaPropietario << endl << vehiculos[i].modelo << endl << vehiculos[i].anio << endl << vehiculos[i].tipoVehiculo << endl;
    }

    arch << totalTransacciones << endl;
    for(int i = 0; i < totalTransacciones; i++) {
        arch << transacciones[i].idTransaccion << endl << transacciones[i].placaVehiculo << endl << transacciones[i].numeroBomba << endl << transacciones[i].litrosDespachados << endl << transacciones[i].tipoCombustible << endl << transacciones[i].usuarioOperador << endl;
    }

    arch << totalFacturas << endl;
    for(int i = 0; i < totalFacturas; i++) {
        arch << facturas[i].numeroFactura << endl << facturas[i].idTransaccion << endl << facturas[i].totalBolivianos << endl << facturas[i].adecuada << endl;
    }
    arch.close();
}

void libpedro_cargar(ClienteBSISA clientes[], int& totalClientes, Vehiculo vehiculos[], int& totalVehiculos, Transaccion transacciones[], int& totalTransacciones, FacturaEmitida facturas[], int& totalFacturas) {
    ifstream arch("ventas.txt");
    if (!arch) return;

    arch >> totalClientes;
    for(int i = 0; i < totalClientes; i++) {
        arch >> clientes[i].cedula;
        arch.ignore();
        arch.getline(clientes[i].nombrePropietario, 60);
        arch >> clientes[i].nitFactura;
    }

    arch >> totalVehiculos;
    for(int i = 0; i < totalVehiculos; i++) {
        arch >> vehiculos[i].placa >> vehiculos[i].cedulaPropietario >> vehiculos[i].modelo >> vehiculos[i].anio >> vehiculos[i].tipoVehiculo;
    }

    arch >> totalTransacciones;
    for(int i = 0; i < totalTransacciones; i++) {
        arch >> transacciones[i].idTransaccion >> transacciones[i].placaVehiculo >> transacciones[i].numeroBomba >> transacciones[i].litrosDespachados >> transacciones[i].tipoCombustible;
        arch.ignore();
        arch.getline(transacciones[i].usuarioOperador, 30);
    }

    arch >> totalFacturas;
    for(int i = 0; i < totalFacturas; i++) {
        arch >> facturas[i].numeroFactura >> facturas[i].idTransaccion >> facturas[i].totalBolivianos >> facturas[i].adecuada;
    }
    arch.close();
}

void libpedro_mostrarFactura(FacturaEmitida factura, Transaccion transaccion, Vehiculo vehiculo, ClienteBSISA cliente) {
    cout << "=========================================" << endl;
    cout << "         FACTURA - SURTIDOR VOLCAN       " << endl;
    cout << "=========================================" << endl;
    cout << "Nro Factura: " << factura.numeroFactura << endl;
    cout << "NIT/CI: " << cliente.nitFactura << endl;
    cout << "Senor(es): " << cliente.nombrePropietario << endl;
    cout << "Placa: " << vehiculo.placa << endl;
    cout << "Modelo/Marca: " << vehiculo.modelo << endl;
    cout << "Anio: " << vehiculo.anio << endl;
    cout << "Tipo de Auto: " << vehiculo.tipoVehiculo << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Bomba Nro: " << transaccion.numeroBomba << endl;
    cout << "Operador: " << transaccion.usuarioOperador << endl;
    cout << "Litros: " << transaccion.litrosDespachados << endl;
    cout << "Combustible: ";
    if (transaccion.tipoCombustible == 1) cout << "GASOLINA" << endl;
    else cout << "DIESEL" << endl;
    cout << "Total Pagado: " << factura.totalBolivianos << " Bs." << endl;
    cout << "=========================================" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa; cin >> pausa;
}

void libpedro_despachar(ClienteBSISA clientes[], int& totalClientes, Vehiculo vehiculos[], int& totalVehiculos, Transaccion transacciones[], int& totalTransacciones, FacturaEmitida facturas[], int& totalFacturas, BombaDispensadora bombas[], int totalBombas, int bombaAsignada, char usuarioActivo[]) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "         NUEVA VENTA DE COMBUSTIBLE      " << endl;
    cout << "=========================================" << endl;
    cout << "Operador: " << usuarioActivo << " | Isla: Bomba " << bombaAsignada << endl;
    cout << "-----------------------------------------" << endl;
    
    char placaBuscar[15];
    cout << "Ingrese la Placa del Vehiculo: ";
    cin >> placaBuscar;
    cin.ignore(100, '\n');

    int i = 0;
    int indiceVehiculo = -1;
    bool encontradoVehiculo = false;
    while (i < totalVehiculos && !encontradoVehiculo) {
        if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
            encontradoVehiculo = true;
            indiceVehiculo = i;
        }
        i = i + 1;
    }

    int indiceCliente = -1;
    if (!encontradoVehiculo) {
        system("cls");
        cout << "=========================================" << endl;
        cout << "        B-SISA: CEDULA PROPIETARIO       " << endl;
        cout << "=========================================" << endl;
        cout << "Vehiculo con placa [" << placaBuscar << "] no registrado EN B-SISA." << endl;
        strcpy(vehiculos[totalVehiculos].placa, placaBuscar);
        cout << "Ingrese Cedula de Identidad del Propietario: ";
        cin >> vehiculos[totalVehiculos].cedulaPropietario;
        cin.ignore(100, '\n');

        system("cls");
        cout << "=========================================" << endl;
        cout << "         B-SISA: MARCA DEL VEHICULO      " << endl;
        cout << "=========================================" << endl;
        cout << "Seleccione la Marca del Vehiculo:" << endl;
        cout << "1. Toyota" << endl;
        cout << "2. Nissan" << endl;
        cout << "3. Suzuki" << endl;
        cout << "4. Mitsubishi" << endl;
        cout << "5. Honda" << endl;
        cout << "6. Otro (Digitar manualmente)" << endl;
        cout << "Ingrese opcion (1-6): ";
        int opcMarca;
        cin >> opcMarca;
        cin.ignore(100, '\n');

        if (opcMarca == 1) strcpy(vehiculos[totalVehiculos].modelo, "Toyota");
        else if (opcMarca == 2) strcpy(vehiculos[totalVehiculos].modelo, "Nissan");
        else if (opcMarca == 3) strcpy(vehiculos[totalVehiculos].modelo, "Suzuki");
        else if (opcMarca == 4) strcpy(vehiculos[totalVehiculos].modelo, "Mitsubishi");
        else if (opcMarca == 5) strcpy(vehiculos[totalVehiculos].modelo, "Honda");
        else {
            system("cls");
            cout << "=========================================" << endl;
            cout << "         B-SISA: REGISTRAR OTRA MARCA    " << endl;
            cout << "=========================================" << endl;
            cout << "Escriba la marca del vehiculo: ";
            cin.getline(vehiculos[totalVehiculos].modelo, 30);
        }

        system("cls");
        cout << "=========================================" << endl;
        cout << "          B-SISA: ANO DEL VEHICULO       " << endl;
        cout << "=========================================" << endl;
        cout << "Ingrese el ano del vehiculo (Ej. 2026): ";
        cin >> vehiculos[totalVehiculos].anio;
        cin.ignore(100, '\n');

        system("cls");
        cout << "=========================================" << endl;
        cout << "         B-SISA: TIPO DE VEHICULO        " << endl;
        cout << "=========================================" << endl;
        cout << "Seleccione Tipo de Vehiculo:" << endl;
        cout << "1. Sedan" << endl;
        cout << "2. Camioneta" << endl;
        cout << "3. Vagoneta" << endl;
        cout << "4. Moto" << endl;
        cout << "5. Otro (Digitar manualmente)" << endl;
        cout << "Ingrese numero de tipo (1-5): ";
        int opcTipo;
        cin >> opcTipo;
        cin.ignore(100, '\n');

        if (opcTipo == 1) strcpy(vehiculos[totalVehiculos].tipoVehiculo, "Sedan");
        else if (opcTipo == 2) strcpy(vehiculos[totalVehiculos].tipoVehiculo, "Camioneta");
        else if (opcTipo == 3) strcpy(vehiculos[totalVehiculos].tipoVehiculo, "Vagoneta");
        else if (opcTipo == 4) strcpy(vehiculos[totalVehiculos].tipoVehiculo, "Moto");
        else {
            system("cls");
            cout << "=========================================" << endl;
            cout << "         B-SISA: REGISTRAR OTRO TIPO     " << endl;
            cout << "=========================================" << endl;
            cout << "Escriba el tipo de vehiculo (ej. Minibus): ";
            cin.getline(vehiculos[totalVehiculos].tipoVehiculo, 30);
        }

        int j = 0;
        bool encontradoCliente = false;
        while (j < totalClientes && !encontradoCliente) {
            if (strcmp(clientes[j].cedula, vehiculos[totalVehiculos].cedulaPropietario) == 0) {
                encontradoCliente = true;
                indiceCliente = j;
            }
            j = j + 1;
        }

        if (!encontradoCliente) {
            system("cls");
            cout << "=========================================" << endl;
            cout << "         B-SISA: NOMBRE PROPIETARIO      " << endl;
            cout << "=========================================" << endl;
            strcpy(clientes[totalClientes].cedula, vehiculos[totalVehiculos].cedulaPropietario);
            cout << "Ingrese el Nombre Completo del Propietario: ";
            cin.getline(clientes[totalClientes].nombrePropietario, 60);
            
            system("cls");
            cout << "=========================================" << endl;
            cout << "         B-SISA: NIT FACTURACION         " << endl;
            cout << "=========================================" << endl;
            cout << "NIT para la Factura: ";
            cin >> clientes[totalClientes].nitFactura;
            cin.ignore(100, '\n');
            
            indiceCliente = totalClientes;
            totalClientes = totalClientes + 1;
        }

        indiceVehiculo = totalVehiculos;
        totalVehiculos = totalVehiculos + 1;
        
        system("cls");
        cout << "=========================================" << endl;
        cout << "         REGISTRO COMPLETADO             " << endl;
        cout << "=========================================" << endl;
        cout << "Vehiculo y Cliente guardados exitosamente." << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Presione cualquier tecla y ENTER para ir al despacho: ";
        char pausaReg; cin >> pausaReg;
    } else {
        int j = 0;
        bool encontradoCliente = false;
        while (j < totalClientes && !encontradoCliente) {
            if (strcmp(clientes[j].cedula, vehiculos[indiceVehiculo].cedulaPropietario) == 0) {
                encontradoCliente = true;
                indiceCliente = j;
            }
            j = j + 1;
        }
    }

    int nroBomba = bombaAsignada;
    int indiceBomba = nroBomba - 1;

    system("cls");
    cout << "=========================================" << endl;
    cout << "        SELECCION DE COMBUSTIBLE         " << endl;
    cout << "=========================================" << endl;
    cout << "1. Gasolina (6.96 Bs)" << endl;
    cout << "2. Diesel (9.70 Bs)" << endl;
    cout << "Ingrese opcion (1-2): ";
    int opcionCombustible;
    cin >> opcionCombustible;
    cin.ignore(100, '\n');

    system("cls");
    cout << "=========================================" << endl;
    cout << "        VOLUMEN DE DESPACHO              " << endl;
    cout << "=========================================" << endl;
    double litrosSolicitados;
    cout << "Ingrese la cantidad de litros a cargar: ";
    cin >> litrosSolicitados;
    cin.ignore(100, '\n');

    bool stockDisponible = false;
    if (opcionCombustible == 1 && bombas[indiceBomba].stockGasolina >= litrosSolicitados) stockDisponible = true;
    else if (opcionCombustible == 2 && bombas[indiceBomba].stockDiesel >= litrosSolicitados) stockDisponible = true;

    if (stockDisponible) {
        double precioFinal = 0.0;
        if (opcionCombustible == 1) {
            bombas[indiceBomba].stockGasolina = bombas[indiceBomba].stockGasolina - litrosSolicitados;
            precioFinal = litrosSolicitados * 6.96;
        } else {
            bombas[indiceBomba].stockDiesel = bombas[indiceBomba].stockDiesel - litrosSolicitados;
            precioFinal = litrosSolicitados * 9.70;
        }

        transacciones[totalTransacciones].idTransaccion = totalTransacciones + 1;
        strcpy(transacciones[totalTransacciones].placaVehiculo, vehiculos[indiceVehiculo].placa);
        transacciones[totalTransacciones].numeroBomba = nroBomba;
        transacciones[totalTransacciones].litrosDespachados = litrosSolicitados;
        transacciones[totalTransacciones].tipoCombustible = opcionCombustible;
        strcpy(transacciones[totalTransacciones].usuarioOperador, usuarioActivo);

        facturas[totalFacturas].numeroFactura = totalFacturas + 1; 
        facturas[totalFacturas].idTransaccion = transacciones[totalTransacciones].idTransaccion;
        facturas[totalFacturas].totalBolivianos = precioFinal;
        facturas[totalFacturas].adecuada = true;

        system("cls");
        libpedro_mostrarFactura(facturas[totalFacturas], transacciones[totalTransacciones], vehiculos[indiceVehiculo], clientes[indiceCliente]);

        totalTransacciones = totalTransacciones + 1;
        totalFacturas = totalFacturas + 1;
        libpedro_guardar(clientes, totalClientes, vehiculos, totalVehiculos, transacciones, totalTransacciones, facturas, totalFacturas);
    } else {
        system("cls");
        cout << "=========================================" << endl;
        cout << "             ERROR DE STOCK              " << endl;
        cout << "=========================================" << endl;
        cout << "Error: Stock insuficiente en la bomba seleccionada." << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Presione cualquier tecla y ENTER para continuar: ";
        char pausaErr; cin >> pausaErr;
    }
}

void libpedro_modificarCliente(ClienteBSISA clientes[], int totalClientes, Vehiculo vehiculos[], int totalVehiculos, Transaccion transacciones[], int totalTransacciones, FacturaEmitida facturas[], int totalFacturas) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "       MODIFICAR CLIENTE Y VEHICULO      " << endl;
    cout << "=========================================" << endl;
    if (totalVehiculos == 0) {
        cout << "No hay vehiculos registrados en el sistema B-SISA." << endl;
    } else {
        char placaBuscar[15];
        cout << "Ingrese la Placa del auto a editar: ";
        cin >> placaBuscar;
        cin.ignore(100, '\n');

        int i = 0;
        bool encontradoV = false;
        while (i < totalVehiculos && !encontradoV) {
            if (strcmp(vehiculos[i].placa, placaBuscar) == 0) {
                encontradoV = true;
                
                system("cls");
                cout << "=========================================" << endl;
                cout << "          MODIFICAR MARCA                " << endl;
                cout << "=========================================" << endl;
                cout << "Seleccione la nueva Marca:" << endl;
                cout << "1. Toyota\n2. Nissan\n3. Suzuki\n4. Mitsubishi\n5. Honda\n6. Otro\nIngrese opcion: ";
                int opcM; cin >> opcM; cin.ignore(100, '\n');
                if (opcM == 1) strcpy(vehiculos[i].modelo, "Toyota");
                else if (opcM == 2) strcpy(vehiculos[i].modelo, "Nissan");
                else if (opcM == 3) strcpy(vehiculos[i].modelo, "Suzuki");
                else if (opcM == 4) strcpy(vehiculos[i].modelo, "Mitsubishi");
                else if (opcM == 5) strcpy(vehiculos[i].modelo, "Honda");
                else {
                    cout << "Ingrese marca manualmente: "; cin.getline(vehiculos[i].modelo, 30);
                }

                system("cls");
                cout << "=========================================" << endl;
                cout << "          MODIFICAR ANO                  " << endl;
                cout << "=========================================" << endl;
                cout << "Ingrese nuevo Ano: "; cin >> vehiculos[i].anio; cin.ignore(100, '\n');
                
                system("cls");
                cout << "=========================================" << endl;
                cout << "          MODIFICAR TIPO                 " << endl;
                cout << "=========================================" << endl;
                cout << "Seleccione el nuevo Tipo:\n1. Sedan\n2. Camioneta\n3. Vagoneta\n4. Moto\n5. Otro\nIngrese opcion: ";
                int opcT; cin >> opcT; cin.ignore(100, '\n');
                if (opcT == 1) strcpy(vehiculos[i].tipoVehiculo, "Sedan");
                else if (opcT == 2) strcpy(vehiculos[i].tipoVehiculo, "Camioneta");
                else if (opcT == 3) strcpy(vehiculos[i].tipoVehiculo, "Vagoneta");
                else if (opcT == 4) strcpy(vehiculos[i].tipoVehiculo, "Moto");
                else {
                    cout << "Ingrese tipo manualmente: "; cin.getline(vehiculos[i].tipoVehiculo, 30);
                }

                int j = 0;
                bool encontradoC = false;
                while (j < totalClientes && !encontradoC) {
                    if (strcmp(clientes[j].cedula, vehiculos[i].cedulaPropietario) == 0) {
                        encontradoC = true;
                        system("cls");
                        cout << "=========================================" << endl;
                        cout << "          MODIFICAR PROPIETARIO          " << endl;
                        cout << "=========================================" << endl;
                        cout << "Ingrese nuevo Nombre del Propietario (Use espacios): "; 
                        cin.getline(clientes[j].nombrePropietario, 60);
                        cout << "Ingrese nuevo NIT de facturacion: "; cin >> clientes[j].nitFactura;
                        cin.ignore(100, '\n');
                    }
                    j = j + 1;
                }
                libpedro_guardar(clientes, totalClientes, vehiculos, totalVehiculos, transacciones, totalTransacciones, facturas, totalFacturas);
                system("cls");
                cout << "=========================================" << endl;
                cout << "         ACTUALIZACION EXITOSA           " << endl;
                cout << "=========================================" << endl;
                cout << "Datos del cliente modificados de forma exitosa." << endl;
            }
            i = i + 1;
        }
        if (!encontradoV) cout << "Error: La placa ingresada no existe." << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "Presione cualquier tecla y ENTER para continuar: ";
    char pausa; cin >> pausa;
}

void libpedro_verRegistroBSISA(Vehiculo vehiculos[], int totalVehiculos, ClienteBSISA clientes[], int totalClientes) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "         REGISTRO GENERAL B-SISA         " << endl;
    cout << "=========================================" << endl;
    if (totalVehiculos == 0) {
        cout << "No hay vehiculos registrados en el sistema B-SISA." << endl;
    } else {
        for (int i = 0; i < totalVehiculos; i++) {
            char ciBusca[15];
            strcpy(ciBusca, vehiculos[i].cedulaPropietario);
            
            int idxCliente = -1;
            for (int j = 0; j < totalClientes; j++) {
                if (strcmp(clientes[j].cedula, ciBusca) == 0) {
                    idxCliente = j;
                    break;
                }
            }
            
            cout << "PLACA:       " << vehiculos[i].placa << endl;
            cout << "VEHICULO:    " << vehiculos[i].modelo << " (" << vehiculos[i].tipoVehiculo << ") - Ano: " << vehiculos[i].anio << endl;
            if (idxCliente != -1) {
                cout << "PROPIETARIO: " << clientes[idxCliente].nombrePropietario << " (CI: " << clientes[idxCliente].cedula << ")" << endl;
                cout << "NIT FACTURA: " << clientes[idxCliente].nitFactura << endl;
            } else {
                cout << "PROPIETARIO: No Vinculado o No Encontrado." << endl;
            }
            cout << "-----------------------------------------" << endl;
        }
    }
    cout << "=========================================" << endl;
    cout << "Presione cualquier tecla y ENTER para regresar: ";
    char pausa; cin >> pausa;
}

void libpedro_historial(FacturaEmitida facturas[], int totalFacturas, Transaccion transacciones[], int totalTransacciones) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "         HISTORIAL GLOBAL DE VENTAS      " << endl;
    cout << "=========================================" << endl;
    
    double totalB1 = 0.0, totalB2 = 0.0, totalB3 = 0.0, totalGlobal = 0.0;

    if (totalFacturas == 0) {
        cout << "No se han emitido facturas en este turno." << endl;
    } else {
        for (int i = 0; i < totalFacturas; i++) {
            int idTrans = facturas[i].idTransaccion;
            int nroBombaFactura = 1;
            char opNombre[30] = "Desconocido";
            double ltsDesp = 0.0;
            
            int t = 0;
            bool encontradoTrans = false;
            while (t < totalTransacciones && !encontradoTrans) {
                if (transacciones[t].idTransaccion == idTrans) {
                    nroBombaFactura = transacciones[t].numeroBomba;
                    strcpy(opNombre, transacciones[t].usuarioOperador);
                    ltsDesp = transacciones[t].litrosDespachados;
                    encontradoTrans = true;
                }
                t = t + 1;
            }

            cout << "Factura: " << facturas[i].numeroFactura 
                 << " | Bomba: " << nroBombaFactura 
                 << " | Operador: " << opNombre 
                 << " | Volumen: " << ltsDesp << " Lts"
                 << " | Total: " << facturas[i].totalBolivianos << " Bs." << endl;
            
            if (nroBombaFactura == 1) totalB1 += facturas[i].totalBolivianos;
            if (nroBombaFactura == 2) totalB2 += facturas[i].totalBolivianos;
            if (nroBombaFactura == 3) totalB3 += facturas[i].totalBolivianos;
            totalGlobal += facturas[i].totalBolivianos;
        }
        cout << "-----------------------------------------" << endl;
        cout << "RECAUDACION DESGLOSADA POR BOMBA:" << endl;
        cout << "-> Total Bomba 1: " << totalB1 << " Bs." << endl;
        cout << "-> Total Bomba 2: " << totalB2 << " Bs." << endl;
        cout << "-> Total Bomba 3: " << totalB3 << " Bs." << endl;
        cout << "-----------------------------------------" << endl;
        cout << "TOTAL GLOBAL DEL SURTIDOR: " << totalGlobal << " Bs." << endl;
    }
    cout << "=========================================" << endl;
    cout << "Presione cualquier tecla y ENTER para regresar: ";
    char pausa; cin >> pausa;
}

void libpedro_menuVentas(ClienteBSISA clientes[], int& totalClientes, Vehiculo vehiculos[], int& totalVehiculos, Transaccion transacciones[], int& totalTransacciones, FacturaEmitida facturas[], int& totalFacturas, BombaDispensadora bombas[], int totalBombas, int bombaAsignada, char usuarioActivo[]) {
    bool enMiniturno = true;
    int opcionVentas = 0;

    while (enMiniturno) {
        system("cls");
        cout << "=========================================" << endl;
        cout << "        MODULO DE VENTAS          " << endl;
        cout << "=========================================" << endl;
        cout << "1. Despachar Combustible (Venta)" << endl;
        cout << "2. Modificar Datos de Cliente o Vehiculo" << endl;
        cout << "3. Ver Registro General B-SISA" << endl;
        cout << "4. Ver Historial Global de Ventas" << endl;
        cout << "5. Volver al Menu Principal" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcionVentas;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            opcionVentas = 0;
        } else {
            cin.ignore(100, '\n');
        }

        switch (opcionVentas) {
            case 1: libpedro_despachar(clientes, totalClientes, vehiculos, totalVehiculos, transacciones, totalTransacciones, facturas, totalFacturas, bombas, totalBombas, bombaAsignada, usuarioActivo); break;
            case 2: libpedro_modificarCliente(clientes, totalClientes, vehiculos, totalVehiculos, transacciones, totalTransacciones, facturas, totalFacturas); break;
            case 3: libpedro_verRegistroBSISA(vehiculos, totalVehiculos, clientes, totalClientes); break;
            case 4: libpedro_historial(facturas, totalFacturas, transacciones, totalTransacciones); break;
            case 5: enMiniturno = false; break;
            default: break;
        }
    }
}

#endif
