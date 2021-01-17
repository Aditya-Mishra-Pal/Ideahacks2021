/*
  Project help from: https://RandomNerdTutorials.com/esp32-http-get-open-weather-map-thingspeak-arduino/ courtesy of Rui Santos
  His parts are getting the json file from weather map API
*/

#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#endif

#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>
#include <Arduino_JSON.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Adafruit_Sensor.h>
//#include <DHT.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>
#include "ESP32_MailClient.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* serverNameThingspeak = "http://api.thingspeak.com/update";
String apiKey = "SIGKEDTCZRD4RW9H";


const char* ssid = "yaten";
const char* password = "9165433476";
const int ledPin = 26;
//Your Domain name with URL path or IP address with path
const char* serverName = "http://10.0.0.6/esp-post-data.php";
String openWeatherMapApiKey = "54e1767413527964af2fd5af043b2436";


// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /esp-post-data.php also needs to have the same key
String apiKeyValue = "tPmAT5Ab3j7F9";
String sensorName = "Soil Moisture";
String sensorLocation = "Lincoln CA";
int sensor_pin = 34;
int value ;

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME280 bme;  // I2C
//Adafruit_BME280 bme(BME_CS);  // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);  // software SPI

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 30 seconds (30000)
unsigned long timerDelay = 10000;
String jsonBuffer;
SMTPData data;
/*
String sendEmail(char *subject, char *sender, char *body, char *recipient, boolean htmlFormat) {
  data.setLogin(GMAIL_SMTP_SEVER, GMAIL_SMTP_PORT, GMAIL_SMTP_USERNAME, GMAIL_SMTP_PASSWORD);
  data.setSender(sender, GMAIL_SMTP_USERNAME);
  data.setSubject(subject);
  data.setMessage(body, htmlFormat);
  data.addRecipient(recipient);
  if (!MailClient.sendMail(data)) 
    return MailClient.smtpErrorReason();
  
  return "";
}
*/

void setup() {
  pinMode (ledPin, OUTPUT);
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  /*
  // (you can also pass in a Wire library object like &Wire2)
  bool status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring or change I2C address!");
    while (1);
  }
  
  Serial.println("Timer set to 30 seconds (timerDelay variable), it will take 30 seconds before publishing the first reading.");
  */
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?id=5366375&appid=54e1767413527964af2fd5af043b2436";
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      value= analogRead(sensor_pin);
      value = map(value,0,3200,0,100);

      if(value < 30) {
        digitalWrite (ledPin, HIGH);
      } else  {
        digitalWrite (ledPin, LOW);
      }
      
      String value_str = String(value);

      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String temperature = JSON.stringify(myObject["main"]["temp"]);
      float tempFahr = temperature.toFloat();
      tempFahr = tempFahr - 273.15;
      tempFahr = (tempFahr*(9.0/5.0)) + 32;
      temperature = String(tempFahr);
      /*
      if (tempFahr < 50.0) {
        sprintf(body, "<h2>Too Cold, Protect Plants</h2><br/><p><b>Temperature (°C)</b>: <font color='red'>%.2f</font></p><br/><p><b>Humidity (%)</b>: <font color='blue'>%.2f</font></p>", temperature, JSON.stringify(myObject["main"]["humidity"]));
        String result = sendEmail("Sensor data", "ESP32", body, "gtemp962@gmail.com", true);
      }
      */

        // display temperature
      display.setTextSize(1);
      display.setCursor(0,0);
      display.print("Temperature: ");
      display.setTextSize(2);
      display.setCursor(0,10);
      display.print(tempFahr);
      display.print(" ");
      display.setTextSize(1);
      display.cp437(true);
      display.write(167);
      display.setTextSize(2);
      display.print("F");
      
      // display humidity
      display.setTextSize(1);
      display.setCursor(0, 35);
      display.print("Humidity: ");
      display.setTextSize(2);
      display.setCursor(0, 45);
      display.print(JSON.stringify(myObject["main"]["humidity"]));
      display.print(" %"); 
      
      display.display(); 
      
      Serial.print("tempFahr");
      Serial.println(tempFahr);
      
      // Prepare your HTTP POST request data
      String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                            + "&location=" + sensorLocation + "&value1=" + temperature
                            + "&value2=" + JSON.stringify(myObject["main"]["humidity"]) 
                            + "&value3=" + JSON.stringify(myObject["main"]["pressure"]) +
                            "&value4=" + value_str + "&value5=" + JSON.stringify(myObject["wind"]["speed"]) + "";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);

      // You can comment the httpRequestData variable above
      // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
      //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");

      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");

      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
      http.begin(serverNameThingspeak);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      httpRequestData = "api_key=" + apiKey + "&field1=" + temperature; 
      httpResponseCode = http.POST(httpRequestData);
      http.end();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.println("WiFi Disconnected");
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
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
