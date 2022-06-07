#ifndef INCLUDES_BASE_H_
#define INCLUDES_BASE_H_
#include <string>
#include <vector>

#define SIG_M(signal_fn) (Base::Signal)(&signal_fn)
#define HDR_M(handler_fn) (Base::Handler)(&handler_fn)

class Base {
 private:
  unsigned int uid;
  Base* parent;
  std::vector<Base*> children;

  static unsigned int get_next_uid();
  static unsigned int _next_uid;

  struct SignalStruct;
  std::vector<Base::SignalStruct*> connections;

 public:
  explicit Base(Base* parent);
  virtual ~Base();

  enum Command {
    GET_INIT_STATE,
    SET_INIT_STATE,
    GET_USER_INPUT,
    PROCESS_USER_INPUT,
    ADD_TABLE,
    GROUP_LEAVE,
    FREE_TABLE,
    ADD_GROUP,
    PRINT,
    PRINT_PAUSE,
    NEXT_TICK,
    MAKE_STATE_REPORT,
    STATE_REPORT_DONE
  };
  typedef void (Base::*Handler)(Base::Command, std::string);
  typedef void (Base::*Signal)(Base::Command, std::string&);

  Base* get_parent();
  std::vector<Base*> get_children();
  unsigned int get_uid();

  void set_parent(Base* new_parent);

  void add_child(Base* child);
  void remove_child(Base* child);
  Base* get_child_by_uid(unsigned int target_uid);

  virtual Base::Signal get_signal_emitter() = 0;
  virtual Base::Handler get_signal_handler() = 0;

  void emit(Signal signal_fn, Command cid, std::string payload);
  void add_connection(Signal signal_fn, Handler handler_fn, Base* target);
  void remove_connection(Signal signal_fn, Handler handler_fn, Base* target);
};

#endif  // INCLUDES_BASE_H_
