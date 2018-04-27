#include "main.h"
#include "mainframe.h"

wxIMPLEMENT_APP(ICPApp);

bool ICPApp::OnInit() {
    MainFrame *frame = new MainFrame(this->GetTopWindow());
    frame->Show( true );
    return true;
}
