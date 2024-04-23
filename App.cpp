#include "App.h"
#include "Frame.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame(wxT("MyFrame"));
    frame->Show(true);
    return true;
}

