#include "giasu.h"

//Xem chi tiết thông tin gia sư và đặt lịch
int xemChiTietGiaSu() {
    char buffer[100];
    int idChon;
    
    do {
        printf(GREEN "\n -> Nhap ID gia su de xem chi tiet " RED "(Hoac nhap 0 de thoat ra): " RESET);
        gets(buffer);
        idChon = atoi(buffer);
        
        if (idChon != 0) {
            int timThay = 0;
            Node* temp = head;
            
            while (temp != NULL) {
                if (temp->data.id == idChon) {
                    timThay = 1;
                    
                    printf(PURPLE "\n+--------------------------------------------------+\n");
                    printf("|              HO SO CHI TIET GIA SU               |\n");
                    printf("+--------------------------------------------------+\n" RESET);
                    printf("  - ID Ho so   : " YELLOW "%d\n" RESET, temp->data.id);
                    printf("  - Ho va Ten  : " CYAN "%s\n" RESET, temp->data.ten);
                    printf("  - Mon day    : %s\n", temp->data.mon_hoc);
                    printf("  - Khu vuc    : %s\n", temp->data.khu_vuc);
                    printf("  - Trinh do   : %s\n", temp->data.trinh_do);
                    printf("  - Buoi day   : %s\n", temp->data.buoi_day);
                    printf("  - Hoc phi    : " GREEN "%d VND/thang\n" RESET, temp->data.hoc_phi);
                    printf("  - Danh gia   : " YELLOW "%.1f / 5.0 Sao\n" RESET, temp->data.danh_gia);
                    printf(PURPLE "+--------------------------------------------------+\n");
                    printf("|                 THONG TIN LIEN HE                |\n");
                    printf("+--------------------------------------------------+\n" RESET);
                    printf("  - Dien thoai : " CYAN "%s\n" RESET, temp->data.sdt);
                    printf("  - Email      : " CYAN "%s\n" RESET, temp->data.email);
                    printf(PURPLE "+--------------------------------------------------+\n" RESET);
                    
                    printf(YELLOW "\n   Ban co muon dat lich hoc voi gia su nay khong?\n" RESET);
                    printf("   1. Co, toi muon de lai thong tin dat lich\n");
                    printf("   0. Khong, quay lai de xem nguoi khac\n");
                    printf(GREEN "   -> Lua chon cua ban: " RESET);
                    gets(buffer);
                    int chonDatLich = atoi(buffer);

                    if (chonDatLich == 1) {
                        char tenPH[100], sdtPH[20], loiNhan[200];
                        system("cls");
                        printf(CYAN "\n   --- NHAP THONG TIN LIEN HE CUA BAN ---\n" RESET);
                        printf("   - Ten cua ban / Phu huynh: "); gets(tenPH);
                        printf("   - So dien thoai lien he: "); gets(sdtPH);
                        printf("   - Loi nhan: "); gets(loiNhan);

                        FILE *f = fopen("datlich.txt", "a");
                        if (f != NULL) {
                            fprintf(f, ">> DAT LICH GIA SU ID: %d (%s)\n", temp->data.id, temp->data.ten);
                            fprintf(f, "- Khach hang : %s\n", tenPH);
                            fprintf(f, "- So DT      : %s\n", sdtPH);
                            fprintf(f, "========================================\n\n");
                            fclose(f);
                            
                            printf(YELLOW "\n   Dang gui thong tin ve Tong dai... Vui long doi giay lat!\n" RESET);
                        

                            FILE *ps = fopen("sendmail.ps1", "w");
                            if (ps != NULL) {
                                fprintf(ps, "$EmailTongDai = 'hanfacebookdmm@gmail.com'\n");
                                fprintf(ps, "$Pass = 'ocyk mtjc xizu bgsx'\n"); 
                                fprintf(ps, "$Subject = 'TUTOR SYSTEM: Co khach dat lich voi gia su %s'\n", temp->data.ten);
                                fprintf(ps, "$Body = '--- THONG TIN KHACH HANG ---\n");
                                fprintf(ps, "Ho ten: %s\n", tenPH);
                                fprintf(ps, "So DT: %s\n", sdtPH);
                                fprintf(ps, "Loi nhan: %s\n\n", loiNhan);
                                fprintf(ps, "--- THONG TIN GIA SU BI DAT ---\n");
                                fprintf(ps, "ID: %d\n", temp->data.id);
                                fprintf(ps, "Ten Gia Su: %s\n", temp->data.ten);
                                fprintf(ps, "Mon day: %s\n", temp->data.mon_hoc);
                                fprintf(ps, "Lien he: %s - %s'\n", temp->data.sdt, temp->data.email);

                                fprintf(ps, "$SMTP = New-Object Net.Mail.SmtpClient('smtp.gmail.com', 587)\n");
                                fprintf(ps, "$SMTP.EnableSsl = $true\n");
                                fprintf(ps, "$SMTP.Credentials = New-Object System.Net.NetworkCredential($EmailTongDai, $Pass)\n");
                                fprintf(ps, "$SMTP.Send($EmailTongDai, $EmailTongDai, $Subject, $Body)\n");
                                fclose(ps);

                                system("powershell -ExecutionPolicy Bypass -WindowStyle Hidden -File sendmail.ps1");
                                remove("sendmail.ps1");

                                printf(BG_GREEN B_WHITE BOLD "\n GUI TONG DAI THANH CONG! " RESET GREEN " Ban se som nhan duoc phan hoi.\n" RESET);
                                printf("\n");
                                system("pause");
                                return 1;
                            }
                        }
                    }
                    system("cls"); 
                    inBangGiaSu(ketQuaHienTai, soLuongKetQua); 
                    break; 
                }
                temp = temp->next;
            }
            if (timThay == 0) printf(RED " => LOI: Khong tim thay ho so nao mang ID %d. Vui long nhap lai!\n" RESET, idChon);
        }
    } while (idChon != 0); 
    
    return 0;
}