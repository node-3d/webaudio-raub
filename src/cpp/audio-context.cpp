#include "audio-context.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioContext::AudioContext() : BaseAudioContext() {
	
	_isDestroyed = false;
	
}


AudioContext::AudioContext(float sampleRate) : BaseAudioContext(sampleRate) {
	
	_isDestroyed = false;
	
}


AudioContext::~AudioContext() {
	
	_destroy();
	
}


void AudioContext::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	BaseAudioContext::_destroy();
	
}


// ------ Methods and props


JS_METHOD(AudioContext::suspend) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::close) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::getOutputTimestamp) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::createMediaElementSource) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaElement);
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::createMediaStreamSource) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaStream);
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::createMediaStreamDestination) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_GETTER(AudioContext::baseLatencyGetter) { THIS_CHECK;
	
	RET_NUM(_baseLatency);
	
}


// ------ System methods and props for ObjectWrap

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


AudioContext::AudioContext(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioContext>(info) {
	
	CTOR_CHECK("AudioContext");
	
	AudioContext *audioContext = nullptr;
	
	if (info.Length() > 0) {
		
		REQ_OBJ_ARG(0, opts);
		
		if (opts->Has(JS_STR("sampleRate"))) {
			
			if ( !opts->Get(JS_STR("sampleRate"))->IsNumber() ) {
				return JS_THROW("Type of 'opts.sampleRate' must be 'number'.");
			}
			
			float sampleRate = static_cast<float>(
				Nan::Get(
					opts,
					JS_STR("sampleRate")
				).ToLocalChecked().As<v8::Number>()->Value()
			);
			audioContext = new AudioContext(sampleRate);
			
		}
		
	}
	
	if ( !audioContext ) {
		audioContext = new AudioContext();
	}
	
	
	audioContext->finishNew(info.This());
	
}


JS_METHOD(AudioContext::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(AudioContext::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
