#include "giasu.h"

Node* head = NULL;
GiaSu* ketQuaHienTai[MAX_RESULTS];
int soLuongKetQua = 0;

char danhSachGoiBuoiDay[50][100]; 
int soLuongGoiBuoiDay = 0;        

char danhSachTrinhDo[20][50]; 
int soLuongTrinhDo = 0;       

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
    if (head == NULL) { 
        head = newNode; 
        return; 
    }
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
    FILE* f = fopen("giasu.txt", "r");
    if (f == NULL) return 0; 

    char buffer[1000]; 
    
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        int len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }
        if (len == 0) continue; 

        GiaSu gs;
        char* token;

        token = strtok(buffer, "|");
        if (token != NULL) gs.id = atoi(token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(gs.mat_khau, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(gs.ten, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(gs.mon_hoc, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(gs.khu_vuc, token);

        token = strtok(NULL, "|");
        if (token != NULL) gs.danh_gia = atof(token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(gs.trinh_do, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(gs.sdt, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(gs.email, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(gs.buoi_day, token);

        token = strtok(NULL, "|");
        if (token != NULL) gs.hoc_phi = atoi(token);

        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = gs;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    fclose(f);
    return 1; 
}

int xoaGiaSuTheoId(int id, const char* ma_admin) {
    if (strcmp(ma_admin, ADMIN_CODE) != 0) return -1; 

    Node* current = head;
    Node* previous = NULL;

    while (current != NULL && current->data.id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) return 0; 

    printf(B_YELLOW "\n [?] Ban co chac chan muon truc xuat Gia su [%s - ID: %d] khong? (Y/N): " RESET, current->data.ten, current->data.id);
    
    char xacNhan;
    scanf(" %c", &xacNhan); 
    
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 

    if (xacNhan != 'Y' && xacNhan != 'y') {
        printf(B_GRAY " [*] Da huy thao tac truc xuat. Gia su van an toan!\n" RESET);
        return 2; 
    }

    if (previous == NULL) head = current->next; 
    else previous->next = current->next;        

    free(current);
    return 1; 
}

GiaSu* timGiaSuTheoId(int id) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            return &(current->data); 
        }
        current = current->next;
    }
    return NULL; 
}
