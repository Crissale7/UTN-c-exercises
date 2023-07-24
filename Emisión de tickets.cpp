// Emisión de tickets.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Producto {
    int idProd;
    char descr[20];
    double precio;
    int idRub;
};

struct Rubro {
    int idRub;
    char descr[20];
    double promo;
};

struct ItemVenta {
    int idProd;
    int cant;
};

bool compararProductos(Producto p1, Producto p2) {
    return strcmp(p1.descr, p2.descr) < 0;
}

bool compararVentas(pair<int, int> v1, pair<int, int> v2) {
    return v1.second > v2.second;
}

int main() {
    ifstream productos("PRODUCTOS.dat", ios::binary);
    ifstream rubros("RUBROS.dat", ios::binary);

    vector<Producto> listaProductos;
    vector<Rubro> listaRubros;

    Producto producto;
    Rubro rubro;

    while (productos.read((char*)&producto, sizeof(Producto))) {
        listaProductos.push_back(producto);
    }

    while (rubros.read((char*)&rubro, sizeof(Rubro))) {
        listaRubros.push_back(rubro);
    }

    productos.close();
    rubros.close();

    int idCli = 0;

    while (idCli == 0) {
        cout << "Ingrese el ID del cliente (0 para salir): ";
        cin >> idCli;

        if (idCli == 0) {
            break;
        }

        vector<ItemVenta> listaItemsVenta;

        int idProd = 0;
        int cant = 0;

        while (idProd != -1) {
            cout << "Ingrese el ID del producto (0 para finalizar la venta): ";
            cin >> idProd;

            if (idProd == 0) {
                break;
            }

            cout << "Ingrese la cantidad: ";
            cin >> cant;

            if (cant == 0) {
                continue;
            }

            ItemVenta itemVenta = { idProd, cant };

            listaItemsVenta.push_back(itemVenta);
        }

        sort(listaItemsVenta.begin(), listaItemsVenta.end(), compararVentas);

        cout << endl << "Número de ticket: " << idCli << endl << endl;

        double total = 0.0;

        for (ItemVenta iv : listaItemsVenta) {
            for (Producto p : listaProductos) {
                if (p.idProd == iv.idProd) {
                    double precioConDescuento = p.precio * ((100.0 - listaRubros[p.idRub - 1].promo) / 100.0);
                    cout << left << setw(20) << p.descr << right << setw(8) << fixed << setprecision(2) << p.precio
                        << setw(8) << fixed << setprecision(2) << precioConDescuento
                        << setw(5) << iv.cant
                        << setw(10) << fixed << setprecision(2) << precioConDescuento * iv.cant
                        << endl;
                    total += precioConDescuento * iv.cant;
                    break;
                }
            }
        }

        cout << endl << "TOTAL: " << fixed << setprecision(2) << total << endl;

        cout << endl << "Ahorro por rubro:" << endl;

        for (Rubro r : listaRubros) {
            double ahorro = 0.0;

            for (ItemVenta iv : listaItemsVenta) {
                for (Producto p : listaProductos) {
                    if (p.idProd == iv.idProd && p.idRub == r.idRub) {
                        double precioConDescuento = p.precio * ((100.0 - r.promo) / 100.0);
                        ahorro += (p.precio - precioConDescuento) * iv.cant;
                        break;
                    }
                }
            }

            cout << left << setw(20) << r.descr
                << right << setw(10) << fixed << setprecision(2) << ahorro
                << endl;

        }

        cout.precision(2);

        vector<pair<int, int>> ventasPorProducto;

        for (Producto p : listaProductos) {
            if (p.idProd != 0) {
                int cantidadVendida = 0;

                for (ItemVenta iv : listaItemsVenta) {
                    if (iv.idProd == p.idProd) {
                        cantidadVendida += iv.cant;
                    }
                }

            }
        }
    }

    //2. Informar cuáles fueron los 10 productos más demandados, ordenando el listado decrecientemente según la cantidad demandada.
    for (Producto p : listaProductos) {
        if (p.idProd != 0) {
            int cantidadVendida = 0;

            for (ItemVenta iv : listaItemsVenta) {
                if (iv.idProd == p.idProd) {
                    cantidadVendida += iv.cant;
                }
            }

            ventasPorProducto.push_back(make_pair(p.idProd, cantidadVendida));
        }
    }

    sort(ventasPorProducto.begin(), ventasPorProducto.end(), compararVentas);

    cout << endl << "Los 10 productos más demandados son:" << endl;

    int i = 0;

    for (pair<int, int> vp : ventasPorProducto) {
        for (Producto p : listaProductos) {
            if (p.idProd == vp.first) {
                cout << left << setw(20) << p.descr
                    << right << setw(5) << vp.second
                    << endl;
                break;
            }
        }

        i++;

        if (i == 10 || i == ventasPorProducto.size()) {
            break;
        }
    }
