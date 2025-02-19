#include "IoTModule.h"

// Constructor
IoTModule::IoTModule() {
    platform = "";
    bot = nullptr;
}

// Set the platform
void IoTModule::set_platform(String platform_name) {
    platform = platform_name;
    if (platform == "Telegram") {
        Serial.println("Platform set to Telegram");
    } else if (platform == "Firebase") {
        Serial.println("Platform set to Firebase");
    } else if (platform == "WebServer") {
        Serial.println("Platform set to WebServer");
    } else {
        Serial.println("Unknown platform");
    }
}

// WiFi Connection
void IoTModule::beginWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");
}

// Telegram Functions
void IoTModule::setTelegramToken(String token) {
    telegramToken = token;
    bot = new UniversalTelegramBot(telegramToken, telegramClient);
}

void IoTModule::setTelegramChatID(String chatID) {
    telegramChatID = chatID;
}

void IoTModule::sendTelegramMessage(String message) {
    if (platform != "Telegram") {
        Serial.println("Error: Platform is not set to Telegram");
        return;
    }
    if (bot) {
        bot->sendMessage(telegramChatID, message, "");
    } else {
        Serial.println("Telegram Bot not initialized");
    }
}

// Firebase Functions
void IoTModule::setFirebaseConfig(String host, String auth) {
    firebaseHost = host;
    firebaseAuth = auth;
    Firebase.begin(firebaseHost, firebaseAuth);
}

void IoTModule::sendFirebaseData(String path, String data) {
    if (platform != "Firebase") {
        Serial.println("Error: Platform is not set to Firebase");
        return;
    }
    if (Firebase.setString(path, data)) {
        Serial.println("Firebase Data Sent Successfully");
    } else {
        Serial.println("Error Sending Data to Firebase");
    }
}

// WebServer Functions
void IoTModule::startWebServer() {
    if (platform != "WebServer") {
        Serial.println("Error: Platform is not set to WebServer");
        return;
    }
    HTTPClient http;
    http.begin("http://example.com"); // Ganti dengan URL server yang sesuai
    int httpCode = http.GET();
    if (httpCode > 0) {
        String payload = http.getString();
        Serial.println(payload);
    } else {
        Serial.println("Error connecting to server");
    }
    http.end();
}
