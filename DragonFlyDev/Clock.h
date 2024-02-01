#ifndef __CLOCK_H__
#define __CLOCK_H__
namespace df {

	class Clock {

	private:

		//Holds the time in windows in microseconds
		long int m_previous_t;

	public:
		
		//Sets previous_t to current time
		Clock();

		//Returns how long it's been since last call in microseconds
		//Resets previous time
		long int delta();

		//Returns how long it's been since last callin microseconds
		//Does not reset previous time
		long int split();

		//Gets the current time in microseconds
		long int getCurTime();

	};//End of Class
}//End of name space

#endif // !__CLOCK_H__

