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

void toolTest() {
  gVector tool = gVector_init(sizeof(int), 2);

  printf("capacity: %zu\n", tool.capacity);
  printf("memory: %zu\n", tool.memory_size);
  printf("size: %zu\n", tool.size);

  gVector_push(&tool, &(int){46});
  printf("capacity: %zu\n", tool.capacity);
  printf("memory: %zu\n", tool.memory_size);
  printf("size: %zu\n", tool.size);

  gVector_push(&tool, &(int){2});
  printf("capacity: %zu\n", tool.capacity);
  printf("memory: %zu\n", tool.memory_size);
  printf("size: %zu\n", tool.size);

  gVector_push(&tool, &(int){7});
  gVector_push(&tool, &(int){0});
  gVector_push(&tool, &(int){0});
  gVector_push(&tool, &(int){1});

  printf("capacity: %zu\n", tool.capacity);
  printf("memory: %zu\n", tool.memory_size);
  printf("size: %zu\n", tool.size);

  for (int i = 0; i < tool.size; i++) {
    printf("item %d: %d\n", i, ((int *)tool.items)[i]);
  }
}

int main(int argc, char *argv[]) {
  toolTest();
  return EXIT_SUCCESS;
}
