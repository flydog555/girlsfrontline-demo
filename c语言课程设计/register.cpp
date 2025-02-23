#define _CRT_SECURE_NO_WARNINGS 1

#undef UNICODE
#undef _UNICODE

#include <graphics.h>
#include <easyx.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <windows.h>  
#include <wingdi.h>  


using namespace std;

extern void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
extern void home();
extern void login();
int sign1;


//按钮
class Button
{
private:
    int x;
    int y;
    int width;
    int height;
    float scale;
    bool isMouseOver;
    string text;
    function<void()> onClick;

public:
    Button(int x, int y, int width, int height, const string& text, const function<void()>& onClick)
        : x(x), y(y), width(width), height(height), text(text), onClick(onClick), scale(1.0f), isMouseOver(false)
    {
    }

    void checkMouseOver(int mouseX, int mouseY)
    {
        isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

        if (isMouseOver) {
            scale = 0.9f;
        }
        else {
            scale = 1.0f;
        }
    }

    bool checkClick(int mouseX, int mouseY)
    {
        if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
        {
            onClick();
            isMouseOver = false;
            scale = 1.0f;
            return true;
        }
        return false;
    }

    void draw()
    {
        int scaledWidth = width * scale;
        int scaledHeight = height * scale;
        int scaledX = x + (width - scaledWidth) / 2;
        int scaledY = y + (height - scaledHeight) / 2;

        if (isMouseOver)
        {
            setlinecolor(RGB(0, 120, 215));
            setfillcolor(RGB(229, 241, 251));

        }
        else
        {
            setlinecolor(RGB(173, 173, 173));
            setfillcolor(RGB(225, 225, 225));
        }

        fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight);
        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(20 * scale, 0, _T("微软雅黑"));
        int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2;
        int textY = scaledY + (scaledHeight - textheight(_T("微软雅黑"))) / 2;
        outtextxy(textX, textY, text.c_str());
    }
};

//文字输入框
class TextBox
{
private:
    int x;
    int y;
    int width;
    int height;
    int maxWord;    //最长单词个数
    string text;   //文本
    bool isSelected;    //是否被选中
    bool showCursor;    //是否显示光标
    int cursorPos;      //光标位置

public:
    TextBox(int x, int y, int width, int height, int maxWord)
        : x(x), y(y), width(width), height(height), maxWord(maxWord), isSelected(false), showCursor(false), cursorPos(0)
    {
    }

    const string& getText() const
    {
        return text;
    }

    bool getSelect() const
    {
        return isSelected;
    }

    bool isEmpty() const
    {
        return text.empty();
    }

    void clear()
    {
        text = "";
    }

    void setText(const string& newText)
    {
        text = newText;
        cursorPos = text.length();
    }

    void draw()
    {
        setfillcolor(WHITE);
        if (isSelected)
        {
            setlinecolor(RGB(0, 120, 215));
            fillrectangle(x, y, x + width, y + height);
        }
        else
        {
            setlinecolor(RGB(122, 122, 122));
            fillrectangle(x, y, x + width, y + height);
        }

        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(height * 3 / 4, 0, _T("微软雅黑"));

        outtextxy(x + 5, y + (height - textheight(_T("微软雅黑"))) / 2, text.c_str());

        setlinecolor(BLACK);
        if (isSelected && showCursor)
        {
            int cursorX = x + 5 + textwidth(text.substr(0, cursorPos).c_str());
            line(cursorX, y + 2 + height / 8, cursorX, y + height * 7 / 8 - 2);
        }
    }

    bool checkClick(int mouseX, int mouseY)
    {
        if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
        {
            isSelected = true;
            return true;
        }
        else
        {
            isSelected = false;
            cursorPos = text.length();
            return false;
        }
    }

    void keyInput(wchar_t ch)
    {
        if (isSelected)
        {
            switch (ch)
            {
            case '\b':				// 用户按退格键，删掉一个字符
                if (!text.empty() && cursorPos > 0)
                {
                    text.erase(cursorPos - 1, 1);
                    cursorPos--;
                }
                break;
            case '\r':
            case '\n':
                cursorPos = text.length();
                isSelected = false;
                break;
            default:				// 用户按其它键，接受文本输入
                if (text.length() < maxWord)
                {
                    text.insert(cursorPos, 1, ch);
                    cursorPos++;
                }
            }
        }
    }

    void updateCursor()
    {
        static DWORD lastTick = GetTickCount();
        DWORD currentTick = GetTickCount();
        if (currentTick - lastTick >= 500) // 每500毫秒切换光标状态
        {
            showCursor = !showCursor;
            lastTick = currentTick;
        }
    }
};

//背景
class Widget
{
private:
    int width;
    int height;
    int currentIndex;
    vector<IMAGE*> pages;
    vector<vector<Button*>> buttons;
    vector<vector<TextBox*>>textBoxs;

    void addPage(IMAGE* page)
    {
        pages.push_back(page);
        buttons.push_back({});
        textBoxs.push_back({});
    }

    void addButton(int index, Button* button)
    {
        if (index >= 0 && index < buttons.size())
        {
            buttons[index].push_back(button);
        }
    }

    void addTextBox(int index, TextBox* textBox)
    {
        if (index >= 0 && index < textBoxs.size())
        {
            textBoxs[index].push_back(textBox);
        }
    }

    void setCurrentIndex(int index)
    {
        if (index >= 0 && index < pages.size())
        {
            currentIndex = index;
        }
    }

