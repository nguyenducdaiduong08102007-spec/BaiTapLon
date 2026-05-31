# HỆ THỐNG TÌM KIẾM VÀ QUẢN LÝ GIA SƯ TẠI TP.HCM (C CONSOLE APPLICATION)

![Language](https://img.shields.io/badge/Language-C99-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![Architecture](https://img.shields.io/badge/Architecture-Micro--Modules-orange.svg)

Dự án Bài tập lớn môn **Kỹ thuật lập trình** được thực hiện bởi sinh viên khóa K66 - Khoa Công nghệ thông tin, Trường Đại học Giao thông Vận tải Phân hiệu tại TP.Hồ Chí Minh (UTC2).

* **Giảng viên hướng dẫn:** ThS. Trần Thị Dung
* **Thành viên nhóm thực hiện:**
    1.  Ngô Thị Ngọc Ánh (MSSV: 6651071003)
    2.  Nguyễn Đức Đại Dương (MSSV: 6651071011)
    3.  Nguyễn Hoài Hận (MSSV: 6651071020)
    4.  Lê Thị Ngọc Tuyết (MSSV: 6651071091)

---

## Mục Lục
* [1. Tổng Quan Dự Án](#1-tổng-quan-dự-án)
* [2. Cấu Trúc Mã Nguồn](#2-cấu-trúc-mã-nguồn-repository-structure)
* [3. Yêu Cầu Môi Trường](#3-yêu-cầu-môi-trường-prerequisites)
* [4. Hướng Dẫn Biên Dịch Và Chạy Ứng Dụng](#4-hướng-dẫn-biên-dịch-và-chạy-ứng-dụng)
* [5. Kịch Bản Kiểm Thử Dành Cho Tester](#5-kịch-bản-kiểm-thử-dành-cho-tester)
* [6. Một Số Lưu Ý Quan Trọng Khi Chạy Thử](#6-một-số-lưu-ý-quan-trọng-khi-chạy-thử-troubleshooting)

---

## 1. Tổng Quan Dự Án
Ứng dụng được viết hoàn toàn bằng ngôn ngữ **C (tiêu chuẩn C99)** hoạt động trên giao diện dòng lệnh (Console). Hệ thống cung cấp giải pháp kết nối tối ưu giữa Gia sư (những người có nhu cầu giảng dạy) và Phụ huynh/Học sinh dựa trên bộ lọc đa tiêu chí, tự động hóa kịch bản hệ thống và tích hợp hệ thống hộp thư thông báo hai chiều.

### Các đặc điểm kỹ thuật nổi bật:
* **Kiến trúc vi mô (Micro-modules):** Chia tách toàn bộ logic nghiệp vụ ra các file riêng biệt theo nguyên lý *Single Responsibility*.
* **Quản lý bộ nhớ động:** Sử dụng cấu trúc danh sách liên kết đơn (`Singly Linked List`) để xử lý cơ sở dữ liệu trên RAM một cách vô hạn, tối ưu hóa vùng nhớ bằng cơ chế giải phóng triệt để trước khi thoát.
* **Giao diện chống trôi thông minh (Anti-scroll UI):** Ứng dụng kỹ thuật mã điều khiển hệ thống (`ANSI escape code \033[A\033[K`) giúp giao diện tự động xóa dòng nhập lỗi, giữ form nhập liệu luôn cố định trên một màn hình tĩnh.
* **Hộp thư thông báo nội bộ (Local Inbox System):** Xây dựng thuật toán xử lý đối sánh chéo đa tệp (`lophoc.txt` và `lichhen.txt`) cho phép Gia sư ứng tuyển, Phụ huynh duyệt đơn và tự động đánh trượt các đối thủ cạnh tranh cùng mã lớp.
* **Giao diện phân tầng ANSI:** Sử dụng hệ màu sắc ANSI phong phú giúp phân tầng thông tin trực quan hóa bảng biểu Console chuẩn mực, tự động căn lề bù byte chính xác cho Tiếng Việt có dấu (UTF-8).

---

## 2. Cấu Trúc Mã Nguồn (Repository Structure)

Dự án được tổ chức chặt chẽ thành các mô-đun chức năng sau:

```text
📦 DU_AN_GIA_SU
├── 📜 main.c          # Điểm khởi chạy, set bảng mã UTF-8, điều phối Menu
├── 📜 giasu.h         # Định nghĩa Struct, biến toàn cục, màu ANSI, nguyên mẫu hàm
├── 📜 danhsach.c      # Quản lý danh sách liên kết (RAM), thao tác Đọc/Ghi File
├── 📜 xuly.c          # Thuật toán tìm kiếm, chuẩn hóa chuỗi, Validate dữ liệu
├── 📜 giaodien.c      # In bảng giao diện Console, Lọc đa tiêu chí & Phân trang
├── 📜 dangkygiasu.c   # Nghiệp vụ Gia sư (Đăng ký, đăng nhập, sửa hồ sơ)
├── 📜 datlich.c       # Nghiệp vụ Phụ huynh (Đăng tin, đặt lịch, duyệt hộp thư)
├── 📄 giasu.txt       # Cơ sở dữ liệu Gia sư (Database 1)
├── 📄 lophoc.txt      # Cơ sở dữ liệu Lớp học được mở (Database 2)
└── 📄 lichhen.txt     # Nhật ký giao dịch và hộp thư thông báo (Database 3)
```

---

## 3. Yêu Cầu Môi Trường (Prerequisites)

Để hệ thống biên dịch và vận hành chính xác tất cả các chức năng nâng cao, môi trường chạy thử của **Tester** cần đảm bảo:
1.  **Hệ điều hành:** Microsoft Windows (Bắt buộc để hỗ trợ thư viện `<windows.h>` cấu hình bảng mã 65001 và lệnh dọn màn hình hệ thống `system("cls")`).
2.  **Trình biên dịch:** `GCC (GNU Compiler Collection)` phiên bản hỗ trợ C99 (Tích hợp sẵn trong Dev-C++ 5.11, MinGW hoặc cài kèm qua MSYS2 trên VS Code).

---

## 4. Hướng Dẫn Biên Dịch Và Chạy Ứng Dụng

Để tiến hành kiểm thử (Test) ứng dụng, bạn vui lòng thực hiện theo đúng 3 bước sau:

**Bước 1: Mở Terminal tại thư mục dự án**
Bật công cụ `PowerShell` hoặc `Command Prompt` (CMD) trên máy tính và di chuyển đường dẫn (`cd`) vào đúng thư mục đang chứa mã nguồn. 
*(Lưu ý: Đảm bảo các file `.txt` nằm chung thư mục với các file code `.c`).*

**Bước 2: Biên dịch hệ thống (Build)**
Copy và dán dòng lệnh sau vào Terminal để gộp 6 file mã nguồn lại thành 1 file thực thi. Bấm Enter:
```bash
gcc main.c xuly.c danhsach.c giaodien.c dangkygiasu.c datlich.c -o app_giasu.exe
```

**Bước 3: Khởi chạy ứng dụng (Run)**
Sau khi biên dịch xong, gõ lệnh sau để mở App và bắt đầu quá trình Test:
```bash
.\app_giasu.exe
```

---

## 5. Kịch Bản Kiểm Thử Dành Cho Tester

Để hỗ trợ nghiệm thu sản phẩm một cách nhanh chóng và bao phủ toàn diện tính năng, Tester hãy thực hiện theo chuỗi kịch bản dưới đây:

###  Test Case 1: Khởi tạo hệ thống & Nạp dữ liệu thành công
* **Thao tác thực hiện:** Khởi chạy `app_giasu.exe`. Chọn vai trò `Phụ huynh/Học sinh (Nhập số 1)` -> Chọn tiếp `Tìm kiếm / lọc gia sư (Nhập số 1)`.
* **Kết quả kỳ vọng:** Bảng Console hiển thị danh sách các gia sư đầy đủ thông tin, căn lề thẳng hàng, các trường học phí và đánh giá được in màu sắc nét. Chữ tiếng Việt hiển thị chính xác không bị lỗi font ô vuông.

###  Test Case 2: Đăng ký Gia sư mới & Bắt lỗi Input
* **Thao tác thực hiện:** Tại Menu chính, chọn `Phân hệ quản lý gia sư (Nhập số 2)` -> `Đăng ký (Nhập số 3)`. Tại bước nhập Học phí, hãy thử gõ chữ cái `abc` hoặc số âm.
* **Kết quả kỳ vọng:**
    * Ứng dụng **không bị crash**. Màn hình sẽ chớp nháy nhanh, xóa đi dòng chữ nhập sai và in ra cảnh báo màu đỏ yêu cầu nhập lại số nguyên dương, giữ màn hình gọn gàng.
    * Sau khi đăng ký thành công bằng dữ liệu chuẩn, mở file `giasu.txt` sẽ thấy bản ghi mới, đồng thời Điểm đánh giá mặc định là `0.0` (Sẽ in chữ `NEW` trên bảng).

###  Test Case 3: Thuật toán so khớp chuỗi chuẩn xác
* **Thao tác thực hiện:** Vào menu Lọc gia sư, tại mục nhập `Khu vực`, gõ từ khóa `Quận 1`.
* **Kết quả kỳ vọng:** Hàm `timKhuVucChuan()` kích hoạt cơ chế chặn ký tự số ở đuôi chuỗi khớp con. Kết quả trả về **CHỈ** xuất hiện gia sư `Quận 1`, tuyệt đối không dính tạp chất từ `Quận 10, Quận 11, Quận 12`.

###  Test Case 4: Bộ lọc đa tiêu chí & Sắp xếp giảm dần
* **Thao tác thực hiện:** Chọn lọc theo `Môn Toán`, `Khu vực Quận 3` và `Học phí tối đa 200000`.
* **Kết quả kỳ vọng:** * Hệ thống lọc đồng thời cả 3 điều kiện, hiển thị số lượng hồ sơ thỏa mãn ở dòng phân trang.
    * Danh sách trả về được sắp xếp ưu tiên **Rating giảm dần** từ cao xuống thấp thông qua thuật toán `qsort`.

###  Test Case 5: Kịch bản Đặt lịch & Hộp thư tự động
* **Thao tác thực hiện:** 1. Phụ huynh **Tạo lớp học mới** (tìm gia sư Toán).
    2. Một Gia sư đăng nhập, dùng tính năng **Xem lớp đang chờ** và nộp đơn ứng tuyển vào lớp đó.
    3. Phụ huynh vào **Hộp thư thông báo**, nhập SĐT của mình để xem đơn ứng tuyển. Bấm `Chấp nhận`.
* **Kết quả kỳ vọng:** Lịch hẹn chuyển sang trạng thái "ĐÃ CHẤP NHẬN". Hệ thống lập tức khóa lớp học đó lại (cập nhật ID gia sư dạy), ghi đè dữ liệu xuống `lophoc.txt`, và tự động bắn thông báo ĐÁNH TRƯỢT tới tất cả các gia sư khác lỡ nộp đơn vào cùng mã lớp này.

---

## 6. Một Số Lưu Ý Quan Trọng Khi Chạy Thử (Troubleshooting)

> **1. Lỗi không mở được file dữ liệu:** Nếu app báo chữ đỏ `Lỗi: Không thể mở file giasu.txt để đọc dữ liệu!` ngay khi vừa chạy, hãy kiểm tra chắc chắn tệp text đó đã được tạo và nằm cùng một folder với file `.exe`.
>
> **2. Lỗi font chữ Console (Ký tự loằng ngoằng):** Dù ứng dụng đã ép mã 65001, nhưng nếu Terminal của bạn đang dùng Font chữ DOS cũ, tiếng Việt sẽ bị lỗi. **Cách khắc phục:** Nhấp chuột phải vào thanh tiêu đề Console -> `Properties` (Thuộc tính) -> Tab `Font` -> Chọn font **Consolas** hoặc **Lucida Console**.
