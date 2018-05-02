#include <stdio.h>
#include "file.h"

int main() {
    order *test_order = create_order();
    read_from_console(&test_order);
    destroy_order(test_order);
    return 0;
}