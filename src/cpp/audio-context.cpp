#include <LabSound/LabSound.h>
#include <iostream>
#include "audio-context.hpp"


Napi::FunctionReference AudioContext::_constructor;

void AudioContext::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(getOutputTimestamp);
	JS_ASSIGN_METHOD(close);
	JS_ASSIGN_METHOD(suspend);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(baseLatency);
		ACCESSOR_M(AudioContext, destroy)
	});
	
	exports.Set("AudioContext", ctor);
	
}


AudioContext::AudioContext(const Napi::CallbackInfo &info):
CommonCtx<AudioContext>(info, "AudioContext") { NAPI_ENV;
	super(info);
	std::cout << "lolo 1" << std::endl;
	// CTOR_CHECK("AudioContext");
	std::cout << "lolo 2" << std::endl;
	if (info.Length() > 0) {
		// LET_FLOAT_ARG(0, sampleRate);
		// reset(std::move(
		// 	lab::Sound::MakeRealtimeAudioContext(lab::Channels::Stereo, sampleRate)
		// ));
	} else {
		std::cout << "lolo 3" << std::endl;
		reset(std::move(
			lab::Sound::MakeRealtimeAudioContext(lab::Channels::Stereo)
		));
		std::cout << "lolo 4" << std::endl;
	}
	std::cout << "lolo 5" << std::endl;
	Napi::Object that = info.This().As<Napi::Object>();std::cout << "lolo 6" << std::endl;
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();std::cout << "lolo 7" << std::endl;
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();std::cout << "lolo 8" << std::endl;
	std::vector<napi_value> args;std::cout << "lolo 9" << std::endl;
	// args.push_back(JS_EXT(&_impl));std::cout << "lolo 10" << std::endl;
	args.push_back(JS_NUM(reinterpret_cast<size_t>(&_impl)));std::cout << "lolo 10" << std::endl;
	consoleLog(env, 1, &_Super);
	_Super.Call(that, args);
	std::cout << "lolo 11 CALLED!" << std::endl;
	
	
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


JS_METHOD(AudioContext::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
