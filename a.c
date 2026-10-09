import cv2, time, threading, queue
import ipywidgets.widgets as widgets
from IPython.display import display
import pyzbar.pyzbar as pyzbar
import numpy as np
from Raspblock import Raspblock
import pygame
from aip import AipSpeech

# ================= 语音配置 =================
APP_ID, API_KEY, SECRET_KEY = '17852430', 'eGeO4iQGAjHCrzBTYd1uvTtf', 'Cn1EVsUngZDbRLv4OxAFrDHSo8PsvFVP'
Speechclient = AipSpeech(APP_ID, API_KEY, SECRET_KEY)
pygame.mixer.init()

robot = Raspblock()
time.sleep(0.5)

# ================= 参数 =================
WHEEL_SPEED = 7
WHEEL_DELTA = 4
T_FORWARD_1 = 2.0
T_ARC       = 1.0
T_RETURN    = 16.0

# ================= 颜色 HSV =================
COLOR_RANGES = {
    "红色": [((0, 80, 80), (10, 255, 255)), ((170, 80, 80), (180, 255, 255))],
    
    "黄色": [((23, 100, 100), (35, 255, 255))],
    "绿色": [((36, 60, 60), (90, 255, 255))],
   '蓝色': [(np.array([100, 90, 70]), np.array([124, 255, 255]))],
}
COLOR_THRESHOLD = 1500

# ================= 运动线程 =================
cmd_q = queue.Queue()

def motion_thread():
    mode, a, b, c, d, deadline = None, 0, 0, 0, 0, None
    while True:
        try:
            mode, a, b, c, d, dur = cmd_q.get_nowait()
            deadline = time.time() + dur if dur else None
        except queue.Empty:
            pass
        if deadline and time.time() > deadline:
            mode, deadline = None, None
        if mode == 'yaw':
            robot.Speed_axis_Yawhold_control(a, b)
        elif mode == 'wheel':
            robot.Speed_Wheel_control(a, b, c, d)
        time.sleep(0.02)

threading.Thread(target=motion_thread, daemon=True).start()

def send(mode, a, b, c, d, duration=None):
    cmd_q.put((mode, a, b, c, d, duration))

def stop():
    while True:
        try: cmd_q.get_nowait()
        except queue.Empty: break
    robot.Speed_axis_Yawhold_control(0, 0)
    robot.Speed_Wheel_control(0, 0, 0, 0)
    cmd_q.put((None, 0, 0, 0, 0, None))

def run_wheel(speed, duration, delta=0):
    """四轮驱动：speed 为基准速度，delta 为左右差速，duration 后自动停"""
    l, r = speed - delta, speed + delta
    send('wheel', l, l, r, r, duration)
    time.sleep(duration + 0.3)

def speak(text):
    print("播报：", text)
    result = Speechclient.synthesis(text, 'zh', 1, {'spd': 2, 'vol': 2, 'per': 1})
    if isinstance(result, dict):
        print("合成失败：", result)
        return
    with open('./voice.mp3', 'wb') as f:
        f.write(result)
    pygame.mixer.music.load('./voice.mp3')
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy():
        time.sleep(0.1)

# ================= 颜色识别 =================
def detect_color(frame):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    for name, ranges in COLOR_RANGES.items():
        mask = None
        for lo, hi in ranges:
            m = cv2.inRange(hsv, np.array(lo), np.array(hi))
            mask = m if mask is None else mask + m
        if cv2.countNonZero(mask) > COLOR_THRESHOLD:
            return name
    return None

# ================= 摄像头 =================
def to_jpeg(v): return bytes(cv2.imencode('.jpg', v)[1])

image_widget = widgets.Image(format='jpeg', width=320, height=240)
display(image_widget)

camera = cv2.VideoCapture(0)
camera.set(3, 320); camera.set(4, 240); camera.set(5, 10)
camera.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('M','J','P','G'))
camera.set(cv2.CAP_PROP_BRIGHTNESS, 40)
camera.set(cv2.CAP_PROP_CONTRAST, 50)
camera.set(cv2.CAP_PROP_EXPOSURE, 156)

# ================= 状态机 =================
state = "IDLE"
color_sequence = []
seen_colors = set()

try:
    while True:
        ret, frame = camera.read()
        if not ret: continue
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # ---------- IDLE：扫 start ----------
        if state == "IDLE":
            if any("start" in b.data.decode() for b in pyzbar.decode(gray)):
                print("[start] 开始")
                color_sequence, seen_colors = [], set()

                run_wheel(WHEEL_SPEED, T_FORWARD_1)             # 起步前进
                run_wheel(WHEEL_SPEED, T_ARC, WHEEL_DELTA)      # 弧线右转
                send('wheel', WHEEL_SPEED, WHEEL_SPEED,
                     WHEEL_SPEED, WHEEL_SPEED)                  # 持续前进
                state = "GOING"

        # ---------- GOING：前进 + 识别 + 扫 stop ----------
        elif state == "GOING":
            color = detect_color(frame)
            if color and color not in seen_colors:
                color_sequence.append(color)
                seen_colors.add(color)
                print("[颜色]", color, color_sequence)

            if any("stop" in b.data.decode() for b in pyzbar.decode(gray)):
                print("[stop] 停车")
                stop(); time.sleep(0.5)

                # 返程：去程动作全部取反
                run_wheel(-WHEEL_SPEED, T_RETURN)               # 直线后退
                stop(); time.sleep(0.3)
                run_wheel(-WHEEL_SPEED, T_ARC, -WHEEL_DELTA)    # 倒车弧线（差速取反）
                stop(); time.sleep(0.3)
                run_wheel(-WHEEL_SPEED, T_FORWARD_1)            # 短直线后退
                stop(); time.sleep(0.5)

                state = "SPEAK"

        # ---------- SPEAK ----------
        elif state == "SPEAK":
            speak("识别到的颜色依次是：" + "、".join(color_sequence)
                  if color_sequence else "没有识别到任何颜色")
            state = "DONE"

        # ---------- DONE ----------
        elif state == "DONE":
            pass

        image_widget.value = to_jpeg(frame)

except KeyboardInterrupt:
    pass
finally:
    stop()
    camera.release()