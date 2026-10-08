#include "IRControl.h"
#include <IRremote.hpp>

void IRControl::startReceiver(uint8_t pin) {
  IrReceiver.begin(pin, DISABLE_LED_FEEDBACK);
}

const IRMapping* IRControl::find(uint16_t command) const {
  for (size_t i = 0; i < _mapSize; i++) {
    if (_map[i].command == command) return &_map[i];
  }
  return nullptr;
}

void IRControl::update() {
  if (!IrReceiver.decode()) return;

  IRData &d = IrReceiver.decodedIRData;

  if (d.flags & IRDATA_FLAGS_WAS_OVERFLOW || d.protocol == UNKNOWN) {
    // señal invalida
  } else if (_address != IR_ANY_ADDRESS && d.address != _address) {
    // otro control
  } else if (d.flags & IRDATA_FLAGS_IS_REPEAT) {
    if (_last && millis() - _pressStart >= _holdDelay) {
      if (_onHold) _onHold(_last->id, _last->name);
    }
  } else {
    _last = find(d.command);
    _pressStart = millis();

    if (_last) {
      if (_onPress) _onPress(_last->id, _last->name);
    } else {
      if (_onUnknown) _onUnknown(d.address, d.command);
    }
  }

  IrReceiver.resume();
}
