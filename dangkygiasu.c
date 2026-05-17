#include "giasu.h"

//Chức năng dành cho gia sư muốn apply vào hệ thống
void dangKyGiaSu() {
    GiaSu gs;
    char buffer[100];
    printf(PURPLE"\n============================================\n");
    printf("           DANG KY HO SO GIA SU\n");
    printf("============================================\n"RESET);

    int max_id = 0;
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data.id > max_id) max_id = temp->data.id;
        temp = temp->next;
    }
    gs.id = max_id + 1;
    if (gs.id < 1000) gs.id = 1000; 

    printf(" - Ho va Ten: "); gets(gs.ten); xoaKhoangTrangThua(gs.ten);
    printf(" - Mon day (VD: Toan, Ly...): "); gets(gs.mon_hoc); xoaKhoangTrangThua(gs.mon_hoc);
    printf(" - Khu vuc (VD: Quan 1, Thu Duc...): "); gets(gs.khu_vuc); xoaKhoangTrangThua(gs.khu_vuc);
    printf(" - Trinh do (VD: Sinh vien, Thac si...): "); gets(gs.trinh_do); xoaKhoangTrangThua(gs.trinh_do);
    printf(" - Buoi day ranh (VD: Thu 2 - 4 - 6): "); gets(gs.buoi_day); xoaKhoangTrangThua(gs.buoi_day);
    printf(" - So dien thoai: "); gets(gs.sdt); xoaKhoangTrangThua(gs.sdt);
    printf(" - Email: "); gets(gs.email); xoaKhoangTrangThua(gs.email);

    printf(" - Hoc phi yeu cau (VND/thang): "); gets(buffer); gs.hoc_phi = atoi(buffer);
    gs.danh_gia = 5.0; 

    FILE *f = fopen("giasu.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d, %s, %s, %s, %.1f, %s, %s, %s, %s, %d\n",
                gs.id, gs.ten, gs.mon_hoc, gs.khu_vuc, gs.danh_gia,
                gs.trinh_do, gs.sdt, gs.email, gs.buoi_day, gs.hoc_phi);
        fclose(f);
        printf(GREEN "\n=> CHUC MUNG! Dang ky thanh cong. ID cua ban la: %d\n" RESET, gs.id);
        system("pause");
        docFile(); 
    } else {
        printf("\n=> LOI: Khong the mo file de ghi du lieu!\n");
    }
}