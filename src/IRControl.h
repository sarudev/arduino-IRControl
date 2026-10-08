#ifndef IR_CONTROL_H
#define IR_CONTROL_H

#include <Arduino.h>

#define IR_ANY_ADDRESS 0xFFFF

struct IRMapping {
  uint16_t    command;
  uint8_t     id;
  const char* name;
};

#if defined(ESP32) || defined(ESP8266)
  #include <functional>
  typedef std::function<void(uint8_t, const char*)>     IRButtonCallback;
  typedef std::function<void(uint16_t, uint16_t)>       IRUnknownCallback;
#else
  typedef void (*IRButtonCallback)(uint8_t, const char*);
  typedef void (*IRUnknownCallback)(uint16_t, uint16_t);
#endif

class IRControl {
  public:
    template <size_t N>
    void begin(uint8_t pin, const IRMapping (&map)[N],
               uint16_t address = IR_ANY_ADDRESS, uint16_t holdDelayMs = 800) {
      setMapping(map, N);
      _address   = address;
      _holdDelay = holdDelayMs;
      startReceiver(pin);
    }

    void setMapping(const IRMapping* map, size_t count) {
      _map = map;
      _mapSize = count;
    }

    void setAddress(uint16_t address) { _address = address; }
    void setHoldDelay(uint16_t ms)    { _holdDelay = ms; }

    void onPress(IRButtonCallback cb)     { _onPress = cb; }
    void onHold(IRButtonCallback cb)      { _onHold = cb; }
    void onUnknown(IRUnknownCallback cb)  { _onUnknown = cb; }

    void update();

  private:
    void startReceiver(uint8_t pin);
    const IRMapping* find(uint16_t command) const;

    const IRMapping* _map = nullptr;
    size_t _mapSize = 0;

    IRButtonCallback  _onPress;
    IRButtonCallback  _onHold;
    IRUnknownCallback _onUnknown;

    uint16_t _address   = IR_ANY_ADDRESS;
    uint16_t _holdDelay = 800;

    const IRMapping* _last = nullptr;
    uint32_t _pressStart = 0;
};

#endif
