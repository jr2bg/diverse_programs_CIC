#include <stdio.h>
// Lattice generation
// void lattice_generator(int ** lattice, int n_rows, int n_cols){
//   // lattice = new int *[n_rows];
//   // for (int i = 0; i < n_rows; i++){
//   //   lattice[i] = new int[n_cols];
//   // }
//
//   for (int i = 0; i < n_rows; i++){
//     for (int j = 0; j < n_cols; j++) {
//       //lattice[i][j] = 0;
//       *(*(lattice +i) + j) = 0;
//     }
//   }
//   printf("Lattice value:  %d\n", lattice[0][1]);
// }

// take neighbourhood from the lattice
// lattice -> lattice
// neighbourhood -> neighbourhood
// t_neigh -> tipo de vecindad
// row_p -> row position
// col_p -> column position
int neigh_array(int **lattice,int neighbourhood[3][3], int row_p, int col_p, int n_rows, int n_cols){
  int n_r, n_c;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3 ; j++){
      n_r = row_p + (i - 1);  // -1 para que esté acorde con la vecindad de MOORE
      n_c = col_p + (j - 1);
      // creación del toroide
      if (n_r < 0) n_r = n_rows + n_r;  // + por que de por sí ya son < 0
      if (n_c < 0) n_c = n_cols + n_c;
      if (n_r >= n_rows) n_r = n_rows - n_r;  // - por que debemos ir hacia el principio
      if (n_c >= n_cols) n_c = n_cols - n_c;
      neighbourhood[i][j] = lattice[n_r][n_c];

      //printf("N NEIGH row %d  col %d:  %d\n",i ,j, neighbourhood[i][j]);
      //printf("LATTICE row %d  col %d:  %d\n\n",n_r ,n_c, lattice[n_r][n_c]);
    }
  }
}


// reglas de GOL
// input -> array 2D de 3x3
// output -> estado de la célula en el centro de la vecindad
int rules(int neighbourhood[3][3]) {
  int i, j, num_live_cells = 0, state;
  // rows
  for (i = 0; i <= 2 ; i++) {
    //columns
    for (j = 0; j <= 2; j++) {
      // all elements except the center
      if ((i != 1) || (j != 1 )){
        // live cells updating
        num_live_cells = num_live_cells + neighbourhood[i][j];
      }
    }
  }
  // RULES of GOL
  if ((num_live_cells == 3) || (num_live_cells == 2 && neighbourhood[1][1] == 1)){
    state = 1;
  }
  else state = 0;
return state;
}

// función para la evolución de la configuración
void evolution(int **lattice, int neighbourhood[3][3], int n_rows, int n_cols, int **n_lattice){
  // row_p -> posición fila
  // col_p -> posición columna
  int state;
  // barrido en la fila
  for (int row_p = 0; row_p < n_rows; row_p++){
    // barrido en elemento de la fila
    for (int col_p = 0; col_p < n_cols; col_p++){
      // creación de los vecinos
      neigh_array( lattice, neighbourhood, row_p, col_p, n_rows, n_cols);
      // aplicación de las reglas de LIFE
      state = rules(neighbourhood);
      // creación de una nueva lattice con los valores actualizados
      n_lattice[row_p][col_p] = state;
      printf("row %d col %d    state:\t%d\n", row_p, col_p, state);
    }
  }

  // actualización del array con respecto al creado previamente
  for (int i = 0; i < n_rows; i++){
    for (int j = 0; j < n_cols; j++) {
      lattice[i][j] = n_lattice[i][j];
    }
  }
}



int main() {
  const int n_rows = 6, n_cols = 4;
  //int state, row_p, col_p;

  int i, j;

  // inicializando la lattice y la vecindad
  //int lattice[n_rows][n_cols], neighbourhood[3][3] = {};
  int **lattice = NULL, **n_lattice = NULL, neighbourhood[3][3] = {};

  // Generación de la lattice
  lattice = new int *[n_rows];
  n_lattice = new int *[n_rows];
  for (int i = 0; i < n_rows; i++){
    lattice[i] = new int[n_cols];
    n_lattice[i] = new int[n_cols];
  }
  for (i = 0; i < n_rows; i++){
    for (j = 0; j < n_cols; j++) {
      lattice[i][j] = 0;
      n_lattice[i][j] = 0;
    }
  }
  // Término de la creación de la lattice

  // variables de prueba
  lattice[0][1] = 1;
  lattice[1][0] = 1;
  lattice[2][0] = 1;
  lattice[3][2] = 1;
  lattice[5][0] = 1;
  lattice[5][3] = 1;

  // ciclo de 20 evoluciones temporales
  for (i = 0; i < 20; i++) {
    // generación de la evolución asignada al espacio
    printf("****--------- EVOLUCION %d :v  ------------*****\n", i+1 );
    evolution(lattice, neighbourhood, n_rows, n_cols, n_lattice);

  }
  //printf(" LATTICE 0 3   %d\n", lattice[0][3]);
  delete lattice;
  delete n_lattice;
  return 0;
}
