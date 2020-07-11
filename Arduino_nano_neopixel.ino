#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <StringSplitter.h>


int Couleur[]= {0, 0, 0};

/* Couleur RGB */

int Black[] = {0,0,0};
int White[] = {255,255,255};
int Red[] = {255,0,0};
int Lime[] = {0,255,0};
int Blue[] = {0,0,255};
int Yellow[] = {255,255,0};
int Cyan_Aqua[] = {0,255,255};
int Magenta_Fuchsia[] = {255,0,255};
int Silver[] = {192,192,192};
int Gray[] = {128,128,128};
int Maroon[] = {128,0,0};
int Olive[] = {128,128,0};
int Green[] = {0,128,0};
int Purple[] = {128,0,128};
int Teal[] = {0,128,128};
int Navy[] = {0,0,128};
int maroon[] = {128,0,0};
int dark_red[] = {139,0,0};
int brown[] = {165,42,42};
int firebrick[] = {178,34,34};
int crimson[] = {220,20,60};
int red[] = {255,0,0};
int dark_orange[] = {255,140,0};
int orange[] = {255,165,0};
int gold[] = {255,215,0};
int dark_golden_rod[] = {184,134,11};
int golden_rod[] = {218,165,32};
int pale_golden_rod[] = {238,232,170};
int dark_khaki[] = {189,183,107};
int khaki[] = {240,230,140};
int olive[] = {128,128,0};
int yellow[] = {255,255,0};
int yellow_green[] = {154,205,50};
int dark_olive_green[] = {85,107,47};
int olive_drab[] = {107,142,35};
int lawn_green[] = {124,252,0};
int chart_reuse[] = {127,255,0};
int green_yellow[] = {173,255,47};
int dark_green[] = {0,100,0};
int green[] = {0,128,0};
int forest_green[] = {34,139,34};
int lime[] = {0,255,0};
int lime_green[] = {50,205,50};
int light_green[] = {144,238,144};
int pale_green[] = {152,251,152};
int dark_sea_green[] = {143,188,143};
int medium_spring_green[] = {0,250,154};
int spring_green[] = {0,255,127};
int sea_green[] = {46,139,87};
int medium_aqua_marine[] = {102,205,170};
int medium_sea_green[] = {60,179,113};
int light_sea_green[] = {32,178,170};
int dark_slate_gray[] = {47,79,79};
int teal[] = {0,128,128};
int dark_cyan[] = {0,139,139};
int aqua[] = {0,255,255};
int cyan[] = {0,255,255};
int light_cyan[] = {224,255,255};
int dark_turquoise[] = {0,206,209};
int turquoise[] = {64,224,208};
int medium_turquoise[] = {72,209,204};

int aqua_marine[] = {127,255,212};
int powder_blue[] = {176,224,230};
int cadet_blue[] = {95,158,160};
int steel_blue[] = {70,130,180};
int corn_flower_blue[] = {100,149,237};
int deep_sky_blue[] = {0,191,255};
int dodger_blue[] = {30,144,255};
int light_blue[] = {173,216,230};
int sky_blue[] = {135,206,235};
int light_sky_blue[] = {135,206,250};
int midnight_blue[] = {25,25,112};
int navy[] = {0,0,128};
int dark_blue[] = {0,0,139};
int medium_blue[] = {0,0,205};
int blue[] = {0,0,255};
int royal_blue[] = {65,105,225};
int blue_violet[] = {138,43,226};
int indigo[] = {75,0,130};
int dark_slate_blue[] = {72,61,139};
int slate_blue[] = {106,90,205};


int deep_pink[] = {255,20,147};
int hot_pink[] = {255,105,180};
int light_pink[] = {255,182,193};
int pink[] = {255,192,203};
int antique_white[] = {250,235,215};
int beige[] = {245,245,220};
int bisque[] = {255,228,196};
int blanched_almond[] = {255,235,205};
int wheat[] = {245,222,179};

int white_smoke[] = {245,245,245};
int white[] = {255,255,255};
 

/* Fin Couleur RGB */


int timer_rainbow = 0;
int timer_theaterChase = 0;
int timer_theaterChaseRainbow = 0;

bool boucle_Rainbow = false;
bool boucle_TheaterChase = false;
bool boucle_TheaterChaseRainbow = false;


#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 16

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

#define SLAVE_ADDRESS 0x12
// string to store what the RPi sends
char* str_recieved_from_RPi = "";

