/////////////////////////////////////////////////////////////////////////////
// Name:        httpbuilder.cpp
// Purpose:     wxHTTPBuilderStream
// Author:      Angelo Mandato
// Created:     2005/08/11
// RCS-ID:      $Id: httpbuilder.cpp 896 2009-02-25 23:52:52Z amandato $
// Copyright:   (c) 2002-2005 Angelo Mandato
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////


#ifdef __GNUG__
#pragma implementation "httpbuilder.h"
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
#endif

#include <wx/file.h>
#include <wx/sckstrm.h>
#include <wx/app.h>
#include <wx/tokenzr.h>
#include <wx/wfstream.h>
#include <wx/filename.h>
#include <wx/msgdlg.h>

#include <wx/httpbuilder.h>

// Include base64 functions if desired
#ifdef HTTPBUILDER_BASE64
  #include "wx/base64.h"
#endif



#include <stdlib.h>

wxProxySettings::wxProxySettings(const wxProxySettings& data)
{
    (*this) = data;
}

void wxProxySettings::operator=(const wxProxySettings& data)
{
	m_strProxyHostname = data.m_strProxyHostname;
	m_strProxyUsername = data.m_strProxyUsername;
	m_strProxyPassword = data.m_strProxyPassword;
	m_strProxyExceptions = data.m_strProxyExceptions; // exceptions list
	m_strProxyExceptionsDelim = data.m_strProxyExceptionsDelim; // delimiter of each exception
	m_bUseProxy = data.m_bUseProxy; // Toggles wether proxy settings should be used or not
  m_bRequiresAuth = data.m_bRequiresAuth;
	m_nProxyPort = data.m_nProxyPort;
}

#if wxUSE_CONFIG
void wxProxySettings::ProxySettingsLoad(wxConfigBase& config)
{
  m_bRequiresAuth = (config.Read(wxT("RequiresAuth"), m_bRequiresAuth) == 1);
  m_bUseProxy = (config.Read(wxT("UseProxy"), m_bUseProxy) == 1);
  m_nProxyPort = config.Read(wxT("ProxyPort"), m_nProxyPort);
  m_strProxyExceptions = config.Read(wxT("ProxyExceptions"), m_strProxyExceptions);
  m_strProxyExceptionsDelim = config.Read(wxT("ProxyExceptionsDelim"), m_strProxyExceptionsDelim);
  m_strProxyHostname = config.Read(wxT("ProxyHostname"), m_strProxyHostname);
  m_strProxyPassword = config.Read(wxT("ProxyPassword"), m_strProxyPassword);
  m_strProxyUsername = config.Read(wxT("ProxyUsername"), m_strProxyUsername);
}

void wxProxySettings::ProxySettingsSave(wxConfigBase& config) const
{
  config.Write(wxT("RequiresAuth"), (long)m_bRequiresAuth);
  config.Write(wxT("UseProxy"), (long)m_bUseProxy);
  config.Write(wxT("ProxyPort"), (long)m_nProxyPort);
  config.Write(wxT("ProxyExceptions"), m_strProxyExceptions);
  config.Write(wxT("ProxyExceptionsDelim"), m_strProxyExceptionsDelim);
  config.Write(wxT("ProxyHostname"), m_strProxyHostname);
  config.Write(wxT("ProxyUsername"), m_strProxyUsername);
  config.Write(wxT("ProxyPassword"), m_strProxyPassword);
}
#endif

wxHTTPAuthSettings::wxHTTPAuthSettings(const wxHTTPAuthSettings& data)
{
    (*this) = data;
}

void wxHTTPAuthSettings::operator=(const wxHTTPAuthSettings& data)
{
	m_strAuthUsername = data.m_strAuthUsername;
	m_strAuthPassword = data.m_strAuthPassword;
	m_bRememberPasswd = data.m_bRememberPasswd;
  m_authType = data.m_authType;
}

#if wxUSE_CONFIG
void wxHTTPAuthSettings::AuthSettingsLoad(wxConfigBase& config)
{
  m_authType = (wxHTTPAuthSettings::wxHTTP_Auth)config.Read(wxT("AuthType"), m_authType);
  m_bRememberPasswd = (config.Read(wxT("RememberPasswd"), m_authType) == 1);
  m_strAuthUsername = config.Read(wxT("AuthUsername"), m_strAuthUsername);
  m_strAuthPassword = config.Read(wxT("AuthPassword"), m_strAuthPassword);
}

void wxHTTPAuthSettings::AuthSettingsSave(wxConfigBase& config) const
{
  config.Write(wxT("AuthType"), (long)m_authType);
  config.Write(wxT("RememberPasswd"), (long)m_bRememberPasswd);
  config.Write(wxT("AuthUsername"), m_strAuthUsername);
  config.Write(wxT("AuthPassword"), m_strAuthPassword);
}
#endif

//! wxHTTPBuilderStream handles reading the data received from web server.
//! This class is typically not used outside of the wxHTTPEngine library.

//! wxHTTPBuilderStream constructor
class wxHTTPBuilderStream : public wxSocketInputStream
{
public:
  wxHTTP *m_http;
  size_t m_httpsize;
  unsigned long m_read_bytes;

  wxHTTPBuilderStream(wxHTTP *http) : wxSocketInputStream(*http), m_http(http) {}
  size_t GetSize() const { return m_httpsize; }
  virtual ~wxHTTPBuilderStream(void) { m_http->Abort(); }

protected:
  size_t OnSysRead(void *buffer, size_t bufsize);

    DECLARE_NO_COPY_CLASS(wxHTTPBuilderStream)
};

//! OnSysRead returns number total number bytes received and the buffer by reference
size_t wxHTTPBuilderStream::OnSysRead(void *buffer, size_t bufsize)
{
    if (m_httpsize > 0 && m_read_bytes >= m_httpsize)
    {
        m_lasterror = wxSTREAM_EOF;
        return 0;
    }

    size_t ret = wxSocketInputStream::OnSysRead(buffer, bufsize);
    m_read_bytes += ret;

    return ret;
}

//! wxHTTPBuilder Constructor
wxHTTPBuilder::wxHTTPBuilder()
  : wxHTTP()
{
  m_MultiPartCount = 0;
  //m_httpAuthSettings.m_authType = wxHTTPAuthSettings::wxHTTP_AUTH_NONE;
	// Should already be set in class when constructed
  m_Stop = false;
  m_bytesRead = 0;
  m_bytesSent = 0;
  UseHttpProxy(false);
}

//! wxHTTPBuilder Destructor
wxHTTPBuilder::~wxHTTPBuilder()
{
  // Nothing needs cleaned up, woohoo!
}

