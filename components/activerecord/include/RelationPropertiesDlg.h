/////////////////////////////////////////////////////////////////////////////
// Name:        RelationPropertiesDlg.h
// Purpose:     
// Author:      Matías Szeftel
// Modified by: 
// Created:     Fri 09 Feb 2007 00:58:17 ART
// RCS-ID:      
// Copyright:   (c) 2006 Matías Szeftel <mszeftel@yahoo.com.ar>
// Licence:     GPL (GNU Public License)
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), Fri 09 Feb 2007 00:58:17 ART

#ifndef _RELATIONPROPERTIESDLG_H_
#define _RELATIONPROPERTIESDLG_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "RelationPropertiesDlg.h"
#endif

/*!
 * Includes
 */

////@begin includes
////@end includes

#include "wxActiveRecordGenerator.h"

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_RELATIONDLG 10019
#define ID_CMBTABLES 10028
#define ID_TCITEMNAME 10029
#define ID_CMBFOREIGN 10030
#define ID_TCCLASSNAME 10033
#define SYMBOL_RELATIONPROPERTIESDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_RELATIONPROPERTIESDLG_TITLE _("Relation Properties")
#define SYMBOL_RELATIONPROPERTIESDLG_IDNAME ID_RELATIONDLG
#define SYMBOL_RELATIONPROPERTIESDLG_SIZE wxSize(400, 300)
#define SYMBOL_RELATIONPROPERTIESDLG_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * RelationPropertiesDlg class declaration
 */

class RelationPropertiesDlg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( RelationPropertiesDlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    RelationPropertiesDlg( );
    RelationPropertiesDlg( wxWindow* parent, wxWindowID id = SYMBOL_RELATIONPROPERTIESDLG_IDNAME, const wxString& caption = SYMBOL_RELATIONPROPERTIESDLG_TITLE, const wxPoint& pos = SYMBOL_RELATIONPROPERTIESDLG_POSITION, const wxSize& size = SYMBOL_RELATIONPROPERTIESDLG_SIZE, long style = SYMBOL_RELATIONPROPERTIESDLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_RELATIONPROPERTIESDLG_IDNAME, const wxString& caption = SYMBOL_RELATIONPROPERTIESDLG_TITLE, const wxPoint& pos = SYMBOL_RELATIONPROPERTIESDLG_POSITION, const wxSize& size = SYMBOL_RELATIONPROPERTIESDLG_SIZE, long style = SYMBOL_RELATIONPROPERTIESDLG_STYLE );

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin RelationPropertiesDlg event handler declarations

    /// wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_CMBTABLES
    void OnCmbtablesSelected( wxCommandEvent& event );

    /// wxEVT_UPDATE_UI event handler for ID_CMBFOREIGN
    void OnCmbforeignUpdate( wxUpdateUIEvent& event );

    /// wxEVT_UPDATE_UI event handler for wxID_OK
    void OnOkUpdate( wxUpdateUIEvent& event );

////@end RelationPropertiesDlg event handler declarations

////@begin RelationPropertiesDlg member function declarations

    wxActiveRecordGenerator* GetActiveRecordGen() const { return activeRecordGen ; }
    void SetActiveRecordGen(wxActiveRecordGenerator* value) { activeRecordGen = value ; }

    ArNodeHash* GetNodeHash() const { return p_nodeHash ; }
    void SetNodeHash(ArNodeHash* value) { p_nodeHash = value ; }

    arRelation GetRelation() const { return relation ; }
    void SetRelation(arRelation value) { relation = value ; }

    wxString GetThisTable() const { return thisTable ; }
    void SetThisTable(wxString value) { thisTable = value ; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end RelationPropertiesDlg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin RelationPropertiesDlg member variables
    wxComboBox* cmb_tables;
    wxTextCtrl* tc_itemName;
    wxComboBox* cmb_foreignId;
    wxTextCtrl* tc_className;
    wxButton* btn_OK;
    ArNodeHash* p_nodeHash;
public:
    wxActiveRecordGenerator* activeRecordGen;
    arRelation relation;
    wxString thisTable;
////@end RelationPropertiesDlg member variables
	bool TransferDataToWindow();
	bool TransferDataFromWindow();
};

#endif
    // _RELATIONPROPERTIESDLG_H_
