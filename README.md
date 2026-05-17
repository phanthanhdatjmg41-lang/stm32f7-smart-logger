# STM32F7 Smart Logger

## 🎯 Mục Tiêu
Đồ án xây dựng hệ thống điều khiển phần cứng và giám sát trạng thái thông qua giao tiếp UART trên vi điều khiển **STM32F746**.

---

## 🔌 Phần Cứng Sử Dụng
- **Vi điều khiển**: STM32F746 Core7
- **Board phát triển**: Open7 board
- **Giao tiếp**: USART1 qua module chuyển đổi CP2102 USB to UART
- **Thiết bị ngoại vi**: LED ngoài kết nối tại chân `PB1`

---

## 🛠️ Chức Năng Hiện Tại
Hệ thống hỗ trợ nhận dạng lệnh dạng chuỗi văn bản không phân biệt ký tự đặc biệt, thực thi điều khiển ngoại vi và ghi lại nhật ký hoạt động thông qua UART (baud rate `115200`):
- **Phản hồi trạng thái hệ thống**: `IDLE`, `RUNNING`, `ERROR`.
- **Hỗ trợ 10 lệnh điều khiển & giám sát**:
  - `help`: Hiển thị danh sách tất cả các lệnh khả dụng.
  - `status`: Xem trạng thái hoạt động hiện tại của hệ thống.
  - `start`: Khởi động hệ thống (chuyển trạng thái sang `RUNNING`).
  - `stop`: Dừng hệ thống (chuyển trạng thái sang `IDLE`).
  - `led on`: Bật sáng LED ngoài (chân `PB1`).
  - `led off`: Tắt LED ngoài.
  - `led toggle`: Đảo trạng thái LED ngoài.
  - `led status`: Kiểm tra trạng thái hiện tại của LED (đang `ON` hay `OFF`).
  - `reset`: Khôi phục hệ thống về trạng thái ban đầu (`IDLE`, tắt LED).
  - `uptime`: Hiển thị tổng thời gian hệ thống đã hoạt động liên tục (tính bằng giây).
- **Hệ thống Logging (`app_log`)**:
  - Tự động ghi nhận và in thông báo phân cấp: `[INFO]`, `[WARNING]`, `[ERROR]` cho từng hành động để phục vụ debug và giám sát thời gian thực.

---

## 📂 Cấu Trúc Mã Nguồn (Kiến Trúc Module)
Dự án được tổ chức theo cấu trúc module hóa cao nhằm tối ưu hóa việc quản lý mã nguồn, tránh ghi đè dữ liệu khi cấu hình lại bằng STM32CubeMX:

- **`main.c`**: File khởi động ứng dụng chính (do CubeIDE tạo lập), chỉ gọi hàm khởi tạo `App_Main_Init()` và vòng lặp `App_Main_Loop()`.
- **`app_config.h`**: File cấu hình chung cho toàn bộ ứng dụng (chân GPIO, cổng LED, kích thước bộ đệm UART, timeout,...). giúp dễ dàng thay đổi phần cứng.
- **`app_main.h/c`**: Đóng vai trò lớp đệm quản lý nhận UART, xử lý chuỗi ký tự nhận được và phát hiện kết thúc lệnh (phím `Enter`).
- **`app_command.h/c`**: Bộ phân tích và xử lý lệnh. Phân phối các chuỗi lệnh từ UART đến các module nghiệp vụ tương ứng.
- **`app_system.h/c`**: Quản lý trạng thái logic (`IDLE`, `RUNNING`, `ERROR`) và thời gian hoạt động (`uptime`) của hệ thống.
- **`app_led.h/c`**: Quản lý các thao tác phần cứng trực tiếp với LED ngoài thông qua thư viện HAL.
- **`app_log.h/c`**: Bộ ghi log chuyên dụng hỗ trợ xuất thông báo ra UART theo chuẩn phân cấp sự kiện.
- **`app_uart.h/c`**: Thư viện tiện ích đóng gói hàm truyền dữ liệu chuỗi ký tự qua cổng UART.

---

## 💻 Cách Kiểm Thử (Testing)
1. Kết nối Board STM32F7 với máy tính thông qua cổng USB của CP2102.
2. Mở phần mềm giả lập Terminal (khuyên dùng **Tera Term** hoặc **Hercules**).
3. Cấu hình cổng COM chính xác của CP2102 với thông số:
   - **Baud rate**: `115200`
   - **Data**: `8 bit`
   - **Parity**: `None`
   - **Stop bits**: `1`
