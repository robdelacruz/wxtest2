#ifndef APP_H
#define APP_H

#include "wx/wx.h"

enum {
    ID_DATAVIEW = wxID_HIGHEST,
    ID_COUNT
};

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxDECLARE_APP(MyApp);

#endif
