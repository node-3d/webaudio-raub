#ifndef _AUDIO_TIMESTAMP_HPP_
#define _AUDIO_TIMESTAMP_HPP_


#include <addon-tools.hpp>


class AudioTimestamp : public Napi::ObjectWrap<AudioTimestamp> {
	
public:
	
	~AudioTimestamp();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioTimestamp(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AudioTimestamp(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioTimestamp();
	
	static Napi::FunctionReference _ctorAudioTimestamp;
	
	bool _isDestroyed;
	
	double _contextTime;
	double _performanceTime;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(contextTimeGetter);
	JS_SETTER(contextTimeSetter);
	
	JS_GETTER(performanceTimeGetter);
	JS_SETTER(performanceTimeSetter);
	
};


#endif // _AUDIO_TIMESTAMP_HPP_
