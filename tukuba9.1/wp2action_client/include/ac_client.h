//date : 2012.11.29
//author : shohei TAKESAKO

#ifdef AC_CLIENT
#define AC_CLIENT

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/scoped_ptr.hpp>

#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "actionlib/client/action_client.h"
#include "actionlib/client/simple_goal_state.h"
#include "actionlib/client/simple_client_goal_state.h"
#include "actionlib/client/terminal_state.h"


//ROSとの差別化を図るため、namespaceを利用する
namespace aclib
{	
	class ac_client
	{
		private:

		public:
			
	}
	
}

#endif
