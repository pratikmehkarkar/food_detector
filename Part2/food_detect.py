# Written by Pratik Mehkarkar

import io
import os
import cv2
from google.cloud import vision_v1p3beta1 as vision
import serial
import time

os.environ['GOOGLE_APPLICATION_CREDENTIALS'] = 'client_key.json'
IMAGE_SRC = "/Users/pratikmehkarkar/PycharmProjects/food/foodimage/"
FOOD_TYPE = 'Fruit'
FRUIT_NAME = 'NONE'


def show_food(food_type):
    f_name = [line.rstrip('\n').lower() for line in open('dict/' + food_type + '.dict')]
    return f_name


def food_detector(input_path, list_foods):
    new_image = cv2.imread(input_path)
    height, width = new_image.shape[:2]
    new_image = cv2.resize(new_image, (800, int((height * 800) / width)))
    cv2.imwrite(IMAGE_SRC + "detected_image.jpeg", new_image)
    input_path = IMAGE_SRC + "detected_image.jpeg"
    client = vision.ImageAnnotatorClient()
    with io.open(input_path, 'rb') as image_file:
        content = image_file.read()
    image = vision.types.Image(content=content)
    response = client.label_detection(image=image)
    labels = response.label_annotations

    for label in labels:
        desc = label.description.lower()
        if desc in list_foods:
            global FRUIT_NAME
            FRUIT_NAME = desc.upper()
            cv2.putText(new_image, desc.upper() + " ???", (300, 150), cv2.FONT_HERSHEY_SIMPLEX, 1, (50, 50, 200), 2)
            cv2.waitKey(1)
            break


print('---------- Start FOOD Recognition --------')
print('Connected to NUCLEO F401RE')
serdev = '/dev/tty.usbmodem14203'
mbed_connect = serial.Serial("/dev/tty.usbmodem14203", 9600)
time.sleep(2)
list_foods = show_food(FOOD_TYPE)
path = IMAGE_SRC + '1.jpeg'
food_detector(path, list_foods)
mbed_connect.write(FRUIT_NAME.encode())
print('PROCESS COMPLETED, RESET NUCLEO F401RE BOARD')
print('---------- End ----------')
