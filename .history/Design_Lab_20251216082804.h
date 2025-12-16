#ifndef Design_Lab
#define Design_Lab

#include <windows.h>
#include <iostream>
using namespace std;

// -------- COLOR CONSTANTS --------
enum Color {
    BLACK = 0, BLUE, GREEN, CYAN,
    RED, PURPLE, YELLOW, WHITE,
    GRAY = 8
};

// -------- SET COLOR --------
void SetColor(int text_Color, int bg_Color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_Color << 4) | text_Color);
}

// -------- CLEAR SCREEN --------
void Clear()
{
    system("cls");
}

// -------- TITLE BAR --------
void TitleBar(const string& title)
{
    SetColor(WHITE, BLUE);
    cout << "============================================================\n";
    cout << "  " << title << "\n";
    cout << "============================================================\n";
    SetColor(YELLOW, BLACK);
}

// -------- SECTION HEADER --------
void Section(const string& title)
{
    SetColor(CYAN, BLACK);
    cout << "\n--- " << title << " ---\n";
    SetColor(WHITE, BLACK);
}

// -------- MENU OPTION --------
void MenuOption(int num, const string& text)
{
    SetColor(GREEN, BLACK);
    cout << "  [" << num << "] ";
    SetColor(WHITE, BLACK);
    cout << text << endl;
}

// -------- WARNING --------
void Warning(const string& msg)
{
    SetColor(RED, BLACK);
    cout << "\n[!] " << msg << endl;
    SetColor(WHITE, BLACK);
}

// -------- SUCCESS --------
void Success(const string& msg)
{
    SetColor(GREEN, BLACK);
    cout << "\n[✓] " << msg << endl;
    SetColor(WHITE, BLACK);
}

// -------- INPUT PROMPT --------
void Prompt(const string& msg)
{
    SetColor(YELLOW, BLACK);
    cout << msg;
    SetColor(WHITE, BLACK);
}

// -------- PAUSE --------
void Pause()
{
    SetColor(GRAY, BLACK);
    system("pause");
    SetColor(WHITE, BLACK);
}

#endif
