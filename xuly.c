#include "giasu.h"
#include <ctype.h>
#include <string.h>

void xoaKhoangTrangThua(char* str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

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

int nhapLuaChonThanhCong(int min, int max) {
    char luongNhap[100];
    int giaTriSo;
    int hopLe = 0;
    char thongBaoLoi[150] = ""; 

    while (!hopLe) {
        if (strlen(thongBaoLoi) > 0) {
            printf("%s\n", thongBaoLoi);
        } else {
            printf("\n"); 
        }

        printf(" -> Lua chon cua ban (%d-%d): ", min, max);
        if (fgets(luongNhap, sizeof(luongNhap), stdin) == NULL) {
            continue;
        }

        int len = strlen(luongNhap);
        if (len > 0 && luongNhap[len - 1] == '\n') {
            luongNhap[len - 1] = '\0';
            len--;
        }

        if (strlen(thongBaoLoi) > 0) {
            printf("\033[A\033[K\033[A\033[K"); 
        } else {
            printf("\033[A\033[K"); 
        }

        if (len == 0) {
            strcpy(thongBaoLoi, RED " [!] Khong duoc de trong! Vui long nhap lai." RESET);
            continue;
        }

        int dinh_loi = 0;
        for (int i = 0; i < len; i++) {
            if (luongNhap[i] < '0' || luongNhap[i] > '9') {
                dinh_loi = 1;
                break;
            }
        }

        if (dinh_loi) {
            strcpy(thongBaoLoi, RED " [!] Sai dinh dang! Menu chi nhan so nguyen." RESET);
            continue;
        }

        giaTriSo = atoi(luongNhap);

        if (giaTriSo < min || giaTriSo > max) {
            strcpy(thongBaoLoi, RED " [!] Lua chon khong ton tai trong menu! Vui long nhap lai." RESET);
            continue;
        }

        hopLe = 1;
    }
    printf("\033[K"); 
    return giaTriSo;
}

int laSDTHopLe(const char* sdt) {
    int len = strlen(sdt);
    if (len < 10 || len > 11) return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(sdt[i])) return 0;
    }
    return 1;
}

int TenHopLe(const char* ten) {
    int len = strlen(ten);
    
    if (len < 3) return 0; 

    if (ten[0] == ' ' || ten[len - 1] == ' ') return 0;

    int demKhoangTrang = 0;

    for (int i = 0; i < len; i++) {
        if (ten[i] == ' ' && ten[i+1] == ' ') return 0;

        if (ten[i] == ' ') {
            demKhoangTrang++;
        } 
        else {
            if (isdigit((unsigned char)ten[i])) return 0;
            
            if (ispunct((unsigned char)ten[i])) return 0;
        }
    }

    if (demKhoangTrang == 0) return 0; 

    return 1; 
}

void nhapTenHopLe_UI(char* ketQua, const char* loiNhac) {
    char thongBaoLoi[200] = ""; 
    while (1) {
        if (strlen(thongBaoLoi) > 0) {
            printf("%s\n", thongBaoLoi);
        } else {
            printf("\n"); 
        }

        printf("%s", loiNhac); 
        fgets(ketQua, 100, stdin); 
        
        if (strlen(thongBaoLoi) > 0) {
            printf("\033[A\033[K\033[A\033[K"); 
        } else {
            printf("\033[A\033[K");             
        }

        xoaKhoangTrangThua(ketQua);
        
        if (TenHopLe(ketQua) == 1) {
            printf("%s%s\n", loiNhac, ketQua); 
            break; 
        }
        
        strcpy(thongBaoLoi, RED " [!] Ten sai quy tac! Chi duoc nhap chu, co dau cach, khong chua so/ki tu." RESET);
    }
}

