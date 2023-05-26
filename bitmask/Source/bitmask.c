#include "bitmask.h"

// uint8_t GIO_HANG;

/**
 * @brief Add products to cart
 *
 * @param gio_hang
 * @param ten_do_dung
 */
void addProduct(uint8_t *gio_hang, DO_DUNG_CA_NHAN ten_do_dung)
{
    printf("Them san pham\n");
    *gio_hang |= ten_do_dung;
}

void removeProduct(uint8_t *gio_hang, DO_DUNG_CA_NHAN ten_do_dung)
{
    printf("Xoa san pham\n");
    *gio_hang &= ~ten_do_dung;
}

/**
 * @brief Show everything in cart
 *
 * @param gio_hang
 */
void showCartProduct(uint8_t gio_hang)
{
    printf("Cart in binary: ");
    for (int bit = 7; bit >= 0; bit--)
    {
        printf("%d", (gio_hang >> bit) & 1);
    }
    printf("\n");
    /*
    DEP = 1 << 0,      // 0b0000.0001
    AO = 1 << 1,       // 0b0000.0010
    QUAN = 1 << 2,     // 0b0000.0100
    TAT = 1 << 3,      // 0b0000.1000
    VONG_TAY = 1 << 4, // 0b0001.0000
    NON = 1 << 5,      // 0b0001.0000
    MAT_KINH = 1 << 6, // 0b0100.0000
    GIAY = 1 << 7      // 0b1000.0000
    */
    if ((gio_hang & DEP) != 0)
    {
        printf("Have: dep\n");
    }
    if ((gio_hang & AO) != 0)
    {
        printf("Have: AO\n");
    }
    if ((gio_hang & QUAN) != 0)
    {
        printf("Have: QUAN\n");
    }
    if ((gio_hang & TAT) != 0)
    {
        printf("Have: TAT\n");
    }
    if ((gio_hang & VONG_TAY) != 0)
    {
        printf("Have: VONG_TAY\n");
    }
    if ((gio_hang & NON) != 0)
    {
        printf("Have: NON\n");
    }
    if ((gio_hang & MAT_KINH) != 0)
    {
        printf("Have: MAT_KINH\n");
    }
    if ((gio_hang & GIAY) != 0)
    {
        printf("Have: GIAY\n");
    }
}

/**
 * @brief Check if product is in the cart?
 *
 * @param gio_hang
 * @param ten_do_dung
 */
void checkIfProductExist(uint8_t gio_hang, DO_DUNG_CA_NHAN ten_do_dung)
{
    showCartProduct(gio_hang & ten_do_dung);
}
