//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <data/fontfile.hpp>
#include <wx/file.h>
// ----------------------------------------------------------------------------- : WordList

FontFile::FontFile()
{}

IMPLEMENT_REFLECTION_NO_SCRIPT(FontFile) {
    REFLECT(name);
    REFLECT(path);
}

FontManager::FontManager() {}

bool FontManager::is_load(String name) {
  if (!name) {
    return false;
  }
  auto result = loaded_map.find(name);
  if (result != loaded_map.end()) {
    return true;
  }
  return false;
}

bool FontManager::load(String name, String path) {
  if (is_load(name)) {
    return true;
  }
  bool ret;
  if (wxFile::Exists(path)) {
    ret = wxFont::AddPrivateFont(path);
    if (ret) {
      loaded_map[name] = path;
    }
  }
  else {
    ret = false;
  }
  return ret;
}

FontManager font_manager;