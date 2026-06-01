#include "giasu.h"

void inChuoiUTF8(char* str, int width) {
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] & 0xC0) != 0x80) {
            len++;
        }
    }
    printf("%s", str); 
    for (int i = 0; i < width - len; i++) {
        printf(" ");   
    }
}

void inBangGiaSu(GiaSu* arr[], int n) {
    if (n == 0) {
        printf(RED "\n=> Không tìm thấy gia sư nào phù hợp!\n" RESET);
        return;
    }
    
    printf(B_PINK"\n==================================================================================================================================================\n");
    
    printf("| %-5s | ", "ID");
    inChuoiUTF8("Họ và Tên", 25); printf(" | ");
    inChuoiUTF8("Môn Học", 12); printf(" | ");
    inChuoiUTF8("Khu Vực", 15); printf(" | ");
    inChuoiUTF8("Trình Độ", 15); printf(" | ");
    inChuoiUTF8("Buổi Dạy Rảnh", 32); printf(" | ");
    
    inChuoiUTF8("Học Phí", 12); printf(" | ");
    printf("%-5s |\n", "Rate");
    
    printf("==================================================================================================================================================\n"RESET);
    
    for (int i = 0; i < n; i++) {
        char lichTong[250];
        dichMatrixThanhChu(arr[i]->buoi_day, lichTong);

        char dong1_lich[40] = ""; char dong2_lich[100] = "";
        char tempLich[250]; strcpy(tempLich, lichTong);
        
        char* token = strtok(tempLich, " ");
        while (token != NULL) {
            if (strlen(dong1_lich) == 0) strcpy(dong1_lich, token);
            else if (strlen(dong1_lich) + strlen(token) + 1 <= 20) { strcat(dong1_lich, " "); strcat(dong1_lich, token); }
            else {
                if (strlen(dong2_lich) == 0) strcpy(dong2_lich, token);
                else { strcat(dong2_lich, " "); strcat(dong2_lich, token); }
            }
            token = strtok(NULL, " ");
        }

        printf("| %-5d | ", arr[i]->id);
        inChuoiUTF8(arr[i]->ten, 25); printf(" | ");
        inChuoiUTF8(arr[i]->mon_hoc, 12); printf(" | ");
        inChuoiUTF8(arr[i]->khu_vuc, 15); printf(" | ");
        inChuoiUTF8(arr[i]->trinh_do, 15); printf(" | ");
        inChuoiUTF8(dong1_lich, 32); printf(" | ");

        if (arr[i]->danh_gia == 0.0) {
            printf("%-12d | %-5s |\n", arr[i]->hoc_phi, "NEW");
        } else {
            printf("%-12d | %-5.1f |\n", arr[i]->hoc_phi, arr[i]->danh_gia);
        }
               
        if (strlen(dong2_lich) > 0) {
            printf("| %-5s | %-25s | %-12s | %-15s | %-15s | ", "", "", "", "", "");
            inChuoiUTF8(dong2_lich, 32); 
            printf(" | %-12s | %-5s |\n", "", "");
        }
        
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}

int chucNangLoc() {
    static char mon[50] = "", kv[100] = "", td[100] = "";
    int viTriKytu = -1; 
    int max_hp = 0;
    
    char buffer[100];
    int luaChonLoc;

    int trangHienTai = 0;
    int soDongMotTrang = 10;
    int tongSoTrang, batDau, ketThuc, soLuongHienThi;

    char tenThu[7][15] = {"Thứ 2", "Thứ 3", "Thứ 4", "Thứ 5", "Thứ 6", "Thứ 7", "Chủ Nhật"};
    char tenCa[3][10] = {"SÁNG", "CHIỀU", "TỐI"};

    do {
        soLuongKetQua = 0;
        Node* current = head;
        while (current != NULL) {
            int ok = 1;
            if (strlen(mon) > 0 && !timChuoi(current->data.mon_hoc, mon)) ok = 0;
            if (strlen(kv) > 0 && !timKhuVucChuan(current->data.khu_vuc, kv)) ok = 0;
            if (strlen(td) > 0 && !timChuoi(current->data.trinh_do, td)) ok = 0;
            if (viTriKytu != -1) {
                if (current->data.buoi_day[viTriKytu] == '-') ok = 0;
            }
            if (max_hp > 0 && current->data.hoc_phi > max_hp) ok = 0;

            if (ok && soLuongKetQua < MAX_RESULTS) {
                ketQuaHienTai[soLuongKetQua++] = &(current->data);
            }
            current = current->next;
        }

        if (soLuongKetQua > 0) {
            qsort(ketQuaHienTai, soLuongKetQua, sizeof(GiaSu*), cmpRateGiamDan);
        }
        
        tongSoTrang = (soLuongKetQua + soDongMotTrang - 1) / soDongMotTrang;
        if (tongSoTrang == 0) tongSoTrang = 1; 
        
        if (trangHienTai >= tongSoTrang) trangHienTai = tongSoTrang - 1;
        if (trangHienTai < 0) trangHienTai = 0;

        batDau = trangHienTai * soDongMotTrang;
        ketThuc = batDau + soDongMotTrang;
        if (ketThuc > soLuongKetQua) ketThuc = soLuongKetQua;
        soLuongHienThi = ketThuc - batDau;

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        inBangGiaSu(&ketQuaHienTai[batDau], soLuongHienThi);

        if (soLuongKetQua > 0) {
            printf(B_YELLOW "\n\t\t [ TRANG %d / %d ] --- (Đang hiển thị: %d -> %d / Tổng: %d hồ sơ) \n" RESET, 
                   trangHienTai + 1, tongSoTrang, batDau + 1, ketThuc, soLuongKetQua);
        }

        printf(CYAN "\n--- DANH SÁCH TIÊU CHÍ LỌC ĐANG ÁP DỤNG ---\n" RESET);
        if (strlen(mon) == 0 && strlen(kv) == 0 && strlen(td) == 0 && viTriKytu == -1 && max_hp == 0) {
            printf(B_GRAY " [!] Chưa có tiêu chí nào. Đang hiển thị toàn bộ hệ thống.\n" RESET);
        } else {
            if (strlen(mon) > 0) printf(GREEN " [+] Môn học   : %s\n" RESET, mon);
            if (strlen(kv) > 0) printf(GREEN " [+] Khu vực   : %s\n" RESET, kv);
            if (strlen(td) > 0) printf(GREEN " [+] Trình độ  : %s\n" RESET, td);
            if (viTriKytu != -1) {
                int thu = viTriKytu / 4;
                int ca = viTriKytu % 4;
                printf(GREEN " [+] Lịch rảnh : %s, Ca %s\n" RESET, tenThu[thu], tenCa[ca]);
            }
            if (max_hp > 0) printf(GREEN " [+] Học phí   : Dưới %d VND\n" RESET, max_hp);
        }

        printf(YELLOW "\n========================================================================\n");
        printf(" BẠN MUỐN KẾT HỢP THÊM TIÊU CHÍ NÀO HAY XEM CHI TIẾT GIA SƯ?\n");
        printf("========================================================================\n" RESET);
        printf("  1. Lọc theo Môn học\n");
        printf("  2. Lọc theo Khu vực (VD: Quận 1)\n");
        printf("  3. Lọc theo Trình độ\n");
        printf("  4. Lọc theo Thời gian rảnh (Thứ & Buổi)\n");
        printf("  5. Lọc theo Mức học phí tối đa\n");
        printf("  6. XÓA TẤT CẢ BỘ LỌC (Quay về danh sách gốc)\n");
        if (soLuongKetQua > 0) {
            printf(B_PINK "  7. XEM CHI TIẾT HỒ SƠ / ĐẶT LỊCH GIA SƯ TRONG BẢNG NÀY\n" RESET);
        }
        printf("  0. Thoát tìm kiếm (Quay lại Menu Phụ Huynh)\n");

        int maxMenu = (soLuongKetQua > 0) ? 7 : 6;
        
        printf(" -> Nhập lựa chọn (0-%d, W: Trang trước, S: Trang sau): ", maxMenu);
        luaChonLoc = nhapLuaChonTrang(0, maxMenu); 

        if (luaChonLoc == -1) { 
            if (trangHienTai < tongSoTrang - 1) trangHienTai++;
            continue; 
        }
        if (luaChonLoc == -2) { 
            if (trangHienTai > 0) trangHienTai--;
            continue; 
        }

        if (luaChonLoc >= 1 && luaChonLoc <= 6) {
            trangHienTai = 0; 
        }

        switch (luaChonLoc) {
            case 1: {
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
                    printf(B_GRAY "\n [!] Hệ thống hiện chưa có dữ liệu môn học để lọc!\n" RESET);
                    break;
                }

                printf(CYAN "\n --- DANH SÁCH MÔN HỌC HIỆN CÓ ---\n" RESET);
                for (int i = 0; i < slMon; i += 3) {
                    printf("   %-2d. %-15s", i+1, dsMon[i]);
                    if (i + 1 < slMon) printf(" | %-2d. %-15s", i+2, dsMon[i+1]);
                    if (i + 2 < slMon) printf(" | %-2d. %-15s", i+3, dsMon[i+2]);
                    printf("\n");
                }

                char thongBaoLoiMon[200] = "";
                char bufMon[20];
                
                while(1) {
                    if (strlen(thongBaoLoiMon) > 0) printf("%s\n", thongBaoLoiMon);
                    else printf("\n");

                    printf(" -> Chọn Môn học cần lọc (1-%d) (Nhấn Enter để xóa lọc): ", slMon);
                    fgets(bufMon, sizeof(bufMon), stdin);
                    
                    printf("\033[A\033[K\033[A\033[K");
                    xoaKhoangTrangThua(bufMon);

                    if (strlen(bufMon) == 0 || strcmp(bufMon, "0") == 0) {
                        strcpy(mon, ""); 
                        printf(B_GRAY " [*] Đã xóa tiêu chí lọc môn học.\n" RESET);
                        break; 
                    }

                    int isNumber = 1;
                    for(int i = 0; i < strlen(bufMon); i++) {
                        if(!isdigit(bufMon[i])) { isNumber = 0; break; }
                    }

                    if (isNumber) {
                        int chonMon = atoi(bufMon);
                        if (chonMon >= 1 && chonMon <= slMon) {
                            strcpy(mon, dsMon[chonMon - 1]); 
                            printf(" -> Chọn Môn học cần lọc (1-%d): %s\n", slMon, mon); 
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
            case 2: {
                char dsQuan[24][20] = {
                    "Quận 1", "Quận 2", "Quận 3", "Quận 4", "Quận 5", "Quận 6", 
                    "Quận 7", "Quận 8", "Quận 9", "Quận 10", "Quận 11", "Quận 12", 
                    "Bình Thạnh", "Thủ Đức", "Gò Vấp", "Phú Nhuận", "Tân Bình", 
                    "Tân Phú", "Bình Tân", "Nhà Bè", "Hóc Môn", "Bình Chánh", 
                    "Củ Chi", "Cần Giờ"
                };
                
                printf(YELLOW "\n   [Danh sách Các Quận/Huyện tại TP.HCM]\n" RESET);
                for (int i = 0; i < 24; i += 3) {
                    printf("   %-2d. %-15s %-2d. %-15s %-2d. %-15s\n", 
                           i+1, dsQuan[i], i+2, dsQuan[i+1], i+3, dsQuan[i+2]);
                }
                
                char loiKV[200] = "";
                while(1) {
                    if(strlen(loiKV) > 0) printf("%s\n", loiKV); 
                    else printf("\n");
                    
                    printf("   -> Chọn Khu vực (1-24) (Nhấn Enter để xóa lọc): ");
                    fgets(buffer, sizeof(buffer), stdin);
                    
                    printf("\033[A\033[K\033[A\033[K");
                    xoaKhoangTrangThua(buffer); 
                    
                    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
                        strcpy(kv, ""); 
                        printf(B_GRAY " [*] Đã xóa tiêu chí lọc khu vực.\n" RESET);
                        break;
                    }
                    
                    int isNumber = 1;
                    for(int i = 0; i < strlen(buffer); i++) {
                        if(!isdigit(buffer[i])) { isNumber = 0; break; } 
                    }

                    if (isNumber) {
                        int chon = atoi(buffer);
                        if (chon >= 1 && chon <= 24) {
                            char tenQuanCanTim[50];
                            strcpy(tenQuanCanTim, dsQuan[chon - 1]);
                            
                            int coGiaSu = 0;
                            Node* temp = head;
                            while (temp != NULL) {
                                if (timKhuVucChuan(temp->data.khu_vuc, tenQuanCanTim)) {
                                    coGiaSu = 1; break;
                                }
                                temp = temp->next;
                            }

                            if (coGiaSu) {
                                strcpy(kv, tenQuanCanTim); 
                                printf("   -> Chọn Khu vực cần lọc (1-24): %s\n", kv); 
                                break; 
                            } else {
                                strcpy(loiKV, RED " [!] Chưa có gia sư ở khu vực này! Vui lòng chọn quận khác." RESET);
                            }
                        } else {
                            strcpy(loiKV, RED " [!] Chọn sai! Vui lòng nhập số từ 1 đến 24." RESET);
                        }
                    } else {
                        strcpy(loiKV, RED " [!] Nhập sai! Chỉ được nhập số." RESET);
                    }
                }
                break;
            }
            case 3: {
                char dsTD[20][50]; 
                int slTD = 0;
                Node* temp = head;
                
                while (temp != NULL) {
                    int daXuatHien = 0;
                    for(int i = 0; i < slTD; i++) {
                        if(strcmp(dsTD[i], temp->data.trinh_do) == 0) { 
                            daXuatHien = 1; break; 
                        }
                    }
                    if(!daXuatHien && slTD < 20 && strlen(temp->data.trinh_do) > 0) {
                        strcpy(dsTD[slTD], temp->data.trinh_do);
                        slTD++;
                    }
                    temp = temp->next;
                }

                if (slTD == 0) {
                    printf(B_GRAY "\n [!] Hệ thống hiện chưa có dữ liệu Trình độ nào để lọc!\n" RESET);
                } else {
                    printf(YELLOW "\n   [Danh sách Trình Độ đang có trong hệ thống]\n" RESET);
                    for (int i = 0; i < slTD; i++) {
                        printf("   %d. %s\n", i + 1, dsTD[i]);
                    }
                    
                    char loiTD[200] = "";
                    while(1) {
                        if(strlen(loiTD) > 0) printf("%s\n", loiTD); else printf("\n");
                        
                        printf("   -> Chọn Trình độ (1-%d) (Nhấn Enter để xóa lọc): ", slTD);
                        fgets(buffer, sizeof(buffer), stdin);
                        
                        printf("\033[A\033[K\033[A\033[K");
                        xoaKhoangTrangThua(buffer);
                        
                        if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
                            strcpy(td, ""); 
                            printf(B_GRAY " [*] Đã xóa tiêu chí lọc trình độ.\n" RESET);
                            break;
                        }

                        int isNumber = 1;
                        for(int i = 0; i < strlen(buffer); i++) {
                            if(!isdigit(buffer[i])) { isNumber = 0; break; } 
                        }
                        
                        if (isNumber) {
                            int chon = atoi(buffer);
                            if (chon > 0 && chon <= slTD) {
                                strcpy(td, dsTD[chon - 1]); 
                                printf("   -> Chọn Trình độ cần lọc (1-%d): %s\n", slTD, td); 
                                break;
                            } else {
                                sprintf(loiTD, RED " [!] Chọn sai! Vui lòng nhập số từ 1 đến %d." RESET, slTD);
                            }
                        } else {
                            strcpy(loiTD, RED " [!] Nhập sai! Chỉ được nhập số." RESET);
                        }
                    }
                }
                break;
            }
            case 4: {
                int phThu = -1;
                int phCa = -1;
                char loiThu[200] = "";
                
                printf(YELLOW "\n   [Tìm kiếm theo Thời gian rảnh]\n" RESET);
                printf("   1. Thứ 2    2. Thứ 3    3. Thứ 4\n");
                printf("   4. Thứ 5    5. Thứ 6    6. Thứ 7\n");
                printf("   7. Chủ Nhật \n");

                while(1) {
                    if(strlen(loiThu) > 0) printf("%s\n", loiThu); else printf("\n");
                    
                    printf("   -> Chọn Thứ (1-7) (Nhấn Enter để xóa lọc): ");
                    fgets(buffer, sizeof(buffer), stdin);
                    
                    printf("\033[A\033[K\033[A\033[K");
                    xoaKhoangTrangThua(buffer);
                    
                    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
                        viTriKytu = -1; 
                        printf(B_GRAY " [*] Đã xóa tiêu chí lọc theo thời gian.\n" RESET);
                        break; 
                    }
                    
                    int isNumber = 1;
                    for(int i = 0; i < strlen(buffer); i++) {
                        if(!isdigit(buffer[i])) { isNumber = 0; break; }
                    }

                    if (isNumber) {
                        int chon = atoi(buffer);
                        if (chon >= 1 && chon <= 7) {
                            phThu = chon;
                            char strThu[20];
                            if(phThu == 7) strcpy(strThu, "Chủ Nhật");
                            else sprintf(strThu, "Thứ %d", phThu + 1);
                            
                            printf("   -> Chọn Thứ cần lọc: %s\n", strThu); 
                            break;
                        } else {
                            strcpy(loiThu, RED " [!] Chọn sai! Vui lòng nhập số từ 1 đến 7." RESET);
                        }
                    } else {
                        strcpy(loiThu, RED " [!] Nhập sai! Chỉ được nhập số." RESET);
                    }
                }

                if (phThu != -1) {
                    char loiCa[200] = "";
                    printf(YELLOW "\n   [Chọn Ca học trong ngày]\n" RESET);
                    printf("   1. Ca SÁNG   2. Ca CHIỀU   3. Ca TỐI\n");
                    
                    while(1) {
                        if(strlen(loiCa) > 0) printf("%s\n", loiCa); else printf("\n");
                        
                        printf("   -> Chọn Ca (1-3) (Nhấn Enter để hủy): ");
                        fgets(buffer, sizeof(buffer), stdin);
                        
                        printf("\033[A\033[K\033[A\033[K");
                        xoaKhoangTrangThua(buffer);
                        
                        if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
                            viTriKytu = -1; 
                            printf(B_GRAY " [*] Đã xóa tiêu chí lọc theo thời gian.\n" RESET);
                            break; 
                        }

                        int isNumber = 1;
                        for(int i = 0; i < strlen(buffer); i++) {
                            if(!isdigit(buffer[i])) { isNumber = 0; break; }
                        }

                        if (isNumber) {
                            int chon = atoi(buffer);
                            if (chon >= 1 && chon <= 3) {
                                phCa = chon;
                                char strCa[20];
                                if(phCa == 1) strcpy(strCa, "Ca SÁNG");
                                else if(phCa == 2) strcpy(strCa, "Ca CHIỀU");
                                else strcpy(strCa, "Ca TỐI");
                                
                                printf("   -> Chọn Ca cần lọc: %s\n", strCa);
                                viTriKytu = (phThu - 1) * 4 + (phCa - 1);
                                printf(GREEN " [+] Cập nhật thời gian lọc thành công!\n" RESET);
                                break;
                            } else {
                                strcpy(loiCa, RED " [!] Chọn sai! Vui lòng nhập số 1, 2 hoặc 3." RESET);
                            }
                        } else {
                            strcpy(loiCa, RED " [!] Nhập sai! Chỉ được nhập số." RESET);
                        }
                    }
                }
                break;
            }
            case 5: {
                char thongBaoLoiHP[200] = "";
                while (1) {
                    if (strlen(thongBaoLoiHP) > 0) printf("%s\n", thongBaoLoiHP);
                    else printf("\n");

                    printf(" -> Nhập Học phí tối đa (VND) (Nhấn Enter để xóa lọc): ");
                    fgets(buffer, sizeof(buffer), stdin);
                    
                    printf("\033[A\033[K\033[A\033[K");
                    xoaKhoangTrangThua(buffer);

                    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) { 
                        max_hp = 0; 
                        printf(B_GRAY " [*] Đã xóa tiêu chí lọc học phí.\n" RESET);
                        break; 
                    }

                    int loi = 0;
                    for (int i = 0; i < strlen(buffer); i++) {
                        if (!isdigit(buffer[i])) { loi = 1; break; }
                    }

                    if (loi) {
                        strcpy(thongBaoLoiHP, RED " [!] Lỗi! Học phí chỉ được nhập số, không âm, không chứa chữ." RESET);
                        continue;
                    }

                    int nhapHP = atoi(buffer);
                    if (nhapHP > 0) {
                        max_hp = nhapHP;
                        printf(" -> Nhập Học phí tối đa: %d VND\n", max_hp);
                        break; 
                    } else {
                        strcpy(thongBaoLoiHP, RED " [!] Lỗi! Học phí phải lớn hơn 0 VND." RESET);
                    }
                }
                break;
            }
            case 6: 
                strcpy(mon, ""); strcpy(kv, ""); strcpy(td, ""); viTriKytu = -1; max_hp = 0;
                printf(B_GRAY " [*] Đã xóa tất cả bộ lọc.\n" RESET);
                break;
            case 7: 
                if (soLuongKetQua > 0) {
                    int tiepTucXem = 1;
                    while (tiepTucXem) {
                        system("cls");
                        inBangGiaSu(&ketQuaHienTai[batDau], soLuongHienThi);
                        int ketQua = xemChiTietGiaSu(&ketQuaHienTai[batDau], soLuongHienThi); 
                        if (ketQua == 0) {
                            tiepTucXem = 0; 
                        }
                    }
                } else {
                    printf(RED "\n [!] Không có gia sư để xem!" RESET);
                    system("pause");
                }
                break;
            case 0:
                break; 
        }

    } while (luaChonLoc != 0);

    return 0;
}

