#include <assert.h>
#include <stdio.h>

int check_solved(int field) {
  for (int n = 9; n > 0; n--) {
    if (1 << (n - 1) == field) {
      return n;
    }
  }
  return 0;
}

void print_table(int table[9][9]) {
  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      printf("%d%s", table[n][m], m < 8 ? " " : "\n");
    }
  }
}

void read_table(int table[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      scanf("%d", &table[i][j]);
    }
  }
}

void solve_table(int table[9][9]) {
  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      assert(table[n][m] >= 0 && table[n][m] <= 9);
    }
  }

  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      table[n][m] = table[n][m] == 0 ? 0b111111111 : -1 * table[n][m];
    }
  }

  int num_changes;
  do {
    num_changes = 0;

    for (int n = 0; n < 9; n++) {
      for (int m = 0; m < 9; m++) {
        if (table[n][m] < 0) {
          int value = (-1) * table[n][m];
          int bit = 1 << (value - 1);

          for (int i = 0; i < 9; i++) {  // COLUMN
            if (table[i][m] > 0 && ((table[i][m] & bit) == bit)) {
              table[i][m] = table[i][m] - bit;
              num_changes += 1;
            }
          }

          for (int j = 0; j < 9; j++) {  // ROW
            if (table[n][j] > 0 && ((table[n][j] & bit) == bit)) {
              table[n][j] = table[n][j] - bit;
              num_changes += 1;
            }
          }

          for (int i = 3 * (int)(n / 3); i < 3 * (int)(n / 3) + 3;
               i++) {  // SQUARE
            for (int j = 3 * (int)(m / 3); j < 3 * (int)(m / 3) + 3; j++) {
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
          }
        }
      }
    }
  } while (num_changes != 0);

  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      table[n][m] = table[n][m] < 0 ? -1 * table[n][m] : 0;
    }
  }
}

int main(int argc, char* argv[]) {
  int table[9][9];
  read_table(table);
  solve_table(table);
  print_table(table);

  return 0;
}
