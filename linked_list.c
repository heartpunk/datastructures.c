#include <stdlib.h>
#include <stdio.h>

typedef struct node_s {
  int value;
  struct node_s *next;
} node_t;

node_t *alloc_node(int value, node_t *next) {
  node_t *node;
  if (!(node = malloc(sizeof(node_t)))) return NULL;
  node->value = value;
  node->next = next;
  return node;
}

int main(int *argc, char *argv[]) {
  int i;
  node_t *first;
  node_t *previous;
  for (i = 0; i <= 100; i++) {
    node_t *current = alloc_node(i, NULL);

    if (previous) previous->next = current;
    if (0 == i) first = current;

    previous = current;
  }

  node_t* current = first;
  while (1) {
    printf("%d\n", current->value);
    if (!(current = current->next)) break;
  }

  return 0;
}
