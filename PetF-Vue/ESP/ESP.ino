#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include <Servo.h>  


const char* ssid = "Yan";
const char* password = "CDV0208@";


ESP8266WebServer server(80);


const int servoPin = D1;
Servo feederServo;


const int irPin = D2;


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 8 * 3600, 60000); 



int dayHour = 9, dayMinute = 0;
int nightHour = 18, nightMinute = 0;


bool triggered = false;
unsigned long triggerTime = 0;
int lastMinute = -1;  

// Firebase database URL
const char* firebaseHost = "https://petfeeder-8cf87-default-rtdb.asia-southeast1.firebasedatabase.app/logs.json";


const char* monthNames[] = {
  "Jan","Feb","Mar","Apr","May","Jun",
  "Jul","Aug","Sep","Oct","Nov","Dec"
};


String getTimestamp() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  time_t rawTime = (time_t)epochTime;
  struct tm *ptm = localtime(&rawTime);

  int year   = ptm->tm_year + 1900;
  int month  = ptm->tm_mon; 
  int day    = ptm->tm_mday;
  int hour   = ptm->tm_hour;
  int minute = ptm->tm_min;

  char buf[40];

  sprintf(buf, "%s-%02d-%04d %02d:%02d",
          monthNames[month], day, year, hour, minute);
  return String(buf);
}


void sendLog(const String& event) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();   
    HTTPClient http;
    http.begin(client, firebaseHost);   
    http.addHeader("Content-Type", "application/json");

    String timestamp = getTimestamp();
    String json = "{\"timestamp\":\"" + timestamp + "\",\"event\":\"" + event + "\"}";
    int httpResponseCode = http.POST(json);

    if (httpResponseCode > 0) {
      Serial.printf("Log sent: %s\n", json.c_str());
      Serial.printf("Response code: %d\n", httpResponseCode);
      String payload = http.getString();
      Serial.println("Firebase response: " + payload);
    } else {
      Serial.printf("Error sending log: %d\n", httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi not connected, cannot send log");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(irPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());


  timeClient.begin();

  
  feederServo.attach(servoPin);
  feederServo.write(0);  


  server.on("/servo/feed", []() {
    feederServo.write(180);  
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "Food Served (Manual)");
    Serial.println("Food Served (Manual)");

    sendLog("Food Served (Manual)");

    triggerTime = millis();
    triggered = true;
  });


  server.on("/servo/reset", []() {
    feederServo.write(0);   // return to 0°
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "Servo reset to 0°");
    Serial.println("Servo reset manually");
    triggered = false;
  });

 
  server.on("/setSchedule", []() {
    if (server.hasArg("dayHour")) dayHour = server.arg("dayHour").toInt();
    if (server.hasArg("dayMinute")) dayMinute = server.arg("dayMinute").toInt();
    if (server.hasArg("nightHour")) nightHour = server.arg("nightHour").toInt();
    if (server.hasArg("nightMinute")) nightMinute = server.arg("nightMinute").toInt();

    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "Schedule updated!");
    Serial.printf("Day schedule: %02d:%02d\n", dayHour, dayMinute);
    Serial.printf("Night schedule: %02d:%02d\n", nightHour, nightMinute);
  });


  server.on("/getSchedule", []() {
    String json = "{";
    json += "\"dayHour\":" + String(dayHour) + ",";
    json += "\"dayMinute\":" + String(dayMinute) + ",";
    json += "\"nightHour\":" + String(nightHour) + ",";
    json += "\"nightMinute\":" + String(nightMinute);
    json += "}";

    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", json);
    Serial.println("Schedule requested via /getSchedule");
  });

 
  server.on("/irStatus", []() {
    int irValue = digitalRead(irPin);
    String status = (irValue == HIGH) ? "detected" : "none";
    String json = "{\"status\":\"" + status + "\"}";

    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", json);
    Serial.printf("IR sensor status: %s\n", status.c_str());
  });

  
  server.on("/", []() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "ESP8266 is running!");
  });

  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  timeClient.update();

  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();

  
  bool isScheduledTime =
    (currentHour == dayHour && currentMinute == dayMinute) ||
    (currentHour == nightHour && currentMinute == nightMinute);

  if (isScheduledTime && !triggered && currentMinute != lastMinute) {
    feederServo.write(180);   
    triggerTime = millis();
    triggered = true;
    lastMinute = currentMinute;  
    Serial.println("Food Served (Scheduled)");
    sendLog("Food Served (Scheduled)");
  }

 
  if (triggered && millis() - triggerTime >= 50) {
    feederServo.write(0);   
    Serial.println("Servo returned to 0° after 3 sec");
    triggered = false;
  }
}
