# Assignment-5_Embedded_System
Lập trình GPIO và Giao tiếp UART (với Ngắt) trên STM32F1
Dự án này là một ví dụ minh họa cách kết hợp hoạt động của GPIO và giao tiếp UART sử dụng ngắt trên vi điều khiển STM32F103, dùng thư viện Standard Peripheral Library (SPL).

Chương trình cho phép vi điều khiển nhận lệnh văn bản (text command) từ một máy tính thông qua cổng nối tiếp để điều khiển trạng thái của một đèn LED. Toàn bộ quá trình nhận dữ liệu được xử lý bằng ngắt để tối ưu hóa hiệu năng.

Tính năng 📜
Điều khiển GPIO: Cấu hình một chân GPIO ở chế độ xuất (Output Push-Pull) để điều khiển một đèn LED duy nhất.

Giao tiếp UART: Cấu hình và sử dụng USART1 để gửi và nhận dữ liệu nối tiếp với máy tính, hoạt động như một giao diện điều khiển.

Sử dụng Ngắt UART: Cấu hình ngắt USART_IT_RXNE (Receive Not Empty) để chương trình có thể phản ứng ngay lập tức mỗi khi có byte dữ liệu mới đến mà không cần phải kiểm tra liên tục trong vòng lặp chính (polling).

Xử lý Lệnh Văn bản: Xây dựng một bộ đệm (buffer) để lưu trữ các ký tự nhận được và xử lý chuỗi lệnh hoàn chỉnh (ví dụ: "ON", "OFF") khi nhận được ký tự xuống dòng.

Cấu hình phần cứng 🛠️
Vi điều khiển: STM32F103C8T6 (Board Blue Pill hoặc tương tự).

Đèn LED:

Nối với chân PA4.

Giao tiếp Nối tiếp (với máy tính):

Nối chân PA9 (TX) của STM32 với chân RX của mạch chuyển USB-to-TTL.

Nối chân PA10 (RX) của STM32 với chân TX của mạch chuyển USB-to-TTL.

Nối chân GND của hai board với nhau.

Lưu ý: Cần một phần mềm terminal trên máy tính (như PuTTY, Tera Term) được cấu hình ở 9600 baud, 8 data bits, 1 stop bit, no parity.

Cách hoạt động của code ⌨️
Hàm led_Init():
Kích hoạt xung clock cho GPIOA.

Cấu hình chân PA4 là GPIO_Mode_Out_PP (Output Push-Pull).

Thiết lập trạng thái ban đầu cho LED là TẮT bằng hàm GPIO_SetBits().

Hàm uart_Init():
Kích hoạt xung clock cho GPIOA (cho các chân TX/RX) và USART1.

Cấu hình chân PA9 (TX) là GPIO_Mode_AF_PP (Alternate Function Push-Pull).

Cấu hình chân PA10 (RX) là GPIO_Mode_IN_FLOATING (Input Floating).

Cấu hình các tham số cho USART1 bao gồm baud rate là 9600.

Kích hoạt ngắt USART_IT_RXNE để báo hiệu khi có dữ liệu được nhận.

Kích hoạt và cài đặt độ ưu tiên cho trình phục vụ ngắt USART1_IRQn trong NVIC.

Hàm main():
Gọi các hàm cấu hình uart_Init() và led_Init().

Gửi một chuỗi chào mừng "Hello from STM32!\r\n" đến máy tính.

Vào một vòng lặp while(1) vô tận.

Bên trong vòng lặp, chương trình chỉ kiểm tra biến cờ vri_Stt. Biến này hoạt động như một tín hiệu báo rằng trình phục vụ ngắt đã nhận xong một lệnh hoàn chỉnh.

Khi vri_Stt được bật lên, main sẽ xử lý chuỗi lệnh lưu trong bộ đệm vrc_Res. Nó so sánh chuỗi này với "ON" hoặc "OFF" để điều khiển LED.

Sau khi xử lý xong, nó xóa bộ đệm và reset cờ vri_Stt để chuẩn bị cho lệnh tiếp theo.

Hàm USART1_IRQHandler() (Trình phục vụ ngắt):
Hàm này sẽ tự động được gọi mỗi khi một byte dữ liệu được nhận vào thanh ghi của USART1.

Đầu tiên, nó đọc byte dữ liệu vừa nhận.

Nếu ký tự đó không phải là ký tự kết thúc (\r hoặc \n), nó sẽ được thêm vào bộ đệm vrc_Res.

Nếu ký tự đó là ký tự kết thúc, nó sẽ đặt ký tự NULL (\0) vào cuối bộ đệm để tạo thành một chuỗi C hợp lệ và sau đó bật cờ vri_Stt = 1 để báo cho vòng lặp main() biết rằng một lệnh đã sẵn sàng.
