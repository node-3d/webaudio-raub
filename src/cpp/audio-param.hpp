#ifndef _AUDIO_PARAM_HPP_
#define _AUDIO_PARAM_HPP_


#include <memory>

#include <addon-tools.hpp>

namespace lab { class AudioParam; };


class AudioParam : public Napi::ObjectWrap<AudioParam> {
	
public:
	
	typedef std::shared_ptr<lab::AudioParam> ParamPtr;
	
	~AudioParam();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	// Make a new instance from C++ land
	explicit AudioParam(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	ParamPtr getParam() const;
	
	static bool isAudioParam(Napi::Object obj);
	
	
// Methods and props, available for children
protected:
	
	AudioParam(Napi::Object context, ParamPtr param);
	
	static Napi::FunctionReference _ctorAudioParam;
	
	bool _isDestroyed;
	
	ParamPtr _impl;
	Napi::ObjectReference _context;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(setValueAtTime);
	JS_METHOD(linearRampToValueAtTime);
	JS_METHOD(exponentialRampToValueAtTime);
	JS_METHOD(setTargetAtTime);
	JS_METHOD(setValueCurveAtTime);
	JS_METHOD(cancelScheduledValues);
	JS_METHOD(cancelAndHoldAtTime);
	
	JS_GETTER(valueGetter);
	JS_SETTER(valueSetter);
	
	JS_GETTER(defaultValueGetter);
	
	JS_GETTER(minValueGetter);
	
	JS_GETTER(maxValueGetter);
	
};


#endif // _AUDIO_PARAM_HPP_
