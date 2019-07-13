#include "observer.hpp"

#include <iostream>

struct MsgA{};
struct MsgB{};
struct MsgC{};
struct MsgD{};

std::ostream& operator<<(std::ostream& s, const MsgA& o)
{
   return s << "MsgA ";
}

std::ostream& operator<<(std::ostream& s, const MsgB& o)
{
   return s << "MsgB ";
}

std::ostream& operator<<(std::ostream& s, const MsgC& o)
{
   return s << "MsgC ";
}

std::ostream& operator<<(std::ostream& s, const MsgD& o)
{
   return s << "MsgD ";
}

class DBusHandler : public Subject<MsgA,MsgB,MsgC>
{
	public:
		void emulateRxA()
		{
			MsgA a;
			notify(a);
		}

		void emulateRxB()
		{
			MsgB b;
			notify(b);
		}

		void emulateRxC()
		{
			MsgC c;
			notify(c);
		}

	private:

};

class RPCHander : public Subject<MsgD>
{
	public:
		void emulateRxD()
		{
			MsgD d;
			notify(d);
		}
};



class StateMachine : public Listener<MsgA, MsgB>
{
	public:
		void update(const MsgA& obj) override
		{
			std::cout << "StateMachine MsgA" << std::endl;
		}

		void update(const MsgB& obj) override
		{
			std::cout << "StateMachine MsgB" << std::endl;
		}
};


class Sniffer : public Listener<MsgB, MsgD>
{
	public:
		void update(const MsgB& obj) override
		{
			std::cout << "Sniffer MsgB" << std::endl;
		}	

		void update(const MsgD& obj) override
		{
			std::cout << "Sniffer MsgD" << std::endl;
		}		
};

int main()
{
	DBusHandler dbus;
	RPCHander rpc;
	StateMachine sm;
	Sniffer s;

	dbus.registerListener(&sm);
	dbus.registerListener(&s);
	rpc.registerListener(&s);

	dbus.emulateRxA();
	dbus.emulateRxB();
	dbus.emulateRxC();
	rpc.emulateRxD();

	return 0;
}
