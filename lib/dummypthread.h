#ifndef _DUMMYPTHREAD_H_
#define _DUMMYPTHREAD_H_

#if defined(WITH_THREADING) && !defined(WITH_BROKER)
#	ifdef WIN32
		//on windows, we use native windows threading
#		include <windows.h>
		
		//the second argument here is the timeout, but for our purposes infinite timeout is expected
#		define pthread_mutex_lock(mutex) WaitForSingleObject(* (mutex) ,INFINITE)
#		define pthread_mutex_unlock(mutex) ReleaseMutex( * (mutex) )
#		define pthread_mutex_init(mutex) (* (mutex) = CreateMutex(NULL,FALSE,NULL) )
#		define pthread_mutex_destroy(mutex) CloseHandle( * (mutex) )
#		define pthread_equal(thread1, thread2) (GetThreadId( (thread1) ) == GetThreadId( (thread2) ))
#		define pthread_self() GetCurrentThread()
		//this long one-liner will return GetLastError if there was an error, else NULL if no error
#		define pthread_create(thread, run_function, init_arg) ( * (thread) = CreateThread(NULL, 0, (run_function) , (init_arg) , 0, NULL) ) == NULL ? GetLastError() : 0
#		define pthread_join(otherThread) WaitForSingleObject( (otherThread) , INFINITE)
		//for thread_cancel, just wait for the thread to finish with WaitForSingleObject
#		define pthread_cancel(thread) WaitForSingleObject( (thread), INFINITE )
#	endif /*END IFDEF WIN32*/
#else
	//if we're using the broker or we don't have threading enabled, then just define these to be null
#	define pthread_mutex_lock(mutex)
#	define pthread_mutex_unlock(mutex)
#	define pthread_mutex_init(mutex)
#	define pthread_mutex_destroy(mutex)
#	define pthread_equal(thread1, thread2)
#	define pthread_self()
#	define pthread_create(thread, run_func, init_arg)
#	define pthread_join(otherThread, retval)
#	define pthread_cancel(thread) 
#endif /*defined(WITH_THREADING) && !defined(WITH_BROKER)*/


#endif
