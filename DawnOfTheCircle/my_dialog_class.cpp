#include "my_dialog_class.h"

bool my_dialog::init_dlg(int dlg_number)
{
    this->dialog_number = dlg_number;
    int tempnumber;
    double tempdouble;
    string tempwords;
    string dialog_file="resource\\dialog\\"+int2str(dlg_number)+".dlg";
    fstream read_dialog_file(dialog_file.c_str(),fstream::in);
    if(!read_dialog_file)
    {
        test(4, dlg_number);
        //throw runtime_error("read floor file error!");
        exit(4);
    }

    fontcol = 0;
    font_size = 20;

    while(!read_dialog_file.eof())
    {
        dialog_positionx.push_back(0);
        dialog_positiony.push_back(0);

        read_dialog_file>>tempdouble;
        start_time.push_back(tempdouble);

        read_dialog_file>>tempdouble;
        end_time.push_back(tempdouble);

        read_dialog_file>>tempnumber;
        speaker_number.push_back(tempnumber);

        getline(read_dialog_file, tempwords);
        //tempwords="   "+tempwords;//Îª´òÓ¡Í¼Ïñ¿Õ3¸ñ
        dialog_words.push_back(tempwords);
    }



    read_dialog_file.close();
    read_dialog_file.clear();

    return true;
}
