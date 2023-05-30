#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from arduino.msg import SensorMessage
import rosbag


bag = rosbag.Bag('~/Desktop/test.bag', 'w')

def callback(data):
    rospy.loginfo("Value: %f. Value: %f", data.sensor_1, data.sensor_2)
    bag.write('sensor_log', data)

def listener():
    rospy.init_node('sensor_logger', anonymous=True)
    rospy.Subscriber("sensor_log", SensorMessage, callback)
    rospy.spin()

if __name__ == "__main__":
    try:
        listener()
    finally:
        bag.close()
