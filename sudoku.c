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
      scanf("%hd", &table[i][j]);
    }
  }
}

// not atomic
uint16_t clear_bits(uint16_t *x, uint16_t b) {
  uint16_t r = *x & b;
  *x &= ~b;
  return r;
}

void to_bit_representation(uint16_t table[9][9]) {
  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      table[n][m] =
          table[n][m] == 0 ? ((1 << 9) - 1) : (1 << (table[n][m] - 1));
    }
  }
}

void to_hooman_representation(uint16_t table[9][9]) {
  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      table[n][m] = stdc_count_ones(table[n][m]) == 1
                        ? stdc_trailing_zeros_ui(table[n][m]) + 1
                        : 0;
    }
  }
}

void solve_table(uint16_t table[9][9]) {
  for (int n = 0; n < 9; n++) {
    for (int m = 0; m < 9; m++) {
      assert(table[n][m] >= 0 && table[n][m] <= 9);
    }
  }

  to_bit_representation(table);

  bool change;
  do {
    change = false;

    for (int n = 0; n < 9; n++) {
      for (int m = 0; m < 9; m++) {
        const uint16_t bit = table[n][m];
        if (!stdc_has_single_bit(bit))
          continue;

        for (int i = 0; i < 9; i++) { // COLUMN
          if (i == n)
            continue;
          change |= clear_bits(&table[i][m], bit);
        }

        for (int j = 0; j < 9; j++) { // ROW
          if (j == m)
            continue;
          change |= clear_bits(&table[n][j], bit);
        }

        const int is = 3 * (int)(n / 3);
        const int js = 3 * (int)(m / 3);
        for (int i = is; i < is + 3; i++) { // SQUARE
          for (int j = js; j < js + 3; j++) {
            if (i == n && j == m)
              continue;
            change |= clear_bits(&table[i][j], bit);
          }
        }
      }
    }
  } while (change);

  to_hooman_representation(table);
}

int main(int, char *[]) {
  uint16_t table[9][9];
  read_table(table);
  solve_table(table);
  print_table(table);

  return 0;
}
