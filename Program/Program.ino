#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6KUFzIoeC"
#define BLYNK_TEMPLATE_NAME "Monitoring Lingkungan Tumbuhan"
#define BLYNK_AUTH_TOKEN "GTjxn6w6ZuqE2bdR1vpP3x3P_Y8O8-vh"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

const char* ssid = "Nama Wifi";
const char* password = "Pass Wifi";
#define pinKelTanah 2
#define pinPhTanah 4
#define DHTPIN 5
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void kelTanah(){
  int nilaiKelembabanTanah = analogRead(pinKelTanah);
  int persentaseKelembaban = map(nilaiKelembabanTanah, 0, 4095, 0, 100);

  Serial.print("Kelembaban Tanah: ");
  Serial.print(persentaseKelembaban);
  Serial.println("%");
  Blynk.virtualWrite(V0, persentaseKelembaban);
}

void phTanah(){
  int bacasensor = analogRead(pinPhTanah);
  //rumus didapat berdasarkan datasheet 
  float phtanah = (-0.0139*bacasensor)+7.7851;
  Serial.print("PH Tanah: ");
  Serial.println(phtanah);
  Blynk.virtualWrite(V1, phtanah);
}

void Dht(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT");
    return;
  }
  Serial.print("Kelembaban: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.println("°C");
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  dht.begin();

}

void loop() {
  Blynk.run();
  kelTanah();
  phTanah();
  Dht();
}
