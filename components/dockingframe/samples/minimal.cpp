////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWindows sample
// Author:      Julian Smart
// Modified by: Francesco Montorsi
// Created:     04/01/98
// RCS-ID:      $Id: minimal.cpp,v 1.1 2006-08-31 18:02:25 bart59 Exp $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#include "wx/dockingframe.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "mondrian.xpm"
#endif

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------

// Define a new application type, each program should derive a class from wxApp
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();

	int OnExit();
};

// ----------------------------------------------------------------------------
// constants	
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT,

    // add here new menu IDs
};

// Define a new frame type: this is going to be our main frame
class MyFrame : public wxDockingFrame
{
public:
    // ctor(s)
    MyFrame(const wxString& title);
	~MyFrame();

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    
    //Dock or Undock Event
    void OnMenuDock(wxCommandEvent& event);
	// add here event handlers

private:
    // any class wishing to process wxWindows events must use this macro
    DECLARE_EVENT_TABLE()
};

//Custom events
#define ID_MENU_DOCK_RIGHT        wxID_HIGHEST+200
#define ID_MENU_DOCK_LEFT         wxID_HIGHEST+201
#define ID_MENU_UNDOCK            wxID_HIGHEST+202

// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MyFrame, wxDockingFrame)
    EVT_MENU(Minimal_Quit,  MyFrame::OnQuit)
    EVT_MENU(Minimal_About, MyFrame::OnAbout)
    EVT_MENU    (ID_MENU_DOCK_RIGHT, MyFrame::OnMenuDock)
    EVT_MENU    (ID_MENU_DOCK_LEFT, MyFrame::OnMenuDock)
    EVT_MENU    (ID_MENU_UNDOCK, MyFrame::OnMenuDock)
    // add here EVT_* macros
END_EVENT_TABLE()

// Create a new application object: this macro will allow wxWindows to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
IMPLEMENT_APP(MyApp)

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// wxT('Main program') equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // create the main application window
    MyFrame *frame = new MyFrame(_T("Minimal wxWindows App"));

#if 1
	// create an useful log window
	wxLogWindow *pwindow = new wxLogWindow(frame, wxT("log"));
	pwindow->GetFrame()->Move(50, 50+350);
	pwindow->GetFrame()->SetSize(800, 300);

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);
#endif

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

int MyApp::OnExit()
{
	return 0;
}


// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString& title)
       : wxDockingFrame(NULL, wxID_ANY, title, wxVERTICAL,wxPoint(50, 50), wxSize(500, 300))
{
    // set the frame icon
    SetIcon(wxICON(mondrian));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *menuFile = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    menuFile->Append(ID_MENU_DOCK_RIGHT, wxT("Dock Right"), wxT("dock the frame on the right side of the screen."));
	menuFile->Append(ID_MENU_DOCK_LEFT, _T("Dock Left"), wxT("dock the frame on the left side of the screen.."));
	menuFile->AppendSeparator();
    menuFile->Append(ID_MENU_UNDOCK, _T("UnDock"), wxT("Undock the window if docked"));	
	//menuFile->Append(Minimal_SaveAdv, _T("Save an advanced XHTML file"), _T("Creates a sample XHTML file and saves it in the given location."));	
	//menuFile->Append(Minimal_SaveDTD, _T("Save a DTD file"), _T("Creates a sample DTD file and saves it in the given location."));	
	menuFile->AppendSeparator();
	//menuFile->Append(Minimal_Valid, _T("Validate against DTD"), _T("Validates an XML file against a DTD."));	
	menuFile->AppendSeparator();
    menuFile->Append(Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));	

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to wxWindows!"));
#endif // wxUSE_STATUSBAR
}

MyFrame::~MyFrame()
{
}



// event handlers

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( wxT("This is a little demonstration of dockingFrame component by Bart Rolet.\n"));
    wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnMenuDock(wxCommandEvent& event)
{
    wxLogMessage(wxT("OnMenuDock()"));
     
     switch (event.GetId())
     {
        
        case ID_MENU_UNDOCK:        
            Undock();
            break;
        
        case ID_MENU_DOCK_RIGHT:
            Dock(DOCK_RIGHT);
            break;
       
       case ID_MENU_DOCK_LEFT:
            Dock(DOCK_LEFT);
      break;      
        
     }
}
