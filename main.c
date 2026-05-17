#include "giasu.h"

void hienThiToanBo() {
    soLuongKetQua = 0;
    Node* current = head;
    while (current != NULL && soLuongKetQua < MAX_RESULTS) {
        ketQuaHienTai[soLuongKetQua++] = &(current->data);
        current = current->next;
    }
    if (soLuongKetQua > 0) {
        qsort(ketQuaHienTai, soLuongKetQua, sizeof(GiaSu*), cmpRateGiamDan);
    }
    
    // In cái bảng ra
    inBangGiaSu(ketQuaHienTai, soLuongKetQua);
    // Nếu có gia sư trong bảng thì mới gọi tính năng nhập ID xem chi tiết
    if (soLuongKetQua > 0) {
        xemChiTietGiaSu();
    }
}

int main() {
    if (!docFile()) {
        printf("Loi: Khong the mo file giasu_update.txt de doc du lieu!\n");
        return 1;
    }

    char buffer[10];
    int vaiTro;

    do {
        // Menu 1: Phân quyền truy cập của người dùng 
        system("cls");

        printf(BLUE"\n======================================================\n");
        printf("           CHAO MUNG DEN VOI HE THONG GIA SU\n");
        printf("======================================================\n"RESET);
        printf(" Ban la ai?\n");
        printf("  1. Toi la Gia Su (Muon dang ky ho so day kem)\n");
        printf("  2. Toi la Phuhuynh/Hoc sinh (Muon tim gia su)\n");
        printf("  0. Thoat chuong trinh\n");
        printf("======================================================\n");
        printf(" -> Lua chon cua ban: ");
        gets(buffer);
        vaiTro = atoi(buffer);

        switch (vaiTro) {
            case 1://Gia Sư
            system("cls");
                //Gọi hàm ghi file
                dangKyGiaSu();
                break;
                
            case 2://Phụ huynh, học sinh tìm gia sư
                //Menu 2: Lọc gia sư
                {
                    
                    int luachon;
                    do {system("cls");
                        printf(CYAN"\n======================================================\n");
                        printf("            --- MENU CHO NGUOI TIM GIA SU ---\n");
                        printf("\n======================================================\n"RESET);

                        printf("  1. Xem toan bo danh sach Gia su\n");
                        printf("  2. Tim kiem / Loc Gia su (Theo tieu chi)\n");
                        printf("  0. Quay lai trang chu\n");
                        printf(" -> Nhap lua chon: ");
                        gets(buffer);
                        luachon = atoi(buffer);

                        switch (luachon) {
                            case 1: system("cls"); hienThiToanBo(); break;
                            case 2: system("cls"); chucNangLoc(); break;
                            case 0: break; // Quay lại chọn thân phận
                            default: printf("\nLoi: Lua chon khong hop le!\n");
                        }
                    } while (luachon != 0);
                }
                break;

            case 0:
                printf(YELLOW"\nCam on da su dung phan mem! Tam biet.\n"RESET);
                system("pause");
                break;
                
            default:
                printf("\nLoi: Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (vaiTro != 0);

    giaiPhongDanhSach();
    return 0;
}
