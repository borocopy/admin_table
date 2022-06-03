#ifndef BASE_H_
#define BASE_H_
#include <string>
#include <vector>

#define SIG_M(signal_fn) (Base::Signal)(&signal_fn)
#define HDR_M(handler_fn) (Base::Handler)(&handler_fn)

class Base {
 private:
  Base* parent;
  std::vector<Base*> children;

  struct SignalStruct;
  std::vector<Base::SignalStruct*> connections;

  void add_child(Base* child);
  void remove_child(Base* child);

 public:
  explicit Base(Base* parent);
  virtual ~Base();

  enum Command {
		GET_INIT_STATE,
		SET_INIT_STATE,
    GET_USER_INPUT,
    PROCESS_USER_INPUT,
    RESERVE_TABLE,
    ADD_TABLE,
    FREE_TABLE,
    OCCUPY_TABLE,
    ENQUE_GROUP,
		KILL_APP,
		PRINT_STATE,
  };
  typedef void (Base::*Handler)(Base::Command, std::string);
  typedef void (Base::*Signal)(Base::Command, std::string&);

  Base* get_parent();
  std::vector<Base*> get_children();

  void set_parent(Base* new_parent);

  virtual Base::Signal get_signal_emitter() = 0;
  virtual Base::Handler get_signal_handler() = 0;

  void emit(Signal signal_fn, Command cid, std::string payload);
  void add_connection(Signal signal_fn, Handler handler_fn, Base* target);
  /* void remove_connection(Signal signal_fn, Handler handler_fn, Base* target);
   */
};

#endif  // BASE_H_
