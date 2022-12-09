import pygame
##import Rpi.GPIO as GPIO
import sys
import os
from subprocess import Popen
import serial
from pygame.locals import *
import time

ser1 = serial.Serial('/dev/ttyACM0',9600)
ser2 = serial.Serial('/dev/ttyACM1',9600)

last_state1 = True
last_state2 = True
last_state3 = True
last_state4 = True
input_state1 = True
input_state2 = True
input_state3 = True
input_state4 = True
quit_video = True
player = False
lastSong = 10
newSong = 11
maxSong = 28
currentTime = time.time()
SongInterval = 100
startTime = currentTime
autoSequence = True


fire = ("/home/pi/Videos/fire.mp4")
doworry = ("/home/pi/Videos/doworry3.mp4")
first = ("/home/pi/Videos/first.mp4")
dragon = ("/home/pi/Videos/dragon.mp4")
better = ("/home/pi/Videos/better.mp4")
great = ("/home/pi/Videos/great.mp4")
findyour = ("/home/pi/Videos/find.mp4")
happy = ("/home/pi/Videos/happy3.mp4")
worryThing = ("/home/pi/Videos/worrything3.mp4")

great = ("/home/pi/Videos/great3.mp4")
cheap = ("/home/pi/Videos/cheap3.mp4")
sorry = ("/home/pi/Videos/sorry.mp4")
survive = ("/home/pi/Videos/survive3.mp4")
call = ("/home/pi/Videos/call.mp4")
heist = ("/home/pi/Videos/heist.mp4")
let = ("/home/pi/Videos/let.mp4")
lean = ("/home/pi/Videos/lean.mp4")
ymca = ("/home/pi/Videos/ymca4.mp4")
roar = ("/home/pi/Videos/roar3.mp4")
add = ("/home/pi/Videos/add3.mp4")

turnlove = ("/home/pi/Videos/turnlove3.mp4")
price = ("/home/pi/Videos/price3.mp4")
holdhand = ("/home/pi/Videos/holdhand3.mp4")
airplane = ("/home/pi/Videos/airplaine3.mp4")
titan = ("/home/pi/Videos/titan3.mp4")


applause = ("/home/pi/Videos/applause.mp4")
rock = ("/home/pi/Videos/rock.mp4")
turnlove = ("/home/pi/Videos/turnlove3.mp4")
WorryChild = ("/home/pi/Videos/worrychild.mp4")

pygame.init()
pygame.display.set_mode((1500, 700))


running = True

