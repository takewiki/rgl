#ifndef X11_GUI_HPP
#define X11_GUI_HPP
// ---------------------------------------------------------------------------
// C++ header file
// This file is part of RGL
//
// $Id: x11gui.hpp 976 2013-10-04 15:06:19Z murdoch $
// ---------------------------------------------------------------------------
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <map>
#include "gui.hpp"

namespace rgl {

// ---------------------------------------------------------------------------
class X11WindowImpl;
enum {
  GUI_X11_ATOM_WM_DELETE = 0,
  GUI_X11_ATOM_LAST
};
// ---------------------------------------------------------------------------
class X11GUIFactory : public GUIFactory
{
public:
  X11GUIFactory (const char* displayname);
  virtual ~X11GUIFactory ();
  WindowImpl* createWindowImpl(Window* window);
  inline bool isConnected() { return (xdisplay) ? true : false; }
  inline int  getFD()     { return ConnectionNumber(xdisplay); }
  
  void notifyDelete(::Window xwindowid);
  
  // implementation services:
  
  void processEvents();
  void flushX();
  
  // display specific:
  
  Display* xdisplay;
  
  ::Atom atoms[GUI_X11_ATOM_LAST];
  
  // GLX specific
  int errorBase, eventBase;
  
  // Font specific
  XFontStruct* xfont;
  
  void throw_error(const char* string);
private:

  void connect(const char* displayname);
  void disconnect();

  // administrative data:

  typedef std::map< XID , X11WindowImpl*> WindowMap;
  
  WindowMap windowMap;
};
// ---------------------------------------------------------------------------

} // namespace rgl

#endif // X11_GUI_HPP

