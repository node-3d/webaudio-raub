#ifndef _AUDIO_TIMESTAMP_HPP_
#define _AUDIO_TIMESTAMP_HPP_


#include "common.hpp"


class AudioTimestamp : public CommonNode<AudioTimestamp> {
	
public:
	
	~AudioTimestamp();
	explicit AudioTimestamp(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioTimestamp(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	AudioTimestamp();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	double _contextTime;
	double _performanceTime;
	
	
private:
	
	JS_DECLARE_METHOD(destroy);
	JS_DECLARE_GETTER(isDestroyed);
	
	
	
	JS_DECLARE_GETTER(contextTime);
	JS_DECLARE_SETTER(contextTime);
	
	JS_DECLARE_GETTER(performanceTime);
	JS_DECLARE_SETTER(performanceTime);
	
};


#endif // _AUDIO_TIMESTAMP_HPP_
