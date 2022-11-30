#include <SPI.h>
#include <Ethernet2.h>
#define PIN_PHOTO_SENSOR A1

byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};
EthernetClient client;
EthernetServer server(80);
IPAddress ip(192, 168, 31, 131);

int raw = 0;
float temp = 0;
int rainPin = 0;
int sensorValuePercent = 0;

void setup() {
  Serial.begin(9600);
  pinMode( A0, INPUT );
  Ethernet.begin(mac, ip);
  pinMode(A2, INPUT);
  server.begin();
}


void loop() {
  EthernetClient client = server.available();
  raw = analogRead(A0);
  temp = (1.1 * raw * 100.0) / 1024;
  int valLamp = 1023 - analogRead(PIN_PHOTO_SENSOR);
  rainPin = analogRead(A2);
  sensorValuePercent = map(rainPin, 0, 1023, 100, 0);

  if (client) {
    Serial.println("new client");
    boolean ok = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n' && ok) {

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5");  // время обновления страницы
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><meta charset='UTF-8'>");

          client.println("<h1>Температура: ");
          client.println(temp);
          client.println(" &#176;C</h1>");

          client.println("<h1>Освещенность: ");
          client.println(valLamp);
          client.println("лк</h1>");

          client.println("<h1>Влажность: ");
          client.println(sensorValuePercent);
          client.println("%</h1>");

          client.println("</html>");

          break;
        }
        if (c == '\n') {
          ok = true;
        } else if (c != '\r') {
          ok = false;
        }
      }
    }

    delay(5000);
    client.stop();
    Serial.println("client disconnected");
  }
}