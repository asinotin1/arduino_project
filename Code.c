#include <Wire.h>
#include <LiquidCrystal_I2C.h> // KHAI BÁO I2C, MÀN HÌNH LCD, CẢM BIẾN ÁNH SÁNG, SERVO
#include <BH1750FVI.h>
#include <Servo.h>
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
// Tạo môi trường chuyển đổi giá trị cảm biến ánh sáng
uint16_t as; 
// khai báo giá trị as lưu giá trị ánh sáng lux
LiquidCrystal_I2C lcd(0X3F, 20, 4);
int  button1=0, button2=0, button3=0, button4=0; 
// khai báo nút nhấn

int count=0, save=0 , save1 , pos = 90;
// count là biến lưu giá trị từ nút nhấn tăng 2, giảm 3 count = 0 ,1 ,2 ,...,n
// save là biến lưu giá trị nút nhấn 1
// save1 là biến lưu giá trị nút nhấn  4
// pos là biến nằm trong khoảng (0-180) độ , góc ban đầu khi dàn che nắng đóng lại là 90 độ
int a,b; 	// a,b là khoảng giá trị mong muốn vd: (100-500), (500-1000), (n-65500)

int level; 	//Khai báo biến đọc giá trị quang trở photocel (0-1023)

int i=0; 	//Khai báo biến xuất giá trị ra led (0-255)


Servo myservo;
void setup()
{
  Wire.begin();	// khởi động chức năng I2C
  myservo.attach(6); 	// chọn chân số 6 làm chân xuất giá trị  PWM ra servo
  Serial.begin(9600);
  LightSensor.begin();	// khởi động cảm biến ánh sáng
  lcd.init(); 	// khởi động LCD
  lcd.clear();	// xóa màn hình LCD
  lcd.backlight();	 // Bật đèn LCD
  lcd.setCursor(5 , 1); 	// đưa con trỏ đến vị trí  (hàng, cột)
  lcd.print("XIN CHAO");
  lcd.setCursor(5 , 2);
  lcd.print("MOI NGUOI");
  myservo.write(pos); 	// xuất giá trị ban đầu là góc 90 độ ra servo
  delay(2000);
  lcd.clear();
  lcd.setCursor(0 , 3);
  lcd.print("press");  

  pinMode(3, INPUT_PULLUP);	// khai báo chân số 3 là  nút nhấn kéo lên (nút 1)
  pinMode(4, INPUT_PULLUP);	// khai báo chân số 4 là  nút nhấn kéo lên (nút 2)
  pinMode(5, INPUT_PULLUP);	// khai báo chân số 5là  nút nhấn kéo lên (nút 3)
  pinMode(7, INPUT_PULLUP);	// khai báo chân số 7 là  nút nhấn kéo lên (nút 4)

  pinMode(6, OUTPUT); 	//khai báo chân số 6 là chân output xuất PWM của servo
  
  pinMode(11, OUTPUT);	// khai báo chân số 11 là chân output xuất PWM của đèn led
}

int tinhtoan(void) // Chương trình con chuyển đổi giá trị điện áp ra giá trị ánh sáng lux
{
   uint16_t lux = LightSensor.GetLightIntensity();
   delay(100);
   return lux;
}

