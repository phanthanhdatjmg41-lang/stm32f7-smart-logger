# 📋 Báo Cáo Tổng Quan Dự Án: STM32F7 Smart Logger

---

## 1. Tổng Quan Dự Án

**STM32F7 Smart Logger** là một hệ thống nhúng chạy trên vi điều khiển **STM32F746**, cho phép người dùng điều khiển phần cứng (LED) và giám sát trạng thái hệ thống thông qua giao thức **UART**. Giao tiếp được thực hiện bằng phần mềm **Tera Term** trên máy tính, kết nối qua module chuyển đổi CP2102 (USB to UART).

Nói đơn giản hơn: bạn mở Tera Term lên, gõ lệnh như `led on` hoặc `status`, bấm Enter — vi điều khiển sẽ nhận lệnh đó, hiểu nó, thực thi và phản hồi lại kết quả. Đây là bước nền tảng quan trọng để sau này bạn có thể mở rộng thành các hệ thống logging phức tạp hơn (đo nhiệt độ, đọc cảm biến, v.v.).

---

## 2. Bản Đồ Module

Dự án được chia thành **7 module** rõ ràng. Mỗi module chỉ làm đúng một việc — đây chính là nguyên tắc **Single Responsibility** trong thiết kế phần mềm.

| Module | Vai trò | Hình ảnh ví von |
|---|---|---|
| **`main.c`** | Điểm khởi động của toàn bộ chương trình, do CubeIDE tự sinh. Chỉ gọi `App_Main_Init()` và `App_Main_Loop()`. | 🔑 Chìa khóa khởi động xe — bạn chỉ vặn rồi nó tự chạy, không cần biết động cơ hoạt động thế nào. |
| **`app_main`** | Vòng lặp chính của ứng dụng: lắng nghe từng ký tự UART, ghép thành lệnh, khi nhận Enter thì gọi xử lý. | 🎧 Người trực điện thoại — ngồi nghe từng chữ, khi câu hoàn chỉnh thì chuyển máy. |
| **`app_uart`** | Hàm tiện ích để gửi chuỗi ra UART. Chỉ có một nhiệm vụ: **gửi** dữ liệu ra terminal. | 📢 Loa phát thanh — ai cần thông báo gì thì gọi nó, nó phát ra màn hình. |
| **`app_command`** | Nhận chuỗi lệnh, so sánh và điều phối sang module xử lý tương ứng. | 🚦 Anh cảnh sát giao thông — `led on` đi hướng này, `status` đi hướng kia, `help` đi đường kia nữa. |
| **`app_led`** | Điều khiển trực tiếp phần cứng LED qua GPIO. Bật, tắt, đảo trạng thái, đọc trạng thái. | 💡 Công tắc điện — đơn giản, không thêm không bớt, chỉ bật/tắt. |
| **`app_system`** | Lưu giữ và quản lý trạng thái tổng thể của hệ thống: IDLE / RUNNING / ERROR. | 🧠 Bảng điều khiển trung tâm — theo dõi "hệ thống đang ở trạng thái nào". |
| **`app_log`** | In ra thông báo có mức độ phân loại rõ ràng: `[INFO]`, `[WARNING]`, `[ERROR]`. | 📓 Nhật ký sự kiện — ghi lại mọi chuyện xảy ra để tiện theo dõi và debug sau này. |
| **`app_config.h`** | File cấu hình tập trung: định nghĩa GPIO của LED, kích thước buffer, timeout UART. | ⚙️ Bảng cài đặt — muốn đổi phần cứng thì chỉ cần sửa ở đây, không phải lục tung cả project. |

---

## 3. Luồng Hoạt Động — Khi Bạn Gõ `led on` và Bấm Enter

Đây là diễn biến chi tiết xảy ra bên dưới code, từng bước một:

```
[Tera Term] ─────────────── USB/UART ──────────────▶ [STM32F746]
```

**Bước 1 — Nhận từng ký tự:**
> Bạn gõ chữ `l`, `e`, `d`, ` `, `o`, `n`. Mỗi ký tự được gửi qua UART.
> Hàm `HAL_UART_Receive()` trong `App_Main_Loop()` bắt được từng ký tự một.
> Mỗi ký tự được **echo ngược lại** màn hình (để bạn thấy mình đang gõ gì) và được **lưu vào `rxBuffer[]`**.
> Lúc này `rxBuffer` = `"led on"`, `rxIndex` = 6.

**Bước 2 — Phát hiện Enter:**
> Bạn bấm `Enter`. Ký tự `\r` (carriage return) được gửi qua UART.
> `App_Main_Loop()` phát hiện đây là ký tự kết thúc lệnh.
> Nó thêm `'\0'` vào cuối buffer → `rxBuffer` = `"led on\0"` (chuỗi hoàn chỉnh).

