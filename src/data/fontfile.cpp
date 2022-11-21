//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <data/fontfile.hpp>

// ----------------------------------------------------------------------------- : WordList

FontFile::FontFile()
{}

IMPLEMENT_REFLECTION_NO_SCRIPT(FontFile) {
    REFLECT(path);
}

void after_reading(FontFile& ar, Version) {
}