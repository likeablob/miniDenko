#include "denko.h"

Denko::Denko(LedControl &lc) : lc(lc), enableScroll(true) {}

void Denko::begin() {
    for(int i = 0; i < NUM_DISP; i++) {
        lc.shutdown(i, false);
        lc.setIntensity(i, 10);
        lc.clearDisplay(i);
    }
}

void Denko::handle() {
    if(refreshTask.hasPassed(refreshInterval) && enableScroll) {
        refreshTask.restart();
        scroll();
    }
}

void Denko::setRefreshInterval(uint16_t interval) {
    refreshInterval = interval;
    refreshTask.restart();
}

void Denko::draw(uint16_t offset) {
    for(int i = 0; i < NUM_COLS; i++) { // loop for columns
        int disp = i / 8;               // index of the display
        int col = 7 - i % 8;            // index of the coulmn(reversed)
        int buffIdx = i + offset;
        if(buffUsedLength < NUM_COLS) {
            buffIdx %= (NUM_COLS + 8);
        } else if((buffUsedLength + 8) < BUFF_SIZE) {
            buffIdx %= (buffUsedLength + 8);
        } else {
            buffIdx %= BUFF_SIZE;
        }
        buffIdx = buffIdx < 0 ? BUFF_SIZE + buffIdx : buffIdx;
        lc.setColumn(disp, col, dispBuff[buffIdx]); // set data for the column
    }
}

void Denko::scroll() { draw(scrollPos++); }

void Denko::clearBuff() { memset(dispBuff, 0, BUFF_SIZE); }

void Denko::rotate(uint8_t *in, uint8_t *out) {
    for(int i = 0; i < 8; i++) {
        uint8_t tmp = 0;
        for(int j = 0; j < 8; j++) {
            tmp |= ((in[j] >> (7 - i)) & 1) << j;
        }
        out[i] = tmp;
    }
}

uint8_t Denko::getLeftSpace(uint8_t *fontData) {
    uint8_t count = 0;
    for(size_t i = 0; i < 8; i++) {
        if(fontData[i]) {
            break;
        }
        count++;
    }
    return count;
}

uint8_t Denko::getRightSpace(uint8_t *fontData) {
    uint8_t count = 0;
    for(size_t i = 7; i > 0; i--) {
        if(fontData[i]) {
            break;
        }
        count++;
    }
    return count;
}

void Denko::addStr(const char *str, uint16_t offset, bool isMonospace) {
    uint8_t fontData[8];
    uint8_t fontDataRotated[8] = {0};
    uint16_t pos = offset;
    while(true) {
        str = getFontData(fontData, str, !false, NULL);
        if(str == NULL)
            break;
        rotate(fontData, fontDataRotated);
        uint8_t charWidth = 8;
        uint8_t leftSpace = 0;
        if(!isMonospace) {
            leftSpace = getLeftSpace(fontDataRotated);
            uint8_t rightSpace = getRightSpace(fontDataRotated);
            leftSpace = leftSpace > 0 ? leftSpace - 1 : leftSpace;
            rightSpace = rightSpace > 0 ? rightSpace - 1 : rightSpace;
            charWidth = 8 - leftSpace - rightSpace;
            if(leftSpace >= 7) { // for " "
                leftSpace = 0;
                charWidth = 4;
            }
        }
        if((pos + charWidth) >= BUFF_SIZE)
            break;
        memcpy(dispBuff + pos, fontDataRotated + leftSpace, charWidth);
        pos += charWidth;
    }
    buffUsedLength = pos;
};

void Denko::drawStr(const char *str, bool isMonospace) {
    clearBuff();
    addStr(str, 0, isMonospace);
    scrollPos = 0;
    draw(0);
};

void Denko::drawStr(String str, bool isMonospace) {
    clearBuff();
    addStr(str.c_str(), 0, isMonospace);
    scrollPos = 0;
    draw(0);
};

void Denko::drawMsg(DenkoMessage msg) {
    drawStr(msg.value, msg.monospace);
    enableScroll = msg.scroll;
};

void Denko::setBrightness(uint8_t brightness) {
    if(brightness) {
        for(size_t j = 0; j < NUM_DISP; j++) {
            lc.shutdown(j, false);
            lc.setIntensity(j, brightness % 17 - 1);
        }
    } else {
        for(size_t j = 0; j < NUM_DISP; j++) {
            lc.shutdown(j, true);
        }
    }
};
