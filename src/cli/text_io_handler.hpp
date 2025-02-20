//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>

// ----------------------------------------------------------------------------- : Text I/O handler

// color codes
extern const Char *BRIGHT, *NORMAL, *PARAM, *FILE_EXT, *GRAY, *RED, *ENDL;

/// Command line input / output handler
class TextIOHandler {
public:
  void init();
  
  /// Do we have a console to read/write from/to?
  bool haveConsole() const;
  
  /// Output text to the console
  TextIOHandler& operator << (const Char*);
  TextIOHandler& operator << (const String&);
  TextIOHandler& operator << (const int);
  
  /// Read a line from stdin
  String getLine();
  /// Can another line be got?
  bool canGetLine();
  
  /// Flush output
  void flush();
  
  /// Show an error or warning message
  void show_message(MessageType type, String const& message);
  void print_pending_errors();
  bool shown_errors() const;
  
  /// Enable raw mode
  void enableRaw();
  /// Output a single raw-mode record
  /// Has no effect unless enableRaw() was called
  void flushRaw();
  
private:
  bool have_console;
  bool escapes;
  FILE* stream; ///< Output stream
  String buffer; ///< Buffer when not writing to console
  bool raw_mode;
  int raw_mode_status;
  bool encountered_errors = false;
};

/// The global TextIOHandler object
extern TextIOHandler cli;

