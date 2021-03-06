///////////////////////////////////////////////////////////////////////////////
// Name:        script.cpp
// Author:      Francesco Montorsi
// Created:     2004/29/4
// RCS-ID:      $Id: script.cpp 348 2005-11-18 20:08:02Z frm $
// Copyright:   (c) Francesco Montorsi
// Licence:     wxWidgets licence
///////////////////////////////////////////////////////////////////////////////



// includes
#include "wx/script.h"
#include <wx/filename.h>
#include <wx/file.h>

// now, we can include specific interpreter wrappers
#ifdef wxSCRIPT_USE_CINT
#include "wx/sccint.h"
#endif

#ifdef wxSCRIPT_USE_UNDERC
#include "wx/scunderc.h"
#endif

#ifdef wxSCRIPT_USE_LUA
#include "wx/sclua.h"
#endif

#ifdef wxSCRIPT_USE_PYTHON
#include "wx/scpython.h"
#endif

#ifdef wxSCRIPT_USE_PERL
#include "wx/scperl.h"
#endif


// setup static
wxString wxScriptFile::m_strFileExt[];
wxString wxScriptInterpreter::m_strLastErr;
wxCINT *wxScriptInterpreter::m_pCINT = NULL;
wxUnderC *wxScriptInterpreter::m_pUnderC = NULL;
wxLua *wxScriptInterpreter::m_pLua = NULL;
wxPython *wxScriptInterpreter::m_pPython = NULL;
wxPerl *wxScriptInterpreter::m_pPerl = NULL;


// global objects
wxScriptTypeInfo *wxScriptTypeVOID = NULL;
wxScriptTypeInfo *wxScriptTypeCHAR = NULL;
wxScriptTypeInfo *wxScriptTypeINT = NULL;
wxScriptTypeInfo *wxScriptTypeLONG = NULL;
wxScriptTypeInfo *wxScriptTypeFLOAT = NULL;
wxScriptTypeInfo *wxScriptTypeDOUBLE = NULL;
wxScriptTypeInfo *wxScriptTypeBOOL = NULL;

wxScriptTypeInfo *wxScriptTypePVOID = NULL;
wxScriptTypeInfo *wxScriptTypePCHAR = NULL;
wxScriptTypeInfo *wxScriptTypePINT = NULL;
wxScriptTypeInfo *wxScriptTypePLONG = NULL;
wxScriptTypeInfo *wxScriptTypePFLOAT = NULL;
wxScriptTypeInfo *wxScriptTypePDOUBLE = NULL;
wxScriptTypeInfo *wxScriptTypePBOOL = NULL;





// ----------------------
// wxSCRIPTINTERPRETER
// ----------------------

wxScriptInterpreter::wxScriptInterpreter()
{}

wxScriptInterpreter::~wxScriptInterpreter()
{}

