#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Char.h>

#define LED_R 7
#define LED_G 11
#define LED_B 9

volatile bool Flag_r = 0;
volatile bool Flag_g = 0;
volatile bool Flag_b = 0;
ros::NodeHandle node_handle;

void subscriberCallback(const std_msgs::String led_msg) {
  node_handle.loginfo(led_msg.data);
  if (strcmp(led_msg.data,"r") == 0) {
    node_handle.loginfo("passed");
    Flag_r = !Flag_r;
    digitalWrite(LED_R, Flag_r);
  }
  if (strcmp(led_msg.data,"g") == 0) {
    Flag_g = !Flag_g;
    digitalWrite(LED_G, Flag_g);
  }
  if (strcmp(led_msg.data,"b") == 0) {
    Flag_b = !Flag_b;
    digitalWrite(LED_B, Flag_b);
  }
}

ros::Subscriber<std_msgs::String> led_subscriber("toggle_led", &subscriberCallback);

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  node_handle.initNode();
  node_handle.subscribe(led_subscriber);
}

void loop() {
  node_handle.spinOnce();
  delay(10);
}