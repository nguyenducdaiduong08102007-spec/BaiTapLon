int docFile(GiaSu ds[], int *n) {
    FILE *f = fopen("giasu.txt", "r");
    if (f == NULL) {
        printf("Khong mo duoc file\n");
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
        ds[*n].diem = 0;
        (*n)++;
    }
    fclose(f);
    return 1;
}