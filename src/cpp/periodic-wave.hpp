#ifndef _PERIODIC_WAVE_HPP_
#define _PERIODIC_WAVE_HPP_


#include "common.hpp"


class PeriodicWave : public CommonNode<PeriodicWave> {
	
public:
	
	~PeriodicWave();
	explicit PeriodicWave(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isPeriodicWave(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	PeriodicWave();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	
	
	
private:
	
	JS_DECLARE_METHOD(destroy);
	JS_DECLARE_GETTER(isDestroyed);
	
	
	
};


#endif // _PERIODIC_WAVE_HPP_
