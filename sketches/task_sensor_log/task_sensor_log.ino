#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Char.h>

int sound_dPin = 7;   
int sound_aPin = A1;  
int tmpr_dPin = 2;    
int tmpr_aPin = A0; 

int digitalVal;  
float analogVal_sound;
float analogVal_tmpr;
ros::NodeHandle node_handle;


std_msgs::Float32 float_msg;
ros::Publisher sound_pub("sound_topic", &float_msg);
ros::Publisher tmpr_pub("tmpr_topic", &float_msg);

// 14 std_msgs::String str_msg;
void setup() {
  pinMode(sound_dPin, INPUT);
  pinMode(sound_aPin, INPUT);
  pinMode(tmpr_dPin, INPUT);
  pinMode(tmpr_aPin, INPUT);
  Serial.begin(9600);
  node_handle.initNode();
  node_handle.advertise(sound_pub);
  node_handle.advertise(tmpr_pub);
}

void loop() {
  node_handle.spinOnce();
  analogVal_sound = analogRead(sound_aPin);
  float_msg.data = analogVal_sound;
  sound_pub.publish(&float_msg);

  analogVal_tmpr = analogRead(tmpr_aPin);
  float_msg.data = analogVal_tmpr;
  tmpr_pub.publish(&float_msg);
  delay(100);
}