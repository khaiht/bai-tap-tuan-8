#include <stdio.h>

#define MAX 100  // Giới hạn số lượng sinh viên

// Cấu trúc ngày tháng năm sinh của sinh viên
typedef struct {
    int ngay, thang, nam;
} Ngay;

// Cấu trúc thông tin của sinh viên
typedef struct {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
} SinhVien;

// Cấu trúc Node của danh sách liên kết
typedef struct {
    SinhVien data;
    int link;  // Chỉ số liên kết đến Node tiếp theo
} Node;

// Cấu trúc quản lý danh sách bằng mảng tĩnh
typedef struct {
    Node nodes[MAX];  // Mảng chứa các Node
    int first;        // Chỉ số phần tử đầu tiên
    int last;         // Chỉ số phần tử cuối cùng
    int size;         // Số lượng phần tử trong danh sách
} List;

// Hàm khởi tạo danh sách rỗng
void init(List* list) {
    list->first = -1;  // Danh sách rỗng
    list->last = -1;
    list->size = 0;
}

// Hàm tự cài đặt so sánh chuỗi
int compareStrings(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)s1 - (unsigned char)s2;
}

// Hàm tự cài đặt sao chép chuỗi
void copyString(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';  // Kết thúc chuỗi
}

// Hàm thêm sinh viên vào danh sách liên kết theo thứ tự mã sinh viên
void insert(List* list, SinhVien sv) {
    if (list->size >= MAX) {
        printf("Danh sach da day!\n");
        return;
    }

    int newIndex = list->size++;  // Tạo chỉ số cho phần tử mới
    list->nodes[newIndex].data = sv;  // Gán dữ liệu sinh viên vào Node mới
    list->nodes[newIndex].link = -1;  // Node mới sẽ liên kết đến NULL

    if (list->first == -1 || compareStrings(list->nodes[list->first].data.maSV, sv.maSV) > 0) {
        // Thêm vào đầu danh sách nếu danh sách rỗng hoặc mã sinh viên nhỏ hơn đầu danh sách
        list->nodes[newIndex].link = list->first;
        list->first = newIndex;
        if (list->last == -1) {
            list->last = newIndex;
        }
    } else {
        int current = list->first;
        while (list->nodes[current].link != -1 && compareStrings(list->nodes[list->nodes[current].link].data.maSV, sv.maSV) < 0) {
            current = list->nodes[current].link;
        }
        // Chèn sinh viên mới vào sau current
        list->nodes[newIndex].link = list->nodes[current].link;
        list->nodes[current].link = newIndex;
        if (list->nodes[newIndex].link == -1) {
            list->last = newIndex;
        }
    }
}

// Hàm in ra danh sách sinh viên
void printList(List list) {
    int current = list.first;
    while (current != -1) {
        printf("Ma SV: %s\n", list.nodes[current].data.maSV);
        printf("Ho ten: %s\n", list.nodes[current].data.hoTen);
        printf("Gioi tinh: %s\n", list.nodes[current].data.gioiTinh == 1 ? "Nam" : "Nu");
        printf("Ngay sinh: %02d/%02d/%04d\n", list.nodes[current].data.ngaySinh.ngay, list.nodes[current].data.ngaySinh.thang, list.nodes[current].data.ngaySinh.nam);
        printf("Dia chi: %s\n", list.nodes[current].data.diaChi);
        printf("Lop: %s\n", list.nodes[current].data.lop);
        printf("Khoa: %s\n", list.nodes[current].data.khoa);
        printf("\n");
        current = list.nodes[current].link;
    }
}

// Hàm nhập thông tin sinh viên từ bàn phím
SinhVien nhapSinhVien() {
    SinhVien sv;
    printf("Nhap ma sinh vien: ");
    scanf("%s", sv.maSV);

    printf("Nhap ho ten: ");
    getchar(); // Để xóa bỏ ký tự newline còn sót lại sau lệnh scanf
    fgets(sv.hoTen, sizeof(sv.hoTen), stdin);
    sv.hoTen[strcspn(sv.hoTen, "\n")] = 0; // Loại bỏ ký tự newline nếu có

    printf("Nhap gioi tinh (1: Nam, 0: Nu): ");
    scanf("%d", &sv.gioiTinh);

    printf("Nhap ngay sinh (dd mm yyyy): ");
    scanf("%d %d %d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);

    printf("Nhap dia chi: ");
    getchar(); // Xóa newline
    fgets(sv.diaChi, sizeof(sv.diaChi), stdin);
    sv.diaChi[strcspn(sv.diaChi, "\n")] = 0;

    printf("Nhap lop: ");
    scanf("%s", sv.lop);

    printf("Nhap khoa: ");
    scanf("%s", sv.khoa);

    return sv;
}

int main() {
    List list;
    init(&list);

    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Nhap thong tin sinh vien thu %d:\n", i + 1);
        SinhVien sv = nhapSinhVien();
        insert(&list, sv);
    }

    printf("\nDanh sach sinh vien:\n");
    printList(list);

    return 0;
}