#!/usr/bin/env python
import imp
import rospy
from std_msgs.msg import String
from std_msgs.msg import UInt8
from std_msgs.msg import Char
from geometry_msgs.msg import Twist
import sys, select, os
import tty, termios


def talker():
    rospy.init_node("talker", anonymous=False)
    pub = rospy.Publisher("move_lcd", String, queue_size=10)
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
        key = str.lower(getKey())
        # data_srt = String()
        # data_srt.data = "r"
        rospy.loginfo(key)
        pub.publish(key)
        rate.sleep()
        if (key == '\x03'):
            break


def getKey():
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ""

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key


if __name__ == "__main__":
    settings = termios.tcgetattr(sys.stdin)
    
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
