#include <iostream>
#include <fstream>

using namespace std;

void mostrar(string v[], int dim){
    for(int i = 0; i < dim; i++){
        cout << i << ": " << v[i] << endl;
    }
}

void listado(float v[][5], int nfil, string client[], string prod[]){
    const int ncol {5};
    for(int i = 0; i < nfil; i++){
        for(int j = 0; j < ncol; j++){
            if(v[i][j] > 13000){
                cout << client[i] << ": " << prod[j] << endl;
            }
        }
    }
}

int mascantidad(float vec[][5], int nfil){
    const int ncol {5};
    int pos {};
    int max {};
    int aux {};
    for (int i = 0; i < nfil; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            if (vec[i][j]>13000)
            {
                aux++;
            }    
        }
      if (aux>max)
      {
        max = aux;
        pos=i;
      }
      aux=0;   
    }
    return pos;
}

void listado2(float v[], int dim, int aux[]){
   int i {};
   int ipos{};
   int imin {};
    for(ipos = 0 ; ipos < dim - 1 ; ipos++ ) {
        imin = ipos;
    for(i = ipos+1 ; i < dim ; i++){
        if (v[i] < v[imin]) {
            imin=i; }
    }
    swap(v[ipos],  v[imin]);
    swap(aux[ipos], aux[imin]);  
    }
}

void mostrarmax(float v[], int dim, string prod[], int pos[]){
    for (int i = 0; i < dim; i++)
    {
        cout << prod[pos[i]] << ": " << v[i] << endl;
    }
    
}

int main(){
    const int ncli {8};
    const int nprod {5};
    float peso [ncli][nprod] {};
    float km [ncli][nprod] {};
    int aux[nprod];
    float pmax[nprod] {};
    float entregas[nprod] {};

    string cliente [ncli];
    string producto [nprod];

    ifstream archilec;
    archilec.open("Nombres.txt");
    if(!archilec){
        cout << "Error al abrir archivo de nombres";
        return 1;
    }
    for(int i = 0; i < ncli; i++){
        archilec >> cliente[i];
    }
    for(int i = 0; i < nprod; i++){
        archilec >> producto[i];
    }
    archilec.close();

    archilec.open("Datos.txt");
    if(!archilec){
        cout << "Error al intentar abrir archivo de datos";
        return 1;
    }
    int icli{};
    int iprod {};
    double ipeso {};
    double idist {};
    while(archilec >> icli >> iprod >> ipeso >> idist){
        peso[icli][iprod] += ipeso;
        km [icli][iprod] += idist;
        entregas[iprod]++;
    }
    archilec.close();

    cout << "Clientes: " << endl;
    mostrar(cliente, ncli);
    cout << "Tipos de Productos: " << endl;
    mostrar(producto, nprod);

    // Punto 1
    cout << "Listado por clientes, de los productos que superen los 13000 kg acumulados " << endl;
    listado(peso, ncli, cliente, producto);

    //Punto 2
    int maxprod = mascantidad(peso, ncli);
    for(int i = 0; i < ncli; ++i)
    {
        for (int j = 0; j < nprod; ++j)
        {
            aux[j] = j;
            pmax[j] = km[maxprod][j];
        }
    }
    listado2(pmax, nprod, aux);
    cout << "Listado de KM recorridos por tipo de producto: " << endl;
    mostrarmax(pmax, nprod, producto, aux);

    //Punto 3
    cout << "Cantidad de entregas para el producto Textiles: " << entregas[3];
    //al estar ordenado, utilizo el ultimo valor de la lista.
    
    return 0;
}