bool wxScriptInterpreter::Init(bool bCINT, bool bUnderC, bool bLua, bool bPython, bool bPerl)
{
	// two conditions must be met in order to properly init of the
	// supported interpreter: 
	//
	// 1) its interface must have been compiled
	//    (that is, this file must be compiled without wxSCRIPT_NO_XXXX
	//    preprocessor symbol defined, where XXXX is the name of the
	//    intepreter).
	// 2) the bXXXX variable must be TRUE.
	//
	// this system allows both compile-time and run-time interpreter
	// support choice

	// now, 
	// 1) remove previous instances, if presents
	// 2) create new ones
	// 3) init them

	Cleanup();

#ifdef wxSCRIPT_USE_CINT
	if (bCINT) m_pCINT = new wxCINT();
	if (bCINT) m_pCINT->Init();
#endif

#ifdef wxSCRIPT_USE_UNDERC
	if (bUnderC) m_pUnderC = new wxUnderC();
	if (bUnderC) m_pUnderC->Init();
#endif

#ifdef wxSCRIPT_USE_LUA
	if (bLua) m_pLua = new wxLua();
	if (bLua) m_pLua->Init();
#endif

#ifdef wxSCRIPT_USE_PYTHON
	if (bPython) m_pPython = new wxPython();
	if (bPython) m_pPython->Init();
#endif

#ifdef wxSCRIPT_USE_PERL
	if (bPerl) m_pPerl = new wxPerl();
	if (bPerl) m_pPerl->Init();
#endif

	// just to avoid compiler warnings when one of the
	// wxSCRIPT_USE_LUA/UNDERC/CINT is not defined...
	wxUnusedVar(bLua);
	wxUnusedVar(bUnderC);
	wxUnusedVar(bCINT);
	wxUnusedVar(bPython);
	wxUnusedVar(bPerl);

	// create global objects
	wxScriptTypeVOID = new wxScriptTypeInfo(wxT("void"));
	wxScriptTypeINT = new wxScriptTypeInfo(wxT("int"));
	wxScriptTypeCHAR = new wxScriptTypeInfo(wxT("char"));
	wxScriptTypeLONG = new wxScriptTypeInfo(wxT("long"));
	wxScriptTypeFLOAT = new wxScriptTypeInfo(wxT("float"));
	wxScriptTypeDOUBLE = new wxScriptTypeInfo(wxT("double"));
	wxScriptTypeBOOL = new wxScriptTypeInfo(wxT("bool"));

	wxScriptTypePVOID = new wxScriptTypeInfo(wxT("void*"));
	wxScriptTypePINT = new wxScriptTypeInfo(wxT("int*"));
	wxScriptTypePCHAR = new wxScriptTypeInfo(wxT("char*"));
	wxScriptTypePLONG = new wxScriptTypeInfo(wxT("long*"));
	wxScriptTypePFLOAT = new wxScriptTypeInfo(wxT("float*"));
	wxScriptTypePDOUBLE = new wxScriptTypeInfo(wxT("double*"));
	wxScriptTypePBOOL = new wxScriptTypeInfo(wxT("bool*"));

	return areAllReady();
}

void wxScriptInterpreter::Cleanup()
{
#ifdef wxSCRIPT_USE_CINT
	wxDELETE(m_pCINT);
#endif

#ifdef wxSCRIPT_USE_UNDERC
	wxDELETE(m_pUnderC);
#endif

#ifdef wxSCRIPT_USE_LUA
	wxDELETE(m_pLua);
#endif

#ifdef wxSCRIPT_USE_PYTHON
	wxDELETE(m_pPython);
#endif

#ifdef wxSCRIPT_USE_PERL
	wxDELETE(m_pPerl);
#endif

	wxDELETE(wxScriptTypeVOID);
	wxDELETE(wxScriptTypeINT);
	wxDELETE(wxScriptTypeCHAR);
	wxDELETE(wxScriptTypeLONG);
	wxDELETE(wxScriptTypeFLOAT);
	wxDELETE(wxScriptTypeDOUBLE);
	wxDELETE(wxScriptTypeBOOL);

	wxDELETE(wxScriptTypePVOID);
	wxDELETE(wxScriptTypePINT);
	wxDELETE(wxScriptTypePCHAR);
	wxDELETE(wxScriptTypePLONG);
	wxDELETE(wxScriptTypePFLOAT);
	wxDELETE(wxScriptTypePDOUBLE);
	wxDELETE(wxScriptTypePBOOL);
}

bool wxScriptInterpreter::areAllReady()
{
	bool res = TRUE;

#ifdef wxSCRIPT_USE_CINT
	if (m_pCINT) res &= m_pCINT->isReady();
#endif

#ifdef wxSCRIPT_USE_UNDERC
	if (m_pUnderC) res &= m_pUnderC->isReady();
#endif
	
#ifdef wxSCRIPT_USE_LUA
	if (m_pLua) res &= m_pLua->isReady();
#endif
	
#ifdef wxSCRIPT_USE_PYTHON
	if (m_pPython) res &= m_pPython->isReady();
#endif

#ifdef wxSCRIPT_USE_PERL
	if (m_pPerl) res &= m_pPerl->isReady();
#endif

	return res;
}

