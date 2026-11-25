# Nhật ký sử dụng AI

## Lịch sử

### 1
- Thời gian: 15-16/11/2026
- Người sử dụng: Ming
- Công cụ/mô hình: Claude 
- Mục đích: Cài môi trường lập trình trên Windows
- Prompt hoặc tóm tắt prompt: "Hướng dẫn cài đặt những gì cần"
- Kết quả: Các bước cài MSYS2 + g++
- Phần đã sử dụng: Toàn bộ hướng dẫn cài đặt
- Chỉnh sửa của nhóm: Chọn chạy trên Windows (thay vì WSL) để cùng môi trường 
- Kiểm chứng: g++ --version (16.2.0), git --version, code --version đều chạy được
- Commit/issue liên quan: Không có

### 2
- Thời gian: 16/11/2026
- Người sử dụng: Ming
- Công cụ/mô hình: Claude 
- Mục đích: Tạo giao diện kernel dùng chung
- Prompt hoặc tóm tắt prompt: "Ý nghĩa của đoạn code kernels.h"
- Kết quả: Giải thích từng dòng của giao diện block_matmul_add và parse_kernel
- Phần đã sử dụng: Giữ nguyên giao diện đã chốt trong kế hoạch nhóm
- Chỉnh sửa của nhóm: Không sửa giao diện
- Kiểm chứng: Biên dịch thành công cùng các file kernel
- Commit/issue liên quan: e0ed908

### 3
- Thời gian: 20/11/2026
- Người sử dụng: Ming
- Công cụ/mô hình: Claude 
- Mục đích: Viết kernel naive và chương trình kiểm thử
- Prompt hoặc tóm tắt prompt: "Tiếp tục hướng dẫn, giải thích và xây dựng kernel naive đơn giản"; "Hướng dẫn test cho kernel"
- Kết quả: Khung naive.cpp (thứ tự i-k-j, cộng dồn C += A*B), dispatch.cpp, kernels_internal.h, test ma trận 2x2
- Phần đã sử dụng: Khung code các file, ý tưởng tổ chức test và kiểm tra kết quả tính toán
- Chỉnh sửa của nhóm: "Không sửa logic"
- Kiểm chứng: Tính tay A*B = [19 22; 43 50], chương trình in OK; gọi 2 lần thì C gấp đôi (đúng tính cộng dồn)
- Commit/issue liên quan: 8c15ce8, 93dc54e

### 4
- Thời gian: 21/11/2026
- Người sử dụng: Ming
- Công cụ/mô hình: Claude 
- Mục đích: Viết chương trình đo thời gian và GFLOPS
- Prompt hoặc tóm tắt prompt: "Hướng dẫn từng bước viết file đo tốc độ"
- Kết quả: Khung bench_kernel.cpp; cách ghim CPU 0 trên Windows
- Phần đã sử dụng: Khung code bench_kernel.cpp, lệnh ghim CPU
- Chỉnh sửa của nhóm: 
- Kiểm chứng: Chạy n=256 ra dòng CSV hợp lệ; checksum xấp xỉ n^3/4 đúng ước lượng lý thuyết; checksum giống nhau giữa hai cấu hình biên dịch
- Commit/issue liên quan: fd99fb1

### 5
- Thời gian: 21-22/11/2026
- Người sử dụng: Ming
- Công cụ/mô hình: Claude 
- Mục đích: Đọc hiểu số liệu baseline
- Prompt hoặc tóm tắt prompt: "Giải thích kết quả đo baseline naive"
- Kết quả: Nhận xét O2 và O2_novec gần bằng nhau (trình biên dịch không tự vector hóa); GFLOPS giảm ở n=2048 do ma trận vượt cache L3
- Phần đã sử dụng: Phần nhận xét
- Chỉnh sửa của nhóm: Không
- Kiểm chứng: Mọi số liệu do tự đo trên máy i9-13900H, lưu nguyên trong results/baseline_naive.csv, không sửa tay; độ lệch chuẩn dưới 5%
- Commit/issue liên quan: a228c35

## Tuyên bố
Nhóm chịu trách nhiệm về tính đúng đắn, bản quyền, số liệu thực nghiệm và mọi nội dung đã nộp.