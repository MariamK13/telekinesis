#ifndef MYALLOCATOR_H_
#define MYALLOCATOR_H_

template <typename T>
class MyAllocator{
	char storage[3000];
	bool flag = false;
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
	MyAllocator() = default;
	~MyAllocator() = default;
	MyAllocator(const MyAllocator& other) = default;
	
	pointer allocate(size_type count) {
		if(!flag) {
	 	return static_cast<pointer>(static_cast<void*>(storage));
	 } else {
	 	return static_cast<pointer>(static_cast<void*>(storage+1500));
	 	}
	 	flag = !flag;
	  };
	void deallocate(void* ptr, size_type count) {}
	template <typename ... Args>
	void construct(pointer ptr,  Args ... args) { construct_at(ptr, std::forward<Args>(args)...); }
	void destroy(pointer ptr) { destroy_at(ptr); }

};


#endif