void dichMatrixThanhChu(const char* matrix, char* ketQua) {
    char cacThuTenGoc[7][10] = {"T2", "T3", "T4", "T5", "T6", "T7", "CN"};
    int co_lich = 0;
    strcpy(ketQua, ""); 

    for (int j = 0; j < 7; j++) {
        int idx = j * 4; 
        if (matrix[idx] != '-' || matrix[idx+1] != '-' || matrix[idx+2] != '-') {
            char cumThu[30] = "";
            sprintf(cumThu, "%s(", cacThuTenGoc[j]); 
            int flag_ca = 0;
            if (matrix[idx] == 'S') { strcat(cumThu, "S"); flag_ca = 1; }
            if (matrix[idx+1] == 'C') { if (flag_ca) strcat(cumThu, ","); strcat(cumThu, "C"); flag_ca = 1; }
            if (matrix[idx+2] == 'T') { if (flag_ca) strcat(cumThu, ","); strcat(cumThu, "T"); }
            strcat(cumThu, ") "); 
            strcat(ketQua, cumThu); 
            co_lich = 1;
        }
    }
    if (!co_lich) strcpy(ketQua, "Chua co lich");
    else {
        int len = strlen(ketQua);
        if (len > 0 && ketQua[len - 1] == ' ') ketQua[len - 1] = '\0';
    }
}

