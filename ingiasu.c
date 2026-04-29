void inBang(FILE *out, GiaSu ds[], int n) {
    fprintf(out, "+----+----------------------+----------+--------------+--------+--------------+------------+----------------------+--------+\n");
    fprintf(out, "| ID | Ten                  | Mon      | Khu vuc      | Phi    | Trinh do     | Danh gia   | Email                | SDT    |\n");
    fprintf(out, "+----+----------------------+----------+--------------+--------+--------------+------------+----------------------+--------+\n");
    for (int i = 0; i < n; i++) {
        fprintf(out, "| %-2d | %-20s | %-8s | %-12s | %-6d | %-12s | %-10.1f | %-20s | %-6d |\n",
            ds[i].id,
            ds[i].ten,
            ds[i].mon,
            ds[i].khuVuc,
            ds[i].hocPhi,
            ds[i].trinhDo,
            ds[i].danhGia,
            ds[i].email,
            ds[i].sdt);
    }
    fprintf(out, "+----+----------------------+----------+--------------+--------+--------------+------------+----------------------+--------+\n");
}
void inThongTin(GiaSu ds[], int n) {
    FILE *f = fopen("ketqua.txt", "w");
    if (f == NULL) {
        printf("Khong mo duoc file\n");
        return;
    }
    printf("\nDANH SACH GIA SU:\n");
    inBang(stdout, ds, n);
    fprintf(f, "DANH SACH GIA SU:\n");
    inBang(f, ds, n);

    fclose(f);
}
