#include "audio-context.hpp"


// Returns input, output
inline std::pair<
	lab::AudioStreamConfig,
	lab::AudioStreamConfig
> GetDefaultAudioDeviceConfiguration(const float sampleRate) {
	lab::AudioStreamConfig inputConfig;
	lab::AudioStreamConfig outputConfig;
	
	const std::vector<lab::AudioDeviceInfo> audioDevices = lab::MakeAudioDeviceList();
	const uint32_t default_output_device = (lab::GetDefaultOutputAudioDeviceIndex()).index;
	const uint32_t default_input_device = (lab::GetDefaultInputAudioDeviceIndex()).index;
	
	lab::AudioDeviceInfo defaultOutputInfo;
	lab::AudioDeviceInfo defaultInputInfo;
	for (auto &info : audioDevices) {
		if (info.index == default_output_device) {
			defaultOutputInfo = info;
		} else if (info.index == default_input_device) {
			defaultInputInfo = info;
		}
	}
	
	if (defaultOutputInfo.index != -1) {
		outputConfig.device_index = defaultOutputInfo.index;
		outputConfig.desired_channels = std::min(
			uint32_t(2),
			defaultOutputInfo.num_output_channels
		);
		outputConfig.desired_samplerate = sampleRate < 0
			? defaultOutputInfo.nominal_samplerate
			: sampleRate;
	}
	
	return { inputConfig, outputConfig };
}


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
	float sampleRate = IS_ARG_EMPTY(0) ? (-1) : info[0].ToNumber().FloatValue();
	const auto config = GetDefaultAudioDeviceConfiguration(sampleRate);
	
	reset(std::move(
		lab::MakeRealtimeAudioContext(config.second, config.first)
	));
	
	napi_value argv[] = { JS_EXT(&_impl) };
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
