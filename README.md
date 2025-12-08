# BumWatch

THIS WATCH CONSISTS ENTIRELY OF BREAKOUT BOARDS AND IN-HOUSE FABRICATED PCBs. Easier place to start (if that's what you want), but it's not the final version. See the final product here: Github coming soon (private atm)

## Introduction

The Bumwatch is truly made for bums - it has all the features a bum needs and nothing else. A very minimalistic display displays two things - steps taken and their heart rate that updates every second. 

We live in a world full of distractions and bum-inducing items. Technology is specifically designed to make our lives easier, which is synonymous with making us more of a bum. Instead of bleeding-edge features, what a bum truly needs is an accountability partner that gives them only what they truly need.

The BumWatch provides the satisfaction of progress through step counting that updates live to provide instant gratification and feedback. Also, knowing the average resting heart rate is 60-100, this would motivate the bums to lower their heartrate through exercise because they become aware they are a bum. Finally, when the bum decides to be a bum, there is a vibration feedback that reminds them they are a bum. If you want to stop being a bum, there is no better method than to create this watch.

*insert picture here*

This iteration of the BumWatch is made entirely in-house and costed $0 (not including time and labor). The BumWatch consists entirely of breakout boards (that I borrowed) placed and stacked neatly and soldered to a custom-PCB that was created using in-house PCB fabrication machines. Although I would never recommend this method (due to problems I will address as we go on), it was fun planning and watching everything come to fruition.

## Making the PCB


## Materials

1x Arduino Pro Mini (MUST BE 3.3V Version)
- Small lipo batteries usually say they supply 3.7V. However, it will drop down from 4.2V when fully charged to 3.0V when fully discharged until it eventually gives out. So, either the breakouts must be rated within the 3.0V-4.2V range or we must use a voltage regulator/buck converter. Nevertheless, it has to be a 3.3V rated version unless you use a step-up converter that can supply 5V.

1x SSD1306 (4-pin display)
- This was the only display I could find that fit my desired form factor that I could find in-person. There were many more options online, but I settled on this one since this version of the watch is not exactly the final version I want to use (i.e. I did not care).

1x Sparkfun ICM-20948 Breakout (IMU)
- The disadvantage of this one over the BNO055 (this was so old and inaccurate it was unusable) is that there is no integrated sensor fusion, meaning it displays the raw IMU data. However, this sensor is much newer and much more accurate than all the alternatives I have considered. In essence, it is better in every way as long as I can write an accurate step counter algorithm.

1x Sparkfun MAX30101 + MAX32664 Breakout (Pulse Oximeter and HR Monitor)
- The cool thing about this breakout is that it has a MAX32664 attached to it. The sole purpose of that chip is to take the raw data from the MAX30101 and use its internal algorithm to display the heart rate without me having to write any algorithms - very convenient.

1x Sparkfun BPM085 Breakout (Pressure Sensor)
- This ended up not being used in the final design because it was the only sensor rated at 1.8V-3.3V and the voltage regulator was a piece of junk. Also, I forgot to route the voltage regulator to the on/off switch meaning this sensor would always be on with the voltage regulator - as mentioned above, I ran out of time so I could not fix this issue. Also, 

1x Adafruit DRV2605L Breakout
- Every sensor above gave me a headache at some point for one reason or another, but this one just worked. Maybe Adafruit is superior to Sparkfun? (this is a joke.. or is it)

1x Vibration Motor
- Okay I lied, this isn't a breakout. But like you need a vibration motor to use the vibration motor driver right? This one is brand agnostic - just find a small vibration motor that fits ur watch.

1x Adafruit USB-C Microlipo Breakout (USB-C Charging)
- Essentially, you can use this to charge/discharge your battery. It's only supports charging though, you do not use this to update your Arduino firmware. And also, it just works (to be fair, all the Sparkfun sensors had more complex wiring diagrams)

1x 3.3V Voltage Regulator
- I got this from my local makerspace and it was bought in bulk from China.. yeah, it was really, REALLY bad. The voltage drop after connecting one sensor was so large my multimeter displayed <3V (???). Luckily, all the sensors here except the BMP085 were rated 3V-5.5V, so I did not need this voltage regulator (i.e. I could connect it directly to the battery since it will always stay within 3V-4.2V). Due to this garbage of a regulator, I had to redo my entire layout and print entire new circuit boards just because this voltage regulator was so bad (rant over). Why not use a buck converter? Well, this only crossed my mind after I created a layout that fit the smartwatch form factor. And considering this was not even the final version, I just could not bother to waste any more time on this.

1x 3.7V LiPo Battery
- Pretty self-explanatory here, just find one that's not a coincell battery and is small enough to fit inside your watch.

1x FTDL Basic Breakout (USB to Serial Converter)
- THIS IS NOT APART OF THE WATCH. The Arduino pro mini does not have a convenient port to update the firmware. So, you actually need this breakout to be able to push your Arduino sketches into the Arduino pro mini.

## Assembly

This part was a headache. I've soldered on a PCB with no solder mask or silkscreen before, but this one just caused a lot more problems than I would have liked.
