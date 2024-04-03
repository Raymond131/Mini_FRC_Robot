import bluetooth
from bluetooth import Protocols
import time
import pygame


Stick = True
Blutooth = True
if(Stick):
    pygame.init()
    pygame.joystick.init()
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

# nearby_devices = bluetooth.discover_devices(lookup_names=True)
# print("Found {} devices.".format(len(nearby_devices)))

# for addr, name in nearby_devices:
#     print("  {} - {}".format(addr, name))

if(Blutooth):
    esp32 = 'SwerveBotDevKit'
    address = ''
    print("at least this runs")
    devices = bluetooth.discover_devices()

    for addr in devices:
        print(addr)
        if esp32 == bluetooth.lookup_name(addr):
            address = addr
            print("found it")
            break

    port = 1
    sock = bluetooth.BluetoothSocket(Protocols.RFCOMM)
    sock.connect((address, port))

while True:
    pygame.event.get()
    ax0 = int(100*(round(joystick.get_axis(0),2)+1))
    ax1 = int(100*(round(joystick.get_axis(1),2)+1))
    bt0 = joystick.get_button(0)
    bt1 = joystick.get_button(1)
    outputByte = (ax0).to_bytes(1,byteorder='big')+(ax1).to_bytes(1,byteorder='big')+(bt0).to_bytes(1,byteorder='big')+(bt1).to_bytes(1,byteorder='big')
    sock.send(outputByte)
    # print(outputByte)
    # print('ax0: %3d, ax1: %3d, bt0, %d, bt1, %d' % (ax0, ax1, bt0, bt1))
    time.sleep(0.01)
for x in range(5):
    sock.send((125).to_bytes(1, byteorder='big')+b'\x01'+b'\x00'+b'\xff')
    time.sleep(0.01)
print("I already said hey")
sock.close() 