**Bước 3 — Chuyển lệnh sang bộ xử lý:**
> `App_Main_Loop()` gọi hàm **`Command_Process("led on")`** trong `app_command.c`.
> Nhiệm vụ của `app_main` kết thúc tại đây — nó không biết và không cần biết `"led on"` nghĩa là gì.

**Bước 4 — Phân loại và xử lý lệnh:**
> `Command_Process()` dùng `strcmp()` so sánh chuỗi `"led on"` lần lượt với từng lệnh đã biết.
> Tìm thấy khớp! Nó gọi 2 hàm:
> - **`LED_On()`** trong `app_led.c` → chân GPIO PB1 được kéo lên `HIGH` → LED bật sáng về phần cứng.
> - **`Log_Info("LED ON")`** trong `app_log.c` → gửi `[INFO] LED ON` ra Tera Term.

**Bước 5 — Phản hồi và chờ lệnh tiếp theo:**
> Sau khi xử lý xong, `Command_Process()` gọi `UART_Send("> ")` để in lại dấu nhắc lệnh.
> Tera Term hiển thị: `[INFO] LED ON` rồi `> ` → bạn biết hệ thống đã thực thi xong và đang chờ lệnh mới.
> `rxIndex` được reset về 0, sẵn sàng nhận lệnh tiếp theo.

**Tóm tắt bằng sơ đồ:**

```
[Tera Term: gõ "led on" + Enter]
         │
         ▼
[app_main.c: App_Main_Loop()]
  → Nhận từng ký tự → ghép buffer → phát hiện '\r'
         │
         ▼
[app_command.c: Command_Process("led on")]
  → strcmp() khớp "led on"
         │
         ├──▶ [app_led.c: LED_On()]       → GPIO PB1 = HIGH → 💡 LED sáng
         │
         └──▶ [app_log.c: Log_Info()]
                    │
                    ▼
              [app_uart.c: UART_Send()]   → "[INFO] LED ON" hiện trên Tera Term
```

---

## 4. Bài Học Kiến Trúc — Tại Sao Không Nhét Hết Vào `main.c`?

### 🔧 Lý do 1: Dễ bảo trì — Sửa một chỗ, không lo ảnh hưởng chỗ khác

Khi bạn muốn đổi chân GPIO của LED từ PB1 sang PA5, bạn chỉ cần sửa **một dòng trong `app_config.h`**. Mọi module đang dùng macro `APP_LED_GPIO_PIN` sẽ tự động cập nhật.

Nếu bạn nhét hết vào `main.c`, bạn phải đi tìm từng chỗ hardcode `GPIO_PIN_1` rải rác khắp file — rất dễ bỏ sót và gây bug.

### 🔄 Lý do 2: Sống sót qua "Generate Code" của CubeIDE

Mỗi lần bạn thêm ngoại vi mới trong file `.ioc` và ấn **Generate Code**, CubeIDE sẽ **tự động ghi đè** phần giữa `/* USER CODE BEGIN */` và `/* USER CODE END */`. Nếu code ứng dụng của bạn nằm ngoài vùng đó, nó sẽ bị xóa mất.

Với kiến trúc hiện tại, `main.c` chỉ chứa 2 dòng: `App_Main_Init()` và `App_Main_Loop()` — toàn bộ logic nằm trong các file `app_*.c` riêng biệt, **an toàn tuyệt đối** dù Generate Code bao nhiêu lần.

### 🚀 Lý do 3: Dễ mở rộng — Thêm tính năng không cần đụng code cũ

Giả sử sau này bạn muốn thêm lệnh `sensor read` để đọc cảm biến nhiệt độ. Bạn chỉ cần:
1. Tạo file `app_sensor.c` và `app_sensor.h` mới.
2. Thêm một nhánh `else if (strcmp(cmd, "sensor read") == 0)` vào `app_command.c`.

Bạn **không cần đụng** vào `app_uart.c`, `app_log.c`, `app_main.c`, hay bất kỳ module nào khác đang chạy ổn định. Đây chính là nguyên tắc **Open/Closed** trong thiết kế phần mềm chuyên nghiệp: mở rộng thì mở, nhưng sửa code cũ đang chạy tốt thì đóng lại.

---

> **💡 Tóm gọn một câu:** Dự án này đã được tổ chức đúng chuẩn embedded software — mỗi module làm đúng một việc, dễ test, dễ sửa, dễ mở rộng, và không sợ CubeIDE ghi đè. Đây là nền tảng tốt để bạn tiếp tục phát triển các tính năng phức tạp hơn.
