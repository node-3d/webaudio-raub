#ifndef _PERIODIC_WAVE_HPP_
#define _PERIODIC_WAVE_HPP_


#include <addon-tools.hpp>


class PeriodicWave : public Napi::ObjectWrap<PeriodicWave> {
	
public:
	
	~PeriodicWave();
	PeriodicWave(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isPeriodicWave(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit PeriodicWave(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	PeriodicWave();
	
	static Napi::FunctionReference _ctorPeriodicWave;
	
	bool _isDestroyed;
	
	
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _PERIODIC_WAVE_HPP_
