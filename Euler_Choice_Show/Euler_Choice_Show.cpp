// Euler_Choice_Show.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <graphics.h>

using namespace std;

#define BLOCK_WIDTH 70

#define START_X 80
#define START_Y 60

#define MAX_PER_LINE 10

#define TEXT_COLOR_UNCHOOSE     RGB(0, 0, 0)
#define BOADER_COLOR_UNCHOOSE   RGB(0, 0, 0)
#define TEXT_COLOR_CHOOSE       RGB(232, 16, 16)
#define BOADER_COLOR_CHOOSE     RGB(23, 213, 107)
#define TEXT_COLOR_CHOOSE_2     RGB(220, 220, 157)
#define BOADER_COLOR_CHOOSE_2   RGB(86, 153, 175)

#define DELAY_TIME 800

int textx = 850, texty = 100;

void printtext(LPCTSTR str) {
    if (texty >= 700) {
        setbkcolor(WHITE);
        clearrectangle(850, 0, 1200, 1000);
        texty = 100;
        textx = 850;
    }
    settextstyle(22, 0, _T("Consolas"));
    settextcolor(BLACK);
    setbkcolor(WHITE);
    outtextxy(textx, texty, str);
    texty += textheight(str) + 3;
}

void TextInRect(LPCTSTR str, int x, int y, int width, int height, bool horizontal = true, bool vertical = true) {
    LOGFONT font;
    gettextstyle(&font);
    int textHeight = font.lfHeight;
    int textWidth = textHeight;
    int strWidth = 0;
    int strNum = lstrlen(str);
    for (int i = 0; i < strNum; ++i)    strWidth += (str[i] > 127) ? textHeight : textHeight / 2;
    if (strWidth >= width || textHeight >= height) {
        outtextxy(x, y, str);
        return;
    }
    if (horizontal) x += (width - strWidth) / 2;
    if (vertical)   y += (height - textHeight) / 2;
    outtextxy(x, y, str);
}

class block {
public:
    int var = 0;
    int x = 0;
    int y = 0;
    int width = BLOCK_WIDTH;
    int isChoose = 0;
    int markTime = 0;
    void draw() {
        FlushBatchDraw();
        settextstyle(36, 0, _T("Consolas"));
        if (!isChoose) {
            setlinecolor(BOADER_COLOR_UNCHOOSE);
            settextcolor(TEXT_COLOR_UNCHOOSE);
            rectangle(this->x, this->y, this->x + BLOCK_WIDTH, this->y + BLOCK_WIDTH);
        }
        else if(isChoose == 1) {
            setbkcolor(BOADER_COLOR_CHOOSE);
            setfillcolor(BOADER_COLOR_CHOOSE);
            setlinecolor(BOADER_COLOR_CHOOSE);
            settextcolor(TEXT_COLOR_CHOOSE);
            fillrectangle(this->x, this->y, this->x + BLOCK_WIDTH, this->y + BLOCK_WIDTH);
        }
        else if (isChoose == 2) {
            setbkcolor(BOADER_COLOR_CHOOSE_2);
            setfillcolor(BOADER_COLOR_CHOOSE_2);
            setlinecolor(BOADER_COLOR_CHOOSE_2);
            settextcolor(TEXT_COLOR_CHOOSE_2);
            fillrectangle(this->x, this->y, this->x + BLOCK_WIDTH, this->y + BLOCK_WIDTH);
        }
        TextInRect(to_wstring(var).c_str(), x, y, BLOCK_WIDTH, BLOCK_WIDTH);
        setbkcolor(WHITE);
    }
};

block blocks[100];


int cnt;
int prime[50000], st[50000];
void Euler(int n) {
    cnt = 0;
    memset(prime, 0, sizeof(prime));
    memset(st, 0, sizeof(st));
    for (int i = 2; i <= n; ++i) {
        Sleep(DELAY_TIME);
        if (!st[i]) {
            wstring msg = _T("选择") + to_wstring(i) + _T("为质数");
            printtext(msg.c_str());
            prime[cnt++] = i;
            blocks[i - 2].isChoose = 1;
            blocks[i - 2].draw();
        }
        for (int j = 0; i * prime[j] <= n; ++j) {
            Sleep(DELAY_TIME);
            st[i * prime[j]] = 1;
            blocks[i * prime[j] - 2].markTime++;
            blocks[i * prime[j] - 2].isChoose = 2;
            blocks[i * prime[j] - 2].draw();
            wstring msg = to_wstring(i) +  _T(" × ") + to_wstring(prime[j]) + _T(" = ") + to_wstring(i * prime[j]);
            printtext(msg.c_str());
            msg = _T("标记") + to_wstring(i * prime[j]) + _T("，它现在被标记了") + to_wstring(blocks[i * prime[j] - 2].markTime) + _T("次");
            printtext(msg.c_str());
            if (i % prime[j] == 0) {
                msg = _T("而此时") + to_wstring(i) + _T(" % ") + to_wstring(prime[j]) + _T(" == 0，退出");
                printtext(msg.c_str());
                Sleep(DELAY_TIME);
                break;
            }
        }
    }
    printtext(_T("END"));
}

void init() {
    setbkcolor(WHITE);
    cleardevice();
    settextstyle(36, 0, _T("Consolas"));

    for (int i = 0; i < MAX_PER_LINE; i++) {
        for (int j = 0; j < MAX_PER_LINE; j++) {
            int nowid = i * MAX_PER_LINE + j;
            blocks[nowid].var = 2 + nowid;
            blocks[nowid].x = j * BLOCK_WIDTH + START_X;
            blocks[nowid].y = i * BLOCK_WIDTH + START_Y;
        }
    }

}
void drawCode() {
    for (auto e : blocks) {
        e.draw();
    }
}

int main() {
    initgraph(1500, 800);
    BeginBatchDraw();
    init();
    drawCode();
    Euler(101);
    EndBatchDraw();
    getchar();
    closegraph();
}