// Write returned content to a file.
// NOTE: This should be a temp folder, once this is downloaded you can
// look for the filename: header attribute and rename the file based on that
//! Save returned data as a file locally.  Returns true if successful.
bool wxHTTPBuilder::SaveFile(const wxString &filename, const wxString& url, const wxString& tempDirOrPrefix)
{
  wxInputStream *inp_stream = GetInputStream( url, tempDirOrPrefix );
  if( inp_stream == NULL )
    return false;

  wxFile file;
  file.Open( filename, wxFile::write );

  m_bytesRead = 0;
  wxChar buf[HTTPBUILDER_BUF_SIZE];

  while( true )
  {
    inp_stream->Read( buf, WXSIZEOF(buf) );
    file.Write( buf, inp_stream->LastRead() );

    int lastRead = inp_stream->LastRead();
    if( lastRead == 0 )
      break;

    AddBytesRead( lastRead );

    if( StopCheck() ) // For threads, they can stop this reading
      break;
  }
  file.Close();

  delete inp_stream;
  return true;
}

//! Send DELETE request.  Returns 20x/30x/40x/50x response code if successful.  Returns -1 if error.
int wxHTTPBuilder::GetDeleteResponse(const wxString &url)
{
  wxString szToReturn = wxT("");
  wxInputStream *inp_stream = GetInputStream(url, wxEmptyString, wxHTTP_DELETE);
  if( inp_stream == NULL )
    return -1; // There was an error

  m_bytesRead = 0;

  // we won't use a wxChar buffer here since the server replies in US/ASCII encoding
  char buf[HTTPBUILDER_BUF_SIZE];

	// read the rest of the string, if anything is there...
  while( true )
  {
    inp_stream->Read( buf, WXSIZEOF(buf) );
    int lastRead = inp_stream->LastRead();
    if( lastRead == 0 )
      break;

    AddBytesRead( lastRead );

    if( StopCheck() ) // For threads, they can stop this reading
      break;
  }

  delete inp_stream;
  inp_stream = NULL;

  return GetResponse();
}

int wxHTTPBuilder::GetPutResponse(const wxString &filename, const wxString &url )
{
	// First, get the size of the file...
	wxULongLong ulContentLength = wxFileName::GetSize(filename);
	if( ulContentLength == wxInvalidSize )
		return -1;
	
	// tell the server what the size of the file is we are sending
	SetHeader( wxT("Content-Length"), wxString::Format( wxT("%lu"), ulContentLength ) );
	
	wxString szToReturn = wxT("");
  wxInputStream *inp_stream = GetInputStream(url, wxEmptyString, wxHTTP_PUT, filename);
  if( inp_stream == NULL )
    return -1; // There was an error

	m_bytesRead = 0;

  // we won't use a wxChar buffer here since the server replies in US/ASCII encoding
	char buf[HTTPBUILDER_BUF_SIZE];

	// read the rest of the string, if anything is there...
  while( true )
  {
    inp_stream->Read( buf, WXSIZEOF(buf) );
    int lastRead = inp_stream->LastRead();
    if( lastRead == 0 )
      break;

    AddBytesRead( lastRead );

    if( StopCheck() ) // For threads, they can stop this reading
      break;
  }

  delete inp_stream;
  inp_stream = NULL;

  return GetResponse();
}

//! Send HEAD request.  Returns 20x/30x/40x/50x response code if successful.  Returns -1 if error.
int wxHTTPBuilder::GetHeadResponse(const wxString &url)
{
  wxString szToReturn = wxT("");
  wxInputStream *inp_stream = GetInputStream(url, wxEmptyString, wxHTTP_HEAD);
  if( inp_stream == NULL )
    return -1; // There was an error

  m_bytesRead = 0;

  // we won't use a wxChar buffer here since the server replies in US/ASCII encoding
  char buf[HTTPBUILDER_BUF_SIZE];

	// read the rest of the string, if anything is there...
  while( true )
  {
    inp_stream->Read( buf, WXSIZEOF(buf) );
    int lastRead = inp_stream->LastRead();
    if( lastRead == 0 )
      break;

    AddBytesRead( lastRead );

    if( StopCheck() ) // For threads, they can stop this reading
      break;
  }

  delete inp_stream;
  inp_stream = NULL;

  return GetResponse();
}

//! Returns an wxInputStream pointer to read information from the web server.
wxInputStream* wxHTTPBuilder::GetInputStream(const wxString& url, const wxString& tempDirOrPrefix, const wxHTTP_Req req, const wxString& put_file )
{
  wxHTTPBuilderStream *inp_stream = NULL;
  m_error = wxT("");

  int nPort = 0;
  wxString szProtocol;
  wxString szHost;
  wxString szRequest;
  wxString szUserName;
  wxString szPassword;

  if( !ParseURL( url, szProtocol, szHost, nPort, szRequest, szUserName, szPassword) )
  {
    m_error = wxT("Parsing URL");
    return NULL;
  }

  if( szUserName.IsNull() == false )
    Authenticate( szUserName, szPassword );

  m_perr = wxPROTO_CONNERR;

  if( m_proxySettings.m_bUseProxy && UseProxyForHost(szHost) )
    m_HttpProxyUsed = true;
 
  // We set m_connected back to false so wxSocketBase will know what to do.
  if( m_HttpProxyUsed )
  {
    if( !Connect(m_proxySettings.m_strProxyHostname, m_proxySettings.m_nProxyPort) )
    {
      m_error = wxT("Resolving proxy host name");
      return NULL;
    }
		
		SetHeader(wxT("Host"), szHost);
  }
  else
  {
    if( !Connect(szHost, nPort) )
    {
      m_error = wxT("Resolving host name");
      return NULL;
    }
  }

  if (!m_addr)
  {
    m_error = wxT("Resolving host name");
    return NULL;
  }

#ifdef __WXMAC__
  wxSocketClient::Connect(*m_addr , false );
  wxSocketClient::WaitOnConnect(10);

  if (!wxSocketClient::IsConnected())
    return NULL;
#else
  if (!wxProtocol::Connect(*m_addr))
  {
    m_error = wxT("Connecting to server");
    return NULL;
  }
#endif

  // Parse the path:
  wxString path = szRequest;
  if( m_HttpProxyUsed )
  {
    path = szProtocol;
    path += wxT("://");
    path += szHost;
    if( nPort != m_proxySettings.m_nProxyPort )
      path += wxString::Format(wxT(":%d"), nPort);
    path += szRequest;
  }

  if ( !SendRequest(path, tempDirOrPrefix, req, put_file) )
  {
    m_error = wxT("Sending Request");
    return NULL;
  }

  inp_stream = new wxHTTPBuilderStream(this);
	inp_stream->m_httpsize = GetContentLength();
  inp_stream->m_read_bytes = 0;

  Notify(false);
  //SetFlags(wxSOCKET_BLOCK | wxSOCKET_WAITALL); // This is not necessary
	
  return inp_stream;
}

