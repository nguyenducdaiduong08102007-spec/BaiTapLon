#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* =============================================
   KHAI BAO STRUCT (KhaiBaoStruct.c)
   ============================================= */
typedef struct {
    int id;
    char ten[50];
    char mon[30];
    char khuVuc[50];
    float danhGia;
    char trinhDo[30];
    char sdt[15];
    char email[50];
    int hocPhi;
    int diem;
} GiaSu;

/* =============================================
   DOC FILE (docfile.c)
   ============================================= */
int docFile(GiaSu ds[], int *n) {
    FILE *f = fopen("giasu.txt", "r");
    if (f == NULL) {
        printf("Khong mo duoc file giasu.txt\n");
        return 0;
    }
    *n = 0;
    while (*n < 100 &&
        fscanf(f, " %d, %[^,], %[^,], %[^,], %f, %[^,], %[^,], %[^,], %d",
            &ds[*n].id,
            ds[*n].ten,
            ds[*n].mon,
            ds[*n].khuVuc,
            &ds[*n].danhGia,
            ds[*n].trinhDo,
            ds[*n].sdt,
            ds[*n].email,
            &ds[*n].hocPhi) == 9)
    {
        /* Xoa khoang trang thua o dau chuoi */
        char *p;
        p = ds[*n].ten;    while (*p == ' ') memmove(p, p+1, strlen(p));
        p = ds[*n].mon;    while (*p == ' ') memmove(p, p+1, strlen(p));
        p = ds[*n].khuVuc; while (*p == ' ') memmove(p, p+1, strlen(p));
        p = ds[*n].trinhDo;while (*p == ' ') memmove(p, p+1, strlen(p));
        p = ds[*n].sdt;    while (*p == ' ') memmove(p, p+1, strlen(p));
        p = ds[*n].email;  while (*p == ' ') memmove(p, p+1, strlen(p));

        ds[*n].diem = 0;
        (*n)++;
    }
    fclose(f);
    return 1;
}

/* =============================================
   TINH TONG DIEM PHU HOP (TongDiemPhuHop.c)
   ============================================= */
void tinhTongDiem(GiaSu ds[], int n,
                  char mon[], char khuVuc[],
                  int hocPhi, char trinhDo[]) {
    for (int i = 0; i < n; i++) {
        ds[i].diem = 0;

        if (strlen(mon) > 0 && strcmp(mon, ds[i].mon) == 0)
            ds[i].diem += 2;

        if (strlen(khuVuc) > 0 && strcmp(khuVuc, ds[i].khuVuc) == 0)
            ds[i].diem += 2;

        if (hocPhi > 0 && ds[i].hocPhi <= hocPhi)
            ds[i].diem += 2;

        if (strlen(trinhDo) > 0 && strcmp(trinhDo, ds[i].trinhDo) == 0)
            ds[i].diem += 2;

        if (ds[i].danhGia >= 4.5)
            ds[i].diem += 3;
    }
}

/* =============================================
   SAP XEP GIA SU (SapxepGiasu.c)
   ============================================= */
void Permute(GiaSu *x, GiaSu *y) {
    GiaSu temp = *x;
    *x = *y;
    *y = temp;
}

void sapXepGiasu(GiaSu ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ds[i].diem < ds[j].diem) {
                Permute(&ds[i], &ds[j]);
            }
        }
    }
}

/* =============================================
   IN GIA SU (ingiasu.c)
   ============================================= */
void inBang(FILE *out, GiaSu ds[], int n) {
    fprintf(out, "+------+----------------------+----------+--------------+----------+--------------+----------+------------------------+\n");
    fprintf(out, "| STT  | Ten                  | Mon      | Khu vuc      | Hoc phi  | Trinh do     | Danh gia | Diem                   |\n");
    fprintf(out, "+------+----------------------+----------+--------------+----------+--------------+----------+------------------------+\n");
    for (int i = 0; i < n; i++) {
        fprintf(out, "| %-4d | %-20s | %-8s | %-12s | %-8d | %-12s | %-8.1f | %-22d |\n",
            i + 1,
            ds[i].ten,
            ds[i].mon,
            ds[i].khuVuc,
            ds[i].hocPhi,
            ds[i].trinhDo,
            ds[i].danhGia,
            ds[i].diem);
    }
    fprintf(out, "+------+----------------------+----------+--------------+----------+--------------+----------+------------------------+\n");
}

