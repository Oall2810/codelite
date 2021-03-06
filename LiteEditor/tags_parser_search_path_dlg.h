//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2013 by Eran Ifrah
// file name            : tags_parser_search_path_dlg.h
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef __tags_parser_search_path_dlg__
#define __tags_parser_search_path_dlg__

/**
@file
Subclass of TagsParserSearchPathsBaseDlg, which is generated by wxFormBuilder.
*/

#include "tagsparsersearchpathsbasedlg.h"

/** Implementing TagsParserSearchPathsBaseDlg */
class TagsParserSearchPathsDlg : public TagsParserSearchPathsBaseDlg
{
public:
	/** Constructor */
	TagsParserSearchPathsDlg( wxWindow* parent, const wxArrayString &paths, const wxArrayString &excludePaths );
	virtual ~TagsParserSearchPathsDlg();

	wxArrayString GetSearchPaths() const;
	wxArrayString GetExcludePath() const;
	
};

#endif // __tags_parser_search_path_dlg__