    void mouseClick(int mouseX, int mouseY)
    {
        if (currentIndex >= 0 && currentIndex < buttons.size())
        {
            for (Button* button : buttons[currentIndex])
            {
                if (button->checkClick(mouseX, mouseY))
                {
                    break;
                }
            }
        }
        if (currentIndex >= 0 && currentIndex < textBoxs.size())
        {
            for (auto textbox : textBoxs[currentIndex])
            {
                textbox->checkClick(mouseX, mouseY);
            }
        }
    }

    void mouseMove(int mouseX, int mouseY)
    {

        if (currentIndex >= 0 && currentIndex < buttons.size())
        {
            for (Button* button : buttons[currentIndex])
            {
                button->checkMouseOver(mouseX, mouseY);
            }
        }
    }

    void keyInput(wchar_t ch)
    {
        if (currentIndex >= 0 && currentIndex < textBoxs.size())
        {
            for (auto textbox : textBoxs[currentIndex])
            {
                if (textbox->getSelect())
                {
                    textbox->keyInput(ch);
                }
            }
        }
    }

    void draw()
    {
        if (currentIndex >= 0 && currentIndex < pages.size())
        {
            putimage(0, 0, pages[currentIndex]);

            if (currentIndex >= 0 && currentIndex < buttons.size())
            {
                for (Button* button : buttons[currentIndex])
                {
                    button->draw();
                }
            }

            if (currentIndex >= 0 && currentIndex < textBoxs.size())
            {
                for (auto textbox : textBoxs[currentIndex])
                {
                    if (textbox->getSelect())
                    {
                        textbox->updateCursor();
                    }
                    textbox->draw();
                }
            }
        }
    }

public:
    Widget(int width, int height)
        :width(width), height(height), currentIndex(-1)
    {
    }
    ~Widget() {}

    void initregister()
    {
        initgraph(width, height);

        // 创建页面1
        IMAGE* page2 = new IMAGE(width, height);
        IMAGE bg1;
        loadimage(&bg1, _T("./resource/background/login.jpg"), width, height);
        putimage(0, 0, &bg1);

        //在界面2显示账户、密码、昵称字样
        settextcolor(RGB(255, 255, 255));
        setbkmode(TRANSPARENT);
        settextstyle(30, 0, _T("微软雅黑"));
        outtextxy(550, 300, "账户：");
        outtextxy(550, 350, "密码：");
        outtextxy(550, 400, "昵称：");
        settextstyle(50, 0, _T("微软雅黑"));
        outtextxy(600, 200, "注册");
        getimage(page2, 0, 0, width, height);
        addPage(page2);




        // 在界面1创建按钮（登录）
        Button* button1_1 = new Button(565, 450, 150, 30, "注册", [&]() {
            FILE* file, * signfile, * signfilea;
            char filename[20];
            //读取命名次数
            signfile = fopen("sign.txt", "r");
            fscanf(signfile, "%d", &sign1);
            fclose(signfile);
            sprintf(filename, "file%d.txt", sign1);
            //printf("%d\n", sign1);
            signfilea = fopen("sign.txt", "w");
            fprintf(signfilea, "%d", sign1 + 1);
            fclose(signfilea);
            file = fopen(filename, "w+");//创建配置文件
            fprintf(file, "accountname:%s\n", textBoxs[1][1]->getText());//写入用户名
            fprintf(file, "password:%s\n", textBoxs[1][2]->getText());//写入密码
            fprintf(file, "name:%s\n", textBoxs[1][3]->getText());//写入昵称
            fprintf(file, "level:1\n");//写入初始等级
            fprintf(file, "manpower:10000\n");//写入初始人力
            fprintf(file, "ammunition:10000\n");//写入初始弹药
            fprintf(file, "pation:10000\n");//写入初始口狼
            fprintf(file, "part:10000\n");//写入初始零件
            MessageBox(GetHWnd(), _T("注册成功，请登录"), _T("成功"), MB_OK);
            fclose(file);
            textBoxs[1][0]->clear();
            textBoxs[1][1]->clear();
            textBoxs[1][2]->clear();
            closegraph;
            login();
            });
        addButton(0, button1_1);

       

        //在界面1创建文本框（账户）
        TextBox* textbox2_1 = new TextBox(615, 300, 150, 30, 10);
        addTextBox(0, textbox2_1);

        //在界面1创建文本框(密码)
        TextBox* textbox2_2 = new TextBox(615, 350, 150, 30, 10);
        addTextBox(0, textbox2_2);

        //在界面1创建文本框(昵称)
        TextBox* textbox2_3 = new TextBox(615, 400, 150, 30, 10);
        addTextBox(0, textbox2_3);

        setCurrentIndex(0);
    }

    void run()
    {
        ExMessage msg;

        BeginBatchDraw();
        while (true)
        {
            if (peekmessage(&msg))
            {
                int mouseX = msg.x;
                int mouseY = msg.y;
                switch (msg.message)
                {
                case WM_LBUTTONDOWN:
                    mouseClick(mouseX, mouseY);
                    break;
                case WM_MOUSEMOVE:
                    mouseMove(mouseX, mouseY);
                    break;
                case WM_CHAR:
                    keyInput(msg.ch);
                    break;
                }
            }
            draw();
            FlushBatchDraw();
            Sleep(10);
        }
        EndBatchDraw();
    }

    void close()
    {
        closegraph();
    }
};

void registerf()
{
    Widget widget(1280, 720);
    widget.initregister();
    widget.run();
    widget.close();
    printf("%d", 2);
    

}