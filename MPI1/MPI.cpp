#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <mpi.h>
#include <omp.h>

#define TAMANIO 30
//#define TAMANIO 200000

class Arreglo {
private:
    int* arreglo;
    int red, nodo;

public:
    Arreglo(int red, int nodo) {
        this->nodo = nodo;
        this->red = red;
        arreglo = new int[TAMANIO];
    }

    ~Arreglo() {
        delete[] arreglo;
    }

    //Genera avance y asigna valores aleatorios al arreglo
    void avance() {
        srand(time(NULL) + nodo); 

        for (int i = 0; i < TAMANIO; ) {
            int num = rand() % 100; 
            bool repetido = false;

            for (int j = 0; j < i; j++) {
                if (arreglo[j] == num) {
                    repetido = true;
                    break;
                }
            }

            if (!repetido) {
                arreglo[i] = num;
                int porcentaje = (i + 1) * (100 / TAMANIO);
                printf("Nodo %d, de %d nodos : %d %% completado\n", nodo, red, porcentaje);
                i++; 
            }
        }
    }

    // Imprimir el contenido del arreglo
    void imprimir() {
        printf("\nNodo %d - Arreglo generado:\n", nodo);
        for (int i = 0; i < TAMANIO; i++) {
            printf("%3d, ", arreglo[i]);

            if ((i + 1) % 10 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
};

int main() {



    MPI_Init(NULL, NULL);
    int red, nodo;

    MPI_Comm_size(MPI_COMM_WORLD, &red);  
    MPI_Comm_rank(MPI_COMM_WORLD, &nodo); 

    printf("===============================\n");
    printf("\nIntegrantes del equipo:\n");
    printf("Lomeli Flores Cesar\nOliva Chavez Miguel Angel\nTadeo Perez Diego \n");
    printf("===============================\n\n");

    printf("Nodo %d INICIANDO\n\n", nodo);

    Arreglo arreglo(red, nodo);
    arreglo.avance();

    arreglo.imprimir();

    printf("\nNodo %d TERMINANDO\n", nodo);
    
    printf("\n===============================");
    printf("\nIntegrantes del equipo:\n");
    printf("Lomeli Flores Cesar\nOliva Chavez Miguel Angel\nTadeo Perez Diego \n");
    printf("===============================\n\n");

    MPI_Finalize();
    return 0;
}
