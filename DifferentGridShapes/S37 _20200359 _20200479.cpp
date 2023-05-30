#include <iostream>
#include <windows.h>

//color function
void SetColor(int ForgC) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

using namespace std;

//intialze private members
class ColoredBox {
private:
    int Len, Width;
    int Color;
    char C;
    char **box;
    static int maxArea;

public:
    //costructor
    ColoredBox(int Len, int Width, int Color = 15, char c = '#');

    //return the max area of all objects
    static int getMaxArea();

    //print the box
    void display();

    //seters and getter
    void setColor(int Color);

    void setwidth(int Width);

    void setlength(int Len);

    void setSign(char C);

    char getColor() const;

    int getWidth() const;

    int getLength() const;

    //make the box transpose
    void displayTransposed();

    //make the box wider
    void displayWider();

    //print the box with two colors
    void displayChess(int col2);

    //get area
    double getArea();

    //delete the dynamic array
    ~ColoredBox();
};

ColoredBox::ColoredBox(int Len, int Width, int Color, char C) {
    this->Len = Len;
    this->Width = Width;
    this->Color = Color;
    this->C = C;
    if (Len * Width > maxArea)
        maxArea = Len * Width;
    box = new char *[Len];
    for (int i = 0; i < Len; ++i) {
        box[i] = new char[Width];
    }
    for (int i = 0; i < Len; i++)
        for (int j = 0; j < Width; j++)
            box[i][j] = C;
}

int ColoredBox::getMaxArea() {
    return maxArea;
}

void ColoredBox::display() {
    SetColor(Color);
    for (int i = 0; i < Len; i++) {
        for (int j = 0; j < Width; j++)
            cout << box[i][j];
        cout << endl;
    }
    // to return the color white
    SetColor(15);
}

void ColoredBox::setColor(int Color) {
    this->Color = Color;
}

void ColoredBox::setwidth(int Width) {
    this->Width = Width;
}

void ColoredBox::setlength(int Len) {
    this->Len = Len;
}

void ColoredBox::setSign(char C) {
    this->C = C;
}

char ColoredBox::getColor() const {
    return Color;
}

int ColoredBox::getWidth() const {
    return Width;
}

int ColoredBox::getLength() const {
    return Len;
}

void ColoredBox::displayTransposed() {
    SetColor(Color);
    for (int j = 0; j < Width; j++) {
        for (int i = 0; i < Len; i++)
            cout << box[i][j];
        cout << endl;
    }
    // to return the color white
    SetColor(15);
}

void ColoredBox::displayWider() {
    SetColor(Color);
    for (int i = 0; i < Len; i++) {
        for (int j = 0; j < Width; j++)
            cout << box[i][j] << " ";
        cout << endl;
    }
    // to return the color white
    SetColor(15);

}

void ColoredBox::displayChess(int col2) {

    int chessColor = col2;
    for (int i = 0; i < Len; i++) {
        for (int j = 0; j < Width; j++) {
            if (chessColor == Color)chessColor = col2;
            else chessColor = Color;
            SetColor(chessColor);
            cout << box[i][j];
        }
        cout << endl;
    }
    // to return the color white
    SetColor(15);
}

double ColoredBox::getArea() {
    return Width * Len;
}

ColoredBox::~ColoredBox() {
    for (int i = 0; i < Len; i++)
        delete[] box[i];
    delete[] box;
}

int ColoredBox::maxArea = 0;

int main() {
    int len, wid, col, col2;
    char boxChar;
    cout << "Enter length and width of the box separated by a space: ";
    cin >> len >> wid;
    ColoredBox *cb1;
    cb1 = new ColoredBox(len, wid);
    cb1->display();
    cout << "Set the box to another color: ";
    cin >> col;
    cb1->setColor(col);
    cout << "Displaying Transposed: " << endl;
    cb1->displayTransposed();
    cout << "Displaying Wider: " << endl;
    cb1->displayWider();
    cout << "Displaying Chess, enter the other color: " << endl;
    cin >> col2;
    cb1->displayChess(col2);
    cout << endl << "Area=" << cb1->getArea();
    cout << endl << "Max Area=" << cb1->getMaxArea();
    delete cb1;

    cout << endl << "Enter length,width,color,character of the box separated by spaces: ";
    cin >> len >> wid >> col >> boxChar;
    ColoredBox *cb2;
    cb2 = new ColoredBox(len, wid, col, boxChar);
    cb2->display();
    cout << "Displaying Transposed: " << endl;
    cb2->displayTransposed();
    cout << "Displaying Wider: " << endl;
    cb2->displayWider();
    cout << "Displaying Chess, enter the other color: " << endl;
    cin >> col2;
    cb2->displayChess(col2);
    cout << "Displaying original again:" << endl;
    cb2->display();
    cout << endl << "Area=" << cb2->getArea();
    cout << endl << "Max Area=" << cb2->getMaxArea();
    delete cb2;
    return 0;
}