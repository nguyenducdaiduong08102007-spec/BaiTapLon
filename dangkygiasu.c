#include "giasu.h"
#include <ctype.h>

int laEmailHopLe(const char* email) {
    if (strlen(email) < 5) return 0;
    const char* at = strchr(email, '@');
    const char* dot = strrchr(email, '.');
    return (at != NULL && dot != NULL && at < dot);
}

int laTrinhDoHopLe(const char* td) {
    const char* dsTD[] = {"Sinh viên", "Cao đẳng", "Đại học", "Cao học", "Thạc sĩ", "Tiến sĩ", "Giáo viên"};
    int n = 7;
    
    for (int i = 0; i < n; i++) {
        if (strcasecmp(td, dsTD[i]) == 0) return 1;
    }
    return 0;
}

void luuFileGiaSuTong() {
    FILE* f = fopen("giasu.txt", "w");
    if (f == NULL) return;
    Node* temp = head;
    while (temp != NULL) {
        fprintf(f, "%d|%s|%s|%s|%s|%.1f|%s|%s|%s|%s|%d\n",
                temp->data.id, temp->data.mat_khau, temp->data.ten,
                temp->data.mon_hoc, temp->data.khu_vuc, temp->data.danh_gia,
                temp->data.trinh_do, temp->data.sdt, temp->data.email,
                temp->data.buoi_day, temp->data.hoc_phi);
        temp = temp->next;
    }
    fclose(f);
}

