#include "TM1637Display.h"
#include "Adafruit_NeoPixel.h"
#include "NTPClient.h"
#include "WiFiManager.h"


// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        17
#define display_CLK 18
#define display_DIO 19

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 35


//========================USEFUL VARIABLES=============================
int UTC = 2; // UTC = value in hour (SUMMER TIME) [For example: Paris UTC+2 => UTC=2]
int Display_backlight = 2; // Adjust it 0 to 7
int led_ring_brightness = 10; // Adjust it 0 to 255
int led_ring_brightness_flash = 250; // Adjust it 0 to 255

// ========================================================================
// ========================================================================

const long utcOffsetInSeconds = 3600; // UTC + 1H / Offset in second

// Adjust the color of the led ring
#define red 00
#define green 20
#define blue 255

// When setting up the NeoPixel library, we tell it how many pixels,
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
TM1637Display display(display_CLK, display_DIO);
int flag = 0;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds*UTC);
bool res;

void setup() {

  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);

  Serial.begin(115200);
  Serial.println("\n Starting");

  WiFiManager manager;   

  //manager.resetSettings();

  manager.setTimeout(180);
  //fetches ssid and password and tries to connect, if connections succeeds it starts an access point with the name called "IRON_MAN_ARC" and waits in a blocking loop for configuration
  res = manager.autoConnect("IRON_MAN_ARC","password");
  
  if(!res) {
  Serial.println("failed to connect and timeout occurred");
  ESP.restart(); //reset and try again
  }

  timeClient.begin();
  display.setBrightness(Display_backlight);
  pixels.begin(); // INITIALIZE NeoPixel pixels object
  pixels.setBrightness(led_ring_brightness);
  

  for(int i=0; i<35;i++){
  pixels.setPixelColor(i, pixels.Color(red, green, blue));
  pixels.show();
  delay(50);
  }

  flash_cuckoo();// white flash

}

void loop() {

  // Update the time
  timeClient.update();

  Serial.print("Time: ");
  Serial.println(timeClient.getFormattedTime());
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime); 
  int currentYear = ptm->tm_year+1900;
  Serial.print("Year: ");
  Serial.println(currentYear);
  
  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int currentMonth = ptm->tm_mon+1;
  Serial.print("Month: ");
  Serial.println(currentMonth);

  if((currentMonth*30 + monthDay) >= 121 && (currentMonth*30 + monthDay) < 331){
  timeClient.setTimeOffset(utcOffsetInSeconds*UTC);} // Change daylight saving time - Summer
  else {timeClient.setTimeOffset((utcOffsetInSeconds*UTC) - 3600);} // Change daylight saving time - Winter

  // switch on the ring in blue
  pixels.clear(); // Set all pixel colors to 'off'
  blue_light();

  // write the time on the display
  display.showNumberDecEx(timeClient.getHours(),0b01000000,true,2,0);
  display.showNumberDecEx(timeClient.getMinutes(),0b01000000,true,2,2);

  // switch on the blue leds
  digitalWrite(25,1);
  digitalWrite(26,1);

  // Animation every hour
  if(timeClient.getMinutes()== 00 && flag==0)
  {
    display_cuckoo();
    flag=1;
  }
   if(timeClient.getMinutes()>=01)
  {
    flag=0;
  }



}

