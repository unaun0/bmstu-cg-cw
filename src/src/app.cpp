#include "app.hpp"

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Настройки изображения");

    frame->SetSize(wxSize(1050, 410));
    frame->SetMinSize(wxSize(1050, 410));
    frame->SetMaxSize(wxSize(1050, 410));

    frame->Show(true);

    return true;
}
