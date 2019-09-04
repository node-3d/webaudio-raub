#ifndef _BASE_AUDIO_CONTEXT_HPP_
#define _BASE_AUDIO_CONTEXT_HPP_

#include "common.hpp"


class BaseAudioContext : public CommonCtx<BaseAudioContext> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	
	explicit BaseAudioContext(const Napi::CallbackInfo &info);
	~BaseAudioContext();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	Napi::ObjectReference _destination;
	Napi::ObjectReference _listener;
	std::string _state;
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_METHOD(update);
	JS_DECLARE_METHOD(resume);
	JS_DECLARE_METHOD(decodeAudioData);
	
	JS_DECLARE_GETTER(destination);
	JS_DECLARE_GETTER(currentTime);
	JS_DECLARE_GETTER(sampleRate);
	JS_DECLARE_GETTER(listener);
	JS_DECLARE_GETTER(state);
	
};


#endif // _BASE_AUDIO_CONTEXT_HPP_
