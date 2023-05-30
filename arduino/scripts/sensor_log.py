#!/usr/bin/env python
import rospy
from std_msgs.msg import String
# from arduino.msg import SensorMessage
from std_msgs.msg import Float32
import rosbag

bag = rosbag.Bag('~\Desktop\test.bag', 'w')

def callback_t(data):
    rospy.loginfo("Temperature sensor: %f", data.data)
    bag.write('sensor_log', data)
def callback_s(data):
    rospy.loginfo("Sound sensor: %f", data.data)
    bag.write('sensor_log', data)

def listener():
    rospy.init_node('sensor_logger', anonymous=True)
    rospy.Subscriber("sound_topic", Float32, callback_s)
    rospy.Subscriber("tmpr_topic", Float32, callback_t)

    rospy.spin()

if __name__ == "__main__":
    try:
        listener()
    finally:
        bag.close()