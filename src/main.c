#include "../inc/data.h"
#include "../inc/game.h"

int main(void) {
    Data data = {0};

    if (init(&data)) {
        return 1;
    }
    if (run(&data)) {
        return 1;
    }
}
