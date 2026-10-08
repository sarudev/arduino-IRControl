#include <IRControl.h>

const IRMapping MAP[] = { {0, 0, ""} };   // tabla vacia
IRControl ir;

void setup() {
  Serial.begin(115200);
  ir.begin(13, MAP);   // sin direccion = acepta cualquier control

  ir.onUnknown([](uint16_t address, uint16_t command) {
    Serial.printf("address: 0x%X  command: 0x%X\n", address, command);
  });
}

void loop() {
  ir.update();
}