int nhapIDGiaSuHopLe() {
    char luongNhap[100];
    int idSo;
    int hopLe = 0;
    char thongBaoLoi[150] = ""; 

    while (!hopLe) {
        if (strlen(thongBaoLoi) > 0) printf("%s\n", thongBaoLoi);
        else printf("\n"); 

        printf(" -> Nhap ID gia su (Nhap 0 de thoat): ");
        if (fgets(luongNhap, sizeof(luongNhap), stdin) == NULL) continue;

        int len = strlen(luongNhap);
        if (len > 0 && luongNhap[len - 1] == '\n') { luongNhap[len - 1] = '\0'; len--; }

        if (strlen(thongBaoLoi) > 0) printf("\033[A\033[K\033[A\033[K"); 
        else printf("\033[A\033[K"); 

        if (len == 0) { strcpy(thongBaoLoi, RED " [!] Khong duoc de trong!" RESET); continue; }

        int dinh_loi = 0;
        for (int i = 0; i < len; i++) {
            if (luongNhap[i] < '0' || luongNhap[i] > '9') { dinh_loi = 1; break; }
        }

        if (dinh_loi) { strcpy(thongBaoLoi, RED " [!] ID phai la so nguyen!" RESET); continue; }

        idSo = atoi(luongNhap);
        hopLe = 1; 
    }
    printf("\033[K"); 
    return idSo;
}

int nhapIDAdminHopLe() {
    char luongNhap[100];
    int idSo;
    int hopLe = 0;
    char thongBaoLoi[150] = ""; 

    while (!hopLe) {
        if (strlen(thongBaoLoi) > 0) printf("%s\n", thongBaoLoi);
        else printf("\n"); 

        printf(" -> Nhap ID can can thiep: (0: Thoat | Phim W: Trang truoc | Phim S: Trang sau): ");
        if (fgets(luongNhap, sizeof(luongNhap), stdin) == NULL) continue;

        int len = strlen(luongNhap);
        if (len > 0 && luongNhap[len - 1] == '\n') { luongNhap[len - 1] = '\0'; len--; }

        if (strlen(thongBaoLoi) > 0) printf("\033[A\033[K\033[A\033[K"); 
        else printf("\033[A\033[K"); 

        if (len == 0) { strcpy(thongBaoLoi, RED " [!] Khong duoc de trong!" RESET); continue; }

        if (len == 1) {
            if (luongNhap[0] == 'w' || luongNhap[0] == 'W') return -2; 
            if (luongNhap[0] == 's' || luongNhap[0] == 'S') return -1; 
        }

        int dinh_loi = 0;
        for (int i = 0; i < len; i++) {
            if (luongNhap[i] < '0' || luongNhap[i] > '9') { dinh_loi = 1; break; }
        }

        if (dinh_loi) { strcpy(thongBaoLoi, RED " [!] ID phai la so, hoac xai phim W / S!" RESET); continue; }

        idSo = atoi(luongNhap);
        hopLe = 1; 
    }
    printf("\033[K"); 
    return idSo;
}

int nhapLuaChonTrang(int min, int max) {
    char luongNhap[100];
    while (1) {
        if (fgets(luongNhap, sizeof(luongNhap), stdin) == NULL) continue;
        int len = strlen(luongNhap);
        if (len > 0 && luongNhap[len - 1] == '\n') { luongNhap[len - 1] = '\0'; len--; }
        
        if (len == 0) {
            printf("\033[A\033[K -> Nhap lua chon (%d-%d, W: Len, S: Xuong): ", min, max); continue;
        }
        
        if (len == 1) {
            if (luongNhap[0] == 'w' || luongNhap[0] == 'W') return -2; 
            if (luongNhap[0] == 's' || luongNhap[0] == 'S') return -1; 
        }
        
        int hopLe = 1;
        for (int i = 0; i < len; i++) {
            if (luongNhap[i] < '0' || luongNhap[i] > '9') { hopLe = 0; break; }
        }
        if (hopLe) {
            int val = atoi(luongNhap);
            if (val >= min && val <= max) return val;
        }
        
        printf("\033[A\033[K" RED " [!] Loi! Nhap tu %d den %d hoac W/S: " RESET, min, max);
    }
}
