#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32
import numpy as np
import cv2

font = cv2.FONT_HERSHEY_SIMPLEX

images = [None, None, None]

for i in range(3):
    images[i] = np.ones((250,1000,3), np.uint8)
    images[i] *= 255

def callback(data, topic_name):
    blank_image = np.ones((300,1000,3), np.uint8)
    blank_image = 255*blank_image
    cv2.rectangle(blank_image,(700,20),(900,280),(125,125,125),5)

    x = data.data

    if x < 0:
        x = 0
    if x > 400:
        x = 400

    x = int(x)

    cv2.line(blank_image,(670 - x, 150),(690,150),(125,125,125),5)

    cv2.line(blank_image,(560 - x,50),(660 - x,150),(125,125,125),5) 
    cv2.line(blank_image,(660 - x,150),(560 - x,250),(125,125,125),5)
    cv2.line(blank_image,(560 - x,250),(560 - x,50),(125,125,125),5) 

    cv2.putText(blank_image,f'{round(data.data,2)} cm',(685-x,100), font, 1,(100,100,100),2)

    cv2.putText(blank_image,f'{topic_name}',(20,170), font, 5,(100,100,100),5)
    cv2.line(blank_image,(0, 300),(1000,300),(0,0,0),5)

    images[topic_name] = blank_image

    if topic_name == 0:
        image = np.concatenate((images[0], images[1]), axis=0)
        image = np.concatenate((image, images[2]), axis=0)
        cv2.imshow('0', image)
        cv2.waitKey(1)

def listener():
    rospy.init_node('sensor_filtering', anonymous=True)
    rospy.Subscriber("filtering_1", Float32, callback, callback_args=0)
    rospy.Subscriber("filtering_2", Float32, callback, callback_args=1)
    rospy.Subscriber("filtering_3", Float32, callback, callback_args=2)
    rospy.spin()

if __name__ == "__main__":
    try:
        listener()
    finally:
        cv2.destroyAllWindows()