#ifndef __EVENT_H__
#define __EVENT_H__

//Included resourses
#include <string>

using namespace std;
namespace df {

	class Event {

	private:
		//Default event type
		const string UNDEFINED_EVENT = "df::undefined";

		//Type of event
		string m_event_type;
	public:

		//Constructer
		Event();

		//Deconstructer must be virtual
		virtual ~Event();

		//Set Event type
		void setType(string new_type);

		//Get Event type
		string getType() const;

	};//End of class
}//End of namespace
#endif // !__EVENT_H__
