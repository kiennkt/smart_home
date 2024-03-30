# Mô hình Smart home
![Mô hình](https://github.com/kiennkt/smart_home/blob/main/smarthome.PNG)
> Chức năng:
> * Thu thập nhiệt độ độ ẩm, hiển thị lên LCD
> * Đo khí gas, kết hợp với còi báo nếu vượt ngưỡng
> * Nhận biết chuyển động qua cảm biến hồng ngoại, điều khiển led
> * Nhận biết chuyển động ra vào cửa, điều khiển servo
> * Dữ liệu nhiệt độ, độ ẩm, khí gas được gửi từ Arduino tới gateway ESP32 qua module NRF24L01 (module thu phát sóng vô tuyến).
> * Tại gateway nhận được dữ liệu sau đó gửi lên nền tảng Thingsboard qua giao thức MQTT. Tại đây thực hiện giám sát, trực quan hóa dữ liệu. Cảnh báo trực tiếp đến điện thoại có sẵn nền tảng Thingsboard nếu khí gas vượt ngưỡng

# Cấu hình chân
## Arduino
### Kết nối module NRF24L01
|    Arduino    |    NRF24L01   |
|---------------|---------------|
| 3v3 | VCC |
| GND | GND |
| D13 | SCK |
| D12 | MISO |
| D11 | MOSI |
| D9 | CE |
| D8 | CSN |
### Kết nối DHT11
|    Arduino    |    DHT11   |
|---------------|---------------|
| 5V | VCC |
| GND | GND |
| A1 | Data |
### Kết nối Gas MQ2
|    Arduino    |    MQ2   |
|---------------|---------------|
| 5V | VCC |
| GND | GND |
| A0 | Analog |
### Kết nối Cảm biến ánh sáng
|    Arduino    |    Light   |
|---------------|---------------|
| 5V | VCC |
| GND | GND |
| D5 | Digital |
### Kết nối còi buzzer
|    Arduino    |    Buzzer   |
|---------------|---------------|
| D6 | Chân (+) |
| GND | Chân (-) |
### Kết nối với LCD1602
Kết nối qua module I2C
|    Arduino    |    LCD   |
|---------------|---------------|
| 5V | VCC |
| GND | GND |
| A4 | SDA |
| A5 | SCL |
### Kết nối Led
|    Arduino    |    Led   |
|---------------|---------------|
| D2 | Anode |
| GND | Cathode |
* Giữa GND và Cathode mắc thêm 1 điện trở
## Gateway ESP32
|    ESP32    |    NRF24L01   |
|---------------|---------------|
| 3v3 | VCC |
| GND | GND |
| D18 | SCK |
| D19 | MISO |
| D23 | MOSI |
| D4 | CE |
| D5 | CSN |