//! returns the returned data from the web server as a string
wxString wxHTTPBuilder::GetInputString(const wxString &url, const wxString& tempDirOrPrefix)
{
  wxString szToReturn = wxT("");
  wxInputStream *inp_stream = GetInputStream(url, tempDirOrPrefix);
  if( inp_stream == NULL )
    return szToReturn; // There was an error

  m_bytesRead = 0;

  // we won't use a wxChar buffer here since the server replies in US/ASCII encoding
  char buf[HTTPBUILDER_BUF_SIZE];

  while( true )
  {
    inp_stream->Read( buf, WXSIZEOF(buf) );

    // convert from char -> wxChar
#if wxUSE_UNICODE
    szToReturn.Append( wxString(buf, wxConvUTF8), inp_stream->LastRead() );
#else
    szToReturn.Append( buf, inp_stream->LastRead() );
#endif

    int lastRead = inp_stream->LastRead();
    if( lastRead == 0 )
      break;

    AddBytesRead( lastRead );

    if( StopCheck() ) // For threads, they can stop this reading
      break;
  }

  delete inp_stream;
  inp_stream = NULL;
  return szToReturn;
}

//! Send just built HTTP request to web server.

//! NOTE: If you are using multipart post data (uploading files)
//! This function may take a while to return.  It is highly recommended
//! you write your application to use threads.
//! 
bool wxHTTPBuilder::SendRequest(const wxString &path, const wxString& tempDirOrPrefix, const wxHTTP_Req req, const wxString& put_file )
{
  wxHTTP_Req req_method = req;
  wxString szTempFile = wxEmptyString;
  wxString szPostBuf = wxEmptyString;
  wxInputStream *streamPost = NULL;
	wxInputStream *streamPut = NULL;

	if( req == wxHTTP_PUT )
	{
		streamPut = (wxInputStream*) new wxFileInputStream(put_file);
	}
  else if( m_MultiPartCount > 0 )
  {
    szTempFile = wxFileName::CreateTempFileName( tempDirOrPrefix  );
    streamPost = GetPostBufferStream(szTempFile);
  }
  else // Try to get post buffer as text, if empty, then we are working with a GET
    szPostBuf = GetPostBuffer();

	// As long as we are not posting data to the server, then we could have a GET or HEAD request
  if( !szPostBuf.IsEmpty() || streamPost )
    req_method = wxHTTP_POST;

  const wxChar *request; // Build the request here

  switch (req_method) {
		case wxHTTP_GET:
			request = wxT("GET");
			break;
		case wxHTTP_POST:
			request = wxT("POST");
			break;
		case wxHTTP_HEAD:
			request = wxT("HEAD");
			break;
		case wxHTTP_PUT:
			request = wxT("PUT");
			break;
		case wxHTTP_DELETE:
			request = wxT("DELETE");
			break;
		default:
			return false;
  }

  m_http_response = 0;
  if( m_httpAuthSettings.m_authType == wxHTTPAuthSettings::wxHTTP_AUTH_BASIC )
  {
    if ( GetHeader( wxT("Authorization") ).IsNull() )
    {
      wxString szBase64 = Base64Encode( wxString::Format(wxT("%s:%s"), m_httpAuthSettings.m_strAuthUsername.c_str(), m_httpAuthSettings.m_strAuthPassword.c_str() ) );
      SetHeader( wxT("Authorization"), wxString::Format( wxT("Basic %s"), szBase64.c_str() ) );
    }
  }

  if( m_HttpProxyUsed )
  {
    // Set Proxy Authentification if passed in...
    if ( GetHeader( wxT("Proxy-Authorization") ).IsNull() && m_proxySettings.m_bRequiresAuth)
    {
      wxString szBase64 = Base64Encode( wxString::Format(wxT("%s:%s"), m_proxySettings.m_strProxyUsername.c_str(), m_proxySettings.m_strProxyPassword.c_str() ) );
      SetHeader( wxT("Proxy-Authorization"), wxString::Format( wxT("Basic %s"), szBase64.c_str() ) );
    }
  }

  if( GetHeader(wxT("Cookie")).IsNull())
  {
    wxString szCookieValues = GetCookieString();
    if( szCookieValues.IsNull() == false )
      SetHeader(wxT("Cookie"), szCookieValues);
  }

  // If there is no User-Agent defined, define it.
  if (GetHeader(wxT("User-Agent")).IsNull())
  {
    wxString szUserAgent = wxT("wxHTTPBuilder ");
    szUserAgent += HTTPBUILDER_VERSION;
    SetHeader(wxT("User-Agent"), szUserAgent);
  }

  SaveState();

	// Changed by Angelo, The function call to SetFlags() should be specified by the designer of the application
	// Some cases you may want the gui to block , other cases you may not want to wait for data, etc...
	// this decision should be made by the programmer for its specific application

	// This information taken from the wxWidgets book, page 476:
	// There are 5 combinations you can pass to the SetFlags function
	//SetFlags(wxSOCKET_NONE|wxSOCKET_BLOCK) - Behaves like standard blocking socket calls (calls to recv and send).
	//SetFlags(wxSOCKET_NOWAIT) - Behaves like standard non-blocking socket calls.
	//SetFlags(wxSOCKET_WAITALL|wxSOCKET_BLOCK) - Behaves like standard blocking socket calls, except that the underlying
	// send or recv will be called repeatedly until all the data is sent or received.
	//SetFlags(wxSOCKET_NONE) - Behaves like standard socket calls except the GUI will not block because of continuous
	// calls to wxYield while the socket opeation is incomplete (for example, not all data has been read).
	//SetFlags(wxSOCKET_WAITALL) - Behaves like wxSOCKET_WAITALL|wxSOCKET_BLOCK except that the GUI will not block.

	// I highly recommend referring to the wxWidgets Book for further details: http://www.wxwidgets.org/book/index.htm

	// The last two methods should be used with extreme caution.  They are only useful when using the socket within the
	// primary thread (eg., not using the wxHTTPBuilderThread object)
	
	// Example usage for your application:
	//SetFlags( wxIsMainThread() && wxApp::IsMainLoopRunning() ? wxSOCKET_NOWAIT
  //                                                        : wxSOCKET_NONE|wxSOCKET_BLOCK );

  Notify(false);

  wxString query = GetQueryString( (req_method == wxHTTP_GET || req_method == wxHTTP_HEAD) ? true : false); // Get the query string of (GET) variables to send to server

  wxString buf;
  buf.Printf(wxT("%s %s%s HTTP/1.0\r\n"), request, path.c_str(), query.c_str() );
  const wxWX2MBbuf pathbuf = wxConvLocal.cWX2MB(buf);
  Write(pathbuf, strlen(wxMBSTRINGCAST pathbuf));
  SendHeaders();
  Write("\r\n", 2);		// NOTE: don't use the wxT() macro here - HTTP 1.1 uses US-ASCII (see RFC 2616)
  m_bytesSent = 0;

	if( streamPut )
	{
		// Loop through stream and write to socket
 		wxChar buf[HTTPBUILDER_BUF_SIZE];

    while( streamPut->Eof() == false )
    {
      streamPut->Read( buf, WXSIZEOF(buf) );
      Write( buf, streamPut->LastRead() );
      AddBytesSent( LastCount() );

      if( StopCheck() ) // For threads, they can stop this writing to the socket
        break;
    }
    delete streamPut;
    streamPut = NULL;
	}

  if( req_method == wxHTTP_POST )
  {
    if( streamPost )
    {
      // Loop through stream and write to socket
      wxChar buf[HTTPBUILDER_BUF_SIZE]; // 8192 is a good size, though in the future this size could be bigger on newer operating systems.
      while( streamPost->Eof() == false )
      {
        streamPost->Read( buf, WXSIZEOF(buf) );
        Write( buf, streamPost->LastRead() );
        AddBytesSent( LastCount() );

        if( StopCheck() ) // For threads, they can stop this writing to the socket
          break;
      }
      delete streamPost;
      streamPost = NULL;

      wxRemoveFile(szTempFile); // Delete the temp file
    }
    else if( szPostBuf.IsEmpty() == false )
    {
      Write(szPostBuf.mbc_str(), szPostBuf.Len());
      szPostBuf = wxEmptyString;
      AddBytesSent( LastCount() );
    }
  }

  wxString tmp_str;
  m_perr = GetLine(this, tmp_str);
  if (m_perr != wxPROTO_NOERR)
  {
    RestoreState();
    return false;
  }

  if (!tmp_str.Contains(wxT("HTTP/")))
  {
    SetHeader(wxT("Content-Length"), wxT("-1"));
    SetHeader(wxT("Content-Type"), wxT("none/none"));
    RestoreState();
    return true;
  }

  wxStringTokenizer token(tmp_str,wxT(' '));
  wxString tmp_str2;
  bool ret_value;

  token.NextToken();
  tmp_str2 = token.NextToken();

	m_http_response = wxAtoi(tmp_str2);
	ret_value = ParseHeaders(); // We want to parse the headers before we return true/false

  switch (tmp_str2[0u]) {
  case wxT('1'):
    // INFORMATION / SUCCESS
    break;
  case wxT('2'):
    // SUCCESS
    break;
  case wxT('3'):
    // REDIRECTION
    break;
	case wxT('4'):
		// File missing or something happened on server
		break;
  default: // a 500+ error occurred, we need to stop
    m_perr = wxPROTO_NOFILE;
    RestoreState();
    return false;
  }

  RestoreState();
  return ret_value;
}

