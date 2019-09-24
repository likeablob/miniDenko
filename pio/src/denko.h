#ifndef INCLUDE_GUARD_DENKO_H
#define INCLUDE_GUARD_DENKO_H

#include <Chrono.h>
#include <LedControl.h>
#include <misakiUTF16.h>
#define NUM_DISP 4               // No. of displays
#define NUM_COLS NUM_DISP * 8    // No. of columns
#define BUFF_SIZE NUM_COLS * 255 // Buffer size

class DenkoMessage {
  public:
    String value;
    bool monospace;
    bool scroll;
    DenkoMessage(){};
    DenkoMessage(String value, bool monospace, bool scroll)
        : value(value), monospace(monospace), scroll(scroll){};
};

class Denko {
  private:
    LedControl &lc;
    uint8_t dispBuff[BUFF_SIZE];
    uint16_t buffUsedLength;
    uint16_t scrollPos;
    uint16_t refreshInterval;
    Chrono refreshTask;
    void rotate(uint8_t *in, uint8_t *out);
    uint8_t getLeftSpace(uint8_t *f);
    uint8_t getRightSpace(uint8_t *f);

  public:
    bool enableScroll;
    Denko(LedControl &lc);
    void begin();
    void draw(uint16_t offset = 0);
    void scroll();
    void clearBuff();
    void addStr(const char *str, uint16_t offset, bool isMonospace);
    void drawStr(const char *str, bool isMonospace = false);
    void drawStr(String str, bool isMonospace = false);
    void drawMsg(DenkoMessage msg);
    void setBrightness(uint8_t brightness);
    void setRefreshInterval(uint16_t interval);
    void handle();
};

#endif // INCLUDE_GUARD_DENKO_H