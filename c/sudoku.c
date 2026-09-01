#include <assert.h>
#include <stdbit.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 9
#define COLS 9
#define INR_ROWS 3
#define INR_COLS 3
#define MAX_FIELD 9
static_assert(ROWS % INR_ROWS == 0, "BAD INR_ROWS");
static_assert(COLS % INR_COLS == 0, "BAD INR_COLS");

void print_table(uint16_t table[ROWS][COLS]) {
  for (int n = 0; n < ROWS; n++) {
    for (int m = 0; m < COLS; m++) {
      printf("%d%s", table[n][m], m < (COLS - 1) ? " " : "\n");
    }
  }
}

void read_table(uint16_t table[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      scanf("%hd", &table[i][j]);
      if (table[i][j] > MAX_FIELD) {
        fprintf(stderr, "bad input for row %d col %d (%d)", i + 1, j + 1,
                table[i][j]);
        exit(1);
      }
    }
  }
}

// not atomic
uint16_t clear_bits(uint16_t *x, uint16_t b) {
  uint16_t r = *x & b;
  *x &= ~b;
  return r;
}

void to_bit_representation(uint16_t table[ROWS][COLS]) {
  for (int n = 0; n < ROWS; n++) {
    for (int m = 0; m < COLS; m++) {
      table[n][m] =
          table[n][m] == 0 ? ((1 << 9) - 1) : (1 << (table[n][m] - 1));
    }
  }
}

void to_hooman_representation(uint16_t table[ROWS][COLS]) {
  for (int n = 0; n < ROWS; n++) {
    for (int m = 0; m < COLS; m++) {
      table[n][m] = stdc_count_ones(table[n][m]) == 1
                        ? stdc_trailing_zeros_ui(table[n][m]) + 1
                        : 0;
    }
  }
}

bool _clear_row(uint16_t table[ROWS][COLS], int n, int m) {
  bool change = false;
  for (int j = 0; j < COLS; j++) {
    if (j == m)
      continue;
    change |= clear_bits(&table[n][j], table[n][m]);
  }
  return change;
}

bool _clear_col(uint16_t table[ROWS][COLS], int n, int m) {
  bool change = false;
  for (int i = 0; i < ROWS; i++) { // COLUMN
    if (i == n)
      continue;
    change |= clear_bits(&table[i][m], table[n][m]);
  }
  return change;
}

bool _clear_sqr(uint16_t table[ROWS][COLS], int n, int m) {
  bool change = false;
  const int is = INR_ROWS * (int)(n / INR_ROWS);
  const int js = INR_COLS * (int)(m / INR_COLS);
  for (int i = is; i < is + INR_ROWS; i++) { // SQUARE
    for (int j = js; j < js + INR_COLS; j++) {
      if (i == n && j == m)
        continue;
      change |= clear_bits(&table[i][j], table[n][m]);
    }
  }
  return change;
}

bool _clear_row_col_square(uint16_t table[ROWS][COLS], int n, int m) {
  bool change = false;
  change |= _clear_row(table, n, m);
  change |= _clear_col(table, n, m);
  change |= _clear_sqr(table, n, m);
  return change;
}

bool solve_bit_table_one_pass(uint16_t table[ROWS][COLS]) {
  bool change = false;
  for (int n = 0; n < ROWS; n++) {
    for (int m = 0; m < COLS; m++) {
      if (!stdc_has_single_bit(table[n][m]))
        continue;
      change |= _clear_row_col_square(table, n, m);
    }
  }
  return change;
}

void solve_bit_table(uint16_t table[ROWS][COLS]) {
  while (solve_bit_table_one_pass(table)) {
  };
}

void solve_table(uint16_t table[ROWS][COLS]) {
  to_bit_representation(table);
  solve_bit_table(table);
  to_hooman_representation(table);
}

int main(int, char *[]) {
  uint16_t table[ROWS][COLS];
  read_table(table);
  solve_table(table);
  print_table(table);

  return 0;
}