void wxScriptInterpreter::GetTotalFunctionList(wxScriptFunctionArray &arr)
{
	wxScriptFunctionArray arrcint, arruc, arrlua, arrpy;

	// even if the wxSCRIPT_USE_XXX symbol is defined,
	// we must still check if that particular interpreter has been
	// created & initialized before calling #GetFunctionList().
#ifdef wxSCRIPT_USE_CINT
	if (m_pCINT && m_pCINT->isReady()) m_pCINT->GetFunctionList(arrcint);
#endif

#ifdef wxSCRIPT_USE_UNDERC
	if (m_pUnderC && m_pUnderC->isReady()) m_pUnderC->GetFunctionList(arruc);
#endif
	
#ifdef wxSCRIPT_USE_LUA
	if (m_pLua && m_pLua->isReady()) m_pLua->GetFunctionList(arrlua);
#endif
	
#ifdef wxSCRIPT_USE_PYTHON
	if (m_pPython && m_pPython->isReady()) m_pPython->GetFunctionList(arrpy);
#endif

#ifdef wxSCRIPT_USE_PERL
	if (m_pPerl && m_pPerl->isReady()) m_pPerl->GetFunctionList(arrpy);
#endif

	// append all the functions collected in one single array
	arr.Append(arrcint);
	arr.Append(arruc);
	arr.Append(arrlua);
	arr.Append(arrpy);
}

wxScriptFile *wxScriptInterpreter::Load(const wxString &file, wxScriptFileType type)
{
	// first of all, check that the file exist...
	if (!wxFileName::FileExists(file)) {

		wxScriptInterpreter::m_strLastErr = wxT("The file [") + 
							file + wxT("] does not exist.\n");
		return FALSE;
	}

	// assign an invalid value just to avoid warnings
	wxScriptFileType t = wxRECOGNIZE_FROM_EXTENSION;

	// try to recognize the type of scriptfile
	if (type == wxRECOGNIZE_FROM_EXTENSION) {
		wxString ext = file.AfterLast(wxT('.'));

		for (int i=0; i < wxSCRIPT_SUPPORTED_FORMATS; i++) {

			// perform a case-insensitive comparison
			if (ext.IsSameAs(wxScriptFile::m_strFileExt[i], FALSE))
				t = (wxScriptFileType)i;
		}

	} else if (type == wxRECOGNIZE_FROM_COMMENT) {

		// we have to read the first chunk of the file...
		wxFile scriptfile(file, wxFile::read);
		int chunksize = 256;

		if (scriptfile.Length() < chunksize)
			chunksize = scriptfile.Length();
		if (chunksize < 2) {
			wxScriptInterpreter::m_strLastErr = wxT("The file is too short.\n");
			return FALSE;
		}

		// read an arbitrary long (256 should be enough) piece of file 
		char *buf = new char[chunksize+10];
		if ((int)scriptfile.Read(buf, chunksize) != chunksize) {
			wxScriptInterpreter::m_strLastErr = wxT("Couldn't read the file.\n");
			return FALSE;
		}

		// now, try to recognize the type of the code interpreting the
		// first non-whitespace characters as a comment declaration...
		buf[chunksize] = '\0';
		wxString tmp(buf, wxConvUTF8);
		delete [] buf;
		tmp.Trim(FALSE);

		// -- is used for lua comments...
		if (tmp.GetChar(0) == wxT('-') && tmp.GetChar(1) == wxT('-'))
			t = wxLUA_SCRIPTFILE;
		else if (tmp.GetChar(0) == wxT('#') 		// # is used by perl and python
                 && (tmp.Find("perl") != -1))       // so we look for a # then 'perl' in perl scripts
			t = wxPERL_SCRIPTFILE;                  // as in #!/usr/bin/perl
		else if (tmp.GetChar(0) == wxT('#'))		// # is used by python
			t = wxPYTHON_SCRIPTFILE;
		else if ((tmp.GetChar(0) == wxT('/') && tmp.GetChar(1) == wxT('/')) ||
					(tmp.GetChar(0) == wxT('/') && tmp.GetChar(1) == wxT('*')))
			t = wxCINT_SCRIPTFILE;
	}

	// the result
	wxScriptFile *p = NULL;

	switch (t) {
	case wxCINT_SCRIPTFILE:
#ifdef wxSCRIPT_USE_CINT
		p = new wxScriptFileCINT();
#endif
		break;
		
	case wxUNDERC_SCRIPTFILE:
#ifdef wxSCRIPT_USE_UNDERC
		p = new wxScriptFileUnderC();
#endif
		break;
		
	case wxLUA_SCRIPTFILE:
#ifdef wxSCRIPT_USE_LUA		
		p = new wxScriptFileLua();
#endif
		break;
		
	case wxPYTHON_SCRIPTFILE:
#ifdef wxSCRIPT_USE_PYTHON		
		p = new wxScriptFilePython();
#endif
		break;

	case wxPERL_SCRIPTFILE:
#ifdef wxSCRIPT_USE_PERL		
		p = new wxScriptFilePerl();
#endif
		break;

	default:
	    wxScriptInterpreter::m_strLastErr = wxT("Interpreter unavailable.\n");
		break;
	}
	
	// unrecognized type or interpreter interface not compiled ?
	if (p == NULL)
		return NULL;

	// actually load the scriptfile
	if (!p->Load(file)) {
		delete p;
		return NULL;
	}
	
	return p;
}




