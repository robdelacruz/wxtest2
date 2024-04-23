#ifndef FRAME_H
#define FRAME_H

#include "wx/wx.h"

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);
    ~MyFrame();

    void CreateControls();

    void OnDataViewSelectionChanged(wxDataViewEvent &event);
private:
    wxDECLARE_EVENT_TABLE();

};

#endif
