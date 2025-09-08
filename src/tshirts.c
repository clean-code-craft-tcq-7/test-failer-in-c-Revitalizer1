#include <assert.h>
#include "tshirts.h"

char size(int cms) {
    char sizeName = '\0';
    if(cms < 38) {
        sizeName = 'S';
    } else if(cms >= 38 && cms < 42) {
        sizeName = 'M';
    } else if(cms >= 43) {
        sizeName = 'L';
    }
    return sizeName;
}

int main() {
    printf("T-shirt size classifier ready for use.\n");
    printf("Example: Size for 37cm = %c\n", size(37));
    printf("Example: Size for 40cm = %c\n", size(40));
    printf("Example: Size for 43cm = %c\n", size(43));
    return 0;
}