void inThongTin(GiaSu ds[], int n) {
    FILE *f = fopen("ketqua.txt", "w");
    if (f == NULL) {
        printf("Khong mo duoc file de ghi ket qua.\n");
    }

    printf("\n\033[1;33mDANH SACH GIA SU PHU HOP:\033[0m\n");
    inBang(stdout, ds, n);

    if (f != NULL) {
        fprintf(f, "DANH SACH GIA SU PHU HOP:\n");
        inBang(f, ds, n);
        fclose(f);
        printf("\033[1;32m(Ket qua da duoc luu vao file ketqua.txt)\033[0m\n");
    }
}

/* =============================================
   TIEN ICH & GIAO DIEN
   ============================================= */
void XoaDong(char s[]) {
    s[strcspn(s, "\n")] = '\0';
}

void inKhungTieuDe(const char *tieuDe) {
    printf("\033[1;31m+\033[0m");
    for (int i = 0; i < 35; i++) printf("\033[1;3%dm=\033[0m", (i % 6) + 1);
    printf("\033[1;31m+\033[0m\n");
    printf("\033[1;33m| %-35s|\033[0m\n", tieuDe);
    printf("\033[1;32m+\033[0m");
    for (int i = 0; i < 35; i++) printf("\033[1;3%dm=\033[0m", (i % 6) + 1);
    printf("\033[1;32m+\033[0m\n");
}

void hienThiMenu() {
    printf("\n");
    inKhungTieuDe("  HE THONG TIM KIEM GIA SU TP.HCM  ");
    printf("\033[1;36m|  1. Tim kiem gia su               |\033[0m\n");
    printf("\033[1;36m|  2. Hien thi tat ca gia su        |\033[0m\n");
    printf("\033[1;36m|  0. Thoat                         |\033[0m\n");
    printf("\033[1;32m+\033[0m");
    for (int i = 0; i < 35; i++) printf("\033[1;3%dm=\033[0m", (i % 6) + 1);
    printf("\033[1;32m+\033[0m\n");
    printf("\033[1;33mChon chuc nang: \033[0m");
}

/* =============================================
   NHAP DIEU KIEN TIM KIEM (Dieu_kien_nguoi_nhap.c)
   ============================================= */
void nhapDieuKien(char mon[], char khuVuc[], float *danhGia,
                  int *hocPhi, char trinhDo[]) {
    inKhungTieuDe("     NHAP DIEU KIEN TIM KIEM      ");

    printf("Nhap mon hoc (bo qua -> Enter): ");
    fgets(mon, 30, stdin);
    XoaDong(mon);

    printf("Nhap khu vuc (bo qua -> Enter): ");
    fgets(khuVuc, 50, stdin);
    XoaDong(khuVuc);

    printf("Danh gia toi thieu 0-5 (bo qua -> nhap 0): ");
    scanf("%f", danhGia);
    getchar();

    printf("Hoc phi toi da (bo qua -> nhap 0, don vi: dong): ");
    scanf("%d", hocPhi);
    getchar();

    printf("Trinh do mong muon:\n");
    printf("  1. Sinh vien nam 1-2\n");
    printf("  2. Sinh vien nam 3-4\n");
    printf("  3. Dai hoc\n");
    printf("  4. Cao hoc\n");
    printf("  5. Thac si\n");
    printf("  0. Khong yeu cau\n");
    printf("Chon (0-5): ");

    int chonTrinhDo;
    scanf("%d", &chonTrinhDo);
    getchar();

    const char *trinhDoDS[] = {"", "Sinh vien nam 1-2", "Sinh vien nam 3-4",
                               "Dai hoc", "Cao hoc", "Thac si"};
    if (chonTrinhDo >= 1 && chonTrinhDo <= 5)
        strcpy(trinhDo, trinhDoDS[chonTrinhDo]);
    else
        strcpy(trinhDo, "");

    /* Hien thi lai dieu kien da nhap */
    printf("\n");
    inKhungTieuDe("        DIEU KIEN DA NHAP         ");
    strlen(mon) == 0
        ? printf("  Mon hoc    : Khong yeu cau\n")
        : printf("  Mon hoc    : %s\n", mon);
    strlen(khuVuc) == 0
        ? printf("  Khu vuc   : Khong yeu cau\n")
        : printf("  Khu vuc   : %s\n", khuVuc);
    *danhGia > 0
        ? printf("  Danh gia  : >= %.1f\n", *danhGia)
        : printf("  Danh gia  : Khong yeu cau\n");
    *hocPhi > 0
        ? printf("  Hoc phi   : <= %d dong\n", *hocPhi)
        : printf("  Hoc phi   : Khong yeu cau\n");
    strlen(trinhDo) == 0
        ? printf("  Trinh do  : Khong yeu cau\n")
        : printf("  Trinh do  : %s\n", trinhDo);
    printf("\033[1;32m+\033[0m");
    for (int i = 0; i < 35; i++) printf("=");
    printf("\033[1;32m+\033[0m\n");
}

