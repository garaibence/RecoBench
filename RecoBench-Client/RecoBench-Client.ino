#include <esp_now.h>
#include <WiFi.h>

// Must match the sender structure
typedef struct data_struct {
  float t;
  float sine;
  float cosine;
} data_struct;

// Create a struct_message called myData
data_struct myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Time: " + (String)myData.t + ",");
  Serial.print("Sine: " + (String)myData.sine + ",");
  Serial.print("Cosine: " + (String)myData.cosine + ",");
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
 
void loop() {

}