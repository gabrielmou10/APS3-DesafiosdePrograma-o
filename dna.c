#include <stdio.h>

#include "dna.h"

void load_string(FILE *file, int *p, char *s, int t) {
  if (fscanf(file, "%d", p) != 1) {
    fprintf(stderr, "erro ao ler tamanho do teste %d\n", t);
  }

  char c;
  do {
    c = getc(file);
  } while (c != '\n');

  if (!fgets(s, *p + 1, file)) {
    fprintf(stderr, "erro ao ler string do teste %d\n", t);
  }
}

int mlcs_w(char a[], int n, char b[], int m, int length[MAX_SIZE + 1][MAX_SIZE + 1]) {
  // Base da recursão
  if (n == 0 || m == 0) {
    length[0][m] = 0;
    length[n][0] = 0;
    return 0;
  }

  // Recursão
  mlcs_w(a, n - 1, b, m, length);
  mlcs_w(a, n, b, m - 1, length);

  // Condiçoes de passo
  if (a[n - 1] == b[m - 1]) {
    length[n][m] = length[n - 1][m - 1] + 1;
  }

  else {
    if (length[n - 1][m] > length[n][m - 1]) {
      length[n][m] = length[n - 1][m];
    } else {
      length[n][m] = length[n][m - 1];
    }
  }
  return length[n][m];
}

int mlcs(char a[], int n, char b[], int m) {
  // Cria a matriz
  int length[MAX_SIZE + 1][MAX_SIZE + 1];
  // Preenche a matriz
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      length[i][j] = -1;
    }
  }
  // Chama a função recursiva
  mlcs_w(a, n, b, m, length);
  return length[n][m];
}

int dlcs(char a[], int n, char b[], int m) {
  int length[MAX_SIZE + 1][MAX_SIZE + 1];
  // Função interativa
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      // Primeiro caso
      if (i == 0 || j == 0) {
        length[i][j] = 0;
      // Segundo caso
      } else if (a[i - 1] == b[j - 1]) {
        length[i][j] = length[i - 1][j - 1] + 1;
      // Qual é maior dos dois casos
      } else {
        if (length[i - 1][j] >= length[i][j - 1]) {
          length[i][j] = length[i - 1][j];
        } else {
          length[i][j] = length[i][j - 1];
        }
      }
    }
  }
  return length[n][m];
}
