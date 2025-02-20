//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/tagged_string.hpp>
#include <data/format/formats.hpp>
#include <data/set.hpp>
#include <data/card.hpp>
#include <data/stylesheet.hpp>
#include <data/settings.hpp>
#include <render/card/viewer.hpp>
#include <wx/filename.h>
#include <gfx/gfx.hpp>

// ----------------------------------------------------------------------------- : Single card export

void export_image(const SetP& set, const CardP& card, const String& filename, int quality, int out_width, int out_height) {
  Image in = export_bitmap(set, card).ConvertToImage();
  in.SetOption(wxIMAGE_OPTION_QUALITY, quality);
  Image out;
  if (out_width > 0 && out_height > 0) {
      out = resample(in, out_width, out_height);
      if (in.GetWidth() != out_width && in.GetHeight() != out_height) {
          in.Destroy();
      }
      out.SetOption(wxIMAGE_OPTION_QUALITY, quality);
  }
  else {
      out = in;
  }
  out.SaveFile(filename);  // can't use Bitmap::saveFile, it wants to know the file type
              // but image.saveFile determines it automagicly
  out.Destroy();
}

class UnzoomedDataViewer : public DataViewer {
public:
  UnzoomedDataViewer(bool use_zoom_settings)
    : use_zoom_settings(use_zoom_settings)
  {}
  Rotation getRotation() const override;
private:
  bool use_zoom_settings;
  double zoom  = 1.0;
  double angle = 0.0;
};
Rotation UnzoomedDataViewer::getRotation() const {
  if (use_zoom_settings) {
    return DataViewer::getRotation();
  } else {
    if (!stylesheet) stylesheet = set->stylesheet;
    return Rotation(angle, stylesheet->getCardRect(), zoom, 1.0, ROTATION_ATTACH_TOP_LEFT);
  }
}

Bitmap export_bitmap(const SetP& set, const CardP& card) {
  if (!set) throw Error(_("no set"));
  // create viewer
  UnzoomedDataViewer viewer(!settings.stylesheetSettingsFor(set->stylesheetFor(card)).card_normal_export());
  viewer.setSet(set);
  viewer.setCard(card);
  // size of cards
  RealSize size = viewer.getRotation().getExternalSize();
  // create bitmap & dc
  Bitmap bitmap((int) size.width, (int) size.height);
  if (!bitmap.Ok()) throw InternalError(_("Unable to create bitmap"));
  wxMemoryDC dc;
  dc.SelectObject(bitmap);
  // draw
  viewer.draw(dc);
  dc.SelectObject(wxNullBitmap);
  return bitmap;
}

// ----------------------------------------------------------------------------- : Multiple card export


void export_images(const SetP& set, const vector<CardP>& cards,
                   const String& path, const String& filename_template, FilenameConflicts conflicts,
                   int quality, int out_width, int out_height)
{
  wxBusyCursor busy;
  // Script
  ScriptP filename_script = parse(filename_template, nullptr, true);
  // Path
  wxFileName fn(path);
  // Export
  std::set<String> used; // for CONFLICT_NUMBER_OVERWRITE
  FOR_EACH_CONST(card, cards) {
    // filename for this card
    Context& ctx = set->getContext(card);
    String filename = clean_filename(untag(ctx.eval(*filename_script)->toString()));
    if (!filename) continue; // no filename -> no saving
    // full path
    fn.SetFullName(filename);
    // does the file exist?
    if (!resolve_filename_conflicts(fn, conflicts, used)) continue;
    // write image
    filename = fn.GetFullPath();
    used.insert(filename);
    export_image(set, card, filename, quality, out_width, out_height);
  }
}
