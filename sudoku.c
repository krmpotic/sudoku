#include <stdio.h>

int check_solved(int field) {
  int n, j;
  j = 256;
  for (n = 9; n > 0; n--) {
    if (j == field) {
      return n;
    } else {
      j = j / 2;
    }
  }

  return 0;
}

int main(int argc, char* argv[]) {
  int table[9][9] = {
      {0, 8, 5, 0, 6, 7, 0, 0, 9},  //
      {0, 0, 0, 0, 0, 0, 0, 0, 0},  //
      {7, 3, 1, 4, 0, 0, 0, 6, 5},  //
      {0, 7, 0, 0, 1, 0, 0, 8, 0},  //
      {0, 0, 3, 9, 2, 6, 0, 4, 0},  //
      {2, 0, 0, 0, 4, 0, 1, 3, 0},  //
      {0, 0, 2, 5, 3, 0, 0, 0, 0},  //
      {0, 4, 0, 8, 9, 1, 6, 2, 0},  //
      {0, 0, 0, 6, 0, 0, 4, 5, 1},  //
  };

  int n, m;
  for (n = 0; n < 9; n++) {
    for (m = 0; m < 9; m++) {
      table[n][m] = -1 * table[n][m];
      if (table[n][m] == 0) {
        table[n][m] = 511;
      }
    }
  }

  for (n = 0; n < 9; n++) {
    for (m = 0; m < 9; m++) {
      printf("%03d | ", table[n][m]);
    }
    printf("\n");
  }
  printf("\n");

  int num_changes;
  int solved_flag;
  do {
    num_changes = 0;
    int i, j;
    solved_flag = 1;

    for (n = 0; n < 9; n++) {
      for (m = 0; m < 9; m++) {
        if (table[n][m] < 0) {
          int value = (-1) * table[n][m];
          int bit = 1 << (value - 1);

          for (i = 0; i < 9; i++) {  // COLUMN
            if (table[i][m] > 0 && ((table[i][m] & bit) == bit)) {
              table[i][m] = table[i][m] - bit;
              num_changes += 1;
            }
          }

          for (j = 0; j < 9; j++) {  // ROW
            if (table[n][j] > 0 && ((table[n][j] & bit) == bit)) {
              table[n][j] = table[n][j] - bit;
              num_changes += 1;
            }
          }

          for (i = 3 * (int)(n / 3); i < 3 * (int)(n / 3) + 3; i++) {  // SQUARE
            for (j = 3 * (int)(m / 3); j < 3 * (int)(m / 3) + 3; j++) {
              if (table[i][j] > 0 && ((table[i][j] & bit) == bit)) {
                table[i][j] = table[i][j] - bit;
                num_changes += 1;
              }
            }
          }
        } else {
          int solved = check_solved(table[n][m]);
          if (solved) {
            table[n][m] = -1 * solved;
            num_changes += 1;
          } else {
            solved_flag = 0;
          }
        }
      }
    }
  } while (num_changes != 0);

  if (solved_flag == 1) {
    for (n = 0; n < 9; n++) {
      for (m = 0; m < 9; m++) {
        table[n][m] = -1 * table[n][m];
      }
    }
  }

  for (n = 0; n < 9; n++) {
    for (m = 0; m < 9; m++) {
      printf("%3d | ", table[n][m]);
    }
    printf("\n");
  }

  return 0;
}
