#ifndef GIASU_H
#define GIASU_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_RESULTS 150

// Bản màu ANSI
#define RESET       "\033[0m"   
#define BLACK       "\033[30m"  
#define RED         "\033[31m"  
#define GREEN       "\033[32m"  
#define YELLOW      "\033[33m"  
#define BLUE        "\033[34m"  
#define PURPLE      "\033[35m"  
#define CYAN        "\033[36m"  
#define WHITE       "\033[37m"  

#define B_GRAY      "\033[90m"  
#define B_RED       "\033[91m"  
#define B_GREEN     "\033[92m"  
#define B_YELLOW    "\033[93m"  
#define B_BLUE      "\033[94m"  
#define B_PINK      "\033[95m"  
#define B_CYAN      "\033[96m"  
#define B_WHITE     "\033[97m"  
#define B_ORANGE    "\033[38;5;214m"  

#define BOLD        "\033[1m"   
#define UNDERLINE   "\033[4m"   

// STRUCT
typedef struct {
    int id;
    char mat_khau[30]; 
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

typedef struct LopHoc {
    int idLop;
    char monHoc[50];
    char diaChi[100];
    char tenPhuHuynh[50];
    char sdtPhuHuynh[15];
    int idGiaSuDay; 
    int trangThai; 
    int hocPhi;
    char yeuCau[200];
} LopHoc;

typedef struct {
    int idLich;
    int idGiaSu;
    char sdtPhuHuynh[20];
    char tenPhuHuynh[50];         
    char thongBaoGiaSu[500];      
    char thongBaoPhuHuynh[500];  
    int trangThai;
    int loaiThongBao;           
} LichHen;
typedef struct Node {
    GiaSu data;
    struct Node* next;
} Node; 


// Biến toàn cục
extern Node* head; 
extern GiaSu* ketQuaHienTai[MAX_RESULTS]; 
extern int soLuongKetQua;

extern char danhSachGoiBuoiDay[50][100];
extern int soLuongGoiBuoiDay;

extern char danhSachTrinhDo[20][50]; 
extern int soLuongTrinhDo; 

extern LopHoc danhSachLop[200];
extern int soLuongLop;

extern LichHen danhSachLich[200];
extern int soLuongLich;

#define ADMIN_CODE "UTC2_2026" 

//Khai báo hàm
// 1. NHÓM TIỆN ÍCH & XỬ LÝ CHUỖI (Utils & String)
// (Chuyên cắt gọt khoảng trắng, chuyển chữ hoa/thường, xử lý Tiếng Việt)
void xoaKhoangTrangThua(char* str);
void my_strlwr(char* str);
int timChuoi(const char* chuoi_goc, const char* chuoi_tim);
int timKhuVucChuan(const char* chuoi_goc, const char* chuoi_tim);
void dichMatrixThanhChu(const char* matrix, char* ketQua); 
void inChuoiUTF8(char* str, int width);                 
int cmpRateGiamDan(const void *a, const void *b);      

// 2. NHÓM KIỂM TRA ĐẦU VÀO (Validation)
// (Cảnh sát gác cổng: Chặn người dùng nhập bậy bạ, nhập chữ vào số...)
int laSDTHopLe(const char* sdt);
int TenHopLe(const char* ten);

// 3. NHÓM ĐIỀU HƯỚNG & NHẬP LIỆU GIAO DIỆN (Input & Control)
// (Quản lý các menu chọn số, phân trang, chống trôi màn hình)
int nhapLuaChonThanhCong(int min, int max);
int nhapLuaChonTrang(int min, int max);
int nhapIDGiaSuHopLe();
int nhapIDAdminHopLe();
void nhapTenHopLe_UI(char* ketQua, const char* loiNhac);

// 4. NHÓM ĐỌC/GHI FILE & QUẢN LÝ BỘ NHỚ (File I/O & Memory)
// (Giao tiếp với Database dạng .txt và Danh sách liên kết)
Node* taoNode(GiaSu gs);
void themVaoCuoi(GiaSu gs);
void giaiPhongDanhSach();
int docFile();                    // Đọc giasu.txt
void luuFileGiaSuTong();          // Ghi giasu.txt
void docFileLopVaLich();          // Đọc lophoc.txt và lichhen.txt
void luuFileLopVaLich();          // Ghi lophoc.txt và lichhen.txt
void themGoiBuoiDay(char* buoi_day); // Đọc phụ trợ (từ khóa)
void themTrinhDo(char* trinh_do);    // Đọc phụ trợ (từ khóa)

// 5. NHÓM NGHIỆP VỤ GIA SƯ (Tutor Logic)
// (Các tính năng chính của tài khoản Gia sư và Admin quản lý GS)
void dangKyGiaSu();
GiaSu* dangNhapGiaSu(int id, const char* mat_khau);
void capNhatThongTinGiaSu(GiaSu* gs_goc, GiaSu data_moi);
int xoaGiaSuTheoId(int id, const char* ma_admin);

// 6. NHÓM NGHIỆP VỤ LỚP HỌC & ĐẶT LỊCH (Class & Booking Logic)
// (Quy trình: Tạo lớp -> Xin nhận -> Đặt lịch trực tiếp -> Duyệt đơn)
void taoLopHocMoi();
void giaSuXemVaNhanLop(int idGiaSu);
void phuHuynhDatLichTruocTiep(GiaSu* gs);
void xemThongBaoPhuHuynh();
void xemThongBaoGiaSu(int idGiaSu);

// 7. NHÓM GIAO DIỆN & HIỂN THỊ (UI / Display)
// (Render menu, in bảng biểu ra màn hình)
void inBangGiaSu(GiaSu* arr[], int n);
void inBangGiaSuAdmin(GiaSu* arr[], int n);
int xemChiTietGiaSu(GiaSu* arr[], int n); 
int chucNangLoc();
void giaoDienCapNhatHoSo(GiaSu* gs_Logged);
#endif 