void setup() {

  Serial.begin(9600);

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  
  Serial.println("Start");
  // begin running as an I2C slave on the specified address
  Wire.begin(SLAVE_ADDRESS);
 
  // create event for receiving data
  Wire.onReceive(receiveData);

  Wire.onRequest(sendDataToRPI);
}

void loop() {
  // put your main code here, to run repeatedly:
 //  colorWipe(strip.Color(RGB_Rouge[0],RGB_Rouge[1],RGB_Rouge[2]), 50);
  if(boucle_Rainbow == true){
    rainbow(timer_rainbow);
  }

  if(boucle_TheaterChaseRainbow == true){
    theaterChaseRainbow(timer_theaterChaseRainbow); 
  }

  if(boucle_TheaterChase == true){
    theaterChase(strip.Color(127, 127, 127), timer_theaterChase); // White, half brightness
  }
}



volatile boolean receiveFlag = false;
char temp[50];
void receiveData(int howMany) {
  while(Wire.available()) {
    for (int i = 0; i < howMany; i++) {
          temp[i] = Wire.read();
          temp[i + 1] = '\0'; //add null after ea. char
        }  

        //RPi first byte is cmd byte so shift everything to the left 1 pos so temp contains our string
        for (int i = 0; i < howMany; ++i)
          temp[i] = temp[i + 1];
      
        receiveFlag = true;
        //Serial.println(temp);

        char* mess_recu = temp;
        char * dmess=strdup(mess_recu); // duplique le message
        char* Mode;
        Mode = strtok(dmess, "-");
        char* Val;
        Val = strtok(NULL, " ");  
        String myMode(Mode); 
        String myVal(Val);

        if (myMode == "stop" ) {
          boucle_Rainbow = false;
          boucle_TheaterChase = false;
          boucle_TheaterChaseRainbow = false;
          strip.show();
          Serial.print("Mode = ");
          Serial.println("Stop");
          
          
        }
        
        if (myMode == "theaterChaseRainbow" ) {
          boucle_Rainbow = false;
          boucle_TheaterChase = false;
          boucle_TheaterChaseRainbow = false;
          strip.show();
          Serial.print("Mode = ");
          Serial.println("theaterChaseRainbow");
          Serial.print("Val = ");
          Serial.println(Val);

          boucle_TheaterChaseRainbow = true;
         timer_theaterChaseRainbow = myVal.toInt();
          theaterChaseRainbow(timer_theaterChaseRainbow); 
       //   sendData("true");
        }

        else if (myMode == "rainbow") { 
          boucle_Rainbow = false;
          boucle_TheaterChase = false;
          boucle_TheaterChaseRainbow = false;
          strip.show();
          Serial.print("Mode = ");
           Serial.println("rainbow");
           Serial.print("Val = ");
           Serial.println(Val);

          boucle_Rainbow = true;
          timer_rainbow = myVal.toInt();
            rainbow(timer_rainbow);
          //  sendData("true");
        }

         if (myMode == "theaterChase" ) {
          boucle_Rainbow = false;
          boucle_TheaterChase = false;
          boucle_TheaterChaseRainbow = false;
          strip.show();
          Serial.print("Mode = ");
          Serial.println("theaterChase");
          Serial.print("Val = ");
          Serial.println(Val);

        
          boucle_TheaterChase = true;
          timer_theaterChase = myVal.toInt(); 
          theaterChase(strip.Color(Couleur[0], Couleur[1], Couleur[2]), timer_theaterChase); // White, half brightness
        }
        
        else if (myMode == "colorWipe" ) {
          boucle_Rainbow = false;
          boucle_TheaterChase = false;
          boucle_TheaterChaseRainbow = false;
          strip.show();
          Serial.print("Mode = ");
          Serial.println("colorWipe");
          Serial.print("Val = ");
          Serial.println(Val);

          
          
           if (myVal == "Black" ){
            Couleur[0] = Black[0];
            Couleur[1] = Black[1];
            Couleur[2] = Black[2];
            }
            
            if (myVal == "White" ){
            Couleur[0] = White[0];
            Couleur[1] = White[1];
            Couleur[2] = White[2];
            }
            
            if (myVal == "Red" ){
            Couleur[0] = Red[0];
            Couleur[1] = Red[1];
            Couleur[2] = Red[2];
            }
            
            if (myVal == "Lime" ){
            Couleur[0] = Lime[0];
            Couleur[1] = Lime[1];
            Couleur[2] = Lime[2];
            }
            
            if (myVal == "Blue" ){
            Couleur[0] = Blue[0];
            Couleur[1] = Blue[1];
            Couleur[2] = Blue[2];
            }
            
            if (myVal == "Yellow" ){
            Couleur[0] = Yellow[0];
            Couleur[1] = Yellow[1];
            Couleur[2] = Yellow[2];
            }
            
            if (myVal == "Cyan_Aqua" ){
            Couleur[0] = Cyan_Aqua[0];
            Couleur[1] = Cyan_Aqua[1];
            Couleur[2] = Cyan_Aqua[2];
            }
            
            if (myVal == "Magenta_Fuchsia" ){
            Couleur[0] = Magenta_Fuchsia[0];
            Couleur[1] = Magenta_Fuchsia[1];
            Couleur[2] = Magenta_Fuchsia[2];
            }
            
            if (myVal == "Silver" ){
            Couleur[0] = Silver[0];
            Couleur[1] = Silver[1];
            Couleur[2] = Silver[2];
            }
            
            if (myVal == "Gray" ){
            Couleur[0] = Gray[0];
            Couleur[1] = Gray[1];
            Couleur[2] = Gray[2];
            }
            
            if (myVal == "Maroon" ){
            Couleur[0] = Maroon[0];
            Couleur[1] = Maroon[1];
            Couleur[2] = Maroon[2];
            }
            
            if (myVal == "Olive" ){
            Couleur[0] = Olive[0];
            Couleur[1] = Olive[1];
            Couleur[2] = Olive[2];
            }
            
            if (myVal == "Green" ){
            Couleur[0] = Green[0];
            Couleur[1] = Green[1];
            Couleur[2] = Green[2];
            }
            
            if (myVal == "Purple" ){
            Couleur[0] = Purple[0];
            Couleur[1] = Purple[1];
            Couleur[2] = Purple[2];
            }
            
            if (myVal == "Teal" ){
            Couleur[0] = Teal[0];
            Couleur[1] = Teal[1];
            Couleur[2] = Teal[2];
            }
            
            if (myVal == "Navy" ){
            Couleur[0] = Navy[0];
            Couleur[1] = Navy[1];
            Couleur[2] = Navy[2];
            }
            
            if (myVal == "maroon" ){
            Couleur[0] = maroon[0];
            Couleur[1] = maroon[1];
            Couleur[2] = maroon[2];
            }
            
            if (myVal == "dark_red" ){
            Couleur[0] = dark_red[0];
            Couleur[1] = dark_red[1];
            Couleur[2] = dark_red[2];
            }
            
            if (myVal == "brown" ){
            Couleur[0] = brown[0];
            Couleur[1] = brown[1];
            Couleur[2] = brown[2];
            }
            
            if (myVal == "firebrick" ){
            Couleur[0] = firebrick[0];
            Couleur[1] = firebrick[1];
            Couleur[2] = firebrick[2];
            }
            
            if (myVal == "crimson" ){
            Couleur[0] = crimson[0];
            Couleur[1] = crimson[1];
            Couleur[2] = crimson[2];
            }
            
            if (myVal == "red" ){
            Couleur[0] = red[0];
            Couleur[1] = red[1];
            Couleur[2] = red[2];
            }
            
            if (myVal == "dark_orange" ){
            Couleur[0] = dark_orange[0];
            Couleur[1] = dark_orange[1];
            Couleur[2] = dark_orange[2];
            }
            
            if (myVal == "orange" ){
            Couleur[0] = orange[0];
            Couleur[1] = orange[1];
            Couleur[2] = orange[2];
            }
            
            if (myVal == "gold" ){
            Couleur[0] = gold[0];
            Couleur[1] = gold[1];
            Couleur[2] = gold[2];
            }
            
            if (myVal == "dark_golden_rod" ){
            Couleur[0] = dark_golden_rod[0];
            Couleur[1] = dark_golden_rod[1];
            Couleur[2] = dark_golden_rod[2];
            }
            
            if (myVal == "golden_rod" ){
            Couleur[0] = golden_rod[0];
            Couleur[1] = golden_rod[1];
            Couleur[2] = golden_rod[2];
            }
            
            if (myVal == "pale_golden_rod" ){
            Couleur[0] = pale_golden_rod[0];
            Couleur[1] = pale_golden_rod[1];
            Couleur[2] = pale_golden_rod[2];
            }
            
            if (myVal == "dark_khaki" ){
            Couleur[0] = dark_khaki[0];
            Couleur[1] = dark_khaki[1];
            Couleur[2] = dark_khaki[2];
            }
            
            if (myVal == "khaki" ){
            Couleur[0] = khaki[0];
            Couleur[1] = khaki[1];
            Couleur[2] = khaki[2];
            }
            
            if (myVal == "olive" ){
            Couleur[0] = olive[0];
            Couleur[1] = olive[1];
            Couleur[2] = olive[2];
            }
            
            if (myVal == "yellow" ){
            Couleur[0] = yellow[0];
            Couleur[1] = yellow[1];
            Couleur[2] = yellow[2];
            }
            
            if (myVal == "yellow_green" ){
            Couleur[0] = yellow_green[0];
            Couleur[1] = yellow_green[1];
            Couleur[2] = yellow_green[2];
            }
            
            if (myVal == "dark_olive_green" ){
            Couleur[0] = dark_olive_green[0];
            Couleur[1] = dark_olive_green[1];
            Couleur[2] = dark_olive_green[2];
            }
            
            if (myVal == "olive_drab" ){
            Couleur[0] = olive_drab[0];
            Couleur[1] = olive_drab[1];
            Couleur[2] = olive_drab[2];
            }
            
            if (myVal == "lawn_green" ){
            Couleur[0] = lawn_green[0];
            Couleur[1] = lawn_green[1];
            Couleur[2] = lawn_green[2];
            }
            
            if (myVal == "chart_reuse" ){
            Couleur[0] = chart_reuse[0];
            Couleur[1] = chart_reuse[1];
            Couleur[2] = chart_reuse[2];
            }
            
            if (myVal == "green_yellow" ){
            Couleur[0] = green_yellow[0];
            Couleur[1] = green_yellow[1];
            Couleur[2] = green_yellow[2];
            }
            
            if (myVal == "dark_green" ){
            Couleur[0] = dark_green[0];
            Couleur[1] = dark_green[1];
            Couleur[2] = dark_green[2];
            }
            
            if (myVal == "green" ){
            Couleur[0] = green[0];
            Couleur[1] = green[1];
            Couleur[2] = green[2];
            }
            
            if (myVal == "forest_green" ){
            Couleur[0] = forest_green[0];
            Couleur[1] = forest_green[1];
            Couleur[2] = forest_green[2];
            }
            
            if (myVal == "lime" ){
            Couleur[0] = lime[0];
            Couleur[1] = lime[1];
            Couleur[2] = lime[2];
            }
            
            if (myVal == "lime_green" ){
            Couleur[0] = lime_green[0];
            Couleur[1] = lime_green[1];
            Couleur[2] = lime_green[2];
            }
            
            if (myVal == "light_green" ){
            Couleur[0] = light_green[0];
            Couleur[1] = light_green[1];
            Couleur[2] = light_green[2];
            }
            
            if (myVal == "pale_green" ){
            Couleur[0] = pale_green[0];
            Couleur[1] = pale_green[1];
            Couleur[2] = pale_green[2];
            }
            
            if (myVal == "dark_sea_green" ){
            Couleur[0] = dark_sea_green[0];
            Couleur[1] = dark_sea_green[1];
            Couleur[2] = dark_sea_green[2];
            }
            
            if (myVal == "medium_spring_green" ){
            Couleur[0] = medium_spring_green[0];
            Couleur[1] = medium_spring_green[1];
            Couleur[2] = medium_spring_green[2];
            }
            
            if (myVal == "spring_green" ){
            Couleur[0] = spring_green[0];
            Couleur[1] = spring_green[1];
            Couleur[2] = spring_green[2];
            }
            
            if (myVal == "sea_green" ){
            Couleur[0] = sea_green[0];
            Couleur[1] = sea_green[1];
            Couleur[2] = sea_green[2];
            }
            
            if (myVal == "medium_aqua_marine" ){
            Couleur[0] = medium_aqua_marine[0];
            Couleur[1] = medium_aqua_marine[1];
            Couleur[2] = medium_aqua_marine[2];
            }
            
            if (myVal == "medium_sea_green" ){
            Couleur[0] = medium_sea_green[0];
            Couleur[1] = medium_sea_green[1];
            Couleur[2] = medium_sea_green[2];
            }
            
            if (myVal == "light_sea_green" ){
            Couleur[0] = light_sea_green[0];
            Couleur[1] = light_sea_green[1];
            Couleur[2] = light_sea_green[2];
            }
            
            if (myVal == "dark_slate_gray" ){
            Couleur[0] = dark_slate_gray[0];
            Couleur[1] = dark_slate_gray[1];
            Couleur[2] = dark_slate_gray[2];
            }
            
            if (myVal == "teal" ){
            Couleur[0] = teal[0];
            Couleur[1] = teal[1];
            Couleur[2] = teal[2];
            }
            
            if (myVal == "dark_cyan" ){
            Couleur[0] = dark_cyan[0];
            Couleur[1] = dark_cyan[1];
            Couleur[2] = dark_cyan[2];
            }
            
            if (myVal == "aqua" ){
            Couleur[0] = aqua[0];
            Couleur[1] = aqua[1];
            Couleur[2] = aqua[2];
            }
            
            if (myVal == "cyan" ){
            Couleur[0] = cyan[0];
            Couleur[1] = cyan[1];
            Couleur[2] = cyan[2];
            }
            
            if (myVal == "light_cyan" ){
            Couleur[0] = light_cyan[0];
            Couleur[1] = light_cyan[1];
            Couleur[2] = light_cyan[2];
            }
            
            if (myVal == "dark_turquoise" ){
            Couleur[0] = dark_turquoise[0];
            Couleur[1] = dark_turquoise[1];
            Couleur[2] = dark_turquoise[2];
            }
            
            if (myVal == "turquoise" ){
            Couleur[0] = turquoise[0];
            Couleur[1] = turquoise[1];
            Couleur[2] = turquoise[2];
            }
            
            if (myVal == "medium_turquoise" ){
            Couleur[0] = medium_turquoise[0];
            Couleur[1] = medium_turquoise[1];
            Couleur[2] = medium_turquoise[2];
            }
                     
            if (myVal == "aqua_marine" ){
            Couleur[0] = aqua_marine[0];
            Couleur[1] = aqua_marine[1];
            Couleur[2] = aqua_marine[2];
            }
            
            if (myVal == "powder_blue" ){
            Couleur[0] = powder_blue[0];
            Couleur[1] = powder_blue[1];
            Couleur[2] = powder_blue[2];
            }
            
            if (myVal == "cadet_blue" ){
            Couleur[0] = cadet_blue[0];
            Couleur[1] = cadet_blue[1];
            Couleur[2] = cadet_blue[2];
            }
            
            if (myVal == "steel_blue" ){
            Couleur[0] = steel_blue[0];
            Couleur[1] = steel_blue[1];
            Couleur[2] = steel_blue[2];
            }
            
            if (myVal == "corn_flower_blue" ){
            Couleur[0] = corn_flower_blue[0];
            Couleur[1] = corn_flower_blue[1];
            Couleur[2] = corn_flower_blue[2];
            }
            
            if (myVal == "deep_sky_blue" ){
            Couleur[0] = deep_sky_blue[0];
            Couleur[1] = deep_sky_blue[1];
            Couleur[2] = deep_sky_blue[2];
            }
            
            if (myVal == "dodger_blue" ){
            Couleur[0] = dodger_blue[0];
            Couleur[1] = dodger_blue[1];
            Couleur[2] = dodger_blue[2];
            }
            
            if (myVal == "light_blue" ){
            Couleur[0] = light_blue[0];
            Couleur[1] = light_blue[1];
            Couleur[2] = light_blue[2];
            }
            
            if (myVal == "sky_blue" ){
            Couleur[0] = sky_blue[0];
            Couleur[1] = sky_blue[1];
            Couleur[2] = sky_blue[2];
            }
            
            if (myVal == "light_sky_blue" ){
            Couleur[0] = light_sky_blue[0];
            Couleur[1] = light_sky_blue[1];
            Couleur[2] = light_sky_blue[2];
            }
            
            if (myVal == "midnight_blue" ){
            Couleur[0] = midnight_blue[0];
            Couleur[1] = midnight_blue[1];
            Couleur[2] = midnight_blue[2];
            }
            
            if (myVal == "navy" ){
            Couleur[0] = navy[0];
            Couleur[1] = navy[1];
            Couleur[2] = navy[2];
            }
            
            if (myVal == "dark_blue" ){
            Couleur[0] = dark_blue[0];
            Couleur[1] = dark_blue[1];
            Couleur[2] = dark_blue[2];
            }
            
            if (myVal == "medium_blue" ){
            Couleur[0] = medium_blue[0];
            Couleur[1] = medium_blue[1];
            Couleur[2] = medium_blue[2];
            }
            
            if (myVal == "blue" ){
            Couleur[0] = blue[0];
            Couleur[1] = blue[1];
            Couleur[2] = blue[2];
            }
            
            if (myVal == "royal_blue" ){
            Couleur[0] = royal_blue[0];
            Couleur[1] = royal_blue[1];
            Couleur[2] = royal_blue[2];
            }
            
            if (myVal == "blue_violet" ){
            Couleur[0] = blue_violet[0];
            Couleur[1] = blue_violet[1];
            Couleur[2] = blue_violet[2];
            }
            
            if (myVal == "indigo" ){
            Couleur[0] = indigo[0];
            Couleur[1] = indigo[1];
            Couleur[2] = indigo[2];
            }
            
            if (myVal == "dark_slate_blue" ){
            Couleur[0] = dark_slate_blue[0];
            Couleur[1] = dark_slate_blue[1];
            Couleur[2] = dark_slate_blue[2];
            }
            
            if (myVal == "slate_blue" ){
            Couleur[0] = slate_blue[0];
            Couleur[1] = slate_blue[1];
            Couleur[2] = slate_blue[2];
            }
            
            if (myVal == "deep_pink" ){
            Couleur[0] = deep_pink[0];
            Couleur[1] = deep_pink[1];
            Couleur[2] = deep_pink[2];
            }
            
            if (myVal == "hot_pink" ){
            Couleur[0] = hot_pink[0];
            Couleur[1] = hot_pink[1];
            Couleur[2] = hot_pink[2];
            }
            
            if (myVal == "light_pink" ){
            Couleur[0] = light_pink[0];
            Couleur[1] = light_pink[1];
            Couleur[2] = light_pink[2];
            }
            
            if (myVal == "pink" ){
            Couleur[0] = pink[0];
            Couleur[1] = pink[1];
            Couleur[2] = pink[2];
            }
            
            if (myVal == "antique_white" ){
            Couleur[0] = antique_white[0];
            Couleur[1] = antique_white[1];
            Couleur[2] = antique_white[2];
            }
            
            if (myVal == "beige" ){
            Couleur[0] = beige[0];
            Couleur[1] = beige[1];
            Couleur[2] = beige[2];
            }
            
            if (myVal == "bisque" ){
            Couleur[0] = bisque[0];
            Couleur[1] = bisque[1];
            Couleur[2] = bisque[2];
            }
            
            if (myVal == "blanched_almond" ){
            Couleur[0] = blanched_almond[0];
            Couleur[1] = blanched_almond[1];
            Couleur[2] = blanched_almond[2];
            }
            
            if (myVal == "wheat" ){
            Couleur[0] = wheat[0];
            Couleur[1] = wheat[1];
            Couleur[2] = wheat[2];
            }
            
            if (myVal == "white_smoke" ){
            Couleur[0] = white_smoke[0];
            Couleur[1] = white_smoke[1];
            Couleur[2] = white_smoke[2];
            }
            
            if (myVal == "white" ){
            Couleur[0] = white[0];
            Couleur[1] = white[1];
            Couleur[2] = white[2];
            }










          colorWipe(strip.Color(Couleur[0],Couleur[1],Couleur[2]), 100);
           
        }

       

     /*    dmess = "";
        Mode = "";
        Val = "";
        myMode = "";
        myVal = "";
        free(dmess);
        free(Mode);
        free(Val);*/
        
        receiveFlag = false; 
  }
  
}


void sendDataToRPI(){

    Serial.print("Donnee envoyée : ");
    Serial.println("True");

    Wire.write("True");
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  
    for(int a=0; a<10; a++) {  // Repeat 10 times...
      for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
        strip.clear();         //   Set all pixels in RAM to 0 (off)
        // 'c' counts up from 'b' to end of strip in steps of 3...
        for(int c=b; c<strip.numPixels(); c += 3) {
          strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        }
        strip.show(); // Update strip with new contents
        delay(wait);  // Pause for a moment
      }
    }
  
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this outer loop:
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
        // Offset pixel hue by an amount to make one full revolution of the
        // color wheel (range of 65536) along the length of the strip
        // (strip.numPixels() steps):
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
        // optionally add saturation and value (brightness) (each 0 to 255).
        // Here we're using just the single-argument hue variant. The result
        // is passed through strip.gamma32() to provide 'truer' colors
        // before assigning to each pixel:
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}