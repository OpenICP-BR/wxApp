#include "main.h"

wxIMPLEMENT_APP(ICPApp);

bool ICPApp::OnInit() {
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("src/ui.xrc");

    wxFrame *frame = wxXmlResource::Get()->LoadFrame(this->GetTopWindow(), "MainFrame");
    if (frame != NULL) {
        frame->Show(true);
    }
    return true;
}