//! Local call to encode string using base 64. HTTPBUILDER_BASE64 must be defined for this to work.
wxString wxHTTPBuilder::Base64Encode(const wxString &value)
{
  wxString szToReturn;
#ifdef HTTPBUILDER_BASE64
    szToReturn = wxBase64Encode(value);
#endif
  return szToReturn;
}

//! Local call to decode string using base 64.  HTTPBUILDER_BASE64 must be defined for this to work.
wxString wxHTTPBuilder::Base64Decode(const wxString &value)
{
  wxString szToReturn;
#ifdef HTTPBUILDER_BASE64
    szToReturn = wxBase64Decode(value);
#endif
  return szToReturn;
}

//! Convert an int to hex value.  For urlencoding namesa and values.
int wxHTTPBuilder::IntFromHex(const wxString &chars)
{
  int nHi;        // holds high byte
  int nLo;        // holds low byte

  // Get the value of the first byte to Hi
  nHi = chars.GetChar(0);
  if (wxT('0') <= nHi && nHi <= wxT('9'))
    nHi -= wxT('0');
  else if (wxT('a') <= nHi && nHi <= wxT('f'))
    nHi -= (wxT('a')-10);
  else if (wxT('A') <= nHi && nHi <= wxT('F'))
    nHi -= (wxT('A')-10);

  // Get the value of the second byte to Lo
  nLo = chars.GetChar(1);
  if (wxT('0') <= nLo && nLo <= wxT('9')) 
    nLo -= wxT('0');
  else if (wxT('a') <= nLo && nLo <= wxT('f')) 
    nLo -= (wxT('a')-10);
  else if (wxT('A') <= nLo && nLo <= wxT('F'))
    nLo -= (wxT('A')-10);
    
  return ( nLo + (16 * nHi) );
}

//! URL Decode a string.
wxString wxHTTPBuilder::URLDecode(const wxString &value, const bool &rfc1738)
{
  wxString szDecoded;
	wxString szEncoded = value;
    
  unsigned int nEncodedPos = 0;

  // eliminiate + and replace with spaces...
	if( !rfc1738 )
		szEncoded.Replace(wxT("+"), wxT(" "));

  while( nEncodedPos < szEncoded.length() )
  {
    if(szEncoded.GetChar(nEncodedPos)==wxT('%')) 
    {
      nEncodedPos++;
      if( wxIsxdigit(szEncoded.GetChar(nEncodedPos)) && wxIsxdigit(szEncoded.GetChar(nEncodedPos+1)) ) 
      {
        wxString szIntFromHex;
        szIntFromHex.Append( szEncoded.GetChar(nEncodedPos) );
        szIntFromHex.Append( szEncoded.GetChar(nEncodedPos+1) );
        szDecoded.Append( (wxChar) IntFromHex(szIntFromHex) );
        nEncodedPos += 2;
      }
    } 
    else 
    {
      szDecoded.Append(  szEncoded.GetChar(nEncodedPos++) );
    }
  }

  return szDecoded;
}

