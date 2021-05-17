#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

// wifi set up values
const String ssid = "SSID";
const String password = "PASSWORD";
// pin set up values
const int wifi_led_statue = 7; // to define pin number
const int sun = 6; // to define pin number
const int cloud = 5; // to define pin number
const int rain = 4; // to define pin number
const int snow = 3; // to define pin number

// differents configurations

//     | Sun | cloud | rain | snow | temperature | total weather id |
//  1  | X   |       |      |      |             |   ? to define    |
//  2  | X   |   X   |      |      |             |   ? to define    | 
//  3  |     |   X   |      |      |             |   ? to define    |
//  4  |     |   X   |  X   |      |             |   ? to define    |
//  5  |     |   X   |      |  X   |             |   ? to define    |
//  6  |     |   X   |  X   |  X   |             |   ? to define    |

// Your Domain name with URL path or IP address with path
String openWeatherMapApiKey = "bf7dcd4f6c9b368dae6cc55b5dbcdbafY"; //api key

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

  pinMode(wifi_led_statue, OUTPUT);
  pinMode(sun, OUTPUT);
  pinMode(cloud, OUTPUT);
  pinMode(rain, OUTPUT);
  pinMode(snow, OUTPUT);

  Serial.begin(9600); // nb bit/s to PC
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500); //3 blink each 2 times/s
      for (int count = 0; count < 3; count++) {
       digitalWrite(wifi_led_statue, HIGH);
       delay(500);
       digitalWrite(wifi_led_statue, LOW)
       delay(250);
  }; // change to a blue leds blink during time connection
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  for (int count = 0; count < 3; count++) {
       digitalWrite(wifi_led_statue, HIGH);
       delay(500);
       digitalWrite(wifi_led_statue, LOW);
       delay(250);
  }; // change to a triple red leds blink 
 
  //Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading
}

// the loop function runs over and over again forever
void loop() {
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;
      
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") { // find a way to show on the box fail statut
        Serial.println("Parsing input failed!"); // find a way to show on the box fail statut
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(myObject);
      Serial.print("Weather group: ");
      Serial.println(myObject["weather"]["main"]);
      if(myObject["weather"]["main"]=="Clouds") {
        digitalWrite(cloud, HIGH);
        delay(500);
        digitalWrite(cloud, LOW);};
      if(myObject["weather"]["main"]=="Clear") {
        digitalWrite(sun, HIGH);
        delay(500);
        digitalWrite(sun, LOW);};
      if(myObject["weather"]["main"]=="Rain") {
        digitalWrite(rain, HIGH);
        delay(500);
        digitalWrite(rain, LOW);};
      if(myObject["weather"]["main"]=="Snow") {
        digitalWrite(snow, HIGH);
        delay(500);
        digitalWrite(snow, LOW);};
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

String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  
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
