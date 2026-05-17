#include "giasu.h"
#include <ctype.h>

//Các hàm xử lý dữ liệu đầu vào
void xoaKhoangTrangThua(char* str) {
    int i = 0, j = 0;
    while (str[i] == ' ') i++;
    while (str[i] != '\0') str[j++] = str[i++];
    str[j] = '\0';
    while (j > 0 && str[j - 1] == ' ') { str[j - 1] = '\0'; j--; }
}

void themGoiBuoiDay(char* buoi_day) {
    for (int i = 0; i < soLuongGoiBuoiDay; i++) {
        if (strcmp(danhSachGoiBuoiDay[i], buoi_day) == 0) return;
    }
    strcpy(danhSachGoiBuoiDay[soLuongGoiBuoiDay], buoi_day);
    soLuongGoiBuoiDay++;
}

void themTrinhDo(char* trinh_do) {
    for (int i = 0; i < soLuongTrinhDo; i++) {
        if (strcmp(danhSachTrinhDo[i], trinh_do) == 0) return;
    }
    strcpy(danhSachTrinhDo[soLuongTrinhDo], trinh_do);
    soLuongTrinhDo++;
}

void my_strlwr(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int timChuoi(const char* chuoi_goc, const char* chuoi_tim) {
    if (strlen(chuoi_tim) == 0) return 1;
    char goc[100], tim[100];
    strcpy(goc, chuoi_goc); strcpy(tim, chuoi_tim);
    my_strlwr(goc); my_strlwr(tim);
    return strstr(goc, tim) != NULL;
}

int timKhuVucChuan(const char* chuoi_goc, const char* chuoi_tim) {
    if (strlen(chuoi_tim) == 0) return 1;
    char goc[100], tim[100];
    strcpy(goc, chuoi_goc); strcpy(tim, chuoi_tim);
    my_strlwr(goc); my_strlwr(tim);
    char *ptr = strstr(goc, tim);
    if (ptr != NULL) {
        int do_dai = strlen(tim);
        char ky_tu_tiep_theo = ptr[do_dai];
        if (ky_tu_tiep_theo >= '0' && ky_tu_tiep_theo <= '9') return 0;
        return 1;
    }
    return 0;
}

int cmpRateGiamDan(const void *a, const void *b) {
    GiaSu *gs1 = *(GiaSu **)a;
    GiaSu *gs2 = *(GiaSu **)b;
    if (gs1->danh_gia < gs2->danh_gia) return 1;
    if (gs1->danh_gia > gs2->danh_gia) return -1;
    return 0;
}
