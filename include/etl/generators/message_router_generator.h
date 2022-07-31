/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2017 John Wellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

/*[[[cog
import cog
cog.outl("#if 0")
]]]*/
/*[[[end]]]*/
#error THIS HEADER IS A GENERATOR. DO NOT INCLUDE.
/*[[[cog
import cog
cog.outl("#endif")
]]]*/
/*[[[end]]]*/

/*[[[cog
import cog
cog.outl("//***************************************************************************")
cog.outl("// THIS FILE HAS BEEN AUTO GENERATED. DO NOT EDIT THIS FILE.")
cog.outl("//***************************************************************************")
]]]*/
/*[[[end]]]*/

//***************************************************************************
// To generate to header file, run this at the command line.
// Note: You will need Python and COG installed.
//
// python -m cogapp -d -e -omessage_router.h -DHandlers=<n> message_router_generator.h
// Where <n> is the number of messages to support.
//
// e.g.
// To generate handlers for up to 16 messages...
// python -m cogapp -d -e -omessage_router.h -DHandlers=16 message_router_generator.h
//
// See generate.bat
//***************************************************************************

#ifndef ETL_MESSAGE_ROUTER_INCLUDED
#define ETL_MESSAGE_ROUTER_INCLUDED

#include <stdint.h>

#include "platform.h"
#include "message.h"
#include "shared_message.h"
#include "message_packet.h"
#include "message_types.h"
#include "alignment.h"
#include "error_handler.h"
#include "exception.h"
#include "largest.h"
#include "nullptr.h"
#include "placement_new.h"
#include "successor.h"
#include "type_traits.h"

namespace etl
{
  //***************************************************************************
  /// Base exception class for message router
  //***************************************************************************
  class message_router_exception : public etl::exception
  {
  public:

    message_router_exception(string_type reason_, string_type file_name_, numeric_type line_number_)
      : etl::exception(reason_, file_name_, line_number_)
    {
    }
  };

  //***************************************************************************
  /// Router id is out of the legal range.
  //***************************************************************************
  class message_router_illegal_id : public etl::message_router_exception
  {
  public:

    message_router_illegal_id(string_type file_name_, numeric_type line_number_)
      : message_router_exception(ETL_ERROR_TEXT("message router:illegal id", ETL_MESSAGE_ROUTER_FILE_ID"A"), file_name_, line_number_)
    {
    }
  };

  //***************************************************************************
  /// Forward declare null message router functionality.
  //***************************************************************************
  class imessage_router;

  etl::imessage_router& get_null_message_router();

  //***************************************************************************
  /// This is the base of all message routers.
  //***************************************************************************
  class imessage_router : public etl::successor<imessage_router>
  {
  public:

    virtual ~imessage_router() {}
    virtual void receive(const etl::imessage&) = 0;
    virtual bool accepts(etl::message_id_t) const = 0;
    virtual bool is_null_router() const = 0;
    virtual bool is_producer() const = 0;
    virtual bool is_consumer() const = 0;

    //********************************************
    virtual void receive(etl::message_router_id_t destination_router_id, const etl::imessage& message)
    {
      if ((destination_router_id == get_message_router_id()) || (destination_router_id == imessage_router::ALL_MESSAGE_ROUTERS))
      {
        receive(message);
      }
    }

    //********************************************
    virtual void receive(etl::shared_message shared_msg)
    {
      receive(shared_msg.get_message());
    }

    //********************************************
    virtual void receive(etl::message_router_id_t destination_router_id, etl::shared_message shared_msg)
    {
      if ((destination_router_id == get_message_router_id()) || (destination_router_id == imessage_router::ALL_MESSAGE_ROUTERS))
      {
        receive(shared_msg);
      }
    }

    //********************************************
    bool accepts(const etl::imessage& msg) const
    {
      return accepts(msg.get_message_id());
    }

    //********************************************
    etl::message_router_id_t get_message_router_id() const
    {
      return message_router_id;
    }

    enum
    {
      NULL_MESSAGE_ROUTER = 255,
      MESSAGE_BUS         = 254,
      ALL_MESSAGE_ROUTERS = 253,
      MESSAGE_BROKER      = 252,
      MAX_MESSAGE_ROUTER  = 249
    };

  protected:

    imessage_router(etl::message_router_id_t id_)
      : message_router_id(id_)
    {
    }

    imessage_router(etl::message_router_id_t id_, imessage_router& successor_)
      : successor(successor_)
      , message_router_id(id_)
    {
    }

  private:

    // Disabled.
    imessage_router(const imessage_router&);
    imessage_router& operator =(const imessage_router&);