4. Tiến hành nạp code vào vi điều khiển STM32F746.
5. Xem thông báo chào mừng khởi động trên màn hình Terminal và gõ các lệnh điều khiển như: `help`, `led on`, `uptime`, `status`,...

---

## 📈 Lịch Sử Tiến Độ Phát Triển

### 🔹 Giai đoạn 1: UART Command Line cơ bản
- Cấu hình USART1 với tốc độ 115200 baud.
- Gửi thông báo chào mừng ra Tera Term khi khởi động.
- Lắng nghe và ghép từng ký tự nhận được qua UART thành chuỗi lệnh hoàn chỉnh.
- Xử lý các lệnh cơ bản: `help`, `status`, `start`, `stop`, `led on`, `led off`.

### 🔹 Giai đoạn 2: Tách module UART (`app_uart`)
- Tạo các file `app_uart.h` và `app_uart.c`.
- Đóng gói hàm truyền chuỗi `UART_Send` để tối giản hóa code gửi nhận.

### 🔹 Giai đoạn 3: Tách module trạng thái hệ thống (`app_system`)
- Tạo các file `app_system.h` và `app_system.c`.
- Xây dựng cơ chế lưu trữ an toàn trạng thái thông qua các hàm getter/setter: `System_Init`, `System_SetState`, `System_GetState`, `System_GetStateString`.

### 🔹 Giai đoạn 4 - 7: Bổ sung tính năng ngoại vi & lệnh mở rộng
- Tích hợp thêm các tính năng điều khiển LED nâng cao: `led toggle`, `led status`.
- Bổ sung lệnh `reset` để đưa toàn bộ hệ thống về chế độ an toàn ban đầu.
- Bổ sung lệnh `uptime` đo thời gian thực hệ thống hoạt động liên tục thông qua `HAL_GetTick()`.

### 🔹 Giai đoạn 8: Tách module phân phối lệnh (`app_command`)
- Tạo các file `app_command.h` và `app_command.c`.
- Di chuyển toàn bộ nghiệp vụ kiểm tra chuỗi `strcmp` lệnh từ `app_uart.c` sang `app_command.c`. Lớp UART chỉ giữ nhiệm vụ truyền tải.

### 🔹 Giai đoạn 9: Tập trung hóa file cấu hình (`app_config.h`)
- Thiết lập file `app_config.h`.
- Quy hoạch toàn bộ hằng số phần cứng (chân GPIO, port GPIO, kích thước mảng nhận, timeout) thành các định nghĩa Macro rõ ràng giúp dự án dễ dàng ánh xạ sang phần cứng mới.

### 🔹 Giai đoạn 10 & 11: Chuẩn hóa hệ thống Logging (`app_log`)
- Tạo lập các file `app_log.h` và `app_log.c`.
- Định hình 3 hàm xuất log có phân cấp: `Log_Info`, `Log_Warning`, `Log_Error`.
- Triển khai ghi log tự động cho các hành động cấu hình trạng thái, bật/tắt thiết bị, giúp công tác theo dõi sự kiện trở nên trực quan.

### 🔹 Giai đoạn 12: Tách biệt hoàn toàn logic vòng lặp (`app_main`)
- Chuyển toàn bộ các biến nhận đệm (`rxBuffer`, `rxByte`, `rxIndex`) từ file `main.c` sang `app_main.c`.
- Thiết lập hàm quản lý nhận ngắt/phím nhấn `App_Main_Init` và `App_Main_Loop`.
- Đưa file `main.c` về cấu trúc sạch 100%, bảo đảm không bao giờ bị mất mã nguồn ứng dụng khi lập trình viên thực hiện sinh lại code (Generate Code) cấu hình từ CubeMX `.ioc`.

---

## 📊 Kết Quả Build & Phân Tích Hiệu Năng
- **Trạng thái**: Build thành công 100%, **0 Errors**, **0 Warnings**.
- **Tối ưu hóa**: Đã loại bỏ các tác vụ xóa mảng bộ đệm dư thừa tốn tài nguyên (`memset` ở vòng lặp nhận phím), giúp tiết kiệm chu kỳ CPU và tăng tốc độ phản hồi lệnh.
