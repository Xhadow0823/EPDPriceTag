#include "epd.h"
#include "UI.h"
#include <Arduino.h>


void __Background::draw() {
    const int x0 = 0, y0 = 0, x1 = 800-1, y1 = 600-1;
    epd_set_color(WHITE, WHITE);
    epd_fill_rect(x0, y0, x1, y1);
}

String __StatusBar::getPageStr() {
    if(this->ui->getItemList() != nullptr)
        return String(this->ui->getItemList()->getPage()) + '/' +String(this->ui->getItemList()->getMaxPage());
    return String();
}

void __StatusBar::draw() {
    const int x0 = 15, y0 = 520,
              w  = 775, h = 60;
    const unsigned char innerColor = WHITE, outlineColor = BLACK;
    epd_set_color(innerColor, WHITE);
    epd_fill_rect(x0, y0, x0+w, y0+h);
    epd_set_color(outlineColor, WHITE);
    epd_draw_rect(x0, y0, x0+w, y0+h);

    // show text
    const char* status = "STAND BY";
    epd_set_color(BLACK, WHITE);
    epd_set_en_font(ASCII48);
    epd_disp_string(status, 35, 525);
    epd_disp_string("PAGE 2/7", 240, 525);
    epd_disp_string("LAST SYNC:5H AGO", 435, 525);
}

inline __Item::__Item() {
    setItemListPtr(&ItemList);
}
inline void __Item::setChecked(bool isChecked) {
    this-> isChecked = isChecked;
}
inline void __Item::setSelected(bool isSelected) {
    this->isSelected = isSelected;
}
inline void __Item::setLongMode(bool isLongMode) {
    this->isLongMode = isLongMode;
}
inline void __Item::setItemListPtr(const __ItemList* i) {
    this->itemListPtr = i;
}
inline void __Item::draw(int order) {
    draw(order, "");
}
void __Item::draw(int order, const char* content) {
    const int x0 = this->itemListPtr->x0 + hMargin,
              y0 = this->itemListPtr->y0;
    const int itemMargin = (this->itemListPtr->h - maxCount*height)/(maxCount+1);
    const int y = y0 + (itemMargin+height)*order+itemMargin;

    // draw checkbox
    RoundRect.setColor(WHITE, BLACK);
    RoundRect.draw(x0, y, x0+height, y+height);
    //draw content box
    const int ccMargin = 15;
    RoundRect.setColor(WHITE, BLACK);
    RoundRect.draw(x0+height+ccMargin, y, (this->itemListPtr->w)+(this->itemListPtr->x0)-hMargin, y+height);
    // draw text
    if(strlen(content) != 0) {
        epd_set_color(BLACK, WHITE);
        epd_set_en_font(ASCII48);
        epd_disp_string(content, x0+height+ccMargin + 5, y + 5);  /////
    }
}
/**
 * @deprecated
*/
void __Item::draw(int x0, int y0, const char* content = "") {
    // draw checkbox
    RoundRect.setColor(WHITE, BLACK);
    RoundRect.draw(x0, y0, x0+height, y0+height);
    //draw content box
    const int ccMargin = 20; ////////////////
    RoundRect.setColor(WHITE, BLACK);
    RoundRect.draw(x0+height+ccMargin, y0, x0+height+ccMargin+shortWidth, y0+height);
    // draw text
    if(strlen(content) != 0) {
        epd_set_color(BLACK, WHITE);
        epd_set_en_font(ASCII48);
        epd_disp_string(content, x0+height+ccMargin + 5, y0 + 5);
    }
}



void __ItemList::draw() {
    const unsigned char innerColor = WHITE, outlineColor = BLACK;
    epd_set_color(innerColor, WHITE);
    epd_fill_rect(x0, y0, x0+w, y0+h);
    epd_set_color(outlineColor, WHITE);
    epd_draw_rect(x0, y0, x0+w, y0+h);

    for(int i = 0; i < 6; i++) {
        char buf[][64] = {
            {0xB3,0xD4,0xD6,0xF8,0xBB,0xF0,0xE5,0x81, 0x00},
            {0xC5,0xE3,0xD0,0xA1,0xB9,0xB7,0xC8,0xA5,0xB3,0xD4,0xEF,0x95,0xC1,0xCF, 0x00},
            {0xD9,0x49,0xB2,0xCB,0xD9,0x49,0xB2,0xCB,0xD9,0x49,0xB2,0xCB,0xD9,0x49,0xB2,0xCB,0xD9,0x49,0xB2,0xCB,0xD9,0x49,'.','.','.', 0x00},
            {0xB3,0xD4,0xD2,0xBB,0xD5,0xFB,0xCD,0xEB,0xB7,0xAC,0xC7,0xD1,0xE1,0x75, 0x00},
            "English",
            "HONK!#$%^&*(_[]>?<>~`~:\;+"
        };
        
        Item.draw(i, buf[i]);
    }
}

inline int __ItemList::getPage() { return page; }

inline int __ItemList::getMaxPage() { return maxPage; }

void __ButtonPanel::draw() {
    const int x0 = 720, y0 = 15, buttonWidth = 70, height = 495;
    const int nButtons = 4;

    const unsigned char innerColor = WHITE, outlineColor = BLACK;
    for(int i = 0; i < nButtons; i++) {
        epd_set_color(innerColor, WHITE);
        epd_fill_rect(x0, y0+((height-4*buttonWidth)/(nButtons-1)+buttonWidth)*i, x0+buttonWidth, y0+((height-4*buttonWidth)/(nButtons-1)+buttonWidth)*i + buttonWidth);
        epd_set_color(outlineColor, WHITE);
        epd_draw_rect(x0, y0+((height-4*buttonWidth)/(nButtons-1)+buttonWidth)*i, x0+buttonWidth, y0+((height-4*buttonWidth)/(nButtons-1)+buttonWidth)*i + buttonWidth);;
    }
}



__UI::__UI(__ItemList* i, __StatusBar* s, __ButtonPanel* p): itemList(i), statusBar(s), buttonPanel(p) { }

void __UI::draw() { }
inline __ItemList* __UI::getItemList() {
    return this->itemList;
}

__Background Background;
__ItemList ItemList;
__Item Item;
__StatusBar StatusBar;
__ButtonPanel ButtonPanel;
__UI UI = __UI(&ItemList, &StatusBar, &ButtonPanel);