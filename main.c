
#include "shadow_dynamic_array.h"

int main() {
    float* numbers = nullptr;

    array_push(numbers, 3);
    array_push(numbers, 2);

    numbers[0] = 3;

    return 0;
}