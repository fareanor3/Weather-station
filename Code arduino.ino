// esp8266 import

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <Adafruit_NeoPixel.h>

// strip led import

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN   6 // pin output
#define LED_COUNT 5 // number of pins
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// wifi set up values
const String ssid = "Lenovo";
const String password = "plus1mple";
// led set up values
int wifi_led_statue = 0; // is also temperature
int sun = 1; // to redefine led number
int cloud = 2; // to redefine led number
int rain = 3; // to redefine led number
int snow = 4; // to redefine led number
uint32_t Tcolor; // temperature color

// Your Domain name with URL path or IP address with path
String openWeatherMapApiKey = "463e3d3bf6f2a1282f9280434c7d6678"; //api key
String city = "Paris";
String countryCode = "FR";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For the final application, we gonna check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// if Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

String jsonBuffer;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600); // nb bit/s to eternal device
  Serial.println("bebut");
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.println("Strip");

 
  WiFi.begin(ssid, password);
  Serial.println("Wifi");
  // during connection :
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("NC");
    for (int i = -5; i < 5; i += 1) { // light blue leds blink waves
    strip.clear();
    strip.setPixelColor(abs(i), strip.Color(0,125,225)); // Set pixel's color (in RAM)
    strip.show(); //  Update strip to match
    delay(200);
    strip.clear();
    strip.show();
    delay(200);
    };
  }

  // when connected :
  for (int count = 0; count < 3; count++) { //triple light pink leds blink
      strip.clear();
      strip.setPixelColor(wifi_led_statue, strip.Color(255,25,75));
      strip.show();
      delay(200);
      strip.clear();
      strip.show(); 
      delay(200);
    };
  //Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading
  Serial.println("Set up fini");
}

// differents configurations

//     | Sun | cloud | rain | snow |  total weather id |
//  1  |  X  |       |      |      |       800         |
//  2  |  X  |   X   |      |      |       801         |
//  3  |     |   X   |      |      |      802-4        |
//  4  |     |   X   |  X   |      |  200-321 520-31   |
//  5  |     |   X   |      |  X   |      600-22       |
//  6  |  X  |   X   |  X   |      |       500-4       |

// the loop function runs over and over again forever
void loop() {
  
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&appid=" + openWeatherMapApiKey;
      
      jsonBuffer = httpGETRequest(serverPath.c_str());
      //Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);

      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") { // find a way to show on the box fail statut
        Serial.println("Parsing input failed!"); // find a way to show on the box fail statut
        return;
      }
      // cas 1
      if(int(myObject["weather"]["id"]) == 800) {
        strip.clear();         //   Set all pixels in RAM to 0 (off)
        digitalWrite(sun, HIGH);
        delay(timerDelay); // automate change to good value
        digitalWrite(sun, LOW);
      }
      // cas 2
      if (int(myObject["weather"]["id"]) == 801) {
        strip.clear();         //   Set all pixels in RAM to 0 (off)
        strip.setPixelColor(sun, strip.Color(255,   0,   0));        //  Set pixel's color (in RAM)
        strip.setPixelColor(cloud, strip.Color(255,   0,   0)); 
        strip.show();                          //  Update strip to match 
      }
      // cas 3
      if(int(myObject["weather"]["id"]) >= 802 && int(myObject["weather"]["id"]) <= 804 ){
        strip.clear();         //   Set all pixels in RAM to 0 (off)
        digitalWrite(cloud, HIGH);
        delay(timerDelay);
        digitalWrite(cloud, LOW);
      }
      // cas 4
      if(int(myObject["weather"]["id"]) >= 200 && int(myObject["weather"]["id"]) <= 321  && int(myObject["weather"]["id"]) >= 520 && int(myObject["weather"]["id"]) <= 531){
        strip.clear();         //   Set all pixels in RAM to 0 (off) 
        digitalWrite(cloud, HIGH);
        digitalWrite(rain, HIGH);
        delay(timerDelay);
        digitalWrite(cloud, LOW);
        digitalWrite(rain, LOW);
      }
      // cas 5
      if(int(myObject["weather"]["id"]) >= 600 && int(myObject["weather"]["id"]) <= 622 ){
        strip.clear();         //   Set all pixels in RAM to 0 (off)
        digitalWrite(cloud, HIGH);
        digitalWrite(snow, HIGH);
        delay(timerDelay);
        digitalWrite(cloud, LOW);
        digitalWrite(snow, LOW);
      }
      // cas 6
      if(int(myObject["weather"]["id"]) >= 500 && int(myObject["weather"]["id"]) <= 504 ){
        strip.clear();         // Set all pixels in RAM to 0 (off)
        digitalWrite(sun, HIGH);
        digitalWrite(cloud, HIGH);
        digitalWrite(rain, HIGH);
        delay(timerDelay);
        digitalWrite(sun, LOW);
        digitalWrite(cloud, LOW);
        digitalWrite(rain, LOW);
      }
      if (int(myObject["main"]["temp"])<0) { // change a to temperature
        Tcolor = strip.Color(0, 0, 255); // blue
      }
      if (int(myObject["main"]["temp"])>0 && int(myObject["main"]["temp"])<10) {
        Tcolor = strip.Color(0, 255, 255);
      }
      if (int(myObject["main"]["temp"])>10 && int(myObject["main"]["temp"]) <20) {
        Tcolor = strip.Color(0, 255, 50);
      }
      if (int(myObject["main"]["temp"])>20 && int(myObject["main"]["temp"]) <30) {
      Tcolor = strip.Color(255, 255, 0);
      }
      if (int(myObject["main"]["temp"]) >30 && int(myObject["main"]["temp"]) < 40) {
      Tcolor = strip.Color(255, 150, 50);
      }
      else if (int(myObject["main"]["temp"])>40){
        Tcolor = strip.Color(255, 0, 0);//red
      }
      strip.setPixelColor(wifi_led_statue,Tcolor);       // strip.Color(225, 25, 75) Set pixel's color (in RAM)
      strip.show();                          //  Update strip to match
    }
    else {
      Serial.println("WiFi Disconnected"); // find a way to show on the box wifi statut
      for (int count = 0; count < 3; count++) {
        digitalWrite(wifi_led_statue, HIGH);
        delay(250);
        digitalWrite(wifi_led_statue, LOW);
        delay(500);
      delay(500);
    }
    lastTime = millis();
  }
 }
 delay(20000);
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; // payload = find meaning
  
  if (httpResponseCode >= 200 && httpResponseCode<300 ) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode); // find a way to show type error on led. may be by a morse led pulsation
  }
  // Free resources
  http.end();
  return payload;
}
