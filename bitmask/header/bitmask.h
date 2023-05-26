#ifndef __BIT_MASK_H_
#define __BIT_MASK_H_

#include "main.h"

typedef enum
{
    DEP = 1 << 0,      // 0b0000.0001
    AO = 1 << 1,       // 0b0000.0010
    QUAN = 1 << 2,     // 0b0000.0100
    TAT = 1 << 3,      // 0b0000.1000
    VONG_TAY = 1 << 4, // 0b0001.0000
    NON = 1 << 5,      // 0b0001.0000
    MAT_KINH = 1 << 6, // 0b0100.0000
    GIAY = 1 << 7      // 0b1000.0000
} DO_DUNG_CA_NHAN;

void addProduct(uint8_t *gio_hang, DO_DUNG_CA_NHAN ten_do_dung);
void removeProduct(uint8_t *gio_hang, DO_DUNG_CA_NHAN ten_do_dung);
void showCartProduct(uint8_t gio_hang);
void checkIfProductExist(uint8_t gio_hang, DO_DUNG_CA_NHAN ten_do_dung);

#endif