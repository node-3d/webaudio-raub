#ifndef _AUDIO_TIMESTAMP_HPP_
#define _AUDIO_TIMESTAMP_HPP_


#include <addon-tools.hpp>


class AudioTimestamp : public Napi::ObjectWrap<AudioTimestamp> {
	
public:
	
	~AudioTimestamp();
	AudioTimestamp(const Napi::CallbackInfo &info);
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioTimestamp(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AudioTimestamp(const Napi::CallbackInfo& info);
	
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
