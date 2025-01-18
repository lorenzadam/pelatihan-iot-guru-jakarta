#include <WiFi.h>
#include <MQTT.h>

// Nama WiFi dan password nya
const char ssid[] = "Wokwi-GUEST";
const char pass[] = "";

// Object untuk terhubung ke MQTT dan ke WiFi
WiFiClient net;
MQTTClient client;

void connect(){
  rgb(1,0,0);         // LED Merah menyala (belum terhubung ke WiFi)
  while(WiFi.status() != WL_CONNECTED){     // Mengecek apakah sudah terhubung ke WiFi atau belum
    delay(500);
  }
  rgb(0,1,0);   // LED Hijau menyala (berhasil terhubung ke WiFi)

  while(!client.connect("eurghsleutkg9348")){ // ClientID harus berbeda satu sama lain
    delay(500);
  }
  rgb(0,0,1); // LED Biru menyala (berhasil terhubung ke MQTT Broker / server)

  client.subscribe("smarthome/#");  // lakukan subscribe ke topic "smarthome/#"
}

void subscribe(String &topic, String &data){
  if(topic == "smarthome/garasi"){
    if(data == "on"){
      digitalWrite(14, 1);
    } else {
      digitalWrite(14, 0);
    }
  }
}

void setup() {
  // Memberi tahu ESP32 pin yang digunakan sebagai output
  pinMode(14, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);

  WiFi.begin(ssid, pass);   // Memulai penggunaan WiFi
  client.begin("broker.emqx.io", net); // Memulai penggunaan MQTT

  client.onMessage(subscribe);    // Memberi tahu jika ada data yang masuk maka function dengan nama subscribe akan dieksekusi

  connect();  // Panggil function bernama void connect()
}

void loop() {
  client.loop();  // Untuk mengecek secara berkala data yang masuk
  delay(10);
}

void rgb(bool red, bool green, bool blue){
  digitalWrite(27, red);
  digitalWrite(26, green);
  digitalWrite(25, blue);
}