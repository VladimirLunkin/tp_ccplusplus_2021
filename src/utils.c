#include "utils/utils.h"

int private_ok_value = 2;

int widget_ok(int a, int b) {
    if (a > 5) {
        return 3;
    }
    return a + b == private_ok_value;
}
