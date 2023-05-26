#include "transportPrice.h"

void chon_duong_hang_khong(phuong_tien_giao_thong *phuong_tien)
{
    int user_input;
    printf("1: may bay thuong mai\n");
    printf("2: may bay truc thang\n");
    printf("Chon phuong thuc di chuyen: ");
    scanf("%d", &user_input);
    switch (user_input)
    {
    case 1:
        phuong_tien->duong_hang_khong.may_bay_thuong_mai = MAY_BAY_THUONG_MAI;
        break;
    case 2:
        phuong_tien->loai_phuong_tien = MAY_BAY_TRUC_THANG;
        break;

    default:
        break;
    }
}

void chon_duong_thuy(phuong_tien_giao_thong *phuong_tien)
{
    int user_input;
    printf("1: tau thuy\n");
    printf("2: cano\n");
    printf("Chon phuong thuc di chuyen: ");
    scanf("%d", &user_input);
    switch (user_input)
    {
    case 1:
        phuong_tien->loai_phuong_tien = TAU_THUY;
        break;
    case 2:
        phuong_tien->loai_phuong_tien = CANO;
        break;

    default:
        break;
    }
}

void chon_duong_bo(phuong_tien_giao_thong *phuong_tien)
{
    int user_input;
    printf("1: xe khach\n");
    printf("2: xe may\n");
    printf("Chon phuong thuc di chuyen: ");
    scanf("%d", &user_input);
    switch (user_input)
    {
    case 1:
        phuong_tien->loai_phuong_tien = XE_KHACH;
        break;
    case 2:
        phuong_tien->loai_phuong_tien = XE_MAY;
        break;

    default:
        break;
    }
}
void chon_phuong_tien_init(phuong_tien_giao_thong *phuong_tien)
{
    int user_input = 0;
    printf("1: duong hang khong\n");
    printf("2: duong thuy\n");
    printf("3: duong bo\n");
    printf("Chon phuong thuc di chuyen: ");
    scanf("%d", &user_input);
    switch (user_input)
    {
    case 1:
        chon_duong_hang_khong(phuong_tien);
        break;
    case 2:
        chon_duong_thuy(phuong_tien);
        break;
    case 3:
        chon_duong_bo(phuong_tien);
        break;

    default:
        break;
    }
}

void hien_thi_gia_tien(phuong_tien_giao_thong *phuong_tien)
{
    switch (phuong_tien->loai_phuong_tien)
    {
    case MAY_BAY_THUONG_MAI:
        printf("May bay thuong mai 100.000vnd\n");
        break;
    case MAY_BAY_TRUC_THANG:
        printf("May bay truc thang 80.000vnd\n");
        break;
    case XE_KHACH:
        printf("Xe khach 60.000vnd\n");
        break;
    case XE_MAY:
        printf("xe may 10.000vnd\n");
        break;
    case TAU_THUY:
        printf("tau thuy 40.000vnd\n");
        break;
    case CANO:
        printf("cano 20.000vnd\n");
        break;

    default:
        break;
    }
}