while running:
    for event in pygame.event.get():
        if event.type == KEYDOWN:
            if event.key == K_DOWN:
                newSong = lastSong - 1
                if newSong <= 0 :
                    newSong = maxSong
            elif event.key == K_UP:
                newSong = lastSong + 1
                if newSong > maxSong:
                    newSong = 1    
            elif event.key == K_RIGHT:
                newSong = lastSong + 1
                if newSong > maxSong:
                    newSong = 10    
            elif event.key == K_LEFT:
                ser1.write(b'0')
                ser2.write(b'0')
                os.system('killall omxplayer.bin')
                player = False
        if event.type == QUIT:
            running = False
            print("BYE")

    #Check for time up... time to go to next song
    currentTime = time.time()
    if autoSequence :
        if currentTime - startTime > SongInterval:
            newSong = lastSong + 1
            startTime = currentTime
            if newSong > maxSong:
                newSong = 10  

    #starting a new song if requested
    if newSong != lastSong:
        lastSong = newSong
        startTime = currentTime
        if newSong == 24:
            ser1.write(b'24')
            ser2.write(b'24')
            SongInterval = 105
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b','-o','both',  better ])
                player = True
            else:
                omxc = Popen(['omxplayer', '-b','-o','both',   better ])
                player = True
        if newSong == 25:
            ser1.write(b'25')
            ser2.write(b'25')
            SongInterval = 139
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both',  findyour ])
                player = True
            else:
                omxc = Popen(['omxplayer','-b','-o','both',  findyour ])
                player = True
        if newSong == 23:
            ser1.write(b'23')
            ser2.write(b'23')
            SongInterval = 227
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both', rock ])
                player = True
            else:
                omxc = Popen(['omxplayer' ,'-b', '-o','both',  rock ])
                player = True
        if newSong == 21:
            ser1.write(b'21')
            ser2.write(b'21')
            SongInterval = 159
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b','-o','both',  fire ])
                player = True
            else:
                omxc = Popen(['omxplayer', '-b','-o','both',   fire ])
                player = True
        if newSong == 22:
            ser1.write(b'22')
            ser2.write(b'22')
            SongInterval = 209
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both',  applause ])
                player = True
            else:
                omxc = Popen(['omxplayer','-b','-o','both',  applause ])
                player = True
        if newSong == 26:
            ser1.write(b'26')
            ser2.write(b'26')
            SongInterval = 210
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both', titan ])
                player = True
            else:
                omxc = Popen(['omxplayer' ,'-b', '-o','both', titan ])
                player = True

        if newSong == 27:
            ser1.write(b'27')
            ser2.write(b'27')
            SongInterval = 193
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b','-o','both',  great ])
                player = True
            else:
                omxc = Popen(['omxplayer', '-b','-o','both',   great ])
                player = True
        if newSong == 28:
            ser1.write(b'28')
            ser2.write(b'28')
            SongInterval = 130
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both',  cheap ])
                player = True
            else:
                omxc = Popen(['omxplayer','-b','-o','both',  cheap ])
                player = True
        if newSong == 10:
            ser1.write(b'10')
            ser2.write(b'10')
            SongInterval = 142
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both', add ])
                player = True
            else:
                omxc = Popen(['omxplayer' ,'-b', '-o','both',  add ])
                player = True
        if newSong == 14:
            ser1.write(b'14')
            ser2.write(b'14')
            SongInterval = 220
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b','-o','both',  price ])
                player = True
            else:
                omxc = Popen(['omxplayer', '-b','-o','both', price ])
                player = True
        if newSong == 12:
            ser1.write(b'12')
            ser2.write(b'12')
            SongInterval = 225
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both',  holdhand ])
                player = True
            else:
                omxc = Popen(['omxplayer','-b','-o','both',  holdhand ])
                player = True
        if newSong == 11:
            ser1.write(b'11')
            ser2.write(b'11')
            SongInterval = 221
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both', roar ])
                player = True
            else:
                omxc = Popen(['omxplayer' ,'-b', '-o','both', roar ])
                player = True


        if newSong == 13:
            ser1.write(b'13')
            ser2.write(b'13')
            SongInterval = 178
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b','-o','both',  airplane ])
                player = True
            else:
                omxc = Popen(['omxplayer', '-b','-o','both', airplane ])
                player = True

        if newSong == 15:
            ser1.write(b'15')
            ser2.write(b'15')
            SongInterval = 211
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both', ymca ])
                player = True
            else:
                omxc = Popen(['omxplayer' ,'-b', '-o','both',  ymca ])
                player = True
        if newSong == 16:
            ser1.write(b'16')
            ser2.write(b'16')
            SongInterval = 167
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b','-o','both',  doworry ])
                player = True
            else:
                omxc = Popen(['omxplayer', '-b','-o','both', doworry ])
                player = True
        if newSong == 17:
            ser1.write(b'17')
            ser2.write(b'17')
            SongInterval = 197
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b','-o','both',  turnlove ])
                player = True
            else:
                omxc = Popen(['omxplayer', '-b','-o','both', turnlove ])
                player = True


        if newSong == 18:
            ser1.write(b'18')
            ser2.write(b'18')
            SongInterval = 210
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b', '-o','both', worryThing ])
                player = True
            else:
                omxc = Popen(['omxplayer' ,'-b', '-o','both', worryThing ])
                player = True
        if newSong == 19:
            ser1.write(b'19')
            ser2.write(b'19')
            SongInterval = 167
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b','-o','both',  first ])
                player = True
            else:
                omxc = Popen(['omxplayer', '-b','-o','both', first ])
                player = True
        if newSong == 20:
            ser1.write(b'20')
            ser2.write(b'20')
            SongInterval = 207
            if player :
                os.system('killall omxplayer.bin')
                omxc = Popen(['omxplayer','-b','-o','both',  WorryChild ])
                player = True
            else:
                omxc = Popen(['omxplayer', '-b','-o','both', WorryChild ])
                player = True