void blue_light(){

  pixels.setBrightness(led_ring_brightness);
  pixels.setPixelColor(0, pixels.Color(red, green, blue));
  pixels.setPixelColor(1, pixels.Color(red, green, blue));
  pixels.setPixelColor(2, pixels.Color(red, green, blue));
  pixels.setPixelColor(3, pixels.Color(red, green, blue));
  pixels.setPixelColor(4, pixels.Color(red, green, blue));
  pixels.setPixelColor(5, pixels.Color(red, green, blue));
  pixels.setPixelColor(6, pixels.Color(red, green, blue));
  pixels.setPixelColor(7, pixels.Color(red, green, blue));
  pixels.setPixelColor(8, pixels.Color(red, green, blue));
  pixels.setPixelColor(9, pixels.Color(red, green, blue));
  pixels.setPixelColor(10, pixels.Color(red, green, blue));
  pixels.setPixelColor(11, pixels.Color(red, green, blue));
  pixels.setPixelColor(12, pixels.Color(red, green, blue));
  pixels.setPixelColor(13, pixels.Color(red, green, blue));
  pixels.setPixelColor(14, pixels.Color(red, green, blue));
  pixels.setPixelColor(15, pixels.Color(red, green, blue));
  pixels.setPixelColor(16, pixels.Color(red, green, blue));
  pixels.setPixelColor(17, pixels.Color(red, green, blue));
  pixels.setPixelColor(18, pixels.Color(red, green, blue));
  pixels.setPixelColor(19, pixels.Color(red, green, blue));
  pixels.setPixelColor(20, pixels.Color(red, green, blue));
  pixels.setPixelColor(21, pixels.Color(red, green, blue));
  pixels.setPixelColor(22, pixels.Color(red, green, blue));
  pixels.setPixelColor(23, pixels.Color(red, green, blue));
  pixels.setPixelColor(24, pixels.Color(red, green, blue));
  pixels.setPixelColor(25, pixels.Color(red, green, blue));
  pixels.setPixelColor(26, pixels.Color(red, green, blue));
  pixels.setPixelColor(27, pixels.Color(red, green, blue));
  pixels.setPixelColor(28, pixels.Color(red, green, blue));
  pixels.setPixelColor(29, pixels.Color(red, green, blue));
  pixels.setPixelColor(30, pixels.Color(red, green, blue));
  pixels.setPixelColor(31, pixels.Color(red, green, blue));
  pixels.setPixelColor(32, pixels.Color(red, green, blue));
  pixels.setPixelColor(33, pixels.Color(red, green, blue));
  pixels.setPixelColor(34, pixels.Color(red, green, blue));
  pixels.setPixelColor(35, pixels.Color(red, green, blue));
  pixels.show(); 

}

void flash_cuckoo(){
	pixels.setBrightness(led_ring_brightness_flash);
    pixels.setPixelColor(0, pixels.Color(250,250,250));
    pixels.setPixelColor(1, pixels.Color(250,250,250));
    pixels.setPixelColor(2, pixels.Color(250,250,250));
    pixels.setPixelColor(3, pixels.Color(250,250,250));
    pixels.setPixelColor(4, pixels.Color(250,250,250));
    pixels.setPixelColor(5, pixels.Color(250,250,250));
    pixels.setPixelColor(6, pixels.Color(250,250,250));
    pixels.setPixelColor(7, pixels.Color(250,250,250));
    pixels.setPixelColor(8, pixels.Color(250,250,250));
    pixels.setPixelColor(9, pixels.Color(250,250,250));
    pixels.setPixelColor(10, pixels.Color(250,250,250));
    pixels.setPixelColor(11, pixels.Color(250,250,250));
    pixels.setPixelColor(12, pixels.Color(250,250,250));
    pixels.setPixelColor(13, pixels.Color(250,250,250));
    pixels.setPixelColor(14, pixels.Color(250,250,250));
    pixels.setPixelColor(15, pixels.Color(250,250,250));
    pixels.setPixelColor(16, pixels.Color(250,250,250));
    pixels.setPixelColor(17, pixels.Color(250,250,250));
    pixels.setPixelColor(18, pixels.Color(250,250,250));
    pixels.setPixelColor(19, pixels.Color(250,250,250));
    pixels.setPixelColor(20, pixels.Color(250,250,250));
    pixels.setPixelColor(21, pixels.Color(250,250,250));
    pixels.setPixelColor(22, pixels.Color(250,250,250));
    pixels.setPixelColor(23, pixels.Color(250,250,250));
    pixels.setPixelColor(24, pixels.Color(250,250,250));
    pixels.setPixelColor(25, pixels.Color(250,250,250));
    pixels.setPixelColor(26, pixels.Color(250,250,250));
    pixels.setPixelColor(27, pixels.Color(250,250,250));
    pixels.setPixelColor(28, pixels.Color(250,250,250));
    pixels.setPixelColor(29, pixels.Color(250,250,250));
    pixels.setPixelColor(30, pixels.Color(250,250,250));
    pixels.setPixelColor(31, pixels.Color(250,250,250));
    pixels.setPixelColor(32, pixels.Color(250,250,250));
    pixels.setPixelColor(33, pixels.Color(250,250,250));
    pixels.setPixelColor(34, pixels.Color(250,250,250));
    pixels.setPixelColor(35, pixels.Color(250,250,250));
    pixels.show();

  for (int i=led_ring_brightness_flash; i>10 ; i--){
  pixels.setBrightness(i);
  pixels.show();
  delay(7);
  }
  blue_light();

}

void display_cuckoo(){

for (int i =0 ; i<88 ; i++)
{
  display.showNumberDecEx(i,0b01000000,true,2,0);
  display.showNumberDecEx(i,0b01000000,true,2,2);
}

display.showNumberDecEx(88,0b01000000,true,2,0);
display.showNumberDecEx(88,0b01000000,true,2,2);
flash_cuckoo();
delay(2000);

}