    etl::message_router_id_t  message_router_id;
  };

  //***************************************************************************
  /// This router can be used as a sink for messages or a 'null source' router.
  //***************************************************************************
  class null_message_router : public imessage_router
  {
  public:

    null_message_router()
      : imessage_router(imessage_router::NULL_MESSAGE_ROUTER)
    {
    }

    //********************************************
    using etl::imessage_router::receive;

    void receive(const etl::imessage& msg) ETL_OVERRIDE
    {
      if (has_successor())
      {
        get_successor().receive(msg);
      }
    }

    //********************************************
    using etl::imessage_router::accepts;

    bool accepts(etl::message_id_t id) const ETL_OVERRIDE
    {
      if (has_successor())
      {
        return get_successor().accepts(id);
      }
      else
      {
        return false;
      }
    }

    //********************************************
    ETL_DEPRECATED bool is_null_router() const ETL_OVERRIDE
    {
      return true;
    }

    //********************************************
    bool is_producer() const ETL_OVERRIDE
    {
      return false;
    }

    //********************************************
    bool is_consumer() const ETL_OVERRIDE
    {
      return false;
    }

    //********************************************
    static null_message_router& instance()
    {
      static null_message_router nmr;
      return nmr;
    }
  };

  //***********************************************
  /// null message router functionality.
  inline etl::imessage_router& get_null_message_router()
  {
    return etl::null_message_router::instance();
  }

  //***************************************************************************
  /// This router can be used as a producer-only of messages, such an interrupt routine.
  //***************************************************************************
  class message_producer : public imessage_router
  {
  public:

    message_producer(etl::message_router_id_t id_)
      : imessage_router(id_)
    {
    }

    //********************************************
    using etl::imessage_router::receive;

    void receive(const etl::imessage& msg) ETL_OVERRIDE
    {
      if (has_successor())
      {
        get_successor().receive(msg);
      }
    }

    //********************************************
    using etl::imessage_router::accepts;

    bool accepts(etl::message_id_t id) const ETL_OVERRIDE
    {
      if (has_successor())
      {
        return get_successor().accepts(id);
      }
      else
      {
        return false;
      }
    }

    //********************************************
    ETL_DEPRECATED bool is_null_router() const ETL_OVERRIDE
    {
      return false;
    }

    //********************************************
    bool is_producer() const ETL_OVERRIDE
    {
      return true;
    }

    //********************************************
    bool is_consumer() const ETL_OVERRIDE
    {
      return false;
    }
  };

  //***************************************************************************
  /// Send a message to a router.
  //***************************************************************************
  static inline void send_message(etl::imessage_router& destination,
                                  const etl::imessage&  message)
  {
    destination.receive(message);
  }

  //***************************************************************************
  /// Send a shared message to a router.
  //***************************************************************************
  static inline void send_message(etl::imessage_router& destination,
                                  etl::shared_message message)
  {
    destination.receive(message);
  }

//*************************************************************************************************
// For C++17 and above.
//*************************************************************************************************
#if ETL_USING_CPP17 && !defined(ETL_MESSAGE_ROUTER_FORCE_CPP03_IMPLEMENTATION)
  //***************************************************************************
  // The definition for all message types.
  //***************************************************************************
  template <typename TDerived, typename... TMessageTypes>
  class message_router : public imessage_router
  {
  public:

    typedef etl::message_packet<TMessageTypes...> message_packet;

    //**********************************************
    message_router(etl::message_router_id_t id_)
      : imessage_router(id_)
    {
      ETL_ASSERT(id_ <= etl::imessage_router::MAX_MESSAGE_ROUTER, ETL_ERROR(etl::message_router_illegal_id));
    }

    //**********************************************
    message_router(etl::message_router_id_t id_, etl::imessage_router& successor_)
      : imessage_router(id_, successor_)
    {
      ETL_ASSERT(id_ <= etl::imessage_router::MAX_MESSAGE_ROUTER, ETL_ERROR(etl::message_router_illegal_id));
    }

    //**********************************************
    using etl::imessage_router::receive;

    void receive(const etl::imessage& msg) ETL_OVERRIDE
    {
      const bool was_handled = (receive_message_type<TMessageTypes>(msg) || ...);

      if (!was_handled)
      {
        if (has_successor())
        {
          get_successor().receive(msg);
        }
        else
        {
          static_cast<TDerived*>(this)->on_receive_unknown(msg);
        }
      }
    }

