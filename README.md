# LedNeopixel_osctoprint_enclosure
Control led Neopixel with script python from rpi to arduino nano by i2c

use : i2cdetect -y 1



connect Rpi with nano by I2C Connexion

Arduino Nano SDA A4 --> Raspberry SDA BCM2(RPI) 
Arduino Nano SCL A5 --> Raspberry SCL BCM3(RPI)
Arduino GND 		--> Raspberry GND

Give Power on Nano with 5v and connect stripled on Nano 

VCC to Aduino Nano 5V
Gnd to Aduino Nano GND
Signal to Arduino Nano D6


on raspberry to find I2C address of arduino nano


Scipt to use 
	python OctoPrint/Ruban_Neopixel.py colorWipe red

	python OctoPrint/Ruban_Neopixel.py rainbow 10

	python OctoPrint/Ruban_Neopixel.py theaterChase 10

	python OctoPrint/Ruban_Neopixel.py theaterChaseRainbow 10
	
	
Color Pré Configured on Nano :

Black

White

Red

Lime

Blue

Yellow

Cyan_Aqua

Magenta_Fuchsia

Silver

Gray

Maroon

Olive

Green

Purple

Teal

Navy

maroon

dark_red

brown

firebrick

crimson

red

dark_orange

orange

gold

dark_golden_rod

golden_rod

pale_golden_rod

dark_khaki

khaki

olive

yellow

yellow_green

dark_olive_green

olive_drab

lawn_green

chart_reuse

green_yellow

dark_green

green

forest_green

lime

lime_green

light_green

pale_green

dark_sea_green

medium_spring_green

spring_green

sea_green

medium_aqua_marine

medium_sea_green

light_sea_green

dark_slate_gray

teal

dark_cyan

aqua

cyan

light_cyan

dark_turquoise

turquoise

medium_turquoise

aqua_marine

powder_blue

cadet_blue

steel_blue

corn_flower_blue

deep_sky_blue

dodger_blue

light_blue

sky_blue

light_sky_blue

midnight_blue

navy

dark_blue

medium_blue

blue

royal_blue

blue_violet

indigo

dark_slate_blue

slate_blue

deep_pink

hot_pink

light_pink

pink

antique_white

beige

bisque

blanched_almond

wheat

white_smoke

white