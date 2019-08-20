#ifndef _BASE_AUDIO_CONTEXT_HPP_
#define _BASE_AUDIO_CONTEXT_HPP_

#include "common.hpp"


class BaseAudioContext : public Napi::ObjectWrap<BaseAudioContext>, public CommonCtx {
	
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
	
	JS_METHOD(destroy);
	
	JS_METHOD(update);
	JS_METHOD(resume);
	JS_METHOD(decodeAudioData);
	
	JS_GETTER(destinationGetter);
	JS_GETTER(currentTimeGetter);
	JS_GETTER(sampleRateGetter);
	JS_GETTER(listenerGetter);
	JS_GETTER(stateGetter);
	
};


#endif // _BASE_AUDIO_CONTEXT_HPP_
