#include <IRControl.h>

enum Button { BTN_POWER, BTN_MUTE, BTN_VOL_UP, BTN_VOL_DOWN };

const IRMapping MAP[] = {
  {0x02, BTN_POWER,    "on/off"},
  {0x0F, BTN_MUTE,     "mute"},
  {0x07, BTN_VOL_UP,   "volume +"},
  {0x0B, BTN_VOL_DOWN, "volume -"},
};

IRControl ir;

void setup() {
  Serial.begin(115200);
  ir.begin(13, MAP, 0x7);   // pin, tabla, direccion del control

  ir.onPress([](uint8_t id, const char* name) {
    Serial.printf("Boton: %s\n", name);
    if (id == BTN_POWER) { /* ... */ }
    else if (id == BTN_MUTE) { /* ... */ }
    else if (id == BTN_VOL_UP) { /* ... */ }
    else if (id == BTN_VOL_DOWN) { /* ... */ }
  });
}

void loop() {
  ir.update();
}
