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


//��ť
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
        settextstyle(20 * scale, 0, _T("΢���ź�"));
        int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2;
        int textY = scaledY + (scaledHeight - textheight(_T("΢���ź�"))) / 2;
        outtextxy(textX, textY, text.c_str());
    }
};

//���������
class TextBox
{
private:
    int x;
    int y;
    int width;
    int height;
    int maxWord;    //����ʸ���
    string text;   //�ı�
    bool isSelected;    //�Ƿ�ѡ��
    bool showCursor;    //�Ƿ���ʾ���
    int cursorPos;      //���λ��

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
        settextstyle(height * 3 / 4, 0, _T("΢���ź�"));

        outtextxy(x + 5, y + (height - textheight(_T("΢���ź�"))) / 2, text.c_str());

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
            case '\b':				// �û����˸����ɾ��һ���ַ�
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
            default:				// �û����������������ı�����
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
        if (currentTick - lastTick >= 500) // ÿ500�����л����״̬
        {
            showCursor = !showCursor;
            lastTick = currentTick;
        }
    }
};

//����
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

        // ����ҳ��1
        IMAGE* page2 = new IMAGE(width, height);
        IMAGE bg1;
        loadimage(&bg1, _T("./resource/background/login.jpg"), width, height);
        putimage(0, 0, &bg1);

        //�ڽ���2��ʾ�˻������롢�ǳ�����
        settextcolor(RGB(255, 255, 255));
        setbkmode(TRANSPARENT);
        settextstyle(30, 0, _T("΢���ź�"));
        outtextxy(550, 300, "�˻���");
        outtextxy(550, 350, "���룺");
        outtextxy(550, 400, "�ǳƣ�");
        settextstyle(50, 0, _T("΢���ź�"));
        outtextxy(600, 200, "ע��");
        getimage(page2, 0, 0, width, height);
        addPage(page2);




        // �ڽ���1������ť����¼��
        Button* button1_1 = new Button(565, 450, 150, 30, "ע��", [&]() {
            FILE* file, * signfile, * signfilea;
            char filename[20];
            //��ȡ��������
            signfile = fopen("sign.txt", "r");
            fscanf(signfile, "%d", &sign1);
            fclose(signfile);
            sprintf(filename, "file%d.txt", sign1);
            //printf("%d\n", sign1);
            signfilea = fopen("sign.txt", "w");
            fprintf(signfilea, "%d", sign1 + 1);
            fclose(signfilea);
            file = fopen(filename, "w+");//���������ļ�
            fprintf(file, "accountname:%s\n", textBoxs[1][1]->getText());//д���û���
            fprintf(file, "password:%s\n", textBoxs[1][2]->getText());//д������
            fprintf(file, "name:%s\n", textBoxs[1][3]->getText());//д���ǳ�
            fprintf(file, "level:1\n");//д���ʼ�ȼ�
            fprintf(file, "manpower:10000\n");//д���ʼ����
            fprintf(file, "ammunition:10000\n");//д���ʼ��ҩ
            fprintf(file, "pation:10000\n");//д���ʼ����
            fprintf(file, "part:10000\n");//д���ʼ���
            MessageBox(GetHWnd(), _T("ע��ɹ������¼"), _T("�ɹ�"), MB_OK);
            fclose(file);
            textBoxs[1][0]->clear();
            textBoxs[1][1]->clear();
            textBoxs[1][2]->clear();
            closegraph;
            login();
            });
        addButton(0, button1_1);

       

        //�ڽ���1�����ı����˻���
        TextBox* textbox2_1 = new TextBox(615, 300, 150, 30, 10);
        addTextBox(0, textbox2_1);

        //�ڽ���1�����ı���(����)
        TextBox* textbox2_2 = new TextBox(615, 350, 150, 30, 10);
        addTextBox(0, textbox2_2);

        //�ڽ���1�����ı���(�ǳ�)
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