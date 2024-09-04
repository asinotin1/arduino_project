TÊN ĐỀ TÀI: HỆ THỐNG CHE NẮNG TỰ ĐỘNG CHO NHÀ KÍNH TRỒNG RAU - HOA

![image](https://github.com/user-attachments/assets/11f6ab63-8753-4bc3-9993-226c9422bde3)

*)sơ đồ khối :

![image](https://github.com/user-attachments/assets/2475ec42-384b-4966-a797-ccbb76cc8e64)

*)Nguyên lý hoạt động:

Thông qua các nút nhấn (1) người dùng sẽ thao tác chọn khoảng ánh sáng ( khoảng ánh sáng này đã được thiết đặt từ trước từ người lập trình).Khi người dùng đã chọn được khoảng ánh sáng mong muốn từ nút nhấn và khởi động chế độ tự động thì quang trở photocell (2) sẽ nhận ánh sáng từ bên ngoài, trả các giá trị điện áp về vi điều khiển để vi điều khiển xác định trời sáng hoặc tối, tiếp theo đó cảm biến ánh sáng BH1750FVI (3) sẽ đọc giá trị ánh sáng hiện tại trong môi trường (trong phòng kính) và đưa giá trị ánh sáng trong vườn hiện tại về vi điều khiển. Vi điều khiển sẽ tiến hành so sánh giá trị ánh sáng trong vườn với khoảng ánh sáng mà người dùng chọn . Sau đó, vi điều khiển sẽ gửi tín hiệu analog ra động cơ (4) (trời sáng) hoặc đèn (5) (trời tối). Đối với động cơ thì khi ánh sáng trong vườn lớn hơn giá trị mong muốn thì động cơ sẽ quay thuận còn khi ánh sáng nhỏ hơn khoảng giá trị mong muốn thì sẽ quay nghịch, đối với đèn thì khi ánh sáng trong phòng thấp hơn thì sẽ tăng mức sáng của đèn lên và ngược lại.

*)Linh kiện :

Arduino nano.
Quang trở
LCD 2004 tích hợp i2c
Servo SG90
LED
Cảm Biến Cường Độ Ánh Sáng Lux BH1750FVI
Nút nhấn
