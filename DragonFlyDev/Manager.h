#ifndef __MANAGER_H__
#define __MANAGER_H__

//Needed Includes
#include <string>
using namespace std;
namespace df {

	class Manager {


	private:
		//Type variable
		string m_type;

		//Boolean to see if the manager is on
		bool m_is_started;

	protected:
		//Set type identifier for manager.
		void setType(string type);

	public:

		//Constructer
		Manager();

		//Deconstructer
		virtual ~Manager();

		//Get identifier of Manager
		string getType() const;

		//Start up 
		//Return 0 if success, negative if failure
		virtual int startUp();

		//Shut down
		virtual void shutDown();

		//Return true if start up worked (IE returned 0)
		bool isStarted() const;

	};//End of Class
}//End of name space df
#endif // !__MANAGER_H__

