#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_CAPACITY 128

typedef struct {
  size_t size;
  size_t capacity;
  size_t memory_size;
  void *items;
} gVector;

gVector gVector_init(size_t memory_size, size_t capacity) {
  if (memory_size == 0) {
    return (gVector){0};
  }

  size_t cap = capacity == 0 ? INITIAL_CAPACITY : capacity;

  if (SIZE_MAX / cap < memory_size) {
    return (gVector){0};
  }

  void *mem = malloc(cap * memory_size);

  if (mem == NULL) {
    return (gVector){0};
  }

  return (gVector){
      .size = 0, .capacity = cap, .memory_size = memory_size, .items = mem};
}

bool gVector_push(gVector *v, const void *element) {
  if (v == NULL || element == NULL || v->items == NULL) {
    return false;
  }

  if (v->size == v->capacity) {
    if (SIZE_MAX / 2 < v->capacity) {
      return false;
    }

    size_t new_capacity = v->capacity * 2;

    if (SIZE_MAX / new_capacity < v->memory_size) {
      return false;
    }

    void *mem = realloc(v->items, (new_capacity * v->memory_size));

    if (mem == NULL) {
      return false;
    }

    v->items = mem;
    v->capacity = new_capacity;
  }

  size_t byte_offset = v->size * v->memory_size;
  unsigned char *destination = (unsigned char *)v->items + byte_offset;

  memcpy(destination, element, v->memory_size);
  v->size++;

  return true;
}

bool gVector_pop(gVector *v, void *out) {
  if (v == NULL || out == NULL || v->items == NULL || v->size == 0) {
    return false;
  }

  size_t byte_offset = (v->size - 1) * v->memory_size;

  unsigned char *removed = (unsigned char *)v->items + byte_offset;

  memcpy(out, removed, v->memory_size);
  v->size--;
  return true;
}

void pushTest() {
  gVector push = gVector_init(sizeof(int), 2);

  printf("capacity: %zu\n", push.capacity);
  printf("memory: %zu\n", push.memory_size);
  printf("size: %zu\n", push.size);

  gVector_push(&push, &(int){46});
  printf("capacity: %zu\n", push.capacity);
  printf("memory: %zu\n", push.memory_size);
  printf("size: %zu\n", push.size);

  gVector_push(&push, &(int){2});
  printf("capacity: %zu\n", push.capacity);
  printf("memory: %zu\n", push.memory_size);
  printf("size: %zu\n", push.size);

  gVector_push(&push, &(int){7});
  gVector_push(&push, &(int){0});
  gVector_push(&push, &(int){0});
  gVector_push(&push, &(int){1});

  printf("capacity: %zu\n", push.capacity);
  printf("memory: %zu\n", push.memory_size);
  printf("size: %zu\n", push.size);

  for (int i = 0; i < push.size; i++) {
    printf("item %d: %d\n", i, ((int *)push.items)[i]);
  }

  free(push.items);
}

void popTest() {
  gVector v = gVector_init(sizeof(int), 5);

  for (int i = 0; i < 5; i++) {
    gVector_push(&v, &(int){i});
    printf("vector item %d: %d\n", i, ((int *)v.items)[i]);
  }

  int x;

  gVector_pop(&v, &x);

  printf("popped item: %d\n", x);

  for (int i = 0; i < v.size; i++) {
    printf("vector item %d: %d\n", i, ((int *)v.items)[i]);
  }

  gVector_push(&v, &(int){99});

  for (int i = 0; i < v.size; i++) {
    printf("vector item %d: %d\n", i, ((int *)v.items)[i]);
  }

  int y;

  while (gVector_pop(&v, &y)) {
    printf("Popped: %d\n", y);
  }

  for (int i = 0; i < v.size; i++) {
    printf("vector item %d: %d\n", i, ((int *)v.items)[i]);
  }

  int z;
  bool pop_value;

  pop_value = gVector_pop(&v, &z);
  printf("%d\n", pop_value);

  free(v.items);
}

int main(int argc, char *argv[]) {
  // pushTest();
  popTest();
  return EXIT_SUCCESS;
}
