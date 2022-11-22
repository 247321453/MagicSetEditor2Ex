//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/reflect.hpp>
#include <map>

DECLARE_POINTER_TYPE(FontFile);

// ----------------------------------------------------------------------------- : FontFile

/// A word in a WordList
class FontFile : public IntrusivePtrVirtualBase {
public:
  FontFile();

  String name;

  String path;         ///< Path of font

  inline FontFileP clone() const { return make_intrusive<FontFile>(*this); }

  DECLARE_REFLECTION();
};

class FontManager {
public:
  FontManager();
  bool load(String name, String path);
  bool is_load(String name);
private:
  map<String, String> loaded_map;
};


/// The global locale object
extern FontManager font_manager;