void dangKyGiaSu() {
    GiaSu gs;
    char buffer[100];
    printf(PURPLE"\n============================================\n");
    printf("          ĐĂNG KÝ HỒ SƠ GIA SƯ\n");
    printf("============================================\n"RESET);

    int max_id = 0;
    Node* n_temp = head;
    while (n_temp != NULL) {
        if (n_temp->data.id > max_id) max_id = n_temp->data.id;
        n_temp = n_temp->next;
    }
    gs.id = (max_id < 1000) ? 1000 : max_id + 1;

    while (1) {
        printf(" - Mặt khẩu đăng nhập của bạn: "); 
        fgets(gs.mat_khau, sizeof(gs.mat_khau), stdin); 
        xoaKhoangTrangThua(gs.mat_khau);
        if (strlen(gs.mat_khau) >= 3) break;
        printf(RED " [!] Thông tin mật khẩu không hợp lệ ( phải 3 kí tự trở lên). Mời nhập lại: \n" RESET);
    }

    nhapTenHopLe_UI(gs.ten, " - Họ và tên:  ");

    char dsMon[15][30] = {
        "Toán", "Vật Lý", "Hóa Học", "Sinh Học", "Ngữ Văn", 
        "Tiếng Anh", "Lịch Sử", "Địa Lý", "Tin Học", "Tiếng Nhật",
        "Tiếng Hàn", "Tiếng Trung", "Khoa Học", "Toán Tư Duy", "Nghệ Thuật"
    };
    int slMon = 15;
    
    printf(CYAN "\n --- DANH SÁCH CÁC MÔN HỌC --- \n" RESET);
    for (int i = 0; i < slMon; i += 3) {
        printf(" %-2d. %-15s", i+1, dsMon[i]);
        if (i+1 < slMon) printf(" | %-2d. %-15s", i+2, dsMon[i+1]);
        if (i+2 < slMon) printf(" | %-2d. %-15s", i+3, dsMon[i+2]);
        printf("\n");
    }

    while(1) {
        char bufMon[20];
        printf(" -> Chọn Môn dạy (1-%d): ", slMon);
        fgets(bufMon, sizeof(bufMon), stdin);
        xoaKhoangTrangThua(bufMon);

        int isPureNumber = 1;
        int hasDot = 0; 
        
        if (strlen(bufMon) == 0) isPureNumber = 0; 
        
        for(int i = 0; i < strlen(bufMon); i++) {
            if (bufMon[i] == '.') {
                hasDot = 1; 
                break;
            }
            if (!isdigit(bufMon[i])) {
                isPureNumber = 0; 
                break;
            }
        }

        if (isPureNumber && !hasDot) {
            int chon = atoi(bufMon);
            if (chon >= 1 && chon <= slMon) {
                strcpy(gs.mon_hoc, dsMon[chon - 1]);
                break; 
            }
        }
        
        printf(RED " [!] Lỗi! Vui lòng chỉ nhập số nguyên từ 1 đến 24.\n" RESET);
        system("pause"); 
        printf("\033[A\033[K\033[A\033[K\033[A\033[K"); 
    }

    char dsQuan[24][20] = {
        "Quận 1", "Quận 2", "Quận 3", "Quận 4", "Quận 5", "Quận 6", 
        "Quận 7", "Quận 8", "Quận 9", "Quận 10", "Quận 11", "Quận 12", 
        "Bình Thạnh", "Thủ Đức", "Gò Vấp", "Phú Nhuận", "Tân Bình", 
        "Tân Phú", "Bình Tân", "Nhà Bè", "Hóc Môn", "Bình Chánh", 
        "Củ Chi", "Cần Giờ"
    };
    
    printf(CYAN "\n --- DANH SÁCH QUẬN/HUYỆN TP.HCM --- \n" RESET);
    for (int i = 0; i < 24; i += 3) {
        printf(" %-2d. %-15s | %-2d. %-15s | %-2d. %-15s\n", 
               i+1, dsQuan[i], i+2, dsQuan[i+1], i+3, dsQuan[i+2]);
    }

    while(1) {
        char bufKV[20];
        printf(" -> Chọn Khu vực (1-24): ");
        fgets(bufKV, sizeof(bufKV), stdin);
        
        int isPureNumber = 1;
        int hasDot = 0;
        
        xoaKhoangTrangThua(bufKV);
        if (strlen(bufKV) == 0) isPureNumber = 0;
        for(int i = 0; i < strlen(bufKV); i++) {
            if (bufKV[i] == '.') { hasDot = 1; break; }
            if (!isdigit(bufKV[i])) { isPureNumber = 0; break; }
        }

        if (isPureNumber && !hasDot) {
            int chon = atoi(bufKV);
            if (chon >= 1 && chon <= 24) {
                strcpy(gs.khu_vuc, dsQuan[chon - 1]);
                break; 
            }
        }
        
        printf(RED " [!] Lỗi! Vui lòng chỉ nhập số nguyên từ 1 đến 24.\n" RESET);
        system("pause"); 
        printf("\033[A\033[K\033[A\033[K\033[A\033[K"); 
    }

    char thongBaoLoiTD[200] = "";
    while (1) {
        if (strlen(thongBaoLoiTD) > 0) printf("%s\n", thongBaoLoiTD);
        else printf("\n");

        printf(" - Trình độ (Sinh viên, Cao đẳng, Đại học, Cao học, Thạc sĩ, Tiến sĩ, Giáo viên): "); 
        fgets(gs.trinh_do, sizeof(gs.trinh_do), stdin); 
        
        if (strlen(thongBaoLoiTD) > 0) printf("\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(gs.trinh_do);

        if (laTrinhDoHopLe(gs.trinh_do)) {
            printf(" - Trình độ đã lưu: %s\n", gs.trinh_do);
            break; 
        }
        
        strcpy(thongBaoLoiTD, RED " [!] Trình độ không hợp lệ! Vui lòng nhập đúng danh sách gợi ý." RESET);
    }
    
    char thongBaoLoiSDT[200] = "";
    while (1) {
        if (strlen(thongBaoLoiSDT) > 0) printf("%s\n", thongBaoLoiSDT);
        else printf("\n"); 

        printf(" - Số điện thoại: "); 
        fgets(gs.sdt, sizeof(gs.sdt), stdin); 
        
        if (strlen(thongBaoLoiSDT) > 0) printf("\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(gs.sdt);
        if (laSDTHopLe(gs.sdt)) break;
        
        strcpy(thongBaoLoiSDT, RED " [!] SĐT không hợp lệ! (Phải gồm 10 số và bắt đầu bằng 0). Nhập lại." RESET);
    }
    printf(" - Số điện thoại đã lưu: %s\n", gs.sdt); 

    char thongBaoLoiEmail[200] = "";
    while (1) {
        if (strlen(thongBaoLoiEmail) > 0) printf("%s\n", thongBaoLoiEmail);
        else printf("\n");

        printf(" - Email: "); 
        fgets(gs.email, sizeof(gs.email), stdin); 
        
        if (strlen(thongBaoLoiEmail) > 0) printf("\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(gs.email);
        if (laEmailHopLe(gs.email)) break;
        
        strcpy(thongBaoLoiEmail, RED " [!] Email không hợp lệ (Phải chứa '@' và '.'). Vui lòng nhập lại." RESET);
    }
    printf(" - Email đã lưu: %s\n", gs.email); 

    char thongBaoLoiHP[200] = "";
    char bufferHP[50];
    while(1) {
        if (strlen(thongBaoLoiHP) > 0) printf("%s\n", thongBaoLoiHP);
        else printf("\n");

        printf(" - Học phí yêu cầu (VND/buổi): ");
        fgets(bufferHP, sizeof(bufferHP), stdin);
        
        if (strlen(thongBaoLoiHP) > 0) printf("\033[A\033[K\033[A\033[K");
        else printf("\033[A\033[K");

        xoaKhoangTrangThua(bufferHP);

        if (strlen(bufferHP) == 0) {
            strcpy(thongBaoLoiHP, RED " [!] Học phí không được để trống!" RESET);
            continue;
        }

        int isNumber = 1;
        for(int i = 0; i < strlen(bufferHP); i++) {
            if(!isdigit(bufferHP[i])) { isNumber = 0; break; }
        }

        int leadingZero = (bufferHP[0] == '0');

        if (isNumber && !leadingZero && atoi(bufferHP) >= 50000) {
            gs.hoc_phi = atoi(bufferHP);
            printf(" - Học phí yêu cầu: %d VND/buổi\n", gs.hoc_phi);
            break; 
        } else {
            if (!isNumber) strcpy(thongBaoLoiHP, RED " [!] Học phí phải là số nguyên dương!" RESET);
            else if (leadingZero) strcpy(thongBaoLoiHP, RED " [!] Học phí không được bắt đầu bằng số 0!" RESET);
            else strcpy(thongBaoLoiHP, RED " [!] Học phí quá thấp! (Tối thiểu 50,000 VND)." RESET);
        }
    }
    
    char maTranLich[7][4] = {"---", "---", "---", "---", "---", "---", "---"};
    char cacThuTen[7][10] = {"Thu 2", "Thu 3", "Thu 4", "Thu 5", "Thu 6", "Thu 7", "Chu Nhat"};
    int chonThu, chonCa;

    do {
        system("cls");
        printf(PURPLE "============================================\n");
        printf("       CAP NHAT LICH RANH CHI TIET\n");
        printf("============================================\n" RESET);
        for (int i = 0; i < 7; i++) {
            printf("  %d. %s: [%c]Sang  [%c]Chieu  [%c]Toi\n", 
                   i + 1, cacThuTen[i], maTranLich[i][0], maTranLich[i][1], maTranLich[i][2]);
        }
        printf("  0. Hoan tat chon lich vao he thong\n");
        printf("--------------------------------------------\n");
        chonThu = nhapLuaChonThanhCong(0, 7);

        if (chonThu >= 1 && chonThu <= 7) {
            int tIdx = chonThu - 1;
            do {
                system("cls");
                printf(CYAN "--- CAI DAT CA DAY CHO %s ---\n" RESET, cacThuTen[tIdx]);
                printf("  1. Ca SANG  : [%c] (An 1 de Bat/Tat)\n", maTranLich[tIdx][0]);
                printf("  2. Ca CHIEU : [%c] (An 2 de Bat/Tat)\n", maTranLich[tIdx][1]);
                printf("  3. Ca TOI   : [%c] (An 3 de Bat/Tat)\n", maTranLich[tIdx][2]);
                printf("  0. Quay lai menu truoc\n");
                chonCa = nhapLuaChonThanhCong(0, 3);

                if (chonCa == 1) maTranLich[tIdx][0] = (maTranLich[tIdx][0] == '-') ? 'S' : '-';
                if (chonCa == 2) maTranLich[tIdx][1] = (maTranLich[tIdx][1] == '-') ? 'C' : '-';
                if (chonCa == 3) maTranLich[tIdx][2] = (maTranLich[tIdx][2] == '-') ? 'T' : '-';
            } while (chonCa != 0);
        }
    } while (chonThu != 0);

    strcpy(gs.buoi_day, "");
    for(int i = 0; i < 7; i++) {
        strcat(gs.buoi_day, maTranLich[i]);
        if (i < 6) strcat(gs.buoi_day, " ");
    }
    
    gs.danh_gia = 0.0; 

    themVaoCuoi(gs);
    luuFileGiaSuTong();
    
    FILE *f = fopen("giasu.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d, %s, %s, %s, %s, %.1f, %s, %s, %s, %s, %d\n",
                gs.id, gs.mat_khau, gs.ten, gs.mon_hoc, gs.khu_vuc, gs.danh_gia,
                gs.trinh_do, gs.sdt, gs.email, gs.buoi_day, gs.hoc_phi);
        fclose(f);
    }
    
    printf(GREEN "\n=> DANG KY THANH CONG! ID cua ban la: %d\n" RESET, gs.id);
    system("pause");
}

GiaSu* dangNhapGiaSu(int id, const char* mat_khau) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            if (strcmp(current->data.mat_khau, mat_khau) == 0) return &(current->data);
            return NULL;
        }
        current = current->next;
    }
    return NULL;
}

