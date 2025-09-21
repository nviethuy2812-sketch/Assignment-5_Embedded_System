# Assignment-5_Embedded_System

## Lập trình GPIO và Giao tiếp UART (sử dụng Ngắt) trên STM32F1

### 🧾 Giới thiệu

Dự án này minh họa cách kết hợp điều khiển **GPIO** và giao tiếp **UART với ngắt** trên vi điều khiển **STM32F103C8T6**, sử dụng thư viện **Standard Peripheral Library (SPL)**.

Chương trình cho phép nhận lệnh điều khiển LED từ máy tính qua UART (ví dụ: `"ON"`, `"OFF"`), với việc xử lý dữ liệu hoàn toàn bằng **ngắt**, giúp tối ưu hóa hiệu năng và phản hồi tức thì.

---

### 🎯 Tính năng chính

- **Điều khiển LED qua GPIO**: 
  - Cấu hình chân **PA4** là Output Push-Pull để điều khiển một đèn LED.

- **UART truyền nhận**:
  - Sử dụng **USART1** ở chế độ **9600-8-N-1** để giao tiếp với máy tính.

- **Xử lý ngắt UART**:
  - Dùng ngắt **USART_IT_RXNE** để nhận dữ liệu ngay khi có byte mới đến.
  
- **Xử lý lệnh văn bản**:
  - Lưu lệnh nhận được vào bộ đệm.
  - Khi nhận ký tự xuống dòng (`\n` hoặc `\r`), lệnh sẽ được xử lý.
  - Hỗ trợ các lệnh: `"ON"` và `"OFF"` để bật/tắt LED.

---

### 🛠️ Cấu hình phần cứng

| Thành phần         | STM32F103            | Ghi chú |
|--------------------|----------------------|---------|
| **LED**            | PA4                  | Output |
| **UART TX**        | PA9                  | Kết nối đến RX của USB-to-TTL |
| **UART RX**        | PA10                 | Kết nối đến TX của USB-to-TTL |
| **Ground (GND)**   | GND                  | GND chung giữa STM32 và máy tính |

> 💡 **Yêu cầu phần mềm terminal** trên PC: PuTTY, Tera Term,...  
> Cấu hình: **Baudrate: 9600**, **Data: 8 bit**, **Stop: 1**, **Parity: None**

---

### ⚙️ Nguyên lý hoạt động

#### `led_Init()`
- Bật clock cho GPIOA.
- Cấu hình **PA4** làm output.
- Khởi tạo LED ở trạng thái **TẮT**.

#### `uart_Init()`
- Cấu hình USART1 với:
  - Baudrate: 9600
  - Chế độ: Tx/Rx
  - Ngắt **RXNE** được bật để xử lý dữ liệu đến.
- Cấu hình ngắt **USART1_IRQn** trong NVIC.

#### `USART1_IRQHandler()`
- Hàm ngắt USART được gọi khi có dữ liệu đến.
- Nếu không phải ký tự kết thúc dòng, dữ liệu sẽ được lưu vào bộ đệm `vrc_Res`.
- Nếu là ký tự kết thúc (`\r` hoặc `\n`):
  - Kết thúc chuỗi bằng `\0`.
  - Đặt cờ `vri_Stt = 1` để báo main xử lý.

#### `main()`
- Khởi tạo UART và LED.
- Gửi chuỗi `"Hello from STM32!\r\n"` khi bắt đầu.
- Trong vòng lặp chính:
  - Kiểm tra cờ `vri_Stt`.
  - Nếu có lệnh mới, so sánh nội dung:
    - `"ON"` → Bật LED.
    - `"OFF"` → Tắt LED.
  - Reset cờ và bộ đệm sau khi xử lý xong.

---

### 💻 Ví dụ hoạt động

1. Mở terminal, kết nối cổng COM (9600 baud).
2. Nhập lệnh: `ON` → LED bật.
3. Nhập lệnh: `OFF` → LED tắt.
4. Quan sát phản hồi trên LED và terminal.

---

### 📁 Cấu trúc file

