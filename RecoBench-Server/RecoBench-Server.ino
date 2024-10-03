#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0xe8, 0x6b, 0xea, 0xcf, 0xf9, 0x70};

typedef struct data_struct {
  float t;
  float sine;
  float cosine;
} data_struct;

data_struct data;

esp_now_peer_info_t peerInfo;
 
void setup() { 
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    // Error initializing ESP-NOW
    return;
  }
     
  // register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    // Failed to add peer
    return;
  }
}

float counter = 0;
void loop() {
  data.t = counter;
  data.sine = sinf(counter);
  data.cosine = cosf(counter);
  counter+=0.1;
 
  esp_err_t result = esp_now_send(0, (uint8_t *) &data, sizeof(data_struct));
  
  /*
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  */
  delay(50);
}