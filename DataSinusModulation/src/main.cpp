#include "wx/wx.h"
#include "wx/sizer.h"

#include <iostream>

#include "GraphRendering.h"
#include "SignalGenerator.h"
#include "GlobalData.h"

#include "AppConstant.h"



using namespace std;


class MyApp: public wxApp
{
  public:
    MyApp();
    ~MyApp();

    SignalGenerator *  getSignalGenerator()     {   return signal;   }

 private:
    bool OnInit();

    SignalGenerator *signal = nullptr;

};



class MyFrame : public wxFrame
{
public:
    MyFrame(MyApp* parent);

    void buildControlSection();

private:
    MyApp* parent;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

     wxDECLARE_EVENT_TABLE();
};




//////////////////////////////////////////////////////////////////////////////////////////////////////
//                  IMPLEMENTATION OF MyApp function members...
//////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_APP(MyApp)

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
 if ( signal != nullptr )  delete signal;
}


bool MyApp::OnInit()
{
    MyFrame * frame = new MyFrame(this);

    GraphRendering* drawPane   = new GraphRendering( (wxFrame*) frame );

    frame ->buildControlSection();
    frame->SetAutoLayout(true);
    frame->Show();

    cout << "OnInit called\n";
    struct SignalParam params = {255,200};
    signal = new SignalGenerator();
    signal->generate(params);

    GlobalData* singleton = GlobalData::GetInstance();

    singleton->copySignalBuffer(signal->getSignalBuffer(),256);

    return true;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
//                  IMPLEMENTATION OF MyFrame function members...
//////////////////////////////////////////////////////////////////////////////////////////////////////


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
 //   EVT_MENU(ID_StartWorkerMenuItem, MyFrame::OnStartWorkerMenuItemClick)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
  //  EVT_BUTTON(ID_StartWorkerButton, MyFrame::OnStartWorkerButtonClick) // Tell the OS to run MainFrame::OnExit whe
//    EVT_THREAD(ID_WORKER_EVENT, MyFrame::OnWorkerEvent)
wxEND_EVENT_TABLE()


MyFrame::MyFrame(MyApp* parent)  : wxFrame(nullptr, wxID_ANY, "Sinus Draw", wxDefaultPosition, wxSize(FRAME_WIDTH,FRAME_HEIGHT))
{
    this->parent = parent;
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_SPAWN_CHILD, "&Child Process...\tCtrl-C",  "Start a child process");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText("A demo of drawing...");
}

void MyFrame::buildControlSection()
{
    // You should add more controls here
    wxStaticText *control  = new wxStaticText(this, NULL,"You should add more control here...", wxPoint(40,410), wxSize(300,30));

    wxButton* testButton = new wxButton( this, ID_REDRAW_BUTTON, "OK" , wxPoint(40,430), wxSize(100,30));
}


void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Trying to draw a simple curve with wxWidget",
                 "About Sinus Draw...", wxOK | wxICON_INFORMATION);
}



