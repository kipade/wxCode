/////////////////////////////////////////////////////////////////////////////
// Name:        httpbuilderthread.cpp
// Purpose:     HTTP builderThread lets you work with the wxHTTPBuilder class in
//				gui based application using events.
// Author:      Angelo Mandato
// Created:     2005/08/11
// RCS-ID:      $Id: httpbuilderthread.cpp 887 2009-02-09 09:36:12Z amandato $
// Copyright:   (c) 2002-2005 Angelo Mandato
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "httpbuilderthread.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// includes
#ifndef WX_PRECOMP
	// here goes the #include <wx/abc.h> directives for those
	// files which are not included by wxprec.h
	#include <wx/wx.h>
	#include <wx/window.h>
#endif

#include <wx/httpbuilderthread.h>

DEFINE_EVENT_TYPE(wxEVT_HTTPBUILDERTHREAD_FINISHED)

//! Check to see if the thread is marked to be stopped
bool wxHTTPBuilderThreadObj::StopCheck(void)
{
  if( m_thread->TestDestroy() )
    m_Stop = true;

  return m_Stop;
}

//! wxHTTPBuilderThread constructor
wxHTTPBuilderThread::wxHTTPBuilderThread(wxWindow *parent, int id, wxHTTPBuilder *http, const wxString &url)
{
  m_parent = parent;
  m_id = id;
  m_url = url;
  m_http = (wxHTTPBuilderThreadObj*)http;
  m_data = wxT("");
	m_operation = wxHTTPBuilderThread_SaveAsString;
}

//! wxHTTPBuilderThread destructor
wxHTTPBuilderThread::~wxHTTPBuilderThread()
{
  // Empty
}

//! Thread's OnExit
void wxHTTPBuilderThread::OnExit(void)
{ 
  wxHTTPBuilderEvent event( wxEVT_HTTPBUILDERTHREAD_FINISHED, GetId(), true, m_data );
  event.SetEventObject( m_http );
  m_parent->GetEventHandler()->ProcessEvent(event);
}

//! Thread's Entry
void* wxHTTPBuilderThread::Entry(void)
{
	//if( !m_setflags )
	m_http->SetFlags( wxSOCKET_NONE|wxSOCKET_BLOCK ); // Very important
	// wxSOCKET_NONE will try to read some data no matter what
	// wxSOCKET_BLOCK will block the thread, which is fine.
	// If you do not include wxSOCKET_BLOCK, you will see your processor usage go through the roof.

	switch( m_operation )
	{
		case wxHTTPBuilderThread_SaveToFile: {
			m_http->SaveFile(m_filename, m_url, m_tempDir);
		}; break;
		case wxHTTPBuilderThread_HeadRequest: {
			m_http->GetHeadResponse(m_url);
		}; break;
		case wxHTTPBuilderThread_Delete: {
			m_http->GetDeleteResponse(m_url);
		}; break;
		case wxHTTPBuilderThread_PutFile: {
			m_http->GetPutResponse(m_filename, m_url);
		}; break;
		case wxHTTPBuilderThread_SaveAsString:
		default: {
			m_data = m_http->GetInputString( m_url, m_tempDir);
		};
	}

  return NULL;
}

// eof
