#include "giasu.h"
#include <windows.h> 

int main() {
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);
    if (!docFile()) {
        printf(RED "Lỗi: Không thể mở file giasu.txt để đọc dữ liệu!\n" RESET);
        return 1;
    }
    docFileLopVaLich(); 
    
    int vaiTro;

    do {
        system("cls");
        printf(BLUE"\n======================================================\n");
        printf("      CHÀO MỪNG ĐẾN VỚI HỆ THỐNG QUẢN LÝ GIA SƯ\n");
        printf("======================================================\n"RESET);
        printf(B_GREEN"  [1] Phân hệ phụ huynh / học sinh\n");
        printf("  [2] Phân hệ quản lý gia sư\n");
        printf("  [0] Thoát chương trình\n"RESET);
        printf(BLUE"======================================================\n"RESET);
        
        vaiTro = nhapLuaChonThanhCong(0, 2);

        switch (vaiTro) {
            case 1: 
                {
                    int luachon;
                    do {
                        system("cls");
                        printf(CYAN"\n======================================================\n");
                        printf("            --- MENU TÌM GIA SƯ ---\n");
                        printf("\n======================================================\n");
                        printf(B_GREEN"  [1] Tìm kiếm / lọc gia sư\n");
                        printf("  [2] Thông báo của phụ huynh\n");
                        printf("  [3] Đăng tin tạo lớp\n"); 
                        printf("  [0] Quay lại trang chủ\n"RESET);
                        printf(CYAN"\n======================================================\n"RESET);
                        
                        luachon = nhapLuaChonThanhCong(0, 3); 
                        
                        switch (luachon) {
                            case 1: system("cls"); chucNangLoc(); break; 
                            case 2: xemThongBaoPhuHuynh(); break;
                            case 3: taoLopHocMoi(); break;
                            case 0: break;
                        }
                    } while (luachon != 0);
                }
                break;

            case 2: 
                {
                    int chonPhanHeGS;
                    do {
                        system("cls");
                        printf(GREEN "======================================================\n");
                        printf("             GIA SƯ VÀ QUẢN TRỊ GIA SƯ\n");
                        printf("======================================================\n" RESET);
                        printf(CYAN"  [1] Quản trị viên ADMIN\n"); 
                        printf("  [2] Đăng nhập tài khoản gia sư\n");
                        printf("  [3] Đăng ký tài khoản gia sư\n");
                        printf("  [0] Quay lại trang chủ\n"RESET);
                        printf(GREEN"======================================================\n"RESET);
                        
                        chonPhanHeGS = nhapLuaChonThanhCong(0, 3);
                        
                        if (chonPhanHeGS == 1) {
                            char maAdmin[50];
                            int trangHienTai = 0;
                            int soDongMotTrang = 10;
                            extern Node* head; 
                            
                            system("cls");
                            printf(RED "======================================================\n");
                            printf("            QUẢN TRỊ VIÊN\n");
                            printf("======================================================\n" RESET);
                            
                            printf(" -> Nhập Mã Admin công vụ: ");
                            fgets(maAdmin, sizeof(maAdmin), stdin);
                            xoaKhoangTrangThua(maAdmin); 
                            
                            if (strcmp(maAdmin, ADMIN_CODE) != 0) {
                                printf(RED "\n [!] Sai mã Admin tối mật! Bạn không có quyền truy cập.\n" RESET);
                                system("pause");
                                continue; 
                            }
                            
                            while (1) {
                                GiaSu* tatCaGS[1000]; 
                                int tongSo = 0;
                                Node* temp = head;
                                int tongSoTrang, batDau, ketThuc, soLuongHienThi, idXoa, kqXoa;
                                char c[10]; 
                                
                                GiaSu* gsCanSua = NULL;
                                Node* p = NULL;
                                char bufAct[10];
                                char bufRate[10];
                                int act = 0;
                                float diemMoi = 0.0f;

                                system("cls");
                                printf(RED "======================================================\n");
                                printf("            QUẢN TRỊ VIÊN\n");
                                printf("======================================================\n" RESET);

                                while (temp != NULL) {
                                    tatCaGS[tongSo] = &(temp->data);
                                    tongSo++;
                                    temp = temp->next;
                                }

                                tongSoTrang = (tongSo + soDongMotTrang - 1) / soDongMotTrang;
                                if (tongSoTrang == 0) tongSoTrang = 1; 
                                
                                if (trangHienTai >= tongSoTrang) trangHienTai = tongSoTrang - 1;
                                if (trangHienTai < 0) trangHienTai = 0;

                                batDau = trangHienTai * soDongMotTrang;
                                ketThuc = batDau + soDongMotTrang;
                                if (ketThuc > tongSo) ketThuc = tongSo; 
                                soLuongHienThi = ketThuc - batDau;

                                if (tongSo == 0) {
                                    printf(B_GRAY "\n [i] Hệ thống hiện chưa có hồ sơ gia sư nào!\n" RESET);
                                } else {
                                    inBangGiaSuAdmin(&tatCaGS[batDau], soLuongHienThi);
                                    printf(B_YELLOW "\n\t\t [ TRANG %d / %d ] --- (Đang hiển thị: %d -> %d / Tổng: %d hồ sơ) \n" RESET, 
                                           trangHienTai + 1, tongSoTrang, batDau + 1, ketThuc, tongSo);
                                }

                                idXoa = nhapIDAdminHopLe(); 
                                
                                if (idXoa == 0) break; 
                                if (idXoa == -1) { 
                                    if (trangHienTai < tongSoTrang - 1) trangHienTai++;
                                    continue;
                                }
                                if (idXoa == -2) { 
                                    if (trangHienTai > 0) trangHienTai--;
                                    continue;
                                }
                                
                                p = head;
                                while(p != NULL) {
                                    if(p->data.id == idXoa) { 
                                        gsCanSua = &(p->data); 
                                        break; 
                                    }
                                    p = p->next;
                                }

                                if (gsCanSua == NULL) {
                                    printf(YELLOW "\n [!] Không tìm thấy gia sư mang Id %d.\n" RESET, idXoa);
                                } else {
                                    printf(CYAN "\n======================================================\n" RESET);
                                    printf(B_YELLOW " Đang quản lý hồ sơ của Gia sư: %s (ID: %d)\n" RESET, gsCanSua->ten, gsCanSua->id);
                                    printf("  [1] Trục xuất gia sư\n");
                                    printf("  [2] Cập nhật đánh giá\n");
                                    printf("  [0] Bỏ chọn\n");
                                    
                                    act = nhapLuaChonThanhCong(0, 2);

                                    if (act == 1) {
                                        kqXoa = xoaGiaSuTheoId(idXoa, maAdmin);
                                        if (kqXoa == 1) {
                                            printf(GREEN "\n [=>] Trục xuất thành công Gia sư ID %d khỏi hệ thống!\n" RESET, idXoa);
                                            luuFileGiaSuTong(); 
                                        } else if (kqXoa == 2) {
                                        } else {
                                            printf(RED "\n [!] Lỗi nghiêm trọng trong quá trình trục xuất!\n" RESET);
                                        }
                                    } 
                                    else if (act == 2) {
                                        printf("\n -> Nhập điểm đánh giá mới (Từ 0.0 đến 5.0): ");
                                        fgets(bufRate, sizeof(bufRate), stdin);
                                        diemMoi = atof(bufRate);
                                        
                                        if (diemMoi >= 0.0f && diemMoi <= 5.0f) {
                                            gsCanSua->danh_gia = diemMoi;
                                            luuFileGiaSuTong(); 
                                            printf(GREEN " [+] Cập nhật thành công! Gia sư hiện có %.1f sao.\n" RESET, diemMoi);
                                        } else {
                                            printf(RED " [-] Điểm không hợp lệ! Hệ thống chỉ nhận từ 0.0 đến 5.0\n" RESET);
                                        }
                                    }
                                    else if (act == 0) {
                                        printf(B_GRAY "\n [*] Đã hủy thao tác quản lý hồ sơ.\n" RESET);
                                    }
                                }
                            }
                        }
                        else if (chonPhanHeGS == 2) {
                            int idDN;
                            char mkDN[50];
                            char bufID[20];
                            system("cls");
                            printf(GREEN "======================================================\n");
                            printf("               ĐĂNG NHẬP PHÂN HỆ GIA SƯ\n");
                            printf("======================================================\n" RESET);
                            
                            printf(" -> Nhập ID Gia sư của bạn: ");
                            fgets(bufID, sizeof(bufID), stdin);
                            int lenID = strlen(bufID);
                            if (lenID > 0 && bufID[lenID - 1] == '\n') bufID[lenID - 1] = '\0';
                            idDN = atoi(bufID);

                            printf(" -> Nhập mật khẩu: ");
                            fgets(mkDN, sizeof(mkDN), stdin);
                            int lenMK = strlen(mkDN);
                            if (lenMK > 0 && mkDN[lenMK - 1] == '\n') mkDN[lenMK - 1] = '\0';

                            GiaSu* gs_Logged = dangNhapGiaSu(idDN, mkDN);

                            if (gs_Logged == NULL) {
                                printf(RED "\n [!] ID hoặc Mật khẩu không đúng! Đăng nhập thất bại.\n" RESET);
                                system("pause");
                            } else {
                                int chonGiaSu;
                                do {
                                    system("cls");
                                    printf(CYAN "======================================================\n");
                                    printf("    --- XIN CHÀO GIA SƯ: %s (ID: %d) ---\n", gs_Logged->ten, gs_Logged->id);
                                    printf("======================================================\n");
                                    printf("  [1] Cập nhật/Chỉnh sửa hồ sơ cá nhân\n");
                                    printf("  [2] Xem danh sách & Đăng ký nhận lớp từ Phụ huynh\n"); 
                                    printf("  [3] Hộp thư thông báo cá nhân của bạn\n");              
                                    printf("  [0] Đăng xuất\n");
                                    printf("======================================================\n"RESET);
                                    chonGiaSu = nhapLuaChonThanhCong(0, 3);

                                    switch(chonGiaSu) {
                                        case 1:
                                            giaoDienCapNhatHoSo(gs_Logged); 
                                            break;
                                        case 2: 
                                            giaSuXemVaNhanLop(gs_Logged->id); 
                                            break; 
                                        case 3: 
                                            xemThongBaoGiaSu(gs_Logged->id); 
                                            break;  
                                        case 0:
                                            printf(YELLOW "\n [=>] Đã đăng xuất tài khoản Gia sư!\n" RESET);
                                            system("pause");
                                            break;
                                    }
                                } while(chonGiaSu != 0);
                            }
                        } 
                        else if (chonPhanHeGS == 3) {
                            system("cls");
                            dangKyGiaSu(); 
                        }
                    } while (chonPhanHeGS != 0);
                }
                break;

            case 0: 
                printf(YELLOW"\nCảm ơn đã sử dụng phần mềm! Tạm biệt.\n"RESET);
                system("pause");
                break;
        }
    } while (vaiTro != 0);

    giaiPhongDanhSach();
    return 0;
}
