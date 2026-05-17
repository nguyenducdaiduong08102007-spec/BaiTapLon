#include "giasu.h"

// Thiet ke ban cho giao dien
void inBangGiaSu(GiaSu* arr[], int n) {
    if (n == 0) {
        printf(RED "\n=> Khong tim thay gia su nao phu hop!\n" RESET);
        return;
    }
    printf(B_GREEN"\n=> Tong cong tim thay: %d gia su phu hop voi dien kien tren.\n"RESET, n);
    printf(B_PINK"\n=======================================================================================================================\n");
    printf("| %-5s | %-22s | %-10s | %-10s | %-10s | %-15s | %-10s | %-4s |\n", 
           "ID", "Ho va Ten", "Mon", "Khu Vuc", "Trinh Do", "Buoi Day", "Hoc Phi", "Rate");
    printf("=======================================================================================================================\n"RESET);
    for (int i = 0; i < n; i++) {
        printf("| %-5d | %-22s | %-10s | %-10s | %-10s | %-15s | %-10d | %-4.1f |\n",
               arr[i]->id, arr[i]->ten, arr[i]->mon_hoc, arr[i]->khu_vuc, arr[i]->trinh_do, 
               arr[i]->buoi_day, arr[i]->hoc_phi, arr[i]->danh_gia);
    }
    printf("=======================================================================================================================\n");
}

int chucNangLoc() {
    char mon[50] = "", kv[100] = "", td[100] = "", buoi[100] = "";
    int max_hp = 0;
    char buffer[100];

    printf(CYAN"\n--- NHAP THONG TIN LOC (Nhan Enter de bo qua tieu chi khong can thiet) ---\n"RESET);
    
    printf(" - Mon hoc: "); gets(mon); xoaKhoangTrangThua(mon);
    printf(" - Khu vuc (VD: Quan 1): "); gets(kv); xoaKhoangTrangThua(kv);
    
    printf(YELLOW"\n   [Chon Trinh Do]\n"RESET);
    for (int i = 0; i < soLuongTrinhDo; i++) printf("   %d. %s\n", i + 1, danhSachTrinhDo[i]);
    printf("   0. Bo qua tieu chi nay\n");
    printf("   -> Lua chon cua ban (0-%d): ", soLuongTrinhDo);
    gets(buffer); int chonTd = atoi(buffer);
    if (chonTd > 0 && chonTd <= soLuongTrinhDo) strcpy(td, danhSachTrinhDo[chonTd - 1]);
    else strcpy(td, "");
    if (strlen(td) > 0) printf("   => Da chon: %s\n", td);

    printf(YELLOW"\n   [Chon Goi Buoi Day]\n"RESET);
    for (int i = 0; i < soLuongGoiBuoiDay; i++) printf("   %d. %s\n", i + 1, danhSachGoiBuoiDay[i]);
    printf("   0. Bo qua tieu chi nay\n");
    printf("   -> Lua chon cua ban (0-%d): ", soLuongGoiBuoiDay);
    gets(buffer); int chonBuoi = atoi(buffer);
    if (chonBuoi > 0 && chonBuoi <= soLuongGoiBuoiDay) strcpy(buoi, danhSachGoiBuoiDay[chonBuoi - 1]);
    else strcpy(buoi, "");
    if (strlen(buoi) > 0) printf("   => Da chon: %s\n", buoi);

    printf("\n - Hoc phi toi da (VND - Nhap 0 hoac Enter de bo qua): ");
    gets(buffer); max_hp = atoi(buffer);

    soLuongKetQua = 0;
    Node* current = head;
    while (current != NULL) {
        int ok = 1;
        if (strlen(mon) > 0 && !timChuoi(current->data.mon_hoc, mon)) ok = 0;
        if (strlen(kv) > 0 && !timKhuVucChuan(current->data.khu_vuc, kv)) ok = 0;
        if (strlen(td) > 0 && !timChuoi(current->data.trinh_do, td)) ok = 0;
        if (strlen(buoi) > 0 && !timChuoi(current->data.buoi_day, buoi)) ok = 0;
        if (max_hp > 0 && current->data.hoc_phi > max_hp) ok = 0;

        if (ok && soLuongKetQua < MAX_RESULTS) ketQuaHienTai[soLuongKetQua++] = &(current->data);
        current = current->next;
    }
    
    if (soLuongKetQua > 0) {
        qsort(ketQuaHienTai, soLuongKetQua, sizeof(GiaSu*), cmpRateGiamDan);
        inBangGiaSu(ketQuaHienTai, soLuongKetQua);
        if (xemChiTietGiaSu() == 1) return 1;
    } else {
        inBangGiaSu(ketQuaHienTai, 0);
        system("pause");
    }
    return 0;
}