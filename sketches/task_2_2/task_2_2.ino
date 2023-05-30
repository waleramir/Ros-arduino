#include <LiquidCrystal.h>

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Char.h>

byte P[8] = { B00000, B00000, B00000, B00000, B11111, B11111, B11111, B11111 };
byte reverseP[8] = { B11111, B11111, B11111, B11111, B00000, B00000, B00000, B00000 };
int x = 8;
int y = 0;
bool reverse = false;
ros::NodeHandle node_handle;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void subscriberCallback(const std_msgs::String led_msg) {
  node_handle.loginfo(led_msg.data);
  if (strcmp(led_msg.data, "w") == 0) {
    node_handle.loginfo("passed");
    if (!reverse && y == 0)
      reverse = !reverse;

    if (y > 0 && reverse) {
      y--;
      reverse = !reverse;
    }
    if (!reverse && y > 0)
      reverse = !reverse;
    image(x, y, reverse);
  }
  if (strcmp(led_msg.data, "a") == 0) {
    x--;
    image(x, y, reverse);
  }
  if (strcmp(led_msg.data, "s") == 0) {

    if (y > 0 && reverse) {
      reverse = !reverse;
    }
    if (y == 0 && !reverse) {
      y++;
      reverse = !reverse;
    }
    if (reverse && y == 0)
      reverse = !reverse;
    image(x, y, reverse);
  }
  if (strcmp(led_msg.data, "d") == 0) {
    x++;
    image(x, y, reverse);
  }
}

ros::Subscriber<std_msgs::String> lcd_subscriber("move_lcd", &subscriberCallback);

void image(int x, int y, bool reverse) {
  lcd.clear();
  if (reverse)
    lcd.createChar(0, reverseP);
  else
    lcd.createChar(0, P);
  lcd.setCursor(x, y);
  lcd.write(byte(0));
}

void setup() {
  lcd.begin(16, 2);
  image(8, 0, reverse);
  lcd.noCursor();
  node_handle.initNode();
  node_handle.subscribe(lcd_subscriber);
}

void loop() {
  node_handle.spinOnce();
  delay(100);
}