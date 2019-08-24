#include <LabSound/LabSound.h>

#include "audio-context.hpp"


Napi::FunctionReference AudioContext::_constructor;

void AudioContext::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioContext", {
		ACCESSOR_M(AudioContext, getOutputTimestamp),
		ACCESSOR_M(AudioContext, close),
		ACCESSOR_M(AudioContext, suspend),
		ACCESSOR_M(AudioContext, destroy),
		ACCESSOR_R(AudioContext, baseLatency),
		ACCESSOR_M(AudioContext, destroy)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("AudioContext", ctor);
	
}


AudioContext::AudioContext(const Napi::CallbackInfo &info):
Napi::ObjectWrap<AudioContext>(info),
CommonCtx(info, "AudioContext") { NAPI_ENV;
	
	CTOR_CHECK("AudioContext");
	
	if (info.Length() > 0) {
		LET_FLOAT_ARG(0, sampleRate);
		reset(std::move(
			lab::Sound::MakeRealtimeAudioContext(lab::Channels::Stereo, sampleRate)
		));
	} else {
		reset(std::move(
			lab::Sound::MakeRealtimeAudioContext(lab::Channels::Stereo)
		));
	}
	
	Napi::Object that = info.This().As<Napi::Object>();
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();
	std::vector<napi_value> args;
	args.push_back(JS_EXT(&_impl));
	_Super.Call(that, args);
	
	
	// audioContext->finishNew(info.This());
	
}


AudioContext::~AudioContext() {
	_destroy();
}


void AudioContext::_destroy() { DES_CHECK;
	CommonCtx::_destroy();
}


JS_METHOD(AudioContext::suspend) { THIS_CHECK;
	
	// TODO: do something?
	RET_UNDEFINED;
	
}


JS_METHOD(AudioContext::close) { THIS_CHECK;
	
	// TODO: do something?
	RET_UNDEFINED;
	
}


JS_METHOD(AudioContext::getOutputTimestamp) { THIS_CHECK;
	
	// TODO: do something?
	RET_UNDEFINED;
	
}


JS_GETTER(AudioContext::baseLatencyGetter) { THIS_CHECK;
	
	RET_NUM(_baseLatency);
	
}
