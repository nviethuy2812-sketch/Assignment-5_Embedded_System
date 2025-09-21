# Assignment-5_Embedded_System
Chắc chắn rồi! Dưới đây là phiên bản README đã được trình bày lại một cách chuyên nghiệp, rõ ràng và đẹp mắt hơn.

#Hệ Thống Nhúng - Điều Khiển LED qua UART trên STM32F1
Dự án này là một ví dụ cơ bản về cách điều khiển các thiết bị ngoại vi (GPIO) trên vi điều khiển STM32F10x thông qua giao tiếp UART. Người dùng có thể gửi các lệnh văn bản đơn giản từ máy tính để bật hoặc tắt một đèn LED được kết nối với board.

Dự án được xây dựng bằng thư viện Standard Peripheral Library (SPL).

#Tính Năng Chính 💡
Điều khiển LED: Bật/tắt một đèn LED kết nối với chân PA4 thông qua lệnh.

Giao tiếp UART: Sử dụng USART1 để giao tiếp hai chiều với máy tính (Cấu hình: 9600 baud, 8 data bits, no parity, 1 stop bit).

Xử lý bằng ngắt (Interrupt): Nhận dữ liệu từ UART một cách hiệu quả bằng cơ chế ngắt, không làm gián đoạn luồng chính.

Phản hồi lệnh: Gửi thông báo trạng thái (batden / tatden) trở lại máy tính sau khi thực hiện lệnh.

Chức năng Echo: Tự động gửi lại các ký tự đơn lẻ được nhập vào.

#Phần Cứng Cần Thiết ⚙️
Board phát triển: STM32F103C8T6 ("Blue Pill") hoặc tương đương.

Mạch giao tiếp: Mạch chuyển USB to TTL/Serial (ví dụ: CP2102, FT232).

Linh kiện:

1 x Đèn LED (màu bất kỳ).

1 x Điện trở hạn dòng (khoảng 220Ω - 330Ω).

Công cụ:

Mạch nạp và gỡ lỗi ST-Link V2.

Dây cắm breadboard (Jumper wires).


