#include "audio-context.hpp"


Napi::FunctionReference AudioContext::_constructor;

void AudioContext::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioContext", {
		ACCESSOR_M(AudioContext, createMediaStreamDestination),
		ACCESSOR_M(AudioContext, createMediaStreamSource),
		ACCESSOR_M(AudioContext, createMediaElementSource),
		ACCESSOR_M(AudioContext, getOutputTimestamp),
		ACCESSOR_M(AudioContext, close),
		ACCESSOR_M(AudioContext, suspend),
		ACCESSOR_M(AudioContext, destroy),
		ACCESSOR_R(AudioContext, baseLatency),
		ACCESSOR_R(AudioContext, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("AudioContext", ctor);
	
}


AudioContext::AudioContext(const Napi::CallbackInfo &info):
Napi::ObjectWrap<AudioContext>(info) {  NAPI_ENV;
	
	CTOR_CHECK("AudioContext");
	
	AudioContext *audioContext = nullptr;
	// new lab::AudioContext(isOffline, false)
	if (info.Length() > 0) {
		
		REQ_OBJ_ARG(0, opts);
		
		if (opts.Has("sampleRate")) {
			
			if ( ! opts.Get("sampleRate").IsNumber() ) {
				JS_THROW("Type of 'opts.sampleRate' must be 'number'.");
				return;
			}
			
			float sampleRate = opts.Get("sampleRate").ToNumber().FloatValue();
			audioContext = new AudioContext(sampleRate);
			
		}
		
	}
	
	if ( !audioContext ) {
		audioContext = new AudioContext();
	}
	
	
	// audioContext->finishNew(info.This());
	
}


JS_METHOD(AudioContext::suspend) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::close) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::getOutputTimestamp) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_GETTER(AudioContext::baseLatencyGetter) { THIS_CHECK;
	
	RET_NUM(_baseLatency);
	
}
