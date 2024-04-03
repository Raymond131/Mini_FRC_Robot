import pygame
pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()
import time
while True:
    pygame.event.get()
    ax0 = int(100*(round(joystick.get_axis(0),2)+1))
    ax1 = int(100*(round(joystick.get_axis(1),2)+1))
    ax2 = int(100*(round(joystick.get_axis(2),2)+1))
    ax3 = int(100*(round(joystick.get_axis(3),2)+1))
    
    bt0 = joystick.get_button(0)
    bt1 = joystick.get_button(1)
    bt2 = joystick.get_button(2)
    bt3 = joystick.get_button(3)
    bt4 = joystick.get_button(4)
    bt5 = joystick.get_button(5)
    bt6 = joystick.get_button(6)
    bt7 = joystick.get_button(7)
    bt8 = joystick.get_button(8)
    bt9 = joystick.get_button(9)
    # bt10 = joystick.get_button(10)
    # bt11 = joystick.get_button(11)
    

    print('ax0: %3d, ax1: %3d, ax2: %3d, ax3: %3d, bt0:%d, bt1:%d, bt2:%d, bt3:%d, bt4:%d, bt5:%d, bt6:%d, bt7:%d, bt8:%d, bt9:%d' % (ax0, ax1, ax2, ax3, bt0, bt1, bt2, bt3, bt4, bt5, bt6, bt7, bt8, bt9))
    time.sleep(0.05)