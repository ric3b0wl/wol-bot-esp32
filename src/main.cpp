#include <Arduino.h>

#include "WiFiMulti.h"
#include "WiFiClientSecure.h"
// #include "WiFiUDP.h"

#include "WakeOnLan.h"
#include "UniversalTelegramBot.h"
#include "ArduinoJson.h"

#include <FastLED.h>
#include "ledEffects.h"

// Telegram Bot Token
#define BOT_TOKEN  "6688245315:AAG_f9ELYV191u-wxyhxN7jC59shzq2lSdA"
#define ALLOWED_ID "416197915"

// WiFi configuration
#define WIFI_SSID "dd-wrt 10"
#define WIFI_PASS "3qs#73izv449"


// MAC addresses of the target devices
// const char* MAC_ADDR_1 = "18:c0:4d:35:4d:bd";
// const char* MAC_ADDR_2 = "cc:96:e5:0b:ab:01";
#define MAC_ADDR_1 "18:c0:4d:35:4d:bd"
#define MAC_ADDR_2 "cc:96:e5:0b:ab:01"


// Define the array of LEDs
CRGB leds[NUM_LEDS];

// WiFiMulti wifiMulti;
// WiFiClientSecure secured_client;
// WiFiUDP udpClient1, udpClient2; // Separate UDP clients for each WOL instance
WiFiMulti wifiMulti;
WiFiClientSecure secured_client;
WiFiUDP UDP;
WakeOnLan WOL(UDP);

// #define BOT_MTBS 1000 // mean time between scan messages
// UniversalTelegramBot bot(BOT_TOKEN, secured_client);
// unsigned long bot_lasttime = 0; // last time messages' scan has been done
const unsigned long BOT_MTBS = 1000; // mean time between scan messages
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done


void sendWOL(WiFiUDP &udpClient, const char *macAddress) {
  udpClient.beginPacket(IPAddress(255, 255, 255, 255), 9);
  for (int i = 0; i < 6; i++) {
    udpClient.write(0xFF);
  }
  for (int i = 0; i < 16; i++) {
    udpClient.write(macAddress[i]);
  }
  udpClient.endPacket();
  delay(300);
}

void handleNewMessages(int numNewMessages) {
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    Serial.println(bot.messages[i].from_id);
    if (bot.messages[i].from_id != ALLOWED_ID) continue;

    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/ping") {
      bot.sendMessage(chat_id, "pong", "");
    } 
    else if (text == "/start") {
      String welcome = "Welcome to **WoL Bot**, " + from_name + ".\n";
      welcome += "*Use is restricted to the bot owner.*\n\n";
      welcome += "Use /help for more commands\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
    else if (text == "/help") {
      String help = "Help Menu: \n";
      help += "/ping : Check the bot status\n";
      help += "/wol\\_3070 : Wakeup amd3070\n";
      help += "/wol\\_3090 : Wakeup intel3090\n";
      help += "/led\\_chase : Send LED Color Chase Effect\n";
      help += "/led\\_breath : Send LED Breathing Effect\n";
      help += "/led\\_knight : Send LED Knight Rider Effect\n";
      help += "/led\\_rainbow : Send LED Rainbow Effect\n";
      bot.sendMessage(chat_id, help, "Markdown");
    }
    else if (text == "/wol_3070") {
      // sendWOL(udpClient1, MAC_ADDR_1);
      WOL.sendMagicPacket(MAC_ADDR_1);
      wolActiveEffect();
      bot.sendMessage(chat_id, "Magic Packet sent to amd3070!", "");
    }
    else if (text == "/wol_3090") {
      // sendWOL(udpClient2, MAC_ADDR_2);
      WOL.sendMagicPacket(MAC_ADDR_2);
      wolActiveEffect();
      bot.sendMessage(chat_id, "Magic Packet sent to intel3090!", "");
    }
    else if (text == "/led_chase") {
      colorChaseEffect();
      bot.sendMessage(bot.messages[i].chat_id, "Starting LED Color Chase Effect!", "");
    }
    else if (text == "/led_breath") {
      breathingEffect();
      bot.sendMessage(bot.messages[i].chat_id, "Starting LED Breathing Effect!", "");
    }
    else if (text == "/led_knight") {
      knightRiderEffect();
      bot.sendMessage(bot.messages[i].chat_id, "Starting LED Knight Rider KITT Effect!", "");
    }
    else if (text == "/led_rainbow") {
      rainbowEffect();
      bot.sendMessage(bot.messages[i].chat_id, "Starting LED Rainbow Effect!", "");
    }
    else {
      bot.sendMessage(chat_id, "Invalid input, check /help!", "");
    }
  }
}

void setup() {
  wifiMulti.addAP(WIFI_SSID, WIFI_PASS);

  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting to WiFI...");

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("OK");

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS); // Initialize FastLED
  bootUpEffect();

  // ... NTP setup ...

  bot_lasttime = millis();
}

void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    if (numNewMessages > 0) {
      Serial.println("Response received");
      handleNewMessages(numNewMessages);
    }
    bot_lasttime = millis();
  }

}