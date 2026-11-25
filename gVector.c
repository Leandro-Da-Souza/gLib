#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
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

  if (SIZE_MAX / capacity < memory_size) {
    return (gVector){0};
  }

  void *mem = malloc(cap * memory_size);

  if (mem == NULL) {
    return (gVector){0};
  }

  return (gVector){
      .size = 0, .capacity = cap, .memory_size = memory_size, .items = mem};
}

int main(int argc, char *argv[]) { return EXIT_SUCCESS; }
