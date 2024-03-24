// Start of wxWidgets "Hello World" Program

#include <sys/types.h>

#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnSpawnChild(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1,
    ID_SPAWN_CHILD = 2
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()  : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",  "string shown in status bar for this menu item");
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
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnSpawnChild, this, ID_SPAWN_CHILD);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}


void MyFrame::OnSpawnChild(wxCommandEvent& event)
{
    pid_t child_pid;
//    int currentID = (int) getpid ();

   printf ("Main program process ID is %d\n", (int) getpid ());
   child_pid = fork ();
   if (child_pid != 0)
   {
     printf ("this is the parent process, with id %d\n", (int) getpid ());
   }
   else
   {
     char* arg_list[] = { "ls", "-l", "/", NULL };
      printf ("this is the child process, with id %d\n", (int) getpid ());
      execvp ("ls", arg_list);
   }



 wxLogMessage("OnSpawnChild!");


}