//! URL encode a string.
wxString wxHTTPBuilder::URLEncode(const wxString &value, const bool &rfc1738)
{
  wxString szToReturn = wxT("");
  unsigned int nPos = 0;

  while( value.length() > nPos ) 
  {
    wxChar cChar = value.GetChar(nPos);

		if( rfc1738 ) // Encode string according to http://www.faqs.org/rfcs/rfc1738
		{
			switch( (int)cChar )
			{
				// Numbers:
				case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
				// Letters:
				case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
				case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
				case 85: case 86: case 87: case 88: case 89: case 90: case 97: case 98: case 99: case 100:
				case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110:
				case 111: case 112: case 113: case 114: case 115: case 116: case 117: case 118: case 119: case 120:
				case 121: case 122:
				// Other punct (-._):
				case 45: case 46: case 95:
					{
						szToReturn.Append( cChar );
					}; break;
				default:
					{
						szToReturn.Append(wxT("%"));
						szToReturn += HexFromInt( cChar );
					}
			}
		}
		else
		{
			switch( (int)cChar )
			{
				// Numbers:
				case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
				// Letters:
				case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
				case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
				case 85: case 86: case 87: case 88: case 89: case 90: case 97: case 98: case 99: case 100:
				case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110:
				case 111: case 112: case 113: case 114: case 115: case 116: case 117: case 118: case 119: case 120:
				case 121: case 122:
				// Other punct (-_):
				case 45: case 95:

				case 32:  szToReturn.Append(wxT('+')); break;
#ifdef HTTPBUILDER_ENCODE_LN_WITH_CRLN

				case 12: szToReturn.Append(wxT("%0D%0A")); break;

#endif
				default:
				{
					szToReturn.Append(wxT("%"));
					szToReturn += HexFromInt( cChar );
				}
			}
		}
    nPos++;
  }
  return szToReturn;
}

//! Convert HEX value to an int.  For URL Decoding.
wxString wxHTTPBuilder::HexFromInt(const int &value)
{
  wxString szHexHolder;

  if( value < 16)
    szHexHolder.Printf(wxT("0%x"), value );
  else
    szHexHolder.Printf(wxT("%x"), value );

  return szHexHolder.MakeUpper();
}

//! Set a name:value pair to be sent to the web server.

//! type may be one of the following values:
//! wxHTTP_TYPE_POST, wxHTTP_TYPE_GET, wxHTTP_TYPE_FILE, wxHTTP_TYPE_MULTIPART, wxHTTP_TYPE_COOKIE, wxHTTP_TYPE_COOKIERAW
//! NOTE: wxHTTP_TYPE_ANY is not acceptable
bool wxHTTPBuilder::SetValue(const wxString &name, const wxString &value, wxHTTP_Type type )
{
  // 
  if( type == wxHTTP_TYPE_ANY )
    return false;

  int nPos = FindNamePosition( name, type );
  if( nPos != -1 )
  {
    m_Values[nPos] = value;
  }
  else
  {
    m_Types.Add(type);
    m_Fields.Add(name);
    m_Values.Add(value);
    if( type == wxHTTP_TYPE_FILE || type == wxHTTP_TYPE_MULTIPARTDATA )
      m_MultiPartCount++;
  }

  return true;
}

//! Gets the value of a specific name and type in the wxHTTPBuilder.  Returns empty string if not found.

//! type may be one of the following values:
//! wxHTTP_TYPE_POST, wxHTTP_TYPE_GET, wxHTTP_TYPE_FILE, wxHTTP_TYPE_MULTIPART, wxHTTP_TYPE_COOKIE, wxHTTP_TYPE_COOKIERAW
//! NOTE: wxHTTP_TYPE_ANY is not acceptable
wxString wxHTTPBuilder::GetValue(const wxString &name, wxHTTP_Type type )
{
  int nPos = FindNamePosition( name, type );
  if( nPos != -1 )
    return m_Values.Item(nPos);

  return wxEmptyString;
}

//! returns the index of the value in the internal fields array.  Returns -1 if not found
int wxHTTPBuilder::FindNamePosition(const wxString &name, wxHTTP_Type type )
{
  for( unsigned int pos = 0; pos < m_Types.Count(); pos++ )
  {
    switch( type )
    {
      case wxHTTP_TYPE_POST: 
      case wxHTTP_TYPE_GET:
      case wxHTTP_TYPE_FILE:
      case wxHTTP_TYPE_MULTIPARTDATA:
        if( m_Types.Item(pos) != type )
          break;

      case wxHTTP_TYPE_ANY:

        if( m_Fields.Item(pos) == name )
          return pos;
        break;

      case wxHTTP_TYPE_COOKIE:
        if( m_Fields.Item(pos) == name )
          return pos;
        break;
      case wxHTTP_TYPE_COOKIERAW:
        if( m_Fields.Item(pos) == name )
          return pos;
        break;
    }
  }

  return -1;
}

//! Get the query string (GET string) urlencoded from the wxHTTPBuilder object.
wxString wxHTTPBuilder::GetQueryString(bool includeAny)
{
  wxString szToReturn = wxT("");

  for( unsigned int nPos = 0; nPos < m_Types.Count(); nPos++ )
  {
    if( m_Types.Item(nPos) == wxHTTP_TYPE_GET )
    {
      if( szToReturn.IsEmpty() )
        szToReturn += wxT("?");
      else
        szToReturn += wxT("&");

      szToReturn += URLEncode( m_Fields.Item(nPos) );
      szToReturn += wxT("=");
      szToReturn += URLEncode( m_Values.Item(nPos) );
    }
    else if( includeAny && m_Types.Item(nPos) == wxHTTP_TYPE_ANY )
    {
      if( szToReturn.IsEmpty() )
        szToReturn += wxT("?");
      else
        szToReturn += wxT("&");

      szToReturn += URLEncode( m_Fields.Item(nPos) );
      szToReturn += wxT("=");
      szToReturn += URLEncode( m_Values.Item(nPos) );
    }
  }

  return szToReturn;
}

//! Get the entire post buffer (POST string may be urlencoded or multipart post data) as an entire string.
wxString wxHTTPBuilder::GetPostBuffer()
{
  wxString szToReturn = wxT("");
  // Check if there are any post variables
  if( m_Types.Index( wxHTTP_TYPE_POST ) == -1 ) // We do not have to check for wxHTTP_TYPE_FILE
    return szToReturn; // since we would not call GetPostBuffer() otherwise

  for( unsigned int nPos = 0; nPos < m_Types.Count(); nPos++ )
  {
    if( m_Types.Item(nPos) == wxHTTP_TYPE_POST || m_Types.Item(nPos) == wxHTTP_TYPE_ANY )
    {
      if( !szToReturn.IsEmpty() )
        szToReturn += wxT("&");

      szToReturn += URLEncode( m_Fields.Item(nPos) );
      szToReturn += wxT("=");
      szToReturn += URLEncode( m_Values.Item(nPos) );
    }
  }

  if ( GetHeader( wxT("Content-Length") ).IsNull() )
    SetHeader( wxT("Content-Length"), wxString::Format( wxT("%lu"), (unsigned long)szToReturn.Length() ) );
  if ( GetHeader( wxT("Content-Type") ).IsNull() )
    SetHeader( wxT("Content-Type"), wxT("application/x-www-form-urlencoded") );

  return szToReturn;
}