// --------------------
// wxSCRIPTFILE
// --------------------

wxString wxScriptFile::GetAllowedExtString()
{
	wxString ret;

	for (int i=0; i < wxSCRIPT_SUPPORTED_FORMATS; i++)
		if (!wxScriptFile::m_strFileExt[i].IsEmpty())
			ret += wxScriptFile::m_strFileExt[i].MakeUpper() + wxT(";");
	ret.RemoveLast();

	return ret;
}

wxArrayString wxScriptFile::GetAllowedExt()
{
	wxArrayString ret;

	for (int i=0; i < wxSCRIPT_SUPPORTED_FORMATS; i++)
		if (!wxScriptFile::m_strFileExt[i].IsEmpty())
			ret.Add(wxScriptFile::m_strFileExt[i].MakeUpper());

	return ret;
}




// --------------------
// wxSCRIPTTYPEINFO
// --------------------

void wxScriptTypeInfo::Set(const wxString &str)
{ 
	// the final form of the m_strName should be:
	//
	//    {int,long,char,float,double,...}[*,&]
	//     
	m_strName = str; 

	// remove leading & trailing spaces
	m_strName.Trim(TRUE);
	m_strName.Trim(FALSE);
	
	// cannot make lower the name of this variable with:
	//       m_strName = m_strName.MakeLower();
	// this would work with simple types like wxT("char"), "int"...
	// but it would destroy the case-sensitivity of the C/C++
	// language for user-types !!!!!!!!!!!!!!!

	// remove the CONST and VOLATILE keywords
	m_strName.Replace(wxT("const"), wxT(""));
	m_strName.Replace(wxT("volatile"), wxT(""));
	m_strName.Trim(TRUE); 
	m_strName.Trim(FALSE);

	// remove spaces before the "*" symbol
	m_strName.Replace(wxT(" *"), wxT("*"));
	m_strName.Replace(wxT(" &"), wxT("&"));

	// remove everything after the type
	if (m_strName.Contains(wxT(' ')))
		m_strName = m_strName.BeforeLast(wxT(' '));
}

bool wxScriptTypeInfo::isPointer() const
{
	if (m_strName.IsEmpty())
		return FALSE;
	if (m_strName.Last() != wxT('*'))
		return FALSE;
	return TRUE;
}

bool wxScriptTypeInfo::isReference() const
{
	if (m_strName.IsEmpty())
		return FALSE;
	if (m_strName.Last() != wxT('&'))
		return FALSE;
	return TRUE;
}

wxString wxScriptTypeInfo::GetPointerTypeName() const
{
	// just remove the last "*" placed at the end...
	if (!isPointer())
		return wxEmptyString;			// this is not a pointer !!
	return m_strName.Left(m_strName.Len()-1);
}

wxScriptTypeGeneric wxScriptTypeInfo::GetGenericType() const
{
	// check for basic types
	if (Match(wxScriptTypeINT))
		return wxSTG_INT;
	if (Match(wxScriptTypeLONG))
		return wxSTG_LONG;
	if (Match(wxScriptTypeCHAR))
		return wxSTG_CHAR;
	if (Match(wxScriptTypeFLOAT))
		return wxSTG_FLOAT;
	if (Match(wxScriptTypeDOUBLE))
		return wxSTG_DOUBLE;
	if (Match(wxScriptTypeBOOL))
		return wxSTG_BOOL;

	if (isPointer()) return wxSTG_POINTER;
	if (isReference()) return wxSTG_REFERENCE;

	// an user defined type ?
	return wxSTG_UNDEFINED;
}

