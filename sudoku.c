#include <assert.h>
#include <stdbit.h>
#include <stdint.h>
#include <stdio.h>

void print_table(uint16_t table[9][9]) {
  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      printf("%d%s", table[n][m], m < 8 ? " " : "\n");
    }
  }
}

void read_table(uint16_t table[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      scanf("%d", &table[i][j]);
    }
  }
}

void solve_table(uint16_t table[9][9]) {
  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      assert(table[n][m] >= 0 && table[n][m] <= 9);
    }
  }

  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      table[n][m] =
          table[n][m] == 0 ? ((1 << 9) - 1) : (1 << (table[n][m] - 1));
    }
  }

  int change;
  do {
    change = 0;

    for (int n = 0; n < 9; n++) {
      for (int m = 0; m < 9; m++) {
        const uint16_t bit = table[n][m];
        if (stdc_count_ones(bit) != 1) continue;

        for (int i = 0; i < 9; i++) {  // COLUMN
          if (i == n) continue;
          if (table[i][m] & bit) {
            table[i][m] = table[i][m] - bit;
            change = 1;
          }
        }

        for (int j = 0; j < 9; j++) {  // ROW
          if (j == m) continue;
          if (table[n][j] & bit) {
            table[n][j] = table[n][j] - bit;
            change = 1;
          }
        }

        const int is = 3 * (int)(n / 3);
        const int js = 3 * (int)(m / 3);
        for (int i = is; i < is + 3; i++) {  // SQUARE
          for (int j = js; j < js + 3; j++) {
            if (i == n && j == m) continue;
            if (table[i][j] & bit) {
              table[i][j] = table[i][j] - bit;
              change = 1;
            }
          }
        }
      }
    }
  } while (change != 0);

  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      table[n][m] = stdc_count_ones(table[n][m]) == 1
                        ? stdc_trailing_zeros_ui(table[n][m]) + 1
                        : 0;
    }
  }
}

int main(int argc, char* argv[]) {
  uint16_t table[9][9];
  read_table(table);
  solve_table(table);
  print_table(table);

  return 0;
}