/* =============================================
   CHON VA HIEN THI THONG TIN LIEN LAC
   ============================================= */
void chonGiaSu(GiaSu ds[], int n) {
    if (n == 0) {
        printf("\033[1;31mKhong co gia su nao phu hop!\033[0m\n");
        return;
    }

    printf("\n\033[1;33mNhap STT gia su ban muon xem (0 = bo qua): \033[0m");
    int stt;
    scanf("%d", &stt);
    getchar();

    if (stt < 1 || stt > n) {
        printf("\033[1;33mKhong chon gia su. Quay ve menu.\033[0m\n");
        return;
    }

    GiaSu *gs = &ds[stt - 1];
    printf("\n");
    inKhungTieuDe("     THONG TIN LIEN LAC GIA SU    ");
    printf("  Ten         : \033[1;32m%s\033[0m\n", gs->ten);
    printf("  Mon day     : %s\n", gs->mon);
    printf("  Khu vuc     : %s\n", gs->khuVuc);
    printf("  Trinh do    : %s\n", gs->trinhDo);
    printf("  Danh gia    : %.1f / 5.0\n", gs->danhGia);
    printf("  Hoc phi     : %d dong/buoi\n", gs->hocPhi);
    printf("  So dien thoai: \033[1;36m%s\033[0m\n", gs->sdt);
    printf("  Email       : \033[1;36m%s\033[0m\n", gs->email);
    printf("\033[1;32m+\033[0m");
    for (int i = 0; i < 35; i++) printf("=");
    printf("\033[1;32m+\033[0m\n");
}

/* =============================================
   MAIN
   ============================================= */
int main() {
    GiaSu ds[100];
    int n = 0;

    /* Doc du lieu tu file */
    if (!docFile(ds, &n)) {
        printf("\033[1;31mLoi: Khong the doc file du lieu. Kiem tra file giasu.txt.\033[0m\n");
        return 1;
    }
    printf("\033[1;32mDa tai %d gia su tu file.\033[0m\n", n);

    int luaChon;
    do {
        hienThiMenu();
        scanf("%d", &luaChon);
        getchar();

        if (luaChon == 1) {
            /* --- TIM KIEM GIA SU --- */
            char mon[30] = "", khuVuc[50] = "", trinhDo[30] = "";
            float danhGia = 0;
            int hocPhi = 0;

            nhapDieuKien(mon, khuVuc, &danhGia, &hocPhi, trinhDo);

            /* Tinh diem, co tinh kem dieu kien danh gia toi thieu */
            tinhTongDiem(ds, n, mon, khuVuc, hocPhi, trinhDo);

            /* Loc bo nhung gia su khong dat danh gia toi thieu */
            GiaSu ketQua[100];
            int soKq = 0;
            for (int i = 0; i < n; i++) {
                if (danhGia == 0 || ds[i].danhGia >= danhGia) {
                    ketQua[soKq++] = ds[i];
                }
            }

            /* Sap xep */
            sapXepGiasu(ketQua, soKq);

            /* Hien thi */
            inThongTin(ketQua, soKq);

            /* Chon gia su */
            chonGiaSu(ketQua, soKq);

        } else if (luaChon == 2) {
            /* --- HIEN THI TAT CA --- */
            printf("\n\033[1;33mTOAN BO DANH SACH GIA SU:\033[0m\n");
            inBang(stdout, ds, n);

        } else if (luaChon != 0) {
            printf("\033[1;31mLua chon khong hop le. Vui long chon lai.\033[0m\n");
        }

    } while (luaChon != 0);

    printf("\033[1;33mCam on ban da su dung chuong trinh. Tam biet!\033[0m\n");
    return 0;
}