    template <typename TMessage, typename etl::enable_if<etl::is_base_of<imessage, TMessage>::value, int>::type = 0>
    void receive(const TMessage& msg)
    {
      if constexpr (etl::is_one_of<TMessage, TMessageTypes...>::value)
      {
        static_cast<TDerived*>(this)->on_receive(msg);
      }
      else
      {
        if (has_successor())
        {
          get_successor().receive(msg);
        }
        else
        {
          static_cast<TDerived*>(this)->on_receive_unknown(msg);
        }
      }
    }

    //**********************************************
    using imessage_router::accepts;

    bool accepts(etl::message_id_t id) const ETL_OVERRIDE
    {
      return (accepts_type<TMessageTypes>(id) || ...);
    }

    //********************************************
    ETL_DEPRECATED bool is_null_router() const ETL_OVERRIDE
    {
      return false;
    }

    //********************************************
    bool is_producer() const ETL_OVERRIDE
    {
      return true;
    }

    //********************************************
    bool is_consumer() const ETL_OVERRIDE
    {
      return true;
    }

  private:

    //********************************************
    template <typename TMessage>
    bool receive_message_type(const etl::imessage& msg)
    {
      if (TMessage::ID == msg.get_message_id())
      {
        static_cast<TDerived*>(this)->on_receive(static_cast<const TMessage&>(msg));
        return true;
      }
      else
      {
        return false;
      }
    }

