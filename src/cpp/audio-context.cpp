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


JS_METHOD(AudioContext::suspend) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::close) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::getOutputTimestamp) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::createMediaElementSource) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaElement);
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::createMediaStreamSource) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaStream);
	
	// TODO: do something?
	
}


JS_METHOD(AudioContext::createMediaStreamDestination) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


JS_GETTER(AudioContext::baseLatencyGetter) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_NUM(_baseLatency);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioContext::_ctorAudioContext;


void AudioContext::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, baseLatency);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "suspend", suspend);
	Nan::SetPrototypeMethod(proto, "close", close);
	Nan::SetPrototypeMethod(proto, "getOutputTimestamp", getOutputTimestamp);
	Nan::SetPrototypeMethod(proto, "createMediaElementSource", createMediaElementSource);
	Nan::SetPrototypeMethod(proto, "createMediaStreamSource", createMediaStreamSource);
	Nan::SetPrototypeMethod(proto, "createMediaStreamDestination", createMediaStreamDestination);
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "AudioContext", {
	
	});
	
	_ctorAudioContext = Napi::Persistent(ctor);
	_ctorAudioContext.SuppressDestruct();
	
	exports.Set("AudioContext", ctor);
	
}


JS_METHOD(AudioContext::newCtor) {
	
	CTOR_CHECK("AudioContext");
	
	AudioContext *audioContext = nullptr;
	
	if (info.Length() > 0) {
		
		REQ_OBJ_ARG(0, opts);
		
		if (opts->Has(JS_STR("sampleRate"))) {
			
			if ( !opts->Get(JS_STR("sampleRate"))->IsNumber() ) {
				return Nan::ThrowTypeError("Type of 'opts.sampleRate' must be 'number'.");
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
	
	audioContext->Wrap(info.This());
	
	audioContext->finishNew(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(AudioContext::destroy) { THIS_AUDIO_CONTEXT; THIS_CHECK;
	
	audioContext->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(AudioContext::isDestroyedGetter) { THIS_AUDIO_CONTEXT;
	
	RET_BOOL(_isDestroyed);
	
}
