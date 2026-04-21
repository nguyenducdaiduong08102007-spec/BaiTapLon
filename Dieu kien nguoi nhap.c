#include <stdio.h>
#include <string.h>
void XoaDong(char s[]) {
    s[strcspn(s, "\n")] = '\0';
}
int main() {
    char Mon[50];
    char KhuVuc[50];
    char ThoiKhoaBieu[100];
    float DanhGia;
    int HocPhi,TrinhDo;
    char a[][50]={"Sinh Vien Nam 1-2","Sinh Vien nam 3-4","Tot nghiep dai hoc","Giao Vien","Thac si"};
    printf("\033[1;31m|\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;34m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;37m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;31m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;31m|\033[0m\n");
    printf("\033[1;33m|\033[0m    \033[1;33mNHAP DIEU KIEN TIM KIEM\033[0m        \033[1;33m|\033[0m\n");
    printf("\033[1;32m|\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;34m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;37m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;31m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;32m|\033[0m\n");
    printf("Nhap mon hoc(khong nhap thi enter): ");
    fgets(Mon, sizeof(Mon), stdin);
    XoaDong(Mon);
    printf("Nhap khu vuc(khong nhap co th? enter): ");
    fgets(KhuVuc, sizeof(KhuVuc), stdin);
    XoaDong(KhuVuc);
    printf("Nhap danh gia toi thieu t? 0 ??n 5(khong yeu cau thi nhap 0): ");
    scanf("%f", &DanhGia);
    getchar();
    printf("Nhap thoi khoa bieu mong muon(khong nhap co the enter): ");
    fgets(ThoiKhoaBieu, sizeof(ThoiKhoaBieu), stdin);
    XoaDong(ThoiKhoaBieu);
    printf("Nhap hoc phi toi da(khong yeu cau thi ghi 0/don vi tinh bang nghin): ");
    scanf("%d", &HocPhi);
    printf("Chon Trinh Do (chon theo so,khong chon thi nhap 0): ");
    printf("\n1.Sinh Vien Nam 1-2");
    printf("\n2.sinh Vien nam 3-4");
    printf("\n3.Tot Nghiep Dai Hoc");
    printf("\n4.Giao Vien");
    printf("\n5.Thac Si");
    printf("\nTrinh do ma b?n muon:");
    scanf("%d",&TrinhDo);
printf("\033[1;31m|\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;34m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;37m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;31m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;31m|\033[0m\n");
    printf("\033[1;33m|\033[0m         \033[1;33mDIEU KIEN DA NHAP\033[0m         \033[1;33m|\033[0m\n");
    printf("\033[1;32m|\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;34m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;37m=\033[0m\033[1;36m=\033[0m\033[1;37m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;31m=\033[0m\033[1;31m=\033[0m\033[1;32m=\033[0m\033[1;33m=\033[0m\033[1;34m=\033[0m\033[1;35m=\033[0m\033[1;36m=\033[0m\033[1;32m|\033[0m\n");
    strlen(Mon)==0?printf("Mon hoc       : Khong co\n"):printf("Mon hoc       : %s\n", Mon);
    strlen(KhuVuc)==0?printf("Khu vuc       : Khong co\n"):printf("Khu vuc       : %s\n", KhuVuc);
    printf("Danh gia      : %.1f\n", DanhGia);
    strlen(ThoiKhoaBieu)==0?printf("Thoi Khoa Bieu: Khong co\n"):printf("Thoi khoa bieu: %s\n", ThoiKhoaBieu);
    printf("Hoc phi       : %d nghin\n", HocPhi);
    TrinhDo!=0?printf("Trinh Do      : %s",a[TrinhDo-1]):printf("Trinh Do      : Khong Co");

}

