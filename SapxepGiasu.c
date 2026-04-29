void Permute(GiaSu *x, GiaSu *y) {
    GiaSu temp = *x;
    *x = *y;
    *y = temp;
}
void sapXepGiasu(GiaSu ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
		    if (ds[i].diem < ds[j].diem) {
                Permute(&ds[i], &ds[j]);}
        }
    }
}
