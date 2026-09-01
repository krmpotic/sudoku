#include <assert.h>
#include <stdio.h>

#define BIT(n) (1 << (n - 1))

int check_solved(int field) {
  for (int n = 9; n > 0; n--) {
    if (BIT(n) == field) {
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

  int change;
  do {
    change = 0;

    for (int n = 0; n < 9; n++) {
      for (int m = 0; m < 9; m++) {
        if (table[n][m] < 0) {
          const int bit = BIT((-1) * table[n][m]);

          for (int i = 0; i < 9; i++) {  // COLUMN
            if (table[i][m] > 0 && ((table[i][m] & bit) == bit)) {
              table[i][m] = table[i][m] - bit;
              change = 1;
            }
          }

          for (int j = 0; j < 9; j++) {  // ROW
            if (table[n][j] > 0 && ((table[n][j] & bit) == bit)) {
              table[n][j] = table[n][j] - bit;
              change = 1;
            }
          }

          const int is = 3 * (int)(n / 3);
          const int js = 3 * (int)(m / 3);
          for (int i = is; i < is + 3; i++) {  // SQUARE
            for (int j = js; j < js + 3; j++) {
              if (table[i][j] > 0 && ((table[i][j] & bit) == bit)) {
                table[i][j] = table[i][j] - bit;
                change = 1;
              }
            }
          }
        } else if (int solved = check_solved(table[n][m])) {
          table[n][m] = -1 * solved;
          change += 1;
        }
      }
    }
  } while (change != 0);

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
