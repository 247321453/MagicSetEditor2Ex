//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/reflect.hpp>

DECLARE_POINTER_TYPE(FontFile);

// ----------------------------------------------------------------------------- : FontFile

/// A word in a WordList
class FontFile : public IntrusivePtrVirtualBase {
public:
	FontFile();

	String path;         ///< Path of font

	inline FontFileP clone() const { return make_intrusive<FontFile>(*this); }

	DECLARE_REFLECTION();
};

void after_reading(FontFile& ar, Version);