//! Remove a name:value pair by name and type

//! type may be one of the following values:
//! wxHTTP_TYPE_POST, wxHTTP_TYPE_GET, wxHTTP_TYPE_FILE, wxHTTP_TYPE_MULTIPART, wxHTTP_TYPE_COOKIE, wxHTTP_TYPE_COOKIERAW
//! NOTE: wxHTTP_TYPE_ANY is not acceptable
bool wxHTTPBuilder::RemoveValue(wxString &name, wxHTTP_Type type)
{
  if( type == wxHTTP_TYPE_ANY )
    return false;

  int nPos = FindNamePosition( name, type );
  if( nPos != -1 )
  {
    if( m_Types.Item(nPos) == wxHTTP_TYPE_FILE || m_Types.Item(nPos) == wxHTTP_TYPE_MULTIPARTDATA )
      m_MultiPartCount--;
    m_Types.RemoveAt(nPos);
    m_Fields.RemoveAt(nPos);
    m_Values.RemoveAt(nPos);
  }

  return true;
}

//! Set the HTTP basic authentication.  type may only be wxHTTPAuthSettings::wxHTTP_AUTH_NONE or  wxHTTPAuthSettings::wxHTTP_AUTH_BASIC
void wxHTTPBuilder::Authenticate(const wxString &user, const wxString &password, wxHTTPAuthSettings::wxHTTP_Auth type)
{
  m_httpAuthSettings.m_strAuthUsername = user;
  m_httpAuthSettings.m_strAuthPassword = password;
  m_httpAuthSettings.m_authType = type;
}

//! Get the to be posted information as a wxInputStream.
wxInputStream* wxHTTPBuilder::GetPostBufferStream(const wxString &szTempFile)
{
  // Get a temp filename, then build 
  wxString szBoundary = CreateBoundary(HTTPBUILDER_BOUNDARY_LENGTH);
  unsigned long nContentLength = 0;
  wxOutputStream *out = (wxOutputStream*) new wxFileOutputStream(szTempFile);

  // Write each post variable here:
  for( unsigned int nPos = 0; nPos < m_Types.Count(); nPos++ )
  {
    if( m_Types.Item(nPos) == wxHTTP_TYPE_POST || m_Types.Item(nPos) == wxHTTP_TYPE_ANY )
    {
      wxString szToWrite = wxString::Format(wxT("--%s\r\nContent-Disposition: form-data; name=\"%s\"\r\n\r\n%s\r\n"), 
          szBoundary.c_str(), m_Fields.Item(nPos).c_str(), m_Values.Item(nPos).c_str() );
      out->Write( szToWrite, szToWrite.Length() );
    }
    else if( m_Types.Item(nPos) == wxHTTP_TYPE_FILE )
    {
      // Content-Disposition: form-data; name=wxT("file"); filename="D:\Angelo\FileReflector\latest.jpg"

      // Set the multipart header here:
      wxString szFileName = m_Values.Item(nPos);
      wxString szContentType = GetContentType( szFileName );

      wxString szToWrite = wxString::Format(wxT("--%s\r\nContent-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\nContent-Type: %s\r\n\r\n"), 
          szBoundary.c_str(), m_Fields.Item(nPos).c_str(), m_Values.Item(nPos).c_str(), szContentType.c_str() );
      out->Write( szToWrite, szToWrite.Length() );

      // Read the file and write it into the out file:
      wxFileInputStream *fin = new wxFileInputStream(szFileName);
    
      wxChar buf[HTTPBUILDER_BUF_SIZE];
      while( fin && fin->Eof() == false )
      {
        fin->Read( buf, WXSIZEOF(buf) );
        out->Write( buf, fin->LastRead() );

        if( StopCheck() ) // For threads, they can stop this writing to buffer
          break;
      }

      delete fin;

      // End with a CRLN
      out->Write( wxT("\r\n"), 2 );
    }
    else if( m_Types.Item(nPos) == wxHTTP_TYPE_MULTIPARTDATA )
    {
      // Write custom multipart data section here:
      wxString szMultipartData = m_Values.Item(nPos);

      wxString szToWrite = wxString::Format(wxT("--%s\r\n%s"), 
          szBoundary.c_str(), szMultipartData.c_str() ); 
      out->Write( szToWrite, szToWrite.Length() );
      AddBytesSent( out->LastWrite() );

      // End with a CRLN
      out->Write( wxT("\r\n"), 2 );
    }
  }

  // End the posted data:
  wxString szToWrite = wxString::Format(wxT("--%s--\r\n"), szBoundary.c_str());
  out->Write( szToWrite, szToWrite.Length() );
	AddBytesSent( out->LastWrite() );
  nContentLength = out->GetSize(); // Get the size of the file before we close it
  delete out; // Close the stream

  // IF all is good, lets set the content-type and content-length here:
  wxString szContentType = wxT("multipart/form-data; boundary=");
  szContentType += szBoundary;

  if ( GetHeader( wxT("Content-Length") ).IsNull() )
    SetHeader( wxT("Content-Length"), wxString::Format( wxT("%lu"), (unsigned long)nContentLength ) );
  if ( GetHeader( wxT("Content-Type") ).IsNull() )
    SetHeader( wxT("Content-Type"), szContentType );

  return (wxInputStream*) new wxFileInputStream(szTempFile);
}

void wxHTTPBuilder::SRand()
{
#ifdef __WXWINCE__
    srand((unsigned) CeGetRandomSeed());
#else
    srand((unsigned) time(NULL));
#endif
}

int wxHTTPBuilder::Rand()
{
  return rand();
}

//! Create a random boundary of a specific lenght for use with a multipart post.
wxString wxHTTPBuilder::CreateBoundary(const int length)
{
  wxString szToReturn = wxT("");

  for( int x = 0; x < length; x++ )
  {
    if( x < 2 )
    {
      szToReturn.Append(wxT('-'));
    }
    else if( x < (length/3 *2) )
    {
      szToReturn.Append(wxT('-'));
    }
    else
    {
      wxChar c = 0;
      while( !wxIsalnum(c) )
        c = wxHTTPBuilder::Rand() % 96 + 32;

      szToReturn.Append(c);
    }
  }
  return szToReturn;
}

bool wxHTTPBuilder::ParseHeaders()
{
	m_rawHeaders.Empty();
	wxString line;
  wxStringTokenizer tokenzr;

  ClearHeaders();
  m_read = true;

#if defined(__VISAGECPP__)
// VA just can't stand while(1)
  bool bOs2var = true;
  while(bOs2var)
#else
  while (1)
#endif
  {
    m_perr = ReadLine(this, line);
    if (m_perr != wxPROTO_NOERR)
      return false;

    if (line.Length() == 0)
      break;
		if( !m_rawHeaders.IsEmpty() )
			m_rawHeaders += wxT("\r\n");
		m_rawHeaders += line;

    wxString left_str = line.BeforeFirst(':');
    m_headers[left_str] = line.AfterFirst(':').Strip(wxString::both);
  }
  return true;
}

