#ifndef GIASU_H
#define GIASU_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RESULTS 150

//Bản màu ANSI mà tụi em sử dụng cho menu mặc dù define nhiều màu nhưng mà menu của của bọn em không dùng hết
#define RESET       "\033[0m"   // Trả về mặc định

// 1. Màu dành cho chữ (Text)
#define BLACK       "\033[30m"  // Đen
#define RED         "\033[31m"  // Đỏ
#define GREEN       "\033[32m"  // Xanh lá
#define YELLOW      "\033[33m"  // Vàng
#define BLUE        "\033[34m"  // Xanh dương
#define PURPLE      "\033[35m"  // Tím
#define CYAN        "\033[36m"  // Xanh lơ
#define WHITE       "\033[37m"  // Trắng

// 2. Màu dành cho chữ sáng (Bright Text)
#define B_GRAY      "\033[90m"  // Xám (Đen sáng)
#define B_RED       "\033[91m"  // Đỏ chói
#define B_GREEN     "\033[92m"  // Xanh lá neon
#define B_YELLOW    "\033[93m"  // Vàng chói
#define B_BLUE      "\033[94m"  // Xanh dương sáng
#define B_PINK      "\033[95m"  // Hồng neon
#define B_CYAN      "\033[96m"  // Xanh lơ sáng
#define B_WHITE     "\033[97m"  // Trắng tinh
#define B_ORANGE    "\033[38;5;214m"  // Màu cam chói (Sáng hơn)

// 3. Màu nền (Background)
#define BG_RED      "\033[41m"  // Nền đỏ
#define BG_GREEN    "\033[42m"  // Nền xanh lá
#define BG_YELLOW   "\033[43m"  // Nền vàng
#define BG_BLUE     "\033[44m"  // Nền xanh dương
#define BG_PURPLE   "\033[45m"  // Nền tím
#define BG_CYAN     "\033[46m"  // Nền xanh lơ
#define BG_WHITE    "\033[47m"  // Nền trắng

// 4. Hiệu ứng định dạng (Formatting)
#define BOLD        "\033[1m"   // In đậm
#define UNDERLINE   "\033[4m"   // Gạch chân

//Khai báo struct
typedef struct {
    int id;
    char ten[100];
    char mon_hoc[50];
    char khu_vuc[100];
    float danh_gia;
    char trinh_do[100];
    char sdt[15];
    char email[50];
    char buoi_day[100];
    int hoc_phi;
} GiaSu;

typedef struct Node {
    GiaSu data;
    struct Node* next;
} Node;

//Biến toàn cục
extern Node* head; 
extern GiaSu* ketQuaHienTai[MAX_RESULTS]; 
extern int soLuongKetQua;

extern char danhSachGoiBuoiDay[50][100];
extern int soLuongGoiBuoiDay;

extern char danhSachTrinhDo[20][50]; 
extern int soLuongTrinhDo;          

// Khai báo hàm xử lý dữ liệu đầu vào
void xoaKhoangTrangThua(char* str);
int timChuoi(const char* chuoi_goc, const char* chuoi_tim);
int timKhuVucChuan(const char* chuoi_goc, const char* chuoi_tim);
int cmpRateGiamDan(const void *a, const void *b);

// Quản lý Danh sách liên kết
void themGoiBuoiDay(char* buoi_day);
void themTrinhDo(char* trinh_do); // MỚI
Node* taoNode(GiaSu gs);
void themVaoCuoi(GiaSu gs);
void giaiPhongDanhSach();
int docFile();

void inBangGiaSu(GiaSu* arr[], int n);
int chucNangLoc();
void dangKyGiaSu();
int xemChiTietGiaSu();

#endif