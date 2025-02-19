#ifndef IOTMODULE_H
#define IOTMODULE_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <UniversalTelegramBot.h>
#include <FirebaseESP32.h>

class IoTModule {
private:
    String platform;
    String telegramToken;
    String telegramChatID;
    String firebaseHost;
    String firebaseAuth;
    WiFiClientSecure telegramClient;
    UniversalTelegramBot *bot;

public:
    IoTModule();
    void set_platform(String platform_name);
    void setTelegramToken(String token);
    void setTelegramChatID(String chatID);
    void sendTelegramMessage(String message);
    void setFirebaseConfig(String host, String auth);
    void sendFirebaseData(String path, String data);
    void startWebServer();
    void beginWiFi(const char* ssid, const char* password);
};

#endif