//! Return specified string with the html special characters encoded.  Similar to PHP's htmlspecialchars() function.
wxString wxHTTPBuilder::HTMLSpecialChars( const wxString &value, const bool bSingleQuotes, const bool bDoubleQuotes )
{
  wxString szToReturn = value;
  szToReturn.Replace(wxT("&"),wxT("&amp;"));
  if( bSingleQuotes )
    szToReturn.Replace(wxT("'"),wxT("&#039;"));
  if( bDoubleQuotes )
    szToReturn.Replace(wxT("\""), wxT("&quot;"));
  szToReturn.Replace(wxT("<"),wxT("&lt;"));
  szToReturn.Replace(wxT(">"),wxT("&gt;"));
  return szToReturn;
}

//! Set a cookie name:value pair in the wxHTTPBuilder object.  set urlencode = false if you do not want the value to be encoded.  The value will be escaped exactly how PHP escapes cookies if urlencode = false
bool wxHTTPBuilder::SetRequestCookie(const wxString &name, const wxString &value, const bool urlencode)
{
  wxHTTP_Type type = wxHTTP_TYPE_COOKIERAW;
  wxString szValue = value;
  wxString szName = name;

  if( szName.Find(wxT('=')) != -1 )
    return false;
  if( szName.Find(wxT(',')) != -1 )
    return false;
  if( szName.Find(wxT(';')) != -1 )
    return false;
  if( szName.Find(wxT(' ')) != -1 )
    return false;
  if( szName.Find(wxT('\t')) != -1 )
    return false;
  if( szName.Find(wxT('\r')) != -1 )
    return false;
  if( szName.Find(wxT('\n')) != -1 )
    return false;
  if( szName.Find(wxT('\013')) != -1 )
    return false;
  if( szName.Find(wxT('\014')) != -1 )
    return false;
  
  if( urlencode )
  {
    type = wxHTTP_TYPE_COOKIE;
  }
  else
  {
    if( szValue.Find(wxT('=')) != -1 )
      return false;
    if( szValue.Find(wxT(',')) != -1 )
      return false;
    if( szValue.Find(wxT(';')) != -1 )
      return false;
    if( szValue.Find(wxT(' ')) != -1 )
      return false;
    if( szValue.Find(wxT('\t')) != -1 )
      return false;
    if( szValue.Find(wxT('\r')) != -1 )
      return false;
    if( szValue.Find(wxT('\n')) != -1 )
      return false;
    if( szValue.Find(wxT('\013')) != -1 )
      return false;
    if( szValue.Find(wxT('\014')) != -1 )
      return false;
  }

  return SetValue( szName, szValue, type );
}

//! Get the eintire cookie string to be sent to the web server.
wxString wxHTTPBuilder::GetCookieString()
{
  wxString szToReturn = wxT("");

  for( unsigned int nPos = 0; nPos < m_Types.Count(); nPos++ )
  {
    if( m_Types.Item(nPos) == wxHTTP_TYPE_COOKIE )
    {
      if( !szToReturn.IsEmpty() )
        szToReturn += wxT("; ");

      szToReturn += m_Fields.Item(nPos);
      szToReturn += wxT("=");
      szToReturn += URLEncode( m_Values.Item(nPos) );
    }
    else if( m_Types.Item(nPos) == wxHTTP_TYPE_COOKIERAW )
    {
      if( !szToReturn.IsEmpty() )
        szToReturn += wxT("; ");

      szToReturn += m_Fields.Item(nPos);
      szToReturn += wxT("=");
      szToReturn += m_Values.Item(nPos);
    }
  }

  return szToReturn;
}

//! Get content length, returns -1 if not found
int wxHTTPBuilder::GetContentLength()
{
	if (!GetHeader(wxT("Content-Length")).IsEmpty())
    return wxAtoi(WXSTRINGCAST GetHeader(wxT("Content-Length")));
	return -1;
}

//! Parse a given URL into its parts (by reference).  Returns true if successful.
bool wxHTTPBuilder::ParseURL(const wxString &url, wxString &protocol, wxString &host, int &port, wxString &request, wxString &username, wxString &password)
{
  wxString temp = url;
  int pos;

  // Find end
  pos = temp.Find(wxT(':'));
  if (pos == wxNOT_FOUND)
    return false;

  protocol = temp(0, pos);
  temp = temp(pos+1, temp.Length());

  if ((temp.GetChar(0) != wxT('/')) || (temp.GetChar(1) != wxT('/')))
    return false;

  temp = temp(2, temp.Length()); // We ust parsed out the wxT("http://"), leaving: "user:pass@host:port/request/dir/file.ext"
  pos = temp.Find(wxT('/'));
  if (pos == wxNOT_FOUND)
  {
    request = wxT("/"); // Default root path is "/"
    temp = temp(0, pos); // leaving: "user:pass@host:port"
  }
  else
  {
    request = temp.Mid(pos); // parsed out: "/request/dir/file.ext"
    temp = temp(0, pos); // leaving: "user:pass@host:port"
  }

  if (pos == 0)
    return false;

  // Fixed logic here on 02/05/2005
  pos = temp.Find(wxT("@"));
  if(pos != wxNOT_FOUND)
  {
    wxString szAuth = temp(0,pos); // parsing out: "user:pass"
    temp = temp.Mid(pos+1); // leaving: "host:port"

    pos = szAuth.Find(wxT(":"));
    if( pos != wxNOT_FOUND )
    {
      password = szAuth.Mid(pos+1);
      username = szAuth(0,pos);
    }
    else
      username = szAuth;
  }

  // left: "host:port"
  pos = temp.Find(wxT(":"));
  if( pos != wxNOT_FOUND )
  {
    port = wxAtoi(temp.Mid(pos+1).c_str());
    host = temp(0,pos);
  }
  else
  {
    host = temp;
    if( protocol == wxT("http") )
      port = 80;
    else if( protocol == wxT("https") )
      port = 443;
    else
      port = 80;
  }

  // Maybe in the future we can separate the query string and anchor
  return true;
}

//! Specify a HTTP proxy server and port
void wxHTTPBuilder::HttpProxy(const wxString &host, const int port)
{
  UseHttpProxy(true);
  m_proxySettings.m_strProxyHostname = host;
  m_proxySettings.m_nProxyPort = port;
}