    //********************************************
    template <typename TMessage>
    bool accepts_type(etl::message_id_t id) const
    {
      if (TMessage::ID == id)
      {
        return true;
      }
      else
      {
        if (has_successor())
        {
          return get_successor().accepts(id);
        }
        else
        {
          return false;
        }
      }
    }
  };
#else
//*************************************************************************************************
// For C++14 and below.
//*************************************************************************************************
  /*[[[cog
      import cog
      ################################################
      # The first definition for all of the messages.
      ################################################
      cog.outl("//***************************************************************************")
      cog.outl("// The definition for all %s message types." % Handlers)
      cog.outl("//***************************************************************************")
      cog.outl("template <typename TDerived,")
      cog.out("          ")
      cog.out("typename T1, ")
      for n in range(2, int(Handlers)):
          cog.out("typename T%s = void, " % n)
          if n % 4 == 0:
              cog.outl("")
              cog.out("          ")
      cog.outl("typename T%s = void>" % int(Handlers))
      cog.out("class message_router")
      cog.outl("  : public imessage_router")
      cog.outl("{")
      cog.outl("public:")
      cog.outl("")
      cog.out("  typedef etl::message_packet<")
      for n in range(1, int(Handlers)):
          cog.out("T%s, " % n)
      cog.outl(" T%s> message_packet;" % int(Handlers))
      cog.outl("")
      cog.outl("  //**********************************************")
      cog.outl("  message_router(etl::message_router_id_t id_)")
      cog.outl("    : imessage_router(id_)")
      cog.outl("  {")
      cog.outl("    ETL_ASSERT(id_ <= etl::imessage_router::MAX_MESSAGE_ROUTER, ETL_ERROR(etl::message_router_illegal_id));")
      cog.outl("  }")
      cog.outl("")
      cog.outl("  //**********************************************")
      cog.outl("  message_router(etl::message_router_id_t id_, etl::imessage_router& successor_)")
      cog.outl("    : imessage_router(id_, successor_)")
      cog.outl("  {")
      cog.outl("    ETL_ASSERT(id_ <= etl::imessage_router::MAX_MESSAGE_ROUTER, ETL_ERROR(etl::message_router_illegal_id));")
      cog.outl("  }")
      cog.outl("")
      cog.outl("  //**********************************************")
      cog.outl("  using etl::imessage_router::receive;")
      cog.outl("")
      cog.outl("  void receive(const etl::imessage& msg) ETL_OVERRIDE")
      cog.outl("  {")
      cog.outl("    const etl::message_id_t id = msg.get_message_id();")
      cog.outl("")
      cog.outl("    switch (id)")
      cog.outl("    {")
      for n in range(1, int(Handlers) + 1):
          cog.out("      case T%d::ID:" % n)
          cog.out(" static_cast<TDerived*>(this)->on_receive(static_cast<const T%d&>(msg));" % n)
          cog.outl(" break;")
      cog.outl("      default:")
      cog.outl("      {")
      cog.outl("         if (has_successor())")
      cog.outl("         {")
      cog.outl("           get_successor().receive(msg);")
      cog.outl("         }")
      cog.outl("         else")
      cog.outl("         {")
      cog.outl("           static_cast<TDerived*>(this)->on_receive_unknown(msg);")
      cog.outl("         }")
      cog.outl("         break;")
      cog.outl("      }")
      cog.outl("    }")
      cog.outl("  }")
      cog.outl("")
      cog.outl("  template <typename TMessage>")
      cog.outl("  void receive(const TMessage& msg, typename etl::enable_if<etl::is_base_of<imessage, TMessage>::value, int>::type = 0)")
      cog.outl("  {")
      cog.out("    if ETL_IF_CONSTEXPR (etl::is_one_of<TMessage, ")
      for n in range(1, int(Handlers)):
          cog.out("T%s, " % n)
          if n % 4 == 0:
              cog.outl("")
              cog.out("                                                  ")
      cog.outl("T%s>::value)" % int(Handlers))
      cog.outl("    {")     
      cog.outl("      static_cast<TDerived*>(this)->on_receive(msg);")
      cog.outl("    }")
      cog.outl("    else")
      cog.outl("    {")
      cog.outl("      if (has_successor())")
      cog.outl("      {")
      cog.outl("        get_successor().receive(msg);")
      cog.outl("      }")
      cog.outl("      else")
      cog.outl("      {")
      cog.outl("        static_cast<TDerived*>(this)->on_receive_unknown(msg);")
      cog.outl("      }")
      cog.outl("    }")
      cog.outl("  }")
      cog.outl("")
      cog.outl("  //**********************************************")
      cog.outl("  using imessage_router::accepts;")
      cog.outl("")
      cog.outl("  bool accepts(etl::message_id_t id) const ETL_OVERRIDE")
      cog.outl("  {")
      cog.outl("    switch (id)")
      cog.outl("    {")
      cog.out("      ")
      for n in range(1, int(Handlers) + 1):
          cog.out("case T%d::ID: " % n)
          if n % 8 == 0:
              cog.outl("")
              cog.out("      ")
      cog.outl("  return true;")
      cog.outl("      default:")
      cog.outl("      {")
      cog.outl("        if (has_successor())")
      cog.outl("        {")
      cog.outl("          return get_successor().accepts(id);")
      cog.outl("        }")
      cog.outl("        else")
      cog.outl("        {")
      cog.outl("          return false;")
      cog.outl("        }")
      cog.outl("      }")
      cog.outl("    }")
      cog.outl("  }")
      cog.outl("")
      cog.outl("  //********************************************")
      cog.outl("  ETL_DEPRECATED bool is_null_router() const ETL_OVERRIDE")
      cog.outl("  {")
      cog.outl("    return false;")
      cog.outl("  }")
      cog.outl("")
      cog.outl("  //********************************************")
      cog.outl("  bool is_producer() const ETL_OVERRIDE")
      cog.outl("  {")
      cog.outl("    return true;")
      cog.outl("  }")
      cog.outl("")
      cog.outl("  //********************************************")
      cog.outl("  bool is_consumer() const ETL_OVERRIDE")
      cog.outl("  {")
      cog.outl("    return true;")
      cog.outl("  }")
      cog.outl("};")

      ####################################
      # All of the other specialisations.
      ####################################
      for n in range(int(Handlers) - 1, 0, -1):
          cog.outl("")
          cog.outl("//***************************************************************************")
          if n == 1:
              cog.outl("// Specialisation for %d message type." % n)
          else:
              cog.outl("// Specialisation for %d message types." % n)
          cog.outl("//***************************************************************************")
          cog.outl("template <typename TDerived, ")
          cog.out("          ")
          for t in range(1, n):
              cog.out("typename T%d, " % t)
              if t % 4 == 0:
                  cog.outl("")
                  cog.out("          ")
          cog.outl("typename T%d>" % n)
          cog.out("class message_router<TDerived, ")
          for t in range(1, n + 1):
              cog.out("T%d, " % t)
              if t % 16 == 0:
                  cog.outl("")
                  cog.out("               ")
          for t in range(n + 1, int(Handlers)):
              cog.out("void, ")
              if t % 16 == 0:
                  cog.outl("")
                  cog.out("               ")
          cog.outl("void>")
          cog.outl(" : public imessage_router")
          cog.outl("{")
          cog.outl("public:")
          cog.outl("")
          cog.out("  typedef etl::message_packet<")
          for t in range(1, n):
              cog.out("T%s, " % t)
          cog.outl(" T%s> message_packet;" % n)
          cog.outl("")
          cog.outl("  //**********************************************")
          cog.outl("  message_router(etl::message_router_id_t id_)")
          cog.outl("    : imessage_router(id_)")
          cog.outl("  {")
          cog.outl("    ETL_ASSERT(id_ <= etl::imessage_router::MAX_MESSAGE_ROUTER, ETL_ERROR(etl::message_router_illegal_id));")
          cog.outl("  }")
          cog.outl("")
          cog.outl("  //**********************************************")
          cog.outl("  message_router(etl::message_router_id_t id_, etl::imessage_router& successor_)")
          cog.outl("    : imessage_router(id_, successor_)")
          cog.outl("  {")
          cog.outl("    ETL_ASSERT(id_ <= etl::imessage_router::MAX_MESSAGE_ROUTER, ETL_ERROR(etl::message_router_illegal_id));")
          cog.outl("  }")
          cog.outl("")
          cog.outl("  //**********************************************")
          cog.outl("  using etl::imessage_router::receive;")
          cog.outl("")
          cog.outl("  void receive(const etl::imessage& msg) ETL_OVERRIDE")
          cog.outl("  {")
          cog.outl("    const size_t id = msg.get_message_id();")
          cog.outl("")
          cog.outl("    switch (id)")
          cog.outl("    {")
          for t in range(1, n + 1):
              cog.out("      case T%d::ID:" % t)
              cog.out(" static_cast<TDerived*>(this)->on_receive(static_cast<const T%d&>(msg));" % t)
              cog.outl(" break;")
          cog.outl("      default:")
          cog.outl("      {")
          cog.outl("         if (has_successor())")
          cog.outl("         {")
          cog.outl("           get_successor().receive(msg);")
          cog.outl("         }")
          cog.outl("         else")
          cog.outl("         {")
          cog.outl("           static_cast<TDerived*>(this)->on_receive_unknown(msg);")
          cog.outl("         }")
          cog.outl("         break;")
          cog.outl("      }")
          cog.outl("    }")
          cog.outl("  }")
          cog.outl("")
          cog.outl("  template <typename TMessage>")
          cog.outl("  void receive(const TMessage& msg, typename etl::enable_if<etl::is_base_of<imessage, TMessage>::value, int>::type = 0)")
          cog.outl("  {")
          cog.out("    if ETL_IF_CONSTEXPR (etl::is_one_of<TMessage, ")
          for t in range(1, n):
              cog.out("T%s, " % t)
              if t % 4 == 0:
                  cog.outl("")
                  cog.out("                                                  ")
          cog.outl("T%s>::value)" % n)
          cog.outl("    {")
          cog.outl("      static_cast<TDerived*>(this)->on_receive(msg);")
          cog.outl("    }")
          cog.outl("    else")
          cog.outl("    {")
          cog.outl("      if (has_successor())")
          cog.outl("      {")
          cog.outl("        get_successor().receive(msg);")
          cog.outl("      }")
          cog.outl("      else")
          cog.outl("      {")
          cog.outl("        static_cast<TDerived*>(this)->on_receive_unknown(msg);")
          cog.outl("      }")
          cog.outl("    }")
          cog.outl("  }")
          cog.outl("")
          cog.outl("  //**********************************************")
          cog.outl("  using imessage_router::accepts;")
          cog.outl("")
          cog.outl("  bool accepts(etl::message_id_t id) const ETL_OVERRIDE")
          cog.outl("  {")
          cog.outl("    switch (id)")
          cog.outl("    {")
          cog.out("      ")
          for t in range(1, n + 1):
              cog.out("case T%d::ID: " % t)
              if t % 8 == 0:
                  cog.outl("")
                  cog.out("      ")
          cog.outl("")
          cog.outl("        return true;")
          cog.outl("      default:")
          cog.outl("      {")
          cog.outl("        if (has_successor())")
          cog.outl("        {")
          cog.outl("          return get_successor().accepts(id);")
          cog.outl("        }")
          cog.outl("        else")
          cog.outl("        {")
          cog.outl("          return false;")
          cog.outl("        }")
          cog.outl("      }")
          cog.outl("    }")
          cog.outl("  }")
          cog.outl("")
          cog.outl("  //********************************************")
          cog.outl("  ETL_DEPRECATED bool is_null_router() const ETL_OVERRIDE")
          cog.outl("  {")
          cog.outl("    return false;")
          cog.outl("  }")
          cog.outl("")
          cog.outl("  //********************************************")
          cog.outl("  bool is_producer() const ETL_OVERRIDE")
          cog.outl("  {")
          cog.outl("    return true;")
          cog.outl("  }")
          cog.outl("")
          cog.outl("  //********************************************")
          cog.outl("  bool is_consumer() const ETL_OVERRIDE")
          cog.outl("  {")
          cog.outl("    return true;")
          cog.outl("  }")
          cog.outl("};")
  ]]]*/
  /*[[[end]]]*/
#endif
}

#endif
