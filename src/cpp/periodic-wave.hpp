#ifndef _PERIODIC_WAVE_HPP_
#define _PERIODIC_WAVE_HPP_


#include <addon-tools.hpp>


class PeriodicWave : public Nan::ObjectWrap {
	
public:
	
	~PeriodicWave();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isPeriodicWave(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	PeriodicWave();
	
	static V8_STORE_FT _protoPeriodicWave;
	static V8_STORE_FUNC _ctorPeriodicWave;
	
	bool _isDestroyed;
	
	
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _PERIODIC_WAVE_HPP_
