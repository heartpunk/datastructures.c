#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int heap_array[(1 << 5) - 1];
int swapped[2];

void randomize_array (int *array, size_t size) {
  int i;
  for (i = 0; i < size; i++) { array[i] = random() % 1000; }
}

void swap (int *first, int *second) {
  int tmp;
  memcpy(&tmp, first, sizeof(int));
  memcpy(first, second, sizeof(int));
  memcpy(second, &tmp, sizeof(int));
}

void downheapify (int *array, size_t size, int current) {
  while (1) {
    int largest = current;
    int right = right_child_index(current);
    int left = left_child_index(current);

    if (right < size && array[right] > array[largest]) {
      largest = right;
    }
    if (left < size && array[left] > array[largest]) {
      largest = left;
    }

    if (largest == current) { break; }
    else {
      swap(&array[current], &array[largest]);
      current = largest;
    }
  }
}

void heapify (int *array, size_t size) {
  int i;
  for (i = (size - 1) / 2 - 1; i >= 0; i--) { downheapify(array, size, i); }
}

int parent_index (int index) { return floor(((float )index) - 1.0/2); };

int left_child_index (int index) { return 2 * index + 1; };
int right_child_index (int index) { return 2 * index + 2; };

void inspect_array(int *array, size_t size) {
  int i, j, k;
  for (j = 1; j < size; j = j * 2 ) {
    int offset = (((size/2-j) * 2 - (size/2-j))*15)/2;
    for (k = 0; k < offset; k++) { printf(" "); };
    for (k = j; k/2 < j; k++) {i = k-1; if ((i == swapped[0]) || (i == swapped[1])) { printf("\e[31;1m"); }; printf("%02d: %010d\e[0m ", i, array[i]); };
    printf("\n\n\n\n\n");
  };
  printf("\n");
}

int verify_heap(int *array, size_t size) {
  int i;
  for (i = 0; left_child_index(i) < size; i++) { if (array[i] < array[left_child_index(i)] || array[i] < array[right_child_index(i)]) { return 0; } }
  return 1;
}

int main (int argc, char *argv[]) {
  size_t heap_size = sizeof(heap_array) / sizeof(int);
  int i;

  for (i = 0; i < 1000000000; i++) {
    randomize_array(heap_array, heap_size);
    heapify(heap_array, heap_size);
    if (!verify_heap(heap_array, heap_size)) { return(1); }
    if (i % 1000000 == 0) { printf("%d\n", i); }
  }

  return 0;
}
