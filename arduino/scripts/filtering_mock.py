#!/usr/bin/env python
import rospy
import time
from std_msgs.msg import String, Header, Float32

def talker() :
	rospy.init_node('filtering_mock', anonymous=True)
	sensor_1 = 13.764
	sensor_2 = 8.75
	sensor_3 = 0.75
	pub_1 = rospy.Publisher('filtering_1', Float32, queue_size=10)
	pub_2 = rospy.Publisher('filtering_2', Float32, queue_size=10)
	pub_3 = rospy.Publisher('filtering_3', Float32, queue_size=10)
	rate = rospy.Rate(50) # 10hz
	while not rospy.is_shutdown():
		sensor_type = 'Test'
		sensor_1 += 0.1
		sensor_2 += 0.1
		sensor_3 += 0.1

		msg = Float32()
		msg.data = sensor_1
		pub_1.publish(msg)


		msg = Float32()
		msg.data = sensor_2
		pub_2.publish(msg)


		msg = Float32()
		msg.data = sensor_3
		pub_3.publish(msg)
		rate.sleep()

if __name__ == "__main__":
	try:
		talker()
	except rospy.ROSInterruptException: 
		pass