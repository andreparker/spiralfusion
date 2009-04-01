/*
 * SDLmm - a C++ wrapper for SDL and related libraries
 * Copyright � 2001 David Hedbor <david@hedbor.org>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef SDLMM_EVENT_H
#define SDLMM_EVENT_H
#include <cstring>

namespace SDLmm {
  //! The general Event class
  /*!
    The Event class is the core to all event handling is SDLmm. It's
    probably the most important class after Surface. The Event class
    can be used to store any type of event.
  */
  class DECLSPEC Event {
  public:
    //! The event structure.
    /*!
      If you use the event polling method, this is where the result is
      stored. You should consider using the more elegant EventHandler
      method instead however.
      \sa EventHandler, HandleEvents(), Poll(), Wait()
    */
    SDL_Event me;

    //! Polls for currently pending events
    /*!
      If there are any pending events, it will by default be removed
      from the queue and stored in this class instance.
      \param fetch if false, only poll for pending events but don't
      fetch it.
      \returns true if any events were pending.
      \sa EventHandler, HandleEvents(), Wait()
    */
    bool Poll(bool fetch = true);
    
    //! Waits indefinitely for the next available event
    /*!
      This function will wait for an event to become available. It
      will not return until an event is queued.
      \param fetch if false, don't fetch and dequeue the event once it
      becomes available.
      \returns true when an event became available and false if
      something went wrong.
      \sa EventHandler, HandleEvents(), Poll()
    */
    bool Wait(bool fetch = true);

    //! Push this event onto the event queue.
    /*!
      The event queue can actually be used as a two way communication
      channel. Not only can events be read from the queue, but the
      user can also push their own events onto it. 
      
      \note Pushing device input events onto the queue doesn't modify
      the state of the device within SDL.
      \warning Make sure to initialize the Event before pushing it!
      \returns true on success, falese if the Event couldn't be pushed.
    */
    bool Push();

    //! \name Event Methods
    //@{ 
    //! Pumps the event loop, gathering events from the input devices.
    /*!
      PumpEvents() gathers all the pending input information from devices
      and places it on the event queue. Without calls to PumpEvents() no
      events would ever be placed on the queue. Often the calls to
      PumpEvents() is hidden from the user since Poll and Wait implicitly
      call Pump. However, if you are not polling or waiting for events
      (e.g. your filtering them), then you must call Pump to force an
      event queue update.

      \note You can only call this function in the thread that set the
      video mode.
    */
    static void PumpEvents();

    //! Sets up a filter to process all events before they are posted
    //! to the event queue.
    /*!
      This function sets up a filter to process all events before they
      are posted to the event queue. This is a very powerful and
      flexible feature. The filter is prototyped as: 

      \code
      typedef int (*SDL_EventFilter)(const SDL_Event *event);
      \endcode

      If the filter returns 1, then the event will be added to the
      internal queue. If it returns 0, then the event will be dropped
      from the queue. This allows selective filtering of dynamically.

      There is one caveat when dealing with the SDL_QUITEVENT event
      type. The event filter is only called when the window manager
      desires to close the application window. If the event filter
      returns 1, then the window will be closed, otherwise the window
      will remain open if possible. If the quit event is generated by
      an interrupt signal, it will bypass the internal queue and be
      delivered to the application at the next event poll.
      
     \note Events pushed onto the queue with Push() or Peep() do not
     get passed through the event filter.

     \warning Be careful! The event filter function may run in a
     different thread so be careful what you do within it.
     \sa GetEventFilter()
    */
    static void SetEventFilter(SDL_EventFilter filter);

    //! Retrieves a pointer to the event filter.
    /*!
      This function retrieves a pointer to the event filter that was
      previously set using SetEventFilter(). An SDL_EventFilter
      function is defined as:

      \code
      typedef int (*SDL_EventFilter)(const SDL_Event *event);
      \endcode
      \returns Returns a pointer to the event filter or 0 if no filter
      has been set.
      \sa SetEventFilter()
    */
    static SDL_EventFilter  GetEventFilter();

    //! Set the state of processing for certain events.
    /*!
      This function allows you to set the state of processing certain
      event types.  

      If \a state is set to SDL_IGNORE, that event type will be
      automatically dropped from the event queue and will not be
      filtered.

      If \a state is set to SDL_ENABLE, that event type will be
      processed normally.

      If \a state is set to SDL_QUERY, EventState() will return the
      current processing state of the specified event type.

      A list of event types can be found in the SDL_Event section in the SDL
      documentation.

      \param type the event type
      \param state the state as documented above.
      \returns the current processing state for the specified event \a
      type
    */
    static Uint8 EventState(Uint8 type, int state);

    //! Handle all queued events using the specified EventHandler
    /*!
      This function polls for active events and calls the event
      callback methods. To actually handle any events, you need to
      create a derivate of the EventHandler class reimplementing the
      callbacks for the events you're interested in. See the
      EventHandler documentation for more details.
      \param handler the EventHandler which should handle the events.
      \sa EventHandler
    */
    static void HandleEvents(EventHandler &handler);
    
    //@}

    //! \name Keyboard Methods
    //@{ 
    
    //! Get a snapshot of the current keyboard state
    /*!
      Gets a snapshot of the current keyboard state. The current state
      is returned as a pointer to an array. The size of this array is
      stored in \a numkeys. The array is indexed by the SDLK_* symbols. A
      value of 1 means the key is pressed and a value of 0 means its
      not. 

      \note Use PumpEvents() to update the state array.
      \sa PumpEvents()
      \param numkeys a reference to an integer used to store the size of
      the returned array.
    */
    static Uint8 *GetKeyState(int &numkeys);

    //! Get a snapshot of the current keyboard state
    /*!
      Same as the GetKeyState(int &numkeys) method, used when you
      don't care how many keys were returned (i.e you want to check
      the state of a key that is known to exist).
      \par Example:
      \code
      Uint8 *keystate;
      keystate = Event::GetKeyState();
      if (keystate[SDLK_RETURN])
        cout << "Return Key Pressed.\n";
      \endcode
      \sa GetModState()
    */
    static Uint8 *GetKeyState();

    //! Get the state of modifier keys.
    /*!
      Returns the current of the modifier keys (CTRL, ALT, etc.).
      \return The return value can be an OR'd combination of the
      SDLMod enum or one of the convenience defines:
      - KMOD_NONE
      - KMOD_LSHIFT
      - KMOD_RSHIFT
      - KMOD_LCTRL
      - KMOD_RCTRL
      - KMOD_LALT
      - KMOD_RALT
      - KMOD_LMETA
      - KMOD_RMETA
      - KMOD_NUM
      - KMOD_CAPS
      - KMOD_MODE
      - KMOD_CTRL (KMOD_LCTRL | KMOD_RCTRL)
      - KMOD_SHIFT (KMOD_LSHIFT | KMOD_RSHIFT)
      - KMOD_ALT (KMOD_LALT | KMOD_RALT)
      - KMOD_META (KMOD_LMETA | KMOD_RMETA)
      \sa SetModState(), GetModState()
    */
    static SDLMod GetModState();

    //! Set the current key modifier state.
    /*!
      The inverse of GetModState(), SetModState() allows you to impose
      modifier key states on your application. 

      Simply pass your desired modifier states into \a modstate. This
      value my be a logical OR'd combination of the symbols documented
      in GetModState().
      \param modstate the new key modifier state.
      \sa GetModState()
    */
    static void SetModState(SDLMod modstate);

    //! Get the name of an SDL virtual key symbol.
    /*!
      \return the SDL defined name of the \a key.
      \param key the SDLkey key symbol
    */
    static char *GetKeyName(SDLKey key);

    //! Enable UNICODE keyboard translation
    /*!
      If you wish to translate a keysym to it's printable
      representation, you need to enable UNICODE translation using
      this function and then look in the unicode member of
      the SDL_keysym structure. This value will be zero for keysyms
      that do not have a printable representation. UNICODE translation
      is disabled by default as the conversion can cause a slight
      overhead.

      \param enable if false, disable UNICODE translation (SDL compatibility)
      
      \return true if UNICODE translation was previously enabled,
      false otherwise.
      \sa DisableUNICODE, QueryUNICODE
    */
    static bool EnableUNICODE(bool enable=true) { return SDL_EnableUNICODE(enable) != 0; }

    //! Disable UNICODE translation.
    /*!
      \return true if UNICODE translation was previously enabled,
      false otherwise.
      \sa EnableUNICODE, QueryUNICODE
    */      
    static bool DisableUNICODE() { return SDL_EnableUNICODE(0) != 0; }

    //! Query the current UNICODE translation mode
    /*!
      This function checks whether UNICODE translation is enabled or
      disabled.
      \return true if UNICODE translation is enabled, false otherwise.
      \sa EnableUNICODE, DisableUNICODE
    */
    static bool QueryUNICODE() { return SDL_EnableUNICODE(-1) != 0; }

    //! Set keyboard repeat rate.
    /*!
      Enables or disables the keyboard repeat rate. \a delay specifies
      how long the key must be pressed before it begins repeating. It
      then repeats at the speed specified by \a interval. Both \a
      delay and \a interval are expressed in milliseconds.

      Setting delay to 0 disables key repeating completely. If called
      without parameters, the default values uses are
      SDL_DEFAULT_REPEAT_DELAY and SDL_DEFAULT_REPEAT_INTERVAL.

      \return true on success, false on failure.
      \param delay delay before key repeating starts in ms.
      \param interval delay between repeats in ms.
    */

    static bool EnableKeyRepeat(int delay = SDL_DEFAULT_REPEAT_DELAY,
				int interval = SDL_DEFAULT_REPEAT_DELAY);
    //@}

    //! \name Mouse Methods
    //@{
    //! Retrieve the current state of the mouse.
    /*!
      The current button state is returned as a button bitmask, which
      can be tested using the SDL_BUTTON(X) macros, and \a x and \a y are
      set to the current mouse cursor position. You can pass zero
      for either \a x or \a y.

      \returns the button bitmask.
      \param x, y pointers to integers where the current mouse
      coordinates will be stored.
    */
    static Uint8 GetMouseState(int *x = 0, int *y = 0);

    //! Retrieve the current state of the mouse.
    /*!
      The current button state is returned as a button bitmask, which
      can be tested using the SDL_BUTTON(X) macros, and \a x and \a y are
      set to the change in the mouse position since the last call to
      SDL_GetRelativeMouseState or since event initialization. You can
      pass zero for either \a x or \a y.   

      \returns the button bitmask.
      \param x, y pointers to integers for mouse coordinates or
      relative change.
    */
    static Uint8 GetRelativeMouseState(int *x, int *y);    
    //@}

    //! \name Other Methods
    //@{

    //! Get the state of the application.
    /*!
      This function returns the current state of the application. The
      value returned is a bitwise combination of:
      
      - \b SDL_APPMOUSEFOCUS - 
      the application has mouse focus.
      - \b SDL_APPINPUTFOCUS - 
      the application has keyboard focus
      - \b SDL_APPACTIVE - 
      the application is visible

      \returns The current state of the application.
    */
    static Uint8 GetAppState();

    //! Enable / disable joystick event polling.
    /*
      This function is used to enable or disable joystick event
      processing. With joystick event processing disabled you will
      have to update joystick states with Joystick::JoystickUpdate()
      and read the joystick information manually. \a state is either
      SDL_QUERY, SDL_ENABLE or SDL_IGNORE.

      \note Joystick event handling is preferred.
      \return If \a state is SDL_QUERY then the current state is
      returned, otherwise the new processing \a state is returned.
      \param state the state as documented above.
    */
    
    static int JoystickEventState(int state);
    
    //@}
  };
}

#endif // SDLMM_EVENT_H
