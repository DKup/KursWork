#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
 
const char* ssid = "HUAWEI P40 lite";
const char* password = "a2f0d59e3268";
 
#define BOTtoken "2102346058:AAEQ1oDptbon1eoUXfsllU69DTSjeaq4KUk"  // токен бота
#define CHAT_ID "339204795"
 
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
 
const int motionSensor = 27; //датчик движения
bool motionDetected = false;
 
// Действие при срабатывании датчика движения
void IRAM_ATTR detectsMovement() {
  motionDetected = true;
}
 
void setup() {
  Serial.begin(115200);
  
 

  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
 

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  bot.sendMessage(CHAT_ID, "Bot started up", "");
}
 
void loop() {
  if(motionDetected){
    bot.sendMessage(CHAT_ID, "Motion detected!!", "");
    Serial.println("Motion Detected");
    motionDetected = false;
  }
}
