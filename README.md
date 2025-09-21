# Assignment-5_Embedded_System
STM32F1 - Điều khiển LED qua UART
Đây là một dự án cơ bản dành cho vi điều khiển STM32F10x, sử dụng thư viện Standard Peripheral Library (SPL) để điều khiển một đèn LED thông qua các lệnh gửi từ máy tính qua giao tiếp UART.

Chức năng 💡
Khởi tạo và cấu hình chân GPIO để điều khiển một đèn LED.

Khởi tạo và cấu hình USART1 để giao tiếp nối tiếp (serial communication).

Sử dụng cơ chế ngắt (interrupt) của USART để nhận dữ liệu một cách không đồng bộ.

Phân tích chuỗi lệnh nhận được để bật hoặc tắt đèn LED.

Gửi chuỗi "ON" để bật LED.

Gửi chuỗi "OFF" để tắt LED.

Gửi lại (echo) bất kỳ ký tự đơn nào nhận được.

Gửi phản hồi về máy tính sau khi thực hiện lệnh (batden hoặc tatden).

Yêu cầu phần cứng ⚙️
Board phát triển STM32F1xx (ví dụ: STM32F103C8T6 "Blue Pill").

Mạch chuyển USB to TTL/Serial (ví dụ: PL2303, CP2102, FT232).

Một đèn LED và một điện trở hạn dòng (khoảng 220Ω - 330Ω).

Dây cắm (jumper wires).

Mạch nạp và gỡ lỗi ST-Link.
