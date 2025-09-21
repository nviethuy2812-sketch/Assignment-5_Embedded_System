# Assignment-5_Embedded_System
STM32F1 Project: UART-Controlled LED
Bài tập Hệ Thống Nhúng
Tổng Quan Dự Án 📝
Đây là một firmware cơ bản cho vi điều khiển STM32F10x, trình bày phương pháp điều khiển chân GPIO (cụ thể là một đèn LED) thông qua các lệnh văn bản được gửi từ máy tính qua giao tiếp UART.

Dự án được xây dựng hoàn toàn bằng thư viện Standard Peripheral Library (SPL) của STMicroelectronics.

Các Tính Năng Nổi Bật ✨
Điều khiển Ngoại vi: Bật/tắt một đèn LED kết nối với chân PA4.

Giao tiếp Nối tiếp: Sử dụng USART1 để giao tiếp hai chiều với máy tính tại cấu hình 9600-8-N-1.

Xử lý Bất đồng bộ: Tận dụng ngắt (Interrupt) của UART để nhận dữ liệu hiệu quả mà không cần kiểm tra liên tục (polling).

Hồi đáp Thông minh: Gửi lại các chuỗi trạng thái (batden/tatden) để xác nhận lệnh đã được thực thi.

Chức năng Echo: Phản hồi ngay lập tức các ký tự đơn lẻ nhận được.