void wxScriptTypeInfo::SetGenericType(wxScriptTypeGeneric t)
{
	switch (t) {
	case wxSTG_INT:
		m_strName = wxT("int");
		break;
	case wxSTG_LONG:
		m_strName = wxT("long");
		break;
	case wxSTG_CHAR:
		m_strName = wxT("char");
		break;
	case wxSTG_FLOAT:
		m_strName = wxT("float");
		break;
	case wxSTG_DOUBLE:
		m_strName = wxT("double");
		break;
	case wxSTG_BOOL:
		m_strName = wxT("bool");
		break;
	case wxSTG_VOID:
		m_strName = wxT("void");
		break;

	case wxSTG_POINTER:
	case wxSTG_REFERENCE:
	case wxSTG_USERDEFINED:
	case wxSTG_UNDEFINED:
		break;
	}
}





// --------------------
// wxSCRIPTVAR
// --------------------

void wxScriptVar::Copy(const wxScriptVar &var)
{
	// delete old contents (*before* setting the new type)
	ResetContent();

	// then, copy the type
	m_tType = var.m_tType;

	// then, copy the content using strings; as described
	// in #GetContentString() and #SetContent() functions,
	// no data loss should happen doing this...
	wxString content(var.GetContentString());
	SetContent(content);
}

void wxScriptVar::ResetContent()
{
	if (m_tType.GetGenericType() == wxSTG_POINTER && m_content != 0) {

		if (m_tType.GetPointerType().GetGenericType() == wxSTG_CHAR)
			delete [] ((char*)m_content);
		else
			delete ((void*)m_content);
	}

	m_content = 0;
}

void wxScriptVar::SetContent(const wxString &str)
{
	ResetContent();

	switch (m_tType.GetGenericType()) {
	case wxSTG_INT:
	case wxSTG_LONG:
	case wxSTG_VOID:
		str.ToLong(&m_content, 10);
		break;

	case wxSTG_CHAR:
		m_content = (wxChar)str.GetChar(0);		
		break;

		// even floats & doubles are stored as strings: they could not
		// fit into an 
	case wxSTG_FLOAT:
	case wxSTG_DOUBLE:
		str.ToDouble(&m_floatcontent);
		break;

	case wxSTG_BOOL:

		// there are at least two ways to encode a boolean value into
		// a string: using a number (typically 0 or 1) or using
		// the "true"/"false" strings...
		if (str.IsNumber()) {

			// we're using a number
			str.ToLong(&m_content, 10);

			// normalize content evaluating its truth value
			m_content = (m_content) ? 1 : 0;

		} else {

			// we are using a string
			if (str.CmpNoCase(wxT("TRUE")) == 0)
				m_content = 1;
			else
				m_content = 0;
		}
		break;

	case wxSTG_POINTER:

		// an exception is for char*
		if (m_tType.GetPointerType().GetGenericType() == wxSTG_CHAR) {

			// create a memory buffer encoded in UTF8 standard
			wxCharBuffer cb(str.mb_str(wxConvUTF8));
			const char *original = cb.data();
			int asciilen = strlen(original);

			char *pmem = new char[asciilen+1];
			strcpy(pmem, original);

			// and then set that memory address as the content of this var
			m_content = (long)pmem;

		} else {

			// the pointer address should be expressed in hexadecimal form
			str.ToLong(&m_content, 16);
		}
		break;

	case wxSTG_REFERENCE:
	case wxSTG_USERDEFINED:
	case wxSTG_UNDEFINED:
		// FIXME: what can we do here ?
		break;
	}
}

wxString wxScriptVar::GetContentString() const
{	
	wxString res;

	// get a string representation of the var's contents
	switch (m_tType.GetGenericType()) {
	case wxSTG_INT:
	case wxSTG_LONG:
	case wxSTG_VOID:
		return wxString::Format(wxT("%d"), (int)m_content);

	case wxSTG_CHAR:
		return wxString((wxChar)m_content, 1);

	case wxSTG_FLOAT:
	case wxSTG_DOUBLE:
		return wxString::Format(wxT("%g"), m_floatcontent);

	case wxSTG_BOOL:
		return (m_content ? wxT("true") : wxT("false"));

	case wxSTG_POINTER:

		// an exception is for char*
		if (m_tType.GetPointerType().GetGenericType() == wxSTG_CHAR) {
			
			char *pmem = (char *)m_content;
			return wxString(pmem, wxConvUTF8);

		} else {

			// the pointer address should be expressed in hexadecimal form
			return wxString::Format(wxT("%X"), (unsigned int)m_content);
		}
	
	case wxSTG_REFERENCE:
	case wxSTG_USERDEFINED:
	case wxSTG_UNDEFINED:
		// FIXME: what can we do here ?
		return wxString::Format(wxT("%d"), (int)m_content);
	}

	return res;
}




