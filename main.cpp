#include "src/bulk_proxy.h"
#include <iostream>

int main(int argc, char **argv) {
    int bulkSize = 1;
    if (argc > 1) {
        if (int bs = std::atoi(argv[1]); bs != 0) {
            bulkSize = bs;
        }
    }
    BulkProxy bulk(bulkSize);
    std::cin >> bulk;
    return 0;
}
