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

# nearby_devices = bluetooth.discover_devices(lookup_names=True) //inquiry example from pypi.org on pybluez2 library
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

axes = [0 for i in range(6)]
axesAdj = [0,0.004,0,0,0,0]
buttons = [0 for i in range(10)]

def printJoyInputs():
    messageString = ""
    for a in range(6):
        messageString += 'Ax%d:%3d | '% (a, axes[a]) + " "
    for b in range(10):
        messageString += 'Bt%d:%d | '% (b, buttons[b]) + " "
    print(messageString)

def sayHi():
    for x in range(5):
        sock.send((125).to_bytes(1, byteorder='big')+b'\x01'+b'\x00'+b'\xff')
        time.sleep(0.01)
    print("I already said hey")
    sock.close() 

while True:
    pygame.event.get()
    
    messageBytes = b''
    for axis in range(6):
        axes[axis] = int(100*(round(joystick.get_axis(axis)+axesAdj[axis],2)+1))
        messageBytes += axes[axis].to_bytes(1,byteorder='big')
    for button in range(10):
        buttons[button] = joystick.get_button(button)
        messageBytes += buttons[button].to_bytes(1,byteorder='big')
    sock.send(messageBytes)
    
    time.sleep(0.02)

