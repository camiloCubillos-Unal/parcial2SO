import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;

public class Parcial2_Punto2 {
    private static final int UMBRAL = 100;

    public static void main(String[] args) {
        // Crear un arreglo de enteros a ordenar
        Integer[] arr = {23, 10, 20, 5, 10, 5, 20, 5, 4, 1, 20, 21, 18, 8, 20, 25};

        // Crear un ForkJoinPool
        ForkJoinPool forkJoinPool = new ForkJoinPool();

        // Crear una instancia de la tarea de ordenamiento basada en el algoritmo que deseas usar
        // Descomentando una de las líneas a continuación para usar Quicksort o Mergesort
        TareaQuicksort task = new TareaQuicksort(arr, 0, arr.length - 1);
        //TareaMergesort task = new TareaMergesort(arr);

        // Invocar la tarea de ordenamiento
        forkJoinPool.invoke(task);

        // Imprimir el arreglo ordenado
        System.out.println(Arrays.toString(arr));
    }

    // Implementación de Quicksort
    static class TareaQuicksort extends RecursiveAction {
        private final Integer[] arr;
        private final int bajo;
        private final int alto;

        TareaQuicksort(Integer[] arr, int bajo, int alto) {
            this.arr = arr;
            this.bajo = bajo;
            this.alto = alto;
        }

        @Override
        protected void compute() {
            if (bajo < alto) {
                if (alto - bajo <= UMBRAL) {
                    // Usar un algoritmo de ordenamiento simple para listas pequeñas
                    Arrays.sort(arr, bajo, alto + 1);
                } else {
                    int indicePivote = particion(arr, bajo, alto);
                    TareaQuicksort tareaIzquierda = new TareaQuicksort(arr, bajo, indicePivote - 1);
                    TareaQuicksort tareaDerecha = new TareaQuicksort(arr, indicePivote + 1, alto);
                    invokeAll(tareaIzquierda, tareaDerecha);
                }
            }
        }

        private int particion(Integer[] arr, int bajo, int alto) {
            int pivote = arr[alto];
            int i = bajo - 1;
            for (int j = bajo; j < alto; j++) {
                if (arr[j] < pivote) {
                    i++;
                    intercambiar(arr, i, j);
                }
            }
            intercambiar(arr, i + 1, alto);
            return i + 1;
        }

        private void intercambiar(Integer[] arr, int i, int j) {
            Integer temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Implementación de Mergesort
    static class TareaMergesort extends RecursiveAction {
        private final Integer[] arr;

        TareaMergesort(Integer[] arr) {
            this.arr = arr;
        }

        @Override
        protected void compute() {
            if (arr.length <= UMBRAL) {
                // Usar un algoritmo de ordenamiento simple para listas pequeñas
                Arrays.sort(arr);
            } else {
                int medio = arr.length / 2;
                Integer[] izquierda = Arrays.copyOfRange(arr, 0, medio);
                Integer[] derecha = Arrays.copyOfRange(arr, medio, arr.length);

                TareaMergesort tareaIzquierda = new TareaMergesort(izquierda);
                TareaMergesort tareaDerecha = new TareaMergesort(derecha);

                invokeAll(tareaIzquierda, tareaDerecha);

                combinar(izquierda, derecha, arr);
            }
        }

        private void combinar(Integer[] izquierda, Integer[] derecha, Integer[] resultado) {
            int i = 0, j = 0, k = 0;

            while (i < izquierda.length && j < derecha.length) {
                if (izquierda[i] <= derecha[j]) {
                    resultado[k++] = izquierda[i++];
                } else {
                    resultado[k++] = derecha[j++];
                }
            }

            while (i < izquierda.length) {
                resultado[k++] = izquierda[i++];
            }

            while (j < derecha.length) {
                resultado[k++] = derecha[j++];
            }
        }
    }
}
