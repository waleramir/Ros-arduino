#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Char.h>

const int echo = 2;
const int trig = 3;

const int maxdist = 335;
const float mindist = 2.5;
double distance, duration;
double kaldist;
double lowdist;
double averdist;
float filterArray[20]; 
ros::NodeHandle node_handle;

double kalman(double U) {
  static const double R = 40;
  static const double H = 1.00;
  static double Q = 10;
  static double P = 0;
  static double U_hat = 0;
  static double K = 0;
  K = P * H / (H * P * H + R);
  U_hat += +K * (U - H * U_hat);
  P = (1 - K * H) * P + Q;
  return U_hat;
}

int smooth(int sensor_reading, float filterValue, float smoothedValue) {
  if (filterValue > 1) {
    filterValue = .99;
  } else if (filterValue <= 0) {
    filterValue = 0;
  }

  smoothedValue = (sensor_reading * (1 - filterValue)) + (smoothedValue * filterValue);
  return (int)smoothedValue;
}

void usonic_transmit() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
}

std_msgs::Float32 float_msg;
ros::Publisher kalman_pub("listener_1", &float_msg);
ros::Publisher lowpass_pub("listener_2", &float_msg);
ros::Publisher averg_pub("listener_3", &float_msg);

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  node_handle.initNode();
  node_handle.advertise(kalman_pub);
  node_handle.advertise(lowpass_pub);
  node_handle.advertise(averg_pub);
}

void loop() {
  node_handle.spinOnce();

  usonic_transmit();
  duration = pulseIn(echo, HIGH);
  distance = (duration * .034) / 2;

  kaldist = kalman(distance);
  float_msg.data = kaldist;
  kalman_pub.publish(&float_msg);

  lowdist = smooth(distance, 0.6, 0);
  float_msg.data = lowdist;
  lowpass_pub.publish(&float_msg);

  for (int sample = 0; sample < 20; sample++) {
    filterArray[sample] = distance;
  }
  for (int i = 0; i < 19; i++) {
    for (int j = i + 1; j < 20; j++) {
      if (filterArray[i] > filterArray[j]) {
        float swap = filterArray[i];
        filterArray[i] = filterArray[j];
        filterArray[j] = swap;
      }
    }
  }
  double sum = 0;
  for (int sample = 5; sample < 15; sample++) {
    sum += filterArray[sample];
  }
  averdist = sum / 10;
  float_msg.data = averdist;
  averg_pub.publish(&float_msg);

  delay(1 / 30);
}