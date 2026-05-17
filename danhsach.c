#include "giasu.h"

// Khai báo biến toàn cục
Node* head = NULL;
GiaSu* ketQuaHienTai[MAX_RESULTS];
int soLuongKetQua = 0;
char danhSachGoiBuoiDay[50][100]; 
int soLuongGoiBuoiDay = 0;        
char danhSachTrinhDo[20][50]; 
int soLuongTrinhDo = 0;       

//Các hàm liên quan đến danh sách liên kết (link list)
Node* taoNode(GiaSu gs) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf(RED "Loi: Khong the cap phat bo nho (malloc)!\n" RESET);
        exit(1);
    }
    newNode->data = gs;
    newNode->next = NULL;
    return newNode;
}

void themVaoCuoi(GiaSu gs) {
    Node* newNode = taoNode(gs);
    if (head == NULL) { head = newNode; return; }
    Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

void giaiPhongDanhSach() {
    Node* current = head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current); 
        current = nextNode;
    }
    head = NULL;
}

int docFile() {
    FILE *f = fopen("giasu.txt", "r");
    if (!f) return 0;
    
    giaiPhongDanhSach(); 
    soLuongGoiBuoiDay = 0; 
    soLuongTrinhDo = 0; 

    GiaSu gs_temp;
    while (fscanf(f, "%d, %[^,], %[^,], %[^,], %f, %[^,], %[^,], %[^,], %[^,], %d\n",
        &gs_temp.id, gs_temp.ten, gs_temp.mon_hoc, gs_temp.khu_vuc,
        &gs_temp.danh_gia, gs_temp.trinh_do, gs_temp.sdt, gs_temp.email, gs_temp.buoi_day, &gs_temp.hoc_phi) != EOF) {
        
        xoaKhoangTrangThua(gs_temp.ten); xoaKhoangTrangThua(gs_temp.mon_hoc);
        xoaKhoangTrangThua(gs_temp.khu_vuc); xoaKhoangTrangThua(gs_temp.trinh_do);
        xoaKhoangTrangThua(gs_temp.buoi_day);
        
        themGoiBuoiDay(gs_temp.buoi_day);
        themTrinhDo(gs_temp.trinh_do); 
        
        themVaoCuoi(gs_temp); 
    }
    fclose(f);
    return 1;
}