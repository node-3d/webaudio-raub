#include "audio-context.hpp"


IMPLEMENT_ES5_CLASS(AudioContext);

void AudioContext::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(getOutputTimestamp);
	JS_ASSIGN_METHOD(close);
	JS_ASSIGN_METHOD(suspend);
	JS_ASSIGN_GETTER(baseLatency);
	JS_ASSIGN_METHOD(destroy);
	
	exports.Set("AudioContext", ctor);
	
}


AudioContext::AudioContext(const Napi::CallbackInfo &info):
CommonCtx(info.This(), "AudioContext") { NAPI_ENV;
	
	if (info.Length() > 0) {
		LET_FLOAT_ARG(0, sampleRate);
		reset(std::move(
			lab::Sound::MakeRealtimeAudioContext(lab::Channels::Stereo, sampleRate)
		));
	} else {
		std::cout << "BEFORE" << std::endl;
		
		std::shared_ptr<lab::AudioContext> ctx
			= std::make_shared<lab::AudioContext>(false);
		std::cout << "C 111" << std::endl;
		
		std::shared_ptr<lab::DefaultAudioDestinationNode> dest =
			std::make_shared<lab::DefaultAudioDestinationNode>(
				ctx.get(),
				lab::Channels::Stereo,
				LABSOUND_DEFAULT_SAMPLERATE
			);
		std::cout << "C 222" << std::endl;
		
		ctx->setDestinationNode(dest);
		std::cout << "C 333" << std::endl;
		
		ctx->lazyInitialize();
		// std::cout << "C 444" << std::endl;
		
		// std::unique_ptr<lab::AudioContext> unique =
		// 	lab::Sound::MakeRealtimeAudioContext(lab::Channels::Stereo);
		// std::cout << "UNIQUE" << std::endl;
		// std::shared_ptr<lab::AudioContext> shared = std::move(unique);
		std::cout << "AFTER" << std::endl;
		
		
		reset(ctx);
		
	}
	
	Napi::Value argv[] = {
		static_cast<Napi::Value>(JS_EXT(&_impl))
	};
	super(info, 1, argv);
	
}


AudioContext::~AudioContext() {
	_destroy();
}


void AudioContext::_destroy() { DES_CHECK;
	CommonCtx::_destroy();
}


JS_IMPLEMENT_METHOD(AudioContext, suspend) { THIS_CHECK;
	
	// TODO: do something?
	RET_UNDEFINED;
	
}


JS_IMPLEMENT_METHOD(AudioContext, close) { THIS_CHECK;
	
	// TODO: do something?
	RET_UNDEFINED;
	
}


JS_IMPLEMENT_METHOD(AudioContext, getOutputTimestamp) { THIS_CHECK;
	
	// TODO: https://developer.mozilla.org/en-US/docs/Web/API/AudioContext/getOutputTimestamp
	RET_UNDEFINED;
	
}


JS_IMPLEMENT_GETTER(AudioContext, baseLatency) { THIS_CHECK;
	
	RET_NUM(_baseLatency);
	
}


JS_IMPLEMENT_METHOD(AudioContext, destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
