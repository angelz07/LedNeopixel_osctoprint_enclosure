import sys
import smbus
import time

mode = sys.argv[1]
valeur = sys.argv[2]


bus = smbus.SMBus(1)
address = 0x12

message = mode + "-" + valeur
messagetosend = []
for b in message:
        messagetosend.append(ord(b))

print messagetosend


bus.write_i2c_block_data(address,0x00,messagetosend)
# Pause de 4 seconde pour laisser le temps au traitement de se faire
time.sleep(4)


#reponse
reponse = bus.read_i2c_block_data(address, 0x32, 16)
message_recu = "".join(map(chr, reponse))
print "reponse = " , message_recu
