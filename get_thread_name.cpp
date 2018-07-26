#include <iostream>
#define LOGURU_IMPLEMENTATION 1
#define LOGURU_WITH_STREAMS 1
#include <loguru.hpp>
	
#define LOGURU_PTHREADS 1
#define LOGURU_PTLS_NAMES 1 

#if LOGURU_PTLS_NAMES
	static pthread_once_t s_pthread_key_once = PTHREAD_ONCE_INIT;
	static pthread_key_t  s_pthread_key_name;

	void make_pthread_key_name()
	{
		(void)pthread_key_create(&s_pthread_key_name, free);
	}
#endif


#if LOGURU_PTLS_NAMES
	const char* get_thread_name_ptls()
	{
		(void)pthread_once(&s_pthread_key_once, make_pthread_key_name);
		return static_cast<const char*>(pthread_getspecific(s_pthread_key_name));
	}
#endif // LOGURU_PTLS_NAMES

void get_thread_name(char* buffer, unsigned long long length, bool right_align_hext_id)
{
//		CHECK_NE_F(length, 0u, "Zero length buffer in get_thread_name");
//		CHECK_NOTNULL_F(buffer, "nullptr in get_thread_name");
#if LOGURU_PTHREADS
		auto thread = pthread_self();
		#if LOGURU_PTLS_NAMES
			if (const char* name = get_thread_name_ptls()) {
				snprintf(buffer, length, "%s", name);
			} 
			else {
				buffer[0] = 0;
			}
		#else
			pthread_getname_np(thread, buffer, length);
		#endif

		if (buffer[0] == 0) {
			#ifdef __APPLE__
				uint64_t thread_id;
				pthread_threadid_np(thread, &thread_id);
			#else
				uint64_t thread_id = thread;
			#endif
			if (right_align_hext_id) {
				snprintf(buffer, length, "%*X", length - 1, static_cast<unsigned>(thread_id));
			} else {
				snprintf(buffer, length, "%X", static_cast<unsigned>(thread_id));
			}
		}
#else // LOGURU_PTHREADS
		buffer[0] = 0;
#endif // LOGURU_PTHREADS

}

int main()
{
	char* buffer = new char[11];
        std::cout << "Hi!" << std::endl;
	//std::cout << get_thread_name_ptls() << std::endl;
	std::cout << "Hello, world!" << std::endl;
	get_thread_name(buffer, 11, false);
	std::cout << buffer << std::endl;
        delete[] buffer;
	return 0;
}
