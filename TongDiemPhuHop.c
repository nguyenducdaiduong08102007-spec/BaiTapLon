void tinhTongDiem(GiaSu ds[], int n,
                  char mon[], char khuVuc[],
                  int hocPhi, char trinhDo[]) {

    for (int i = 0; i < n; i++) {
        ds[i].diem = 0; // reset

        // Mon
        if (strlen(mon) > 0 && strcmp(mon, ds[i].mon) == 0)
            ds[i].diem += 2;

        // Khu vuc
        if (strlen(khuVuc) > 0 && strcmp(khuVuc, ds[i].khuVuc) == 0)
            ds[i].diem += 2;

        // Hoc phi
        if (hocPhi > 0 && ds[i].hocPhi <= hocPhi)
            ds[i].diem += 2;

        // Trinh do
        if (strlen(trinhDo) > 0 && strcmp(trinhDo, ds[i].trinhDo) == 0)
            ds[i].diem += 2;

        // Danh gia cao
        if (ds[i].danhGia >= 4.5)
            ds[i].diem += 3;
    }
}
