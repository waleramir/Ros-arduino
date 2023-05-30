#!/usr/bin/env python
import rospy
import time
from std_msgs.msg import String, Header
from arduino.msg import SensorMessage

def talker() :
	rospy.init_node('talker', anonymous=True)
	sensor_1 = 13.764
	sensor_2 = 8.75
	pub = rospy.Publisher('sensor_log', SensorMessage, queue_size=10)
	rate = rospy.Rate(1) # 10hz
	while not rospy.is_shutdown():
		sensor_type = 'Test'
		sensor_1 -= 0.285
		sensor_2 += 0.285
		msg = SensorMessage()
		msg.sensor_1 = sensor_1
		msg.sensor_2 = sensor_2
		
		header = Header()
		header.stamp = rospy.Time.now()

		msg.header = header
		pub.publish(msg)
		rate.sleep()

if __name__ == "__main__":
	try:
		talker()
	except rospy.ROSInterruptException: 
		pass