#include <iostream>
#include <thread>
#include <set>
#include "BufferedAsyncSerial.h"
#include "can_def.h"
#include <windows.h>
#include <iterator>
#include <algorithm>

void clear_screen(char fill = ' ') {
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

using namespace std;

int main(int argc, char* argv[])
{
    CAN cn1;
    set<CAN> canList;
    int id = 0;
    try {
        bool end = false;
        char * port = argv[1];
        BufferedAsyncSerial serial(port, 9600);
        if ( argc > 2 ){
            while ( !end ){
                cn1.id = 0xFA;
                cn1.data64 = 0x8877665544332211;
                cn1.dlc = 8;
                serial.write((const char*)&cn1, 6+cn1.dlc);
                this_thread::sleep_for(chrono::seconds(1));
                if ( id++ % 5 == 0 ){
                    clear_screen();
                    cout << port << endl;
                }
                cout << "wrote: " << cn1 << endl;
            }
        } else {
            while ( !end ){
                size_t s = serial.read((char*)&cn1, sizeof(CAN));
                if ( s > 0 && cn1.id != 0 ){
                    canList.insert(cn1);
                    cn1.id = 0;
                    clear_screen();
                    cout << port << endl;
                    copy(canList.begin(), canList.end(), ostream_iterator<CAN>(cout, "\n"));
                }
            }
        }
        serial.close();

    } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return 1;
    }
}
