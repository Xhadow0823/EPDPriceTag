// UI.h

#ifndef UI_H
#define UI_H

#include "epd.h"
#include <Arduino.h>

class __UI;

/**
 * all UI component should implement this abstract class
*/
class __Component {
    protected:
    public:
    /**
     * draw UI component on epd, but NOT include clear command and update command
    */
    virtual void draw() {}
};

class __Background: public __Component {
    public:
    /**
     * fill a white(default) color rect to cover whole epd
    */
    void draw();
};

class __StatusBar: public __Component {
    private:
    // Mode mode = Mode::SLEEPMODE;
    __UI* ui = nullptr;
    
    /**
     * get the string of page status
     * */
    String getPageStr();
    public:
    // enum Mode {
    //     SLEEPMODE, PAGEMODE, ITEMMODE
    // };
    // __StatusBar(__UI* ui): ui(ui) { }
    
    /**
     * draw the bar to show system status, page status, item status and sync status or something...
    */
    void draw();
};

class __ItemList;

class __Item {
    private:
    bool isChecked = false, isSelected = false, isLongMode = false;
    String content = String();
    __ItemList* itemListPtr = nullptr;

    int shortWidth = 570, longWidth = 625, height = 60, maxCount = 6, hMargin = 15;
    public:
    __Item();
    inline void setChecked(bool isChecked);
    inline void setSelected(bool isSelected);
    inline void setLongMode(bool isLongMode);
    inline void setItemListPtr(const __ItemList* i);
    void draw(int order);
    void draw(int order, const char* content);
    void draw(int x0, int y0, const char* content);
};

class __ItemList: public __Component {
    private:
    __UI* ui = nullptr;
    int page = 0;
    int maxPage = 0;

    const int x0 = 15, y0 = 15,
              w  = 695, h = 495;
    friend class __Item;
    public:
    /**
     * draw a page of to-do-list
    */
    void draw();
    /**
     * get the current page
    */
    inline int getPage();
    /**
     * get the max page number
    */
    inline int getMaxPage();
};

class __ButtonPanel: public __Component {
    private:
    // button mode, status, image file name ...
    public: 
    void draw();
};

/**
 * this component contains main information of UI
*/
class __UI: public __Component {
    private:
    __UI* ui = nullptr;
    __ItemList* itemList = nullptr;
    __StatusBar* statusBar = nullptr;
    __ButtonPanel* buttonPanel = nullptr;

    public:
    // __UI() {};
    __UI(__ItemList* i, __StatusBar* s, __ButtonPanel* p);
    /**
     * draw the whole UI
    */
    void draw();
    /** 
     * get the pointer of UI's ItemList
    */
    inline __ItemList* getItemList();
};

// 電子紙的UI物件
extern __UI UI;
// 繪製item小工具
extern __Item Item;
// 電子紙的代辦事項清單物件
extern __ItemList ItemList;
// 電子紙的狀態條物件
extern __StatusBar StatusBar;
// 電子紙的背景物件
extern __Background Background;
// 電子紙的側邊按鈕提示物件
extern __ButtonPanel ButtonPanel;



#endif