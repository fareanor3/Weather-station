//fareanor3 Update Code arduino.ino
//Latest commit 9d23874
//101 lines (83 sloc)  2.94 KB
  
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
// wifi set up values
const char* ssid = "SSID";
const char* password = "PASSWORD";
// pin set up values
const int wifi_led_statue = ; // to define pin number
const int sun = ; // to define pin number
const int cloud = ; // to define pin number
const int rain = ; // to define pin number
const int snow = ; // to define pin number

// differents configurations

//     | Sun | cloud | rain | snow | total weather id
// ---------------------------------------------------
//  1  | X   |       |      |      |   ? to define
//  2  | X   |   X   |      |      |   ? to define
//  3  |     |   X   |      |      |   ? to define
//  4  |     |   X   |  X   |      |   ? to define
//  5  |     |   X   |      |  X   |   ? to define
//  6  |     |   X   |  X   |  X   |   ? to define

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

  Serial.begin(115200); // what does it's mean
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500); // blink 2 times/s
    Serial.print("."); // change to a blue leds blink during time connection
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: "); // change to a triple red blink of all the leds
 
  //Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading
}

// the loop function runs over and over again forever
void loop() {
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) { // millis meaning ?
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
      Serial.print("Temperature: ");
      Serial.println(myObject["main"]["temp"]);
      Serial.print("Pressure: ");
      Serial.println(myObject["main"]["pressure"]);
      Serial.print("Humidity: ");
      Serial.println(myObject["main"]["humidity"]);
      Serial.print("Wind Speed: ");
      Serial.println(myObject["wind"]["speed"]);
    }
    else {
      Serial.println("WiFi Disconnected"); // find a way to show on the box wifi statut
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
  
  if (httpResponseCode>0) {
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