//! remove specific content type from list of content types.
bool wxHTTPBuilder::RemoveContentType( const wxString &abv )
{
  int pos = m_ContentTypeAbvs.Index( abv, false ); // Extensions are not case sensative
  if( pos == wxNOT_FOUND )
    return false;

  m_ContentTypeAbvs.RemoveAt(pos);
  m_ContentTypeDescs.RemoveAt(pos);
  return true;
}

//! Get the content type value of a specific file. Looks at the extension.
wxString wxHTTPBuilder::GetContentType(const wxString &filename)
{
  wxString abv;
  wxFileName::SplitPath(filename, NULL, NULL, NULL, &abv );
  int pos = m_ContentTypeAbvs.Index( abv, false ); // Extensions are not case sensative
  if( pos == wxNOT_FOUND )
    return wxT("application/octet-stream");

  return m_ContentTypeDescs.Item(pos);
}

//! Initialize a popular set of content types used with HTTP.
void wxHTTPBuilder::InitContentTypes()
{
  AddContentType( wxT("txt"), wxT("text/plain"));
  AddContentType( wxT("html"), wxT("text/html"));
  AddContentType( wxT("htm"), wxT("text/html"));
  AddContentType( wxT("gif"), wxT("image/gif"));
  AddContentType( wxT("jpg"), wxT("image/jpeg"));
  AddContentType( wxT("jpeg"), wxT("image/jpeg"));
  AddContentType( wxT("bmp"), wxT("image/bmp"));
  AddContentType( wxT("avi"), wxT("video/avi"));
  AddContentType( wxT("mpeg"), wxT("video/mpeg"));
  AddContentType( wxT("mpg"), wxT("video/mpeg"));
  AddContentType( wxT("pdf"), wxT("application/pdf"));
  AddContentType( wxT("zip"), wxT("application/zip"));
}

// Get the response string, such as "404 Not Found"
wxString wxHTTPBuilder::GetResponseString(void)
{
  return wxString::Format( wxT("%d %s"), m_http_response, GetStatusCode().c_str() );
}

//! Get the returned status code, such as 404 (for not found)
wxString wxHTTPBuilder::GetStatusCode(void)
{
  switch( m_http_response )
  {
    // According to http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
    // 1xx Informational:
    case 100:  return wxT("Continue"); break;
    case 101:  return wxT("Switching Protocols"); break;

    // 2xx successful:
    case 200:  return wxT("OK"); break;
    case 201:  return wxT("Created"); break;
    case 202:  return wxT("Accepted"); break;
    case 203:  return wxT("Non-Authoritative Information"); break;
    case 204:  return wxT("No Content"); break;
    case 205:  return wxT("Reset Content"); break;
    case 206:  return wxT("Partial Content"); break;

    // 3xx redirection:
    case 300:  return wxT("Multiple Choices"); break;
    case 301:  return wxT("Moved Permanently"); break;
    case 302:  return wxT("Found"); break;
    case 303:  return wxT("See Other"); break;
    case 304:  return wxT("Not Modified"); break;
    case 305:  return wxT("Use Proxy"); break;
    case 307:  return wxT("Temporary Redirect"); break;

    // 4xx errors:
    case 400:  return wxT("Bad Request"); break;
    case 401:  return wxT("Unauthorized"); break;
    case 402:  return wxT("Payment Required"); break;
    case 403:  return wxT("Forbidden"); break;
    case 404:  return wxT("Not Found"); break;
    case 405:  return wxT("Method Not Allowed"); break;
    case 406:  return wxT("Not Acceptable"); break;
    case 407:  return wxT("Proxy Authentication Required"); break;
    case 408:  return wxT("Request Timeout"); break;
    case 409:  return wxT("Conflict"); break;
    case 410:  return wxT("Gone"); break;
    case 411:  return wxT("Length Required"); break;
    case 412:  return wxT("Precondition Failed"); break;
    case 413:  return wxT("Request Entity Too Large"); break;
    case 414:  return wxT("Request-URI Too Long"); break;
    case 415:  return wxT("Unsupported Media Type"); break;
    case 416:  return wxT("Requested Range Not Satisfiable"); break;
    case 417:  return wxT("Expectation Failed"); break;

    // 5xx Internal Server Error:
    case 500:  return wxT("Internal Server Error"); break;
    case 501:  return wxT("Not Implemented"); break;
    case 502:  return wxT("Bad Gateway"); break;
    case 503:  return wxT("Service Unavailable"); break;
    case 504:  return wxT("Gateway Timeout"); break;
    case 505:  return wxT("HTTP Version Not Supported"); break;

    default:  ; break;
  }
  return wxT("Unknown");
}

//! Checks to see if the wxHTTPBuilder should use the proxy server for the specified host.
bool wxHTTPBuilder::UseProxyForHost(const wxString &host)
{
	wxArrayString astrProxyExceptions;
  wxString buf = m_proxySettings.m_strProxyExceptions;

	int nFound = buf.Find(m_proxySettings.m_strProxyExceptionsDelim);

	while( nFound != wxNOT_FOUND )
	{
    wxString value = buf.Left( nFound );
    value.Trim(false);
    value.Trim(true);
    if( !value.IsEmpty() )
      astrProxyExceptions.Add(value);
		
    buf.Remove(0, nFound + m_proxySettings.m_strProxyExceptionsDelim.Length() );
		nFound = buf.Find(m_proxySettings.m_strProxyExceptionsDelim);
	}

  buf.Trim(false);
  buf.Trim(true);
  if( !buf.IsEmpty() )
	  astrProxyExceptions.Add( buf );
	
	// Now check the array for the host that should not use the proxy server
  wxString szHostToCheck = host.Lower();

  // Go through the list of host names, if the host names end with any of the items in the array, return false
  for( unsigned long pos = 0; pos < astrProxyExceptions.GetCount(); pos++)
  {
    wxString szHost = astrProxyExceptions.Item(pos);
    if( szHostToCheck.Length() >= szHost.Length() )
    {
      // Hostname ends with host:
      if( szHostToCheck.Mid( szHostToCheck.Length()-szHost.Length() ) == szHost.Lower() )
        return false;
    }
  }

  return true;
}

//! Send HEAD request.  Returns 20x/30x/40x/50x response code if successful.  Returns -1 if error.
wxProxySettings wxHTTPBuilder::GetProxySettings()
{
	return m_proxySettings;
}

//! Send HEAD request.  Returns 20x/30x/40x/50x response code if successful.  Returns -1 if error.
void wxHTTPBuilder::SetProxySettings(const wxProxySettings &settings)
{
	m_proxySettings = settings;
	m_HttpProxyUsed = false; // Reset the internal flag
}

// eof
