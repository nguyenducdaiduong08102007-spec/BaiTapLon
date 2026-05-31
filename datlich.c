#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "giasu.h"

LopHoc danhSachLop[200];
int soLuongLop = 0;

LichHen danhSachLich[200];
int soLuongLich = 0;

void phuHuynhDatLichTruocTiep(GiaSu* gs) {
    if (soLuongLich >= 200) {
        printf(RED "\n [!] He thong luu tru thong bao da day!\n" RESET);
        return;
    }
    
    LichHen lh;
    lh.idLich = 5000 + soLuongLich + 1;
    lh.idGiaSu = gs->id;

    printf(YELLOW "\n >>> TIẾN HÀNH ĐẶT LỊCH CÓ TRƯỚC VỚI GIA SƯ %s <<<\n" RESET, gs->ten);
    
    char thongBaoLoiTenPH[200] = "";
    while (1) {
        if (strlen(thongBaoLoiTenPH) > 0) printf("%s\n", thongBaoLoiTenPH);
        else printf("\n");

        printf(" -> Nhập Tên của bạn: ");
        fgets(lh.tenPhuHuynh, sizeof(lh.tenPhuHuynh), stdin);

        if (strlen(thongBaoLoiTenPH) > 0) printf("\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(lh.tenPhuHuynh);

        if (TenHopLe(lh.tenPhuHuynh)) break;
        else strcpy(thongBaoLoiTenPH, RED " [!] Tên không hợp lệ! Chỉ được nhập chữ, không chứa số/kí tự đặc biệt." RESET);
    }
    printf(" -> Nhập Tên của bạn: %s\n", lh.tenPhuHuynh);

    char thongBaoLoiSDT[200] = "";
    while (1) {
        if (strlen(thongBaoLoiSDT) > 0) printf("%s\n", thongBaoLoiSDT);
        else printf("\n");

        printf(" -> Nhập SĐT của bạn: ");
        fgets(lh.sdtPhuHuynh, sizeof(lh.sdtPhuHuynh), stdin);

        if (strlen(thongBaoLoiSDT) > 0) printf("\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(lh.sdtPhuHuynh);

        if (laSDTHopLe(lh.sdtPhuHuynh)) break;
        else strcpy(thongBaoLoiSDT, RED " [!] SĐT không hợp lệ! Phải bắt đầu bằng số 0 và đủ 10 số." RESET);
    }
    printf(" -> Nhập SĐT của bạn: %s\n", lh.sdtPhuHuynh);

    sprintf(lh.thongBaoGiaSu, "Phụ huynh %s (SĐT: %s) đã đặt lịch hẹn dạy môn %s với bạn.", lh.tenPhuHuynh, lh.sdtPhuHuynh, gs->mon_hoc);
    sprintf(lh.thongBaoPhuHuynh, "Bạn đã gửi lời mời đặt lịch thành công đến Gia sư %s (ID: %d).", gs->ten, gs->id);
    
    lh.trangThai = 0;       
    lh.loaiThongBao = 2;    

    danhSachLich[soLuongLich++] = lh;
    luuFileLopVaLich();
    printf(GREEN "\n [=>] Gui yeu cau dat lich thanh cong!\n" RESET);
}

int xemChiTietGiaSu(GiaSu* arr[], int n) {
    int idChon = nhapIDGiaSuHopLe();
    if (idChon == 0) return 0; 

    for (int i = 0; i < n; i++) {
        if (arr[i]->id == idChon) {
            char lichTong[250];
            dichMatrixThanhChu(arr[i]->buoi_day, lichTong);
            
            char dong1_lich[50] = "", dong2_lich[100] = "";
            char tempLich[250];
            strcpy(tempLich, lichTong);
            
            char* token = strtok(tempLich, " ");
            while (token != NULL) {
                if (strlen(dong1_lich) == 0) strcpy(dong1_lich, token);
                else if (strlen(dong1_lich) + strlen(token) + 1 <= 18) {
                    strcat(dong1_lich, " "); strcat(dong1_lich, token);
                } else {
                    if (strlen(dong2_lich) == 0) strcpy(dong2_lich, token);
                    else { strcat(dong2_lich, " "); strcat(dong2_lich, token); }
                }
                token = strtok(NULL, " ");
            }

            printf(PURPLE "\n+------------------------------------------------------------+\n");
            printf("|                  CHI TIẾT HỒ SƠ GIA SƯ                     |\n");
            printf("+------------------------------------------------------------+\n" RESET);
            
            printf("  - ID Hồ sơ        : " YELLOW "%d" RESET "\n", arr[i]->id);
            printf("  - Họ và Tên       : " CYAN "%s" RESET "\n", arr[i]->ten);
            printf("  - Môn dạy         : %s\n", arr[i]->mon_hoc);
            printf("  - Khu vực         : %s\n", arr[i]->khu_vuc);
            printf("  - Trình độ        : %s\n", arr[i]->trinh_do);
            printf("  - Học phí         : " B_GREEN "%d" RESET " VND/buổi\n", arr[i]->hoc_phi);
            
            if (arr[i]->danh_gia == 0.0) {
                printf("  - Đánh giá        : " B_YELLOW "NEW" RESET "\n");
            } else {
                printf("  - Đánh giá        : " B_YELLOW "%.1f" RESET " sao\n", arr[i]->danh_gia);
            }
            
            printf("  - Lịch rảnh       : " B_BLUE "%s" RESET "\n", dong1_lich);
            if (strlen(dong2_lich) > 0) {
                printf("                      " B_BLUE "%s" RESET "\n", dong2_lich); 
            }
            
            printf("  - Số điện thoại   : %s\n", arr[i]->sdt);
            printf("  - Email           : %s\n", arr[i]->email);
            
            printf(PURPLE "+------------------------------------------------------------+\n" RESET);
            printf("\n -> Bạn có muốn ĐẶT LỊCH với gia sư này? (1: Có, 0: Không): ");
            
            if (nhapLuaChonThanhCong(0, 1) == 1) {
                phuHuynhDatLichTruocTiep(arr[i]);
                system("pause");
                return 0; 
            }
            return 1;
        }
    }
    printf(RED "\n [!] Không tìm thấy ID gia sư này trong danh sách hiện tại!\n" RESET);
    system("pause");
    return 1;
}

void taoLopHocMoi() {
    if (soLuongLop >= 200) {
        printf(RED " [!] Hệ thống mở lớp đã đầy!\n" RESET);
        system("pause"); return;
    }
    system("cls");
    printf(PURPLE "====================================================\n");
    printf("             TẠO LỚP HỌC MỚI TÌM GIA SƯ\n");
    printf("====================================================\n" RESET);
    
    LopHoc lp;
    lp.idLop = 2000 + soLuongLop + 1;
    
    char dsMon[50][50]; 
    int slMon = 0;
    Node* tempMon = head;

    while (tempMon != NULL) {
        int daXuatHien = 0;
        for (int i = 0; i < slMon; i++) {
            if (strcmp(dsMon[i], tempMon->data.mon_hoc) == 0) { 
                daXuatHien = 1; break; 
            }
        }
        if (!daXuatHien && slMon < 50 && strlen(tempMon->data.mon_hoc) > 0) {
            strcpy(dsMon[slMon], tempMon->data.mon_hoc);
            slMon++;
        }
        tempMon = tempMon->next;
    }

    if (slMon == 0) {
        printf(RED " [!] Hệ thống hiện chưa có gia sư nào, không có môn để chọn!\n" RESET);
        system("pause"); return;
    }

    printf(CYAN "\n --- DANH SÁCH MÔN HỌC HIỆN CÓ ---\n" RESET);
    for (int i = 0; i < slMon; i += 3) {
        printf(" %-2d. %-17s", i+1, dsMon[i]);
        if (i + 1 < slMon) printf(" | %-2d. %-17s", i+2, dsMon[i+1]);
        if (i + 2 < slMon) printf(" | %-2d. %-17s", i+3, dsMon[i+2]);
        printf("\n");
    }

    char thongBaoLoiMon[200] = ""; 
    char bufMon[20];
    while(1) {
        if (strlen(thongBaoLoiMon) > 0) printf("%s\n", thongBaoLoiMon);
        else printf("\n");

        printf(" -> Chọn Môn học cần tìm (1-%d) (Nhấn Enter để hủy): ", slMon);
        fgets(bufMon, sizeof(bufMon), stdin);
        
        if (strlen(thongBaoLoiMon) > 0) printf("\033[A\033[K\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(bufMon);
        
        if (strlen(bufMon) == 0) {
            printf(B_GRAY " [*] Đã hủy thao tác tạo lớp học.\n" RESET); return; 
        }

        int isNumber = 1;
        for(int i = 0; i < strlen(bufMon); i++) {
            if(!isdigit(bufMon[i])) { isNumber = 0; break; }
        }

        if (isNumber) {
            int chonMon = atoi(bufMon);
            if (chonMon >= 1 && chonMon <= slMon) {
                strcpy(lp.monHoc, dsMon[chonMon - 1]);
                printf(" -> Chọn Môn học (1-%d): %s\n", slMon, lp.monHoc); 
                break; 
            } else {
                sprintf(thongBaoLoiMon, RED " [!] Số không hợp lệ! Vui lòng chỉ chọn từ 1 đến %d." RESET, slMon);
            }
        } else {
            strcpy(thongBaoLoiMon, RED " [!] Nhập sai! Chỉ được nhập số, không chứa chữ hay ký tự." RESET);
        }
    }

    char dsQuan[24][20] = {
        "Quận 1", "Quận 2", "Quận 3", "Quận 4", "Quận 5", "Quận 6", 
        "Quận 7", "Quận 8", "Quận 9", "Quận 10", "Quận 11", "Quận 12", 
        "Bình Thạnh", "Thủ Đức", "Gò Vấp", "Phú Nhuận", "Tân Bình", 
        "Tân Phú", "Bình Tân", "Nhà Bè", "Hóc Môn", "Bình Chánh", 
        "Củ Chi", "Cần Giờ"
    };
    
    printf(CYAN "\n --- DANH SÁCH QUẬN/HUYỆN TP.HCM ---\n" RESET);
    for (int i = 0; i < 24; i += 3) {
        printf(" %-2d. %-15s | %-2d. %-15s | %-2d. %-15s\n", 
               i+1, dsQuan[i], i+2, dsQuan[i+1], i+3, dsQuan[i+2]);
    }
    
    char thongBaoLoiKV[200] = "";
    char bufKV[20];
    while(1) {
        if (strlen(thongBaoLoiKV) > 0) printf("%s\n", thongBaoLoiKV);
        else printf("\n");

        printf(" -> Chọn Khu vực diễn ra lớp học (1-24) (Nhấn Enter để hủy): ");
        fgets(bufKV, sizeof(bufKV), stdin);
        
        if (strlen(thongBaoLoiKV) > 0) printf("\033[A\033[K\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(bufKV);

        if (strlen(bufKV) == 0) {
            printf(B_GRAY " [*] Đã hủy thao tác tạo lớp học.\n" RESET); return; 
        }

        int isNumber = 1;
        for(int i = 0; i < strlen(bufKV); i++) {
            if(!isdigit(bufKV[i])) { isNumber = 0; break; }
        }

        if (isNumber) {
            int chonKV = atoi(bufKV);
            if (chonKV >= 1 && chonKV <= 24) {
                strcpy(lp.diaChi, dsQuan[chonKV - 1]);
                printf(" -> Chọn Khu vực diễn ra lớp học (1-24): %s\n", lp.diaChi);
                break;
            } else {
                strcpy(thongBaoLoiKV, RED " [!] Nhập sai! Vui lòng chỉ chọn số từ 1 đến 24." RESET);
            }
        } else {
            strcpy(thongBaoLoiKV, RED " [!] Nhập sai! Chỉ được nhập số." RESET);
        }
    }

    char thongBaoLoiTen[200] = "";
    while(1) {
        if (strlen(thongBaoLoiTen) > 0) printf("%s\n", thongBaoLoiTen);
        else printf("\n");

        printf(" -> Nhập Tên của bạn (Phụ huynh) (Nhấn Enter để hủy): ");
        fgets(lp.tenPhuHuynh, sizeof(lp.tenPhuHuynh), stdin); 
        
        if (strlen(thongBaoLoiTen) > 0) printf("\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(lp.tenPhuHuynh);

        if (strlen(lp.tenPhuHuynh) == 0) {
            printf(B_GRAY " [*] Đã hủy thao tác tạo lớp học.\n" RESET); return; 
        }

        if(TenHopLe(lp.tenPhuHuynh)) {
            printf(" -> Nhập Tên của bạn (Phụ huynh): %s\n", lp.tenPhuHuynh);
            break;
        } else {
            strcpy(thongBaoLoiTen, RED " [!] Tên không hợp lệ! Chỉ được nhập chữ, không chứa số/ký tự." RESET);
        }
    }

    char thongBaoLoiSDT[200] = "";
    while(1) {
        if (strlen(thongBaoLoiSDT) > 0) printf("%s\n", thongBaoLoiSDT);
        else printf("\n");

        printf(" -> Nhập Số điện thoại (10 số, bắt đầu bằng 0): ");
        fgets(lp.sdtPhuHuynh, sizeof(lp.sdtPhuHuynh), stdin); 
        
        if (strlen(thongBaoLoiSDT) > 0) printf("\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(lp.sdtPhuHuynh);

        if (strlen(lp.sdtPhuHuynh) == 0) {
            strcpy(thongBaoLoiSDT, RED " [!] SĐT không được để trống! Vui lòng nhập số điện thoại." RESET);
            continue; 
        }

        if(laSDTHopLe(lp.sdtPhuHuynh)) {
            printf(" -> Nhập Số điện thoại: %s\n", lp.sdtPhuHuynh);
            break; 
        } else {
            strcpy(thongBaoLoiSDT, RED " [!] SĐT không hợp lệ! Phải đủ 10 số và bắt đầu bằng số 0." RESET);
        }
    }

    char thongBaoLoiHP[200] = "";
    char buffer[50];
    while(1) {
        if(strlen(thongBaoLoiHP) > 0) printf("%s\n", thongBaoLoiHP); 
        else printf("\n");

        printf(" -> Nhập Mức học phí (VND/buổi): ");
        fgets(buffer, sizeof(buffer), stdin); 
        
        if(strlen(thongBaoLoiHP) > 0) printf("\033[A\033[K\033[A\033[K"); 
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(buffer);

        if (strlen(buffer) == 0) {
            strcpy(thongBaoLoiHP, RED " [!] Học phí không được để trống! Vui lòng nhập số tiền." RESET);
            continue; 
        }

        int isNumber = 1;
        for(int i = 0; i < strlen(buffer); i++) {
            if(!isdigit(buffer[i])) { isNumber = 0; break; }
        }

        int leadingZero = 0;
        if (strlen(buffer) > 0 && buffer[0] == '0') {
            leadingZero = 1;
        }

        if(isNumber && !leadingZero && atoi(buffer) >= 50000) {
            lp.hocPhi = atoi(buffer);
            printf(" -> Nhập Mức học phí (VND/buổi): %d\n", lp.hocPhi); 
            break; 
        } else {
            if (!isNumber) {
                strcpy(thongBaoLoiHP, RED " [!] Học phí chỉ được nhập số (Không âm, không ký tự)!" RESET);
            } else if (leadingZero) {
                strcpy(thongBaoLoiHP, RED " [!] Học phí không được bắt đầu bằng số 0!" RESET);
            } else {
                strcpy(thongBaoLoiHP, RED " [!] Học phí phải từ 50,000 VND trở lên!" RESET);
            }
        }
    }

    printf("\n -> Nhập Yêu cầu đặc biệt (Enter để bỏ qua): ");
    fgets(lp.yeuCau, sizeof(lp.yeuCau), stdin); 
    xoaKhoangTrangThua(lp.yeuCau);
    
    if(strlen(lp.yeuCau) == 0) strcpy(lp.yeuCau, "Không có");
    else printf(" -> Nhập Yêu cầu đặc biệt: %s\n", lp.yeuCau); 
    
    lp.idGiaSuDay = 0;
    lp.trangThai = 0; 
    
    danhSachLop[soLuongLop++] = lp;
    luuFileLopVaLich();
    
    printf(GREEN "\n [+] Tạo lớp học tìm Gia sư thành công! Mã lớp là: %d\n" RESET, lp.idLop);
    system("pause");
}

void giaSuXemVaNhanLop(int idGiaSu) {
    system("cls");
    printf(CYAN "====================================================================================================\n");
    printf("                                  DANH SÁCH LỚP HỌC ĐANG CHỜ GIA SƯ ỨNG TUYỂN\n");
    printf("====================================================================================================\n" RESET);
    
    int coLop = 0;
    for (int i = 0; i < soLuongLop; i++) {
        if (danhSachLop[i].trangThai == 0) { coLop = 1; break; }
    }
    if (!coLop) { 
        printf(B_GRAY " [!] Hiện tại hệ thống chưa có lớp học nào đang tìm Gia sư.\n" RESET); 
        system("pause"); return; 
    }

    char gachNgang[] = "--------------------------------------------------------------------------------------------------------";

    printf(B_PINK "%s\n", gachNgang);
    printf("| %-8s | ", "ID Lớp");
    inChuoiUTF8("Môn Học", 17); printf(" | ");
    inChuoiUTF8("Địa Điểm", 20); printf(" | ");
    inChuoiUTF8("Học Phí/Buổi", 14); printf(" | ");
    inChuoiUTF8("Yêu Cầu Đặc Biệt", 32); printf(" |\n");
    printf("%s\n" RESET, gachNgang);

    for (int i = 0; i < soLuongLop; i++) {
        if (danhSachLop[i].trangThai == 0) {
            printf("| %-6d | ", danhSachLop[i].idLop);
            inChuoiUTF8(danhSachLop[i].monHoc, 17); printf(" | ");
            inChuoiUTF8(danhSachLop[i].diaChi, 20); printf(" | %-14d | ", danhSachLop[i].hocPhi);
            inChuoiUTF8(danhSachLop[i].yeuCau, 32); printf(" |\n");
            printf("%s\n", gachNgang);
        }
    }

    char thongBaoLoiID[200] = "";
    char bufID[20];
    
    while(1) {
        if (strlen(thongBaoLoiID) > 0) printf("%s\n", thongBaoLoiID); else printf("\n");
        
        printf(" -> Nhập ID lớp bạn muốn đăng ký dạy (Nhấn Enter hoặc 0 để quay lại): ");
        fgets(bufID, sizeof(bufID), stdin);
        
        if (strlen(thongBaoLoiID) > 0) printf("\033[A\033[K\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(bufID);

        if (strlen(bufID) == 0 || strcmp(bufID, "0") == 0) return;

        int isNumber = 1;
        for(int i = 0; i < strlen(bufID); i++) {
            if(!isdigit(bufID[i])) { isNumber = 0; break; }
        }

        if (isNumber) {
            int ma = atoi(bufID);
            int timThay = 0;
            for (int i = 0; i < soLuongLop; i++) {
                if (danhSachLop[i].idLop == ma && danhSachLop[i].trangThai == 0) {
                    timThay = 1;
                    
                    int daXin = 0;
                    for (int j = 0; j < soLuongLich; j++) {
                        int idLopDaXin = 0;
                        sscanf(danhSachLich[j].thongBaoPhuHuynh, "Lop %d", &idLopDaXin);
                        if (idLopDaXin == ma && danhSachLich[j].idGiaSu == idGiaSu && danhSachLich[j].loaiThongBao == 1) {
                            daXin = 1; break;
                        }
                    }
                    if (daXin) {
                        printf(YELLOW "\n [!] Bạn đã nộp đơn xin lớp này rồi! Vui lòng chờ Phụ huynh duyệt.\n" RESET);
                        system("pause"); return;
                    }

                    LichHen lh;
                    lh.idLich = 5000 + soLuongLich + 1;
                    lh.idGiaSu = idGiaSu;
                    strcpy(lh.sdtPhuHuynh, danhSachLop[i].sdtPhuHuynh);
                    strcpy(lh.tenPhuHuynh, danhSachLop[i].tenPhuHuynh);
                    
                    sprintf(lh.thongBaoPhuHuynh, "Lop %d (%s) da co Gia su ID %d xin nhan!", danhSachLop[i].idLop, danhSachLop[i].monHoc, idGiaSu);
                    sprintf(lh.thongBaoGiaSu, "Ban da xin nhan lop %d. Vui long cho Phu huynh xac nhan.", danhSachLop[i].idLop);
                    
                    lh.trangThai = 0; 
                    lh.loaiThongBao = 1; 

                    danhSachLich[soLuongLich++] = lh;
                    luuFileLopVaLich();
                    
                    printf(GREEN "\n [=>] Đã gửi đơn xin nhận lớp thành công! Vui lòng chờ duyệt.\n" RESET);
                    system("pause"); return;
                }
            }
            if (!timThay) strcpy(thongBaoLoiID, RED " [!] Mã ID lớp học không tồn tại hoặc lớp đã có người nhận!" RESET);
        } else {
            strcpy(thongBaoLoiID, RED " [!] Nhập sai! Chỉ được nhập số nguyên." RESET);
        }
    }
}

void xemThongBaoPhuHuynh() {
    char sdtTim[50];
    int hopLe;

    do {
        system("cls");
        printf(PURPLE "====================================================\n");
        printf("          KIEM TRA THONG BAO & DUYET GIA SU\n");
        printf("====================================================\n" RESET);
        printf(" -> Nhap SDT ban da dang ky (Nhap 0 de quay lai): ");
        
        fgets(sdtTim, sizeof(sdtTim), stdin); xoaKhoangTrangThua(sdtTim);
        if (strcmp(sdtTim, "0") == 0) return; 

        hopLe = 1;
        int len = strlen(sdtTim);
        if (len == 0) hopLe = 0; 
        for (int i = 0; i < len; i++) {
            if (sdtTim[i] < '0' || sdtTim[i] > '9') { hopLe = 0; break; }
        }
        if (!hopLe) {
            printf(RED "\n [!] So dien thoai sai dinh dang!" RESET);
            printf(B_GRAY "\n => Nhan Enter de nhap lai..." RESET);
            char c[10]; fgets(c, sizeof(c), stdin); 
        }
    } while (!hopLe);

    while (1) {
        system("cls");
        printf(PURPLE "====================================================\n");
        printf("            HOP THU THONG BAO (SDT: %s)\n", sdtTim);
        printf("====================================================\n" RESET);

        int count = 0;
        int chiSo[100]; 

        for (int i = 0; i < soLuongLich; i++) {
            if (strcmp(danhSachLich[i].sdtPhuHuynh, sdtTim) == 0) {
                printf("\n----------------------------------------------------\n");
                
                if (danhSachLich[i].loaiThongBao == 1) {
                    printf(CYAN " [ID: %d] GIA SU DANG KY LOP CUA BAN:\n" RESET, count + 1);
                    printf("    Noi dung: %s\n", danhSachLich[i].thongBaoPhuHuynh);
                } else {
                    printf(YELLOW " [-] BAN DA MOI GIA SU ID %d DAY:\n" RESET, danhSachLich[i].idGiaSu);
                    printf("    Noi dung: %s\n", danhSachLich[i].thongBaoPhuHuynh);
                }

                printf("    TRANG THAI: ");
                if (danhSachLich[i].trangThai == 0) printf(B_YELLOW "DANG CHO XAC NHAN..." RESET "\n");
                else if (danhSachLich[i].trangThai == 1) printf(B_GREEN "DA CHAP NHAN!" RESET "\n");
                else printf(RED "DA TU CHOI." RESET "\n");
                
                chiSo[count] = i; 
                count++;
            }
        }

        if (count == 0) {
            printf(B_GRAY "\n [!] Hien chua co thong bao nao.\n" RESET);
            printf("\n -> Nhan Enter de quay lai... ");
            char c[10]; fgets(c, sizeof(c), stdin);
            return;
        }

        printf("\n====================================================");
        
        char thongBaoLoiID[200] = "";
        char buffer[20];
        int chon = -1;

        while(1) {
            if (strlen(thongBaoLoiID) > 0) printf("\n%s\n", thongBaoLoiID);
            else printf("\n");

            printf(" -> Nhap ID thong bao [1-%d] de xu ly (Nhan Enter hoac 0 de thoat): ", count);
            fgets(buffer, sizeof(buffer), stdin);
            
            if (strlen(thongBaoLoiID) > 0) printf("\033[A\033[K\033[A\033[K\033[A\033[K");
            else printf("\033[A\033[K");

            xoaKhoangTrangThua(buffer);

            if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
                chon = 0;
                break; 
            }

            int isNumber = 1;
            for(int i = 0; i < strlen(buffer); i++) {
                if(!isdigit(buffer[i])) { 
                    isNumber = 0; 
                    break; 
                }
            }

            if (isNumber) {
                chon = atoi(buffer);
                if (chon >= 1 && chon <= count) {
                    printf(" -> Nhap ID thong bao [1-%d] de xu ly: %d\n", count, chon); 
                    break; 
                } else {
                    sprintf(thongBaoLoiID, RED " [!] ID khong ton tai! Vui long nhap tu 1 den %d." RESET, count);
                }
            } else {
                strcpy(thongBaoLoiID, RED " [!] Nhap sai! ID chi duoc la so nguyen (Khong chu, khong dau cham)." RESET);
            }
        }

        if (chon == 0) break; 
        if (chon > 0 && chon <= count) {
            int viTriThuc = chiSo[chon - 1];
            
            if (danhSachLich[viTriThuc].loaiThongBao == 1 && danhSachLich[viTriThuc].trangThai == 0) {
                
                GiaSu* gs = NULL;
                Node* current = head;
                while (current != NULL) {
                    if (current->data.id == danhSachLich[viTriThuc].idGiaSu) {
                        gs = &(current->data); break;
                    }
                    current = current->next;
                }

                if (gs != NULL) {
                    printf(CYAN "\n --- HO SO CHI TIET GIA SU --- \n" RESET);
                    printf("  [-] Ho va Ten : %s\n", gs->ten);
                    printf("  [-] Mon hoc   : %s\n", gs->mon_hoc);
                    printf("  [-] Trinh do  : %s\n", gs->trinh_do);
                    printf("  [-] Hoc phi   : %d VND/buoi\n", gs->hoc_phi);
                    printf("  [-] Danh gia  : %.1f Sao\n", gs->danh_gia);
                    printf(CYAN " ----------------------------- \n" RESET);
                }

                printf("\n [1] CHAP NHAN gia su nay | [2] TU CHOI gia su nay\n");
                printf(" -> Lua chon cua ban: ");
                fgets(buffer, sizeof(buffer), stdin);
                int qd = atoi(buffer);
                
                if (qd == 1) {
                    danhSachLich[viTriThuc].trangThai = 1;
                    
                    int idLopDuocChon = 0;
                    sscanf(danhSachLich[viTriThuc].thongBaoPhuHuynh, "Lop %d", &idLopDuocChon);

                    for (int j = 0; j < soLuongLop; j++) {
                        if (danhSachLop[j].idLop == idLopDuocChon) {
                            danhSachLop[j].trangThai = 1; 
                            danhSachLop[j].idGiaSuDay = danhSachLich[viTriThuc].idGiaSu;
                            break;
                        }
                    }

                    for (int j = 0; j < soLuongLich; j++) {
                        if (danhSachLich[j].loaiThongBao == 1 && danhSachLich[j].trangThai == 0 && j != viTriThuc) {
                            int idLopKhac = 0;
                            sscanf(danhSachLich[j].thongBaoPhuHuynh, "Lop %d", &idLopKhac);
                            
                            if (idLopKhac == idLopDuocChon && idLopDuocChon != 0) {
                                danhSachLich[j].trangThai = 2; 
                                sprintf(danhSachLich[j].thongBaoGiaSu, "Lop %d da giao cho gia su khac. Chuc ban may man!", idLopKhac);
                            }
                        }
                    }
                    printf(GREEN " [+] Da xac nhan gia su & Tu dong tu choi cac ung vien khac!\n" RESET);

                } else if (qd == 2) {
                    danhSachLich[viTriThuc].trangThai = 2;
                    printf(RED " [-] Da tu choi gia su nay.\n" RESET);
                }
                
                luuFileLopVaLich(); 
                system("pause");
            } 
            else if (danhSachLich[viTriThuc].loaiThongBao == 2) {
                printf(B_GRAY " [!] Day la don ban dat lich, ban chi co the xem gia su phan hoi!\n" RESET);
                system("pause");
            }
            else {
                printf(B_GRAY " [!] Don nay da duoc xu ly truoc do!\n" RESET);
                system("pause");
            }
        }
    }
}

void xemThongBaoGiaSu(int idGiaSu) {
    while (1) {
        system("cls");
        printf(PURPLE "======================================================\n");
        printf("               HOP THU THONG BAO CUA BAN\n");
        printf("======================================================\n" RESET);

        int count = 0;
        int chiSo[100]; 

        for (int i = 0; i < soLuongLich; i++) {
            if (danhSachLich[i].idGiaSu == idGiaSu) {
                printf("\n----------------------------------------------------\n");
                
                if (danhSachLich[i].loaiThongBao == 2) {
                    printf(YELLOW " [ID: %d] LỜI MỜI DẠY TỪ PHỤ HUYNH:\n" RESET, count + 1);
                    printf("    Noi dung: %s\n", danhSachLich[i].thongBaoGiaSu);
                } else {
                    printf(CYAN " [-] BAN DA DANG KY LOP CUA SDT %s:\n" RESET, danhSachLich[i].sdtPhuHuynh);
                    printf("    Noi dung: %s\n", danhSachLich[i].thongBaoGiaSu);
                }

                printf("    TRANG THAI: ");
                if (danhSachLich[i].trangThai == 0) printf(B_YELLOW "DANG CHO XAC NHAN..." RESET "\n");
                else if (danhSachLich[i].trangThai == 1) printf(B_GREEN "DA CHAP NHAN!" RESET "\n");
                else printf(RED "DA TU CHOI." RESET "\n");
                
                chiSo[count] = i; 
                count++;
            }
        }

        if (count == 0) {
            printf(B_GRAY " [!] Hien chua co thong bao moi.\n" RESET);
            printf("\n -> Nhan Enter de quay lai... ");
            char c[10]; fgets(c, sizeof(c), stdin);
            return;
        }

        printf("\n====================================================");
        
        char thongBaoLoiID[200] = "";
        char buffer[20];
        int chon = -1;

        while(1) {
            if (strlen(thongBaoLoiID) > 0) printf("\n%s\n", thongBaoLoiID);
            else printf("\n");

            printf(" -> Nhap ID thong bao [1-%d] de xu ly (Nhan Enter hoac 0 de thoat): ", count);
            fgets(buffer, sizeof(buffer), stdin);
            
            if (strlen(thongBaoLoiID) > 0) printf("\033[A\033[K\033[A\033[K\033[A\033[K");
            else printf("\033[A\033[K");

            xoaKhoangTrangThua(buffer);

            if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
                chon = 0;
                break; 
            }

            int isNumber = 1;
            for(int i = 0; i < strlen(buffer); i++) {
                if(!isdigit(buffer[i])) { 
                    isNumber = 0; 
                    break; 
                }
            }

            if (isNumber) {
                chon = atoi(buffer);
                if (chon >= 1 && chon <= count) {
                    printf(" -> Nhap ID thong bao [1-%d] de xu ly: %d\n", count, chon); 
                    break; 
                } else {
                    sprintf(thongBaoLoiID, RED " [!] ID khong ton tai! Vui lòng nhap tu 1 den %d." RESET, count);
                }
            } else {
                strcpy(thongBaoLoiID, RED " [!] Nhap sai! ID chi duoc la so nguyen (Khong chu, khong dau cham)." RESET);
            }
        }

        if (chon == 0) break; 

        if (chon > 0 && chon <= count) {
            int viTriThuc = chiSo[chon - 1];

            if (danhSachLich[viTriThuc].loaiThongBao == 2 && danhSachLich[viTriThuc].trangThai == 0) {
                printf("\n [1] CHAP NHAN nhan lop | [2] TU CHOI nhan lop\n");
                printf(" -> Lua chon cua ban: ");
                fgets(buffer, sizeof(buffer), stdin);
                int qd = atoi(buffer);
                
                if (qd == 1) {
                    danhSachLich[viTriThuc].trangThai = 1;
                    printf(GREEN " [+] Da chap nhan loi moi thanh cong!\n" RESET);
                } else if (qd == 2) {
                    danhSachLich[viTriThuc].trangThai = 2;
                    printf(RED " [-] Da tu choi loi moi.\n" RESET);
                }
                luuFileLopVaLich(); 
                system("pause");
            } 
            else if (danhSachLich[viTriThuc].loaiThongBao == 1) {
                printf(B_GRAY " [!] Day la lop ban xin day, vui long cho Phụ huynh duyet!\n" RESET);
                system("pause");
            }
            else {
                printf(B_GRAY " [!] Don nay da duoc xu ly truoc do!\n" RESET);
                system("pause");
            }
        }
    }
}

void luuFileLopVaLich() {
    FILE *f1 = fopen("lophoc.txt", "w");
    if(f1) {
        for(int i=0; i<soLuongLop; i++) {
            fprintf(f1, "%d|%s|%s|%s|%s|%d|%d|%d|%s\n", 
                    danhSachLop[i].idLop, danhSachLop[i].monHoc, 
                    danhSachLop[i].diaChi, danhSachLop[i].tenPhuHuynh, 
                    danhSachLop[i].sdtPhuHuynh, danhSachLop[i].idGiaSuDay, 
                    danhSachLop[i].trangThai, danhSachLop[i].hocPhi, 
                    danhSachLop[i].yeuCau);
        }
        fclose(f1);
    }
    
    FILE *f2 = fopen("lichhen.txt", "w");
    if(f2) {
        for(int i=0; i<soLuongLich; i++)
            fprintf(f2, "%d|%d|%s|%s|%s|%s|%d|%d\n", danhSachLich[i].idLich, danhSachLich[i].idGiaSu, danhSachLich[i].sdtPhuHuynh, danhSachLich[i].tenPhuHuynh, danhSachLich[i].thongBaoGiaSu, danhSachLich[i].thongBaoPhuHuynh, danhSachLich[i].trangThai, danhSachLich[i].loaiThongBao);
        fclose(f2);
    }
}

void docFileLopVaLich() {
    FILE *f1 = fopen("lophoc.txt", "r");
    soLuongLop = 0;
    if(f1) {
        while(fscanf(f1, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%[^\n]\n", 
            &danhSachLop[soLuongLop].idLop, danhSachLop[soLuongLop].monHoc, 
            danhSachLop[soLuongLop].diaChi, danhSachLop[soLuongLop].tenPhuHuynh, 
            danhSachLop[soLuongLop].sdtPhuHuynh, &danhSachLop[soLuongLop].idGiaSuDay, 
            &danhSachLop[soLuongLop].trangThai, &danhSachLop[soLuongLop].hocPhi, 
            danhSachLop[soLuongLop].yeuCau) == 9) { 
            soLuongLop++;
        }
        fclose(f1);
    }
    
    FILE *f2 = fopen("lichhen.txt", "r");
    soLuongLich = 0;
    if(f2) {
        while(fscanf(f2, "%d|%d|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d\n", &danhSachLich[soLuongLich].idLich, &danhSachLich[soLuongLich].idGiaSu, danhSachLich[soLuongLich].sdtPhuHuynh, danhSachLich[soLuongLich].tenPhuHuynh, danhSachLich[soLuongLich].thongBaoGiaSu, danhSachLich[soLuongLich].thongBaoPhuHuynh, &danhSachLich[soLuongLich].trangThai, &danhSachLich[soLuongLich].loaiThongBao) == 8) {
            soLuongLich++;
        }
        fclose(f2);
    }
}
