#include <stdio.h>
#include <assert.h>
#include "../src/tshirts.h"

void testTShirtSize() {
    assert(size(37) == 'S');
    assert(size(38) == 'S');
    assert(size(40) == 'M');
    assert(size(42) == 'M');
    assert(size(43) == 'L');
    assert(size(44) == 'L');
    
    // This will fail because size 41 is not properly handled in the implementation
    assert(size(41) == 'M'); // Should expose the bug
}

int main() {
    testTShirtSize();
    printf("All tshirt tests passed\n");
    return 0;
}