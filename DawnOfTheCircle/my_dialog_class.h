#ifndef MY_DIALOG_CLASS_H_
#define MY_DIALOG_CLASS_H_

#include <string>
#include <fstream>
#include <vector>
#include <graphics.h>
#include "test.h"

using namespace std;

class my_dialog
{
    public:
        int dialog_number;
        int font_size;
        unsigned char fontcol;
        vector< int > dialog_positionx;
        vector< int > dialog_positiony;
        vector< double > start_time;
        vector< double > end_time;
        vector< int > speaker_number;
        vector< string > dialog_words;

        bool init_dlg(int dlg_number);
        my_dialog() {}
        ~my_dialog() {}

};

#endif // MY_DIALOG_CLASS_H_