void capNhatThongTinGiaSu(GiaSu* gs_goc, GiaSu data_moi) {
    strcpy(gs_goc->ten, data_moi.ten);
    strcpy(gs_goc->mon_hoc, data_moi.mon_hoc);
    strcpy(gs_goc->khu_vuc, data_moi.khu_vuc);
    strcpy(gs_goc->trinh_do, data_moi.trinh_do);
    strcpy(gs_goc->sdt, data_moi.sdt);
    strcpy(gs_goc->email, data_moi.email);
    strcpy(gs_goc->buoi_day, data_moi.buoi_day);
    gs_goc->hoc_phi = data_moi.hoc_phi;
    strcpy(gs_goc->mat_khau, data_moi.mat_khau);
}

void giaoDienCapNhatHoSo(GiaSu* gs_Logged) {
    GiaSu data_moi = *gs_Logged; 
    int chonSua;
    char buffer[100];

    do {
        system("cls");
        printf(YELLOW "====================================================================\n");
        printf("                   CẬP NHẬT THÔNG TIN HỒ SƠ CÁ NHÂN\n");
        printf("====================================================================\n" RESET);
        printf("  1. Họ và Tên     : " CYAN "%s\n" RESET, data_moi.ten);
        printf("  2. Môn học       : " CYAN "%s\n" RESET, data_moi.mon_hoc);
        printf("  3. Khu vực       : " CYAN "%s\n" RESET, data_moi.khu_vuc);
        printf("  4. Trình độ      : " CYAN "%s\n" RESET, data_moi.trinh_do);
        printf("  5. Số điện thoại : " CYAN "%s\n" RESET, data_moi.sdt);
        printf("  6. Email         : " CYAN "%s\n" RESET, data_moi.email);
        printf("  7. Học phí       : " B_GREEN "%d" RESET " VND/buổi\n", data_moi.hoc_phi);
        printf("  8. Mật khẩu      : " B_RED "********\n" RESET);
        printf(YELLOW "\n  0. HOÀN TẤT CHỈNH SỬA VÀ LƯU LẠI\n" RESET);
        printf("====================================================================\n");

        chonSua = nhapLuaChonThanhCong(0, 8);

        switch(chonSua) {
            case 1: {
                char thongBaoLoiTen[200] = ""; 
                while (1) {
                    if (strlen(thongBaoLoiTen) > 0) printf("%s\n", thongBaoLoiTen);
                    else printf("\n"); 

                    printf(" -> Nhập Họ và Tên mới (Nhấn Enter để giữ nguyên): ");
                    fgets(buffer, sizeof(buffer), stdin); 
                    
                    if (strlen(thongBaoLoiTen) > 0) printf("\033[A\033[K\033[A\033[K");
                    else printf("\033[A\033[K"); 

                    xoaKhoangTrangThua(buffer);
                    
                    if (strlen(buffer) == 0) {
                        printf(B_GRAY " -> Giữ nguyên Họ và Tên cũ: %s\n" RESET, data_moi.ten);
                        break; 
                    }
                    
                    if (TenHopLe(buffer)) { 
                        strcpy(data_moi.ten, buffer); 
                        printf(GREEN " -> Cập nhật Họ và Tên mới: %s\n" RESET, data_moi.ten);
                        break; 
                    }
                    strcpy(thongBaoLoiTen, RED " [!] Tên sai quy tắc! Chỉ được nhập chữ, có khoảng cách, không số/kí tự." RESET);
                }
                break;
            }
            case 2: { 
                char dsMon[15][30] = {
                    "Toán", "Vật Lý", "Hóa Học", "Sinh Học", "Ngữ Văn", 
                    "Tiếng Anh", "Lịch Sử", "Địa Lý", "Tin Học", "Tiếng Nhật",
                    "Tiếng Hàn", "Tiếng Trung", "Khoa Học", "Toán Tư Duy", "Nghệ Thuật"
                };
                int slMon = 15;

                printf(CYAN "\n --- DANH SÁCH MÔN HỌC (Chọn để cập nhật) ---\n" RESET);
                for (int i = 0; i < slMon; i += 3) {
                    printf(" %-2d. %-17s", i+1, dsMon[i]);
                    if (i + 1 < slMon) printf(" | %-2d. %-17s", i+2, dsMon[i+1]);
                    if (i + 2 < slMon) printf(" | %-2d. %-17s", i+3, dsMon[i+2]);
                    printf("\n");
                }

                char thongBaoLoiMon[200] = "";
                char bufMon[10];
                
                while(1) {
                    if (strlen(thongBaoLoiMon) > 0) printf("%s\n", thongBaoLoiMon);
                    else printf("\n");

                    printf(" -> Chọn Môn học mới (1-%d) (Nhấn Enter để hủy): ", slMon);
                    fgets(bufMon, sizeof(bufMon), stdin);
                    
                    if (strlen(thongBaoLoiMon) > 0) printf("\033[A\033[K\033[A\033[K\033[A\033[K");
                    else printf("\033[A\033[K");

                    xoaKhoangTrangThua(bufMon);

                    if (strlen(bufMon) == 0) {
                        printf(B_GRAY " [*] Đã hủy cập nhật môn học.\n" RESET);
                        break; 
                    }

                    int isNumber = 1;
                    for(int i = 0; i < strlen(bufMon); i++) {
                        if(!isdigit(bufMon[i])) { isNumber = 0; break; }
                    }

                    if (isNumber) {
                        int chonMon = atoi(bufMon);
                        if (chonMon >= 1 && chonMon <= slMon) {
                            strcpy(data_moi.mon_hoc, dsMon[chonMon - 1]);
                            printf(" -> Chọn Môn học mới (1-%d): %s\n", slMon, data_moi.mon_hoc); 
                            printf(GREEN " [+] Cập nhật môn học thành công!\n" RESET);
                            break;
                        } else {
                            sprintf(thongBaoLoiMon, RED " [!] Số không hợp lệ! Vui lòng chọn từ 1 đến %d." RESET, slMon);
                        }
                    } else {
                        strcpy(thongBaoLoiMon, RED " [!] Nhập sai! Chỉ được nhập số (Không chữ, không ký tự)." RESET);
                    }
                }
                break;
            }
            case 3: { 
                char dsQuan[24][20] = {
                    "Quận 1", "Quận 2", "Quận 3", "Quận 4", "Quận 5", "Quận 6", 
                    "Quận 7", "Quận 8", "Quận 9", "Quận 10", "Quận 11", "Quận 12", 
                    "Bình Thạnh", "Thủ Đức", "Gò Vấp", "Phú Nhuận", "Tân Bình", 
                    "Tân Phú", "Bình Tân", "Nhà Bè", "Hóc Môn", "Bình Chánh", 
                    "Củ Chi", "Cần Giờ"
                };
                printf(CYAN "\n --- DANH SÁCH QUẬN/HUYỆN TP.HCM (Chọn để cập nhật) ---\n" RESET);
                for (int i = 0; i < 24; i += 3) {
                    printf(" %-2d. %-15s | %-2d. %-15s | %-2d. %-15s\n", 
                           i+1, dsQuan[i], i+2, dsQuan[i+1], i+3, dsQuan[i+2]);
                }
                
                char thongBaoLoiKV[200] = "";
                char bufKV[10];
                
                while(1) {
                    if (strlen(thongBaoLoiKV) > 0) printf("%s\n", thongBaoLoiKV);
                    else printf("\n");

                    printf(" -> Chọn Khu vực mới (1-24) (Nhấn Enter để hủy): ");
                    fgets(bufKV, sizeof(bufKV), stdin);
                    
                    if (strlen(thongBaoLoiKV) > 0) printf("\033[A\033[K\033[A\033[K\033[A\033[K");
                    else printf("\033[A\033[K");

                    xoaKhoangTrangThua(bufKV);

                    if (strlen(bufKV) == 0) {
                        printf(B_GRAY " [*] Đã hủy cập nhật khu vực.\n" RESET);
                        break; 
                    }

                    int isNumber = 1;
                    for(int i = 0; i < strlen(bufKV); i++) {
                        if(!isdigit(bufKV[i])) { isNumber = 0; break; }
                    }

                    if (isNumber) {
                        int chonKV = atoi(bufKV);
                        if (chonKV >= 1 && chonKV <= 24) {
                            strcpy(data_moi.khu_vuc, dsQuan[chonKV - 1]);
                            printf(" -> Chọn Khu vực mới (1-24): %s\n", data_moi.khu_vuc); 
                            printf(GREEN " [+] Cập nhật khu vực thành công!\n" RESET);
                            break;
                        } else {
                            strcpy(thongBaoLoiKV, RED " [!] Số không hợp lệ! Vui lòng chọn từ 1 đến 24." RESET);
                        }
                    } else {
                        strcpy(thongBaoLoiKV, RED " [!] Nhập sai! Chỉ được nhập số (Không chữ, không ký tự)." RESET);
                    }
                }
                break;
            }
            case 4: { 
                char thongBaoLoiTD[200] = "";
                while(1) {
                    if (strlen(thongBaoLoiTD) > 0) printf("%s\n", thongBaoLoiTD);
                    else printf("\n");

                    printf(" -> Nhập Trình độ mới (Nhấn Enter để hủy): ");
                    fgets(buffer, sizeof(buffer), stdin); 
                    
                    if (strlen(thongBaoLoiTD) > 0) printf("\033[A\033[K\033[A\033[K");
                    else printf("\033[A\033[K");

                    xoaKhoangTrangThua(buffer);
                    
                    if (strlen(buffer) == 0) {
                        printf(B_GRAY " [*] Đã hủy cập nhật trình độ.\n" RESET);
                        break; 
                    }

                    if (laTrinhDoHopLe(buffer)) { 
                        strcpy(data_moi.trinh_do, buffer); 
                        printf(GREEN " [+] Cập nhật trình độ thành công: %s\n" RESET, data_moi.trinh_do);
                        break; 
                    }
                    strcpy(thongBaoLoiTD, RED " [!] Trình độ sai định dạng! Vui lòng nhập lại." RESET);
                }
                break;
            }
            case 5: { 
                char thongBaoLoiSDT[200] = "";
                while(1) {
                    if (strlen(thongBaoLoiSDT) > 0) printf("%s\n", thongBaoLoiSDT);
                    else printf("\n");

                    printf(" -> Nhập Số điện thoại mới (Nhấn Enter để hủy): ");
                    fgets(buffer, sizeof(buffer), stdin); 
                    
                    if (strlen(thongBaoLoiSDT) > 0) printf("\033[A\033[K\033[A\033[K");
                    else printf("\033[A\033[K");

                    xoaKhoangTrangThua(buffer);
                    
                    if (strlen(buffer) == 0) {
                        printf(B_GRAY " [*] Đã hủy cập nhật số điện thoại.\n" RESET);
                        break; 
                    }

                    if (laSDTHopLe(buffer)) { 
                        strcpy(data_moi.sdt, buffer); 
                        printf(GREEN " [+] Cập nhật số điện thoại thành công: %s\n" RESET, data_moi.sdt);
                        break; 
                    }
                    strcpy(thongBaoLoiSDT, RED " [!] Số điện thoại sai định dạng! Phải đủ 10 số và bắt đầu bằng số 0." RESET);
                }
                break;
            }
            case 6: { 
                char thongBaoLoiEmail[200] = "";
                while(1) {
                    if (strlen(thongBaoLoiEmail) > 0) printf("%s\n", thongBaoLoiEmail);
                    else printf("\n");

                    printf(" -> Nhập Email mới (Nhấn Enter để hủy): ");
                    fgets(buffer, sizeof(buffer), stdin); 
                    
                    if (strlen(thongBaoLoiEmail) > 0) printf("\033[A\033[K\033[A\033[K");
                    else printf("\033[A\033[K");

                    xoaKhoangTrangThua(buffer);
                    
                    if (strlen(buffer) == 0) {
                        printf(B_GRAY " [*] Đã hủy cập nhật Email.\n" RESET);
                        break; 
                    }

                    if (laEmailHopLe(buffer)) { 
                        strcpy(data_moi.email, buffer); 
                        printf(GREEN " [+] Cập nhật Email thành công: %s\n" RESET, data_moi.email);
                        break; 
                    }
                    strcpy(thongBaoLoiEmail, RED " [!] Email sai định dạng! Vui lòng nhập đúng chuẩn." RESET);
                }
                break;
            }
            case 7: { 
                char thongBaoLoiHP[200] = "";
                while(1) {
                    if (strlen(thongBaoLoiHP) > 0) printf("%s\n", thongBaoLoiHP);
                    else printf("\n");

                    printf(" -> Nhập Học phí mới (Nhấn Enter để hủy): ");
                    fgets(buffer, sizeof(buffer), stdin); 
                    
                    if (strlen(thongBaoLoiHP) > 0) printf("\033[A\033[K\033[A\033[K");
                    else printf("\033[A\033[K");

                    xoaKhoangTrangThua(buffer);

                    if (strlen(buffer) == 0) {
                        printf(B_GRAY " [*] Đã hủy cập nhật học phí.\n" RESET);
                        break; 
                    }

                    int validNum = 1;
                    for(int i = 0; i < strlen(buffer); i++) {
                        if(!isdigit(buffer[i])) { validNum = 0; break; }
                    }

                    if (validNum && atoi(buffer) > 0) {
                        data_moi.hoc_phi = atoi(buffer);
                        printf(GREEN " [+] Cập nhật học phí thành công: %d VND\n" RESET, data_moi.hoc_phi);
                        break;
                    } else {
                        strcpy(thongBaoLoiHP, RED " [!] Lỗi! Học phí phải là số nguyên dương (Không chữ, không âm)." RESET);
                    }
                }
                break;
            }
            case 8: { 
                char thongBaoLoiMK[200] = "";
                while(1) {
                    if (strlen(thongBaoLoiMK) > 0) printf("%s\n", thongBaoLoiMK);
                    else printf("\n");

                    printf(" -> Nhập Mật khẩu mới (Nhấn Enter để hủy): ");
                    fgets(buffer, sizeof(buffer), stdin); 
                    
                    if (strlen(thongBaoLoiMK) > 0) printf("\033[A\033[K\033[A\033[K");
                    else printf("\033[A\033[K");

                    xoaKhoangTrangThua(buffer);

                    if (strlen(buffer) == 0) {
                        printf(B_GRAY " [*] Đã hủy cập nhật mật khẩu.\n" RESET);
                        break; 
                    }

                    if (strlen(buffer) >= 3) {
                        strcpy(data_moi.mat_khau, buffer);
                        printf(GREEN " [+] Cập nhật mật khẩu thành công!\n" RESET);
                        break;
                    } else {
                        strcpy(thongBaoLoiMK, RED " [!] Mật khẩu phải có ít nhất 3 ký tự!" RESET);
                    }
                }
                break;
            }
        }
    } while (chonSua != 0);

    capNhatThongTinGiaSu(gs_Logged, data_moi);
    luuFileGiaSuTong();
    printf(GREEN "\n [=>] Cập nhật thành công!\n" RESET);
    system("pause");
}
