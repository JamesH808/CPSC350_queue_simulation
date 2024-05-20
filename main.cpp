#include "serviceCenter.h"


int main(int argc, char **argv) {

    serviceCenter center;
    center.readFile(argv[1]);

    return 0;
}