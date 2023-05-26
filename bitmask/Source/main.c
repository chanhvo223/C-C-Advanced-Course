#include "main.h"

int main()
{
    uint8_t GIO_HANG;
    addProduct(&GIO_HANG, AO | QUAN | DEP | MAT_KINH);
    checkIfProductExist(GIO_HANG, AO | QUAN | DEP | MAT_KINH);
    removeProduct(&GIO_HANG, AO | DEP);
    checkIfProductExist(GIO_HANG, AO | QUAN | DEP | MAT_KINH);
    return 0;
}
