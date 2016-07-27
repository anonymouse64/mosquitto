#if defined(WITH_THREADING) && !defined(WITH_BROKER) && defined(WIN32)
	//on windows, we use native windows threading
#	include <windows.h>
	//both mutex and thread objects are HANDLE
	typedef HANDLE pthread_mutex_t;
	typedef HANDLE pthread_t;
	//the second argument here is the timeout, but for our purposes infinite timeout is expected
#	define pthread_mutex_lock(mutex) WaitForSingleObject(* (mutex) ,INFINITE)
#	define pthread_mutex_unlock(mutex) ReleaseMutex( * (mutex) )
#	define pthread_mutex_init(mutex, param) (* (mutex) = CreateMutex(NULL,FALSE,NULL) )
#	define pthread_mutex_destroy(mutex) CloseHandle( * (mutex) )
#	define pthread_equal(thread1, thread2) (GetThreadId( (thread1) ) == GetThreadId( (thread2) ))
#	define pthread_self() GetCurrentThread()
	//this long one-liner will return GetLastError if there was an error, else NULL if no error
#	define pthread_create(thread, param, run_function, init_arg) ( * (thread) = CreateThread(NULL, 0, (run_function) , (init_arg) , 0, NULL) ) == 0 ? GetLastError() : 0
#	define pthread_join(otherThread, param) WaitForSingleObject( (otherThread) , INFINITE)
	//for thread_cancel, just wait for the thread to finish with WaitForSingleObject
#	define pthread_cancel(thread) WaitForSingleObject( (thread), INFINITE )
#endif /*END IFDEF WITH_THREADING AND NOT WITH_BROKER AND WIN32*/
