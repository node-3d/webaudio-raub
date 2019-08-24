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
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(contextTimeGetter);
	JS_SETTER(contextTimeSetter);
	
	JS_GETTER(performanceTimeGetter);
	JS_SETTER(performanceTimeSetter);
	
};


#endif // _AUDIO_TIMESTAMP_HPP_