void loop()
{
  lcd.setCursor(3 , 0);
  lcd.print("chi so anh sang");
  lcd.setCursor(15 , 1);
  lcd.print("lux");
  lcd.setCursor(8  , 1);
  tinhtoan();// khởi động chương trình con 
  as=tinhtoan(); 
  lcd.print(as); //xuất màn hình ra giá trị ánh sáng as (lux)
  lcd.print("   ");
  button1 = digitalRead(3);	// đọc giá trị nút nhấn 1,2,3,4 lưu vào các biến button
  button2 = digitalRead(4);
  button3 = digitalRead(5);
  button4 = digitalRead(7);
  if(button1 == LOW)
  {
    delay(20);
    if(button1 == LOW)	// khi nút nhấn 1 được nhấn
    {
      lcd.setCursor(0,3);
      lcd.print("Exit  +   -  Select");
      save++; 	// biến save tăng lên một giá trị
    }
  }
  if(save == 1) 	// khi biến save có giá trị là 1
  {
    lcd.setCursor(0,2);
    if(button2 == LOW) 	// khi nút nhấn 2 được nhấn
    {
      delay(20);
      if(button2 == LOW) 
      {
        count++; 	// biến count tăng lên một giá trị
      }
    }
      //switch 3
    if(button3 == LOW)	// khi nút 3 được nhấn
     {
       delay(20);
       if(button3 == LOW )
       {
         count--; 	// biến count giảm xuống một giá trị
       }
     }
    if(count ==0 )
     {
        lcd.print("         0          ");
     }
     else if(count == 1)
     {
        lcd.print("     100    -  500    ");
        a=100;b=500;
     }
     else if(count == 2)
     {
        lcd.print("     500   -  1000    ");
        a=500;b=1000;
     }
     else if(count == 3)
     {
        lcd.print("     1000 - 1500      ");
        a=1000 ;b=1500;
     }
     else if(count == 4)
     {
        lcd.print("     1500 - 2000       ");
        a=1500;b=2000;
     }
     else if(count == 5)
     {

        lcd.print("     100000 - 20000     ");
        a=10000;b=20000;
     }
     else if(count == 6)
     {
        lcd.print("     20000 - 30000    ");
        a=20000;b=30000;
     }
     else if(count > 6)
     {
        count = 6;
     }
     else if(count < 0 )
     {
        count = 0;
     }
    if(button4 == LOW)
      {
        delay(20);
        if(button4 == LOW)
        {
          save1=1;
          lcd.setCursor(0,3);
          lcd.print("     select mode      ");
          delay(500);
          lcd.setCursor(0,3);
          lcd.print("        start         ");
          delay(500);
          lcd.setCursor(0,3);
          lcd.print("                  ");
        }
      }
    if(save1==1)
      {
        level=analogRead(A0); 	//đọc giá trị analog từ quang trở thông qua chân A0
        Serial.println(level);
        tinhtoan();
        as=tinhtoan();
        if(level > 30)// khi gia tri analog level > 30 => Hiện tại là ban ngày
        {
          analogWrite(11,0);
          // vi du khoang (a,b) = (100 , 10000)
          if(as < a)	// Khi ánh sáng trong phòng thấp hơn giá trị thiết đặt là a
          {
            pos--; 	//quay thuận
            delay(50);
            if(pos<0)
            {
              pos=0;
            }
          }
          if(as > b)// Khi ánh sáng trong phòng cao hơn giá trị thiết đặt là b
          {
            pos++; 	// quay ngịch
            delay(50);
            if(pos>180)
            {
              pos=180;
            }
          }
          myservo.write(pos); Xuất giá trị góc hiện tại ra động cơ servo
        }
        if(level < 30) // khi gia ti analog level <30 => Hiện tại là ban đêm
        {
          myservo.write(90); // Đưa dàn che nắng về góc 90 độ
          if(as < a)// Khi ánh sáng trong phòng thấp hơn giá trị thiết đặt là a
          {
            i++; // tăng ánh sáng lên
            if(i>255)
            {
              i=255;
            }
          }
          if(as > b)// Khi ánh sáng trong phòng cao hơn giá trị thiết đặt là b
          {
            i--	// giảm ánh sáng xuống
            if(i<0)
            {
              i=0;
            }
          }
          analogWrite(11,i); // Xuất giá trị hiện tại ra led
        }
      }
  }
  if(save > 1) // Khi nút nhấn được nhấn thêm thì reset save = 0 ( dừng khẩn cấp ) đưa về màn hình tùy chọn ban đầu
  {
    analogWrite(11,0); // Tắt đèn led
    save=0;// trả giá trị lưu nút nhấn 1 save = 0
    save1=0; // dừng chương trình điều chỉnh ánh sáng tự động
    lcd.setCursor(0,3);
    lcd.print("press               ");
    lcd.setCursor(0,2);
    lcd.print("                    ");
  }
}



