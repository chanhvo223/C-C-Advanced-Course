#ifndef __TRANSPORT_PRICE_H__
#define __TRANSPORT_PRICE_H__

#include "main.h"

typedef enum
{
    MAY_BAY_THUONG_MAI,
    MAY_BAY_TRUC_THANG,
    XE_KHACH,
    XE_MAY,
    TAU_THUY,
    CANO
} phuong_tien;

typedef union
{
    phuong_tien may_bay_thuong_mai;
    phuong_tien may_bay_truc_thang;
} hang_khong;

typedef union
{
    phuong_tien xe_khach;
    phuong_tien xe_may;
} bo;

typedef union
{
    phuong_tien tau_thuy;
    phuong_tien cano;
} thuy;

typedef union
{
    hang_khong duong_hang_khong;
    bo duong_bo;
    thuy duong_thuy;
    phuong_tien loai_phuong_tien;
} phuong_tien_giao_thong;

void chon_duong_hang_khong(phuong_tien_giao_thong *phuong_tien);
void chon_duong_thuy(phuong_tien_giao_thong *phuong_tien);
void chon_duong_bo(phuong_tien_giao_thong *phuong_tien);
void chon_phuong_tien_init(phuong_tien_giao_thong *phuong_tien);
void hien_thi_gia_tien(phuong_tien_giao_thong *phuong_tien);

#endif