void inBangGiaSuAdmin(GiaSu* arr[], int n) {
    if (n == 0) {
        printf(RED "\n=> Hệ thống hiện tại chưa có hồ sơ gia sư nào!\n" RESET);
        return;
    }
    
    int tongSoGiaSu = 0;
    Node* tempDem = head;
    while (tempDem != NULL) {
        tongSoGiaSu++;
        tempDem = tempDem->next;
    }
    
    printf(B_GREEN"\n=> TỔNG SỐ GIA SƯ TRONG HỆ THỐNG: %d hồ sơ.\n"RESET, tongSoGiaSu);
    
    printf(B_RED"\n==================================================================================================================================================\n");
    printf("| %-5s | ", "ID");
    inChuoiUTF8("Họ và Tên", 25); printf(" | ");
    inChuoiUTF8("Môn Học", 12); printf(" | ");
    inChuoiUTF8("Khu Vực", 15); printf(" | ");
    inChuoiUTF8("Trình Độ", 15); printf(" | ");
    inChuoiUTF8("Buổi Dạy Rảnh", 32); printf(" | ");
    inChuoiUTF8("Học Phí", 12); printf(" | ");
    printf("%-5s |\n", "Rate");
    printf("==================================================================================================================================================\n"RESET);
    
    for (int i = 0; i < n; i++) {
        char lichTong[250];
        dichMatrixThanhChu(arr[i]->buoi_day, lichTong);

        char dong1_lich[40] = ""; char dong2_lich[100] = "";
        char tempLich[250]; strcpy(tempLich, lichTong);
        
        char* token = strtok(tempLich, " ");
        while (token != NULL) {
            if (strlen(dong1_lich) == 0) strcpy(dong1_lich, token);
            else if (strlen(dong1_lich) + strlen(token) + 1 <= 20) { strcat(dong1_lich, " "); strcat(dong1_lich, token); }
            else {
                if (strlen(dong2_lich) == 0) strcpy(dong2_lich, token);
                else { strcat(dong2_lich, " "); strcat(dong2_lich, token); }
            }
            token = strtok(NULL, " ");
        }

        printf("| %-5d | ", arr[i]->id);
        inChuoiUTF8(arr[i]->ten, 25); printf(" | ");
        inChuoiUTF8(arr[i]->mon_hoc, 12); printf(" | ");
        inChuoiUTF8(arr[i]->khu_vuc, 15); printf(" | ");
        inChuoiUTF8(arr[i]->trinh_do, 15); printf(" | ");
        inChuoiUTF8(dong1_lich, 32); printf(" | ");

        if (arr[i]->danh_gia == 0.0) {
            printf("%-12d | %-5s |\n", arr[i]->hoc_phi, "NEW");
        } else {
            printf("%-12d | %-5.1f |\n", arr[i]->hoc_phi, arr[i]->danh_gia);
        }
               
        if (strlen(dong2_lich) > 0) {
            printf("| %-5s | %-25s | %-12s | %-15s | %-15s | ", "", "", "", "", "");
            inChuoiUTF8(dong2_lich, 32); 
            printf(" | %-12s | %-5s |\n", "", "");
        }
        
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}