// --------------------
// wxSCRIPTFUNCTION
// --------------------

wxString wxScriptFunction::GetCallString(wxScriptVar *arg) const
{
	wxString cmd = m_strName + wxT("(");

	// create the string with the arguments...
	for (int i=0; i < m_nArgCount; i++) {
		if (i != 0) cmd += wxT(", ");
		cmd += wxT("\"") + arg[i].GetContentString() + wxT("\"");
	}
	
	cmd += wxT(")");
	return cmd;
}

void wxScriptFunction::Set(const wxString &name, const wxString &ret,
							  wxScriptTypeInfo *arr, int n)
{
	m_strName = name;
	m_tReturn.Set(ret);

	// copy arg list
	m_nArgCount = n;
	for (int i=0; i < n; i++)
		m_pArgList[i].DeepCopy(&arr[i]);
}

bool wxScriptFunction::Match(const wxScriptTypeInfo *ret, int argc, ...)
{
	// first of all, check return type & arg count
	if (!m_tReturn.Match(ret) || argc != GetArgCount())
		return FALSE;

	wxScriptTypeInfo *p = NULL;
	va_list marker;
	bool okay = TRUE;
	int n = 0;
	
	va_start(marker, argc);     /* Initialize variable arguments. */
	do {

		p = va_arg(marker, wxScriptTypeInfo *);

		if (p) {

			// check if n-th argument types coincides
			okay &= GetArgType(n).Match(p);
		}

		// check next arg
		n++;

	} while (p && n < argc);

	va_end(marker);              /* Reset variable arguments.      */

	return okay;
}




// -----------------------
// wxSCRIPTFUNCTIONARRAY
// -----------------------

void wxScriptFunctionArray::DeepCopy(const wxScriptFunctionArray *arr)
{
	// be sure to be empty....
	Clear();
	Append(*arr);

	// copy the prefix to strip
	m_strToStrip = arr->m_strToStrip;
}

void wxScriptFunctionArray::Append(const wxScriptFunctionArray &arr)
{
	// don't use the WX_APPEND_ARRAY macro
	// because it would just copy pointers; we must 
	// copy the wxScriptFunction objects
	for (int i=0; i < (int)arr.m_arr.GetCount(); i++)
		m_arr.Add(arr.Get(i)->Clone());
}

void wxScriptFunctionArray::Insert(wxScriptFunction *toadd, int idx)
{
	// always insert only one copy because we insert pointers and not
	// the objects itself; inserting twice the same memory address would
	// result in twice deletion of that same object !!!
	m_arr.Insert(toadd, idx, 1);
}

wxString wxScriptFunctionArray::GetName(int n) const
{
	wxString tmp = Get(n)->GetName();

	// remove the "prefix-to-strip" if present...
	if (tmp.Left(m_strToStrip.Len()) == m_strToStrip)
		tmp.Remove(0, m_strToStrip.Len());
	return tmp;
}

int wxScriptFunctionArray::GetIdx(const wxString &fncname, int n) const
{
	int occ = -1;
	for (int i=0; i < GetCount(); i++) {
		if (GetName(i) == fncname) {
			occ++;

			// is this the occurence we're looking for ?
			if (occ == n)
				return i;
		}
	}

	// not found
	return -1;
}

wxScriptFunction *wxScriptFunctionArray::Get(const wxString &fncname, int n) const
{
	int idx = GetIdx(fncname, n);

	if (idx >= 0)
		return Get(idx);
	return NULL;
}

int wxScriptFunctionArray::GetCountOf(const wxString &fncname) const
{
	int n=0;
	for (int i=0; i < GetCount(); i++)
		if (GetName(i) == fncname)
			n++;
	return n;
}

void wxScriptFunctionArray::Remove(int n)
{ 
	if (n < 0 || n >= GetCount())
		return;

	// we must delete the object
	delete Get(n);
	
	// and remove it from the array...
	m_arr.RemoveAt(n);
}

void wxScriptFunctionArray::Clear()
{
	for (int i=(int)m_arr.GetCount(); i > 0; i--)
		Remove(0);		// always remove the first: the array automatically shrinks

	// array should be already empty...
	m_arr.Clear();
}


