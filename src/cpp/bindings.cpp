#include "analyser-node.hpp"
#include "audio-buffer.hpp"
#include "audio-buffer-source-node.hpp"
#include "audio-context.hpp"
#include "audio-destination-node.hpp"
#include "audio-listener.hpp"
#include "audio-node.hpp"
#include "audio-param.hpp"
#include "audio-setting.hpp"
#include "audio-scheduled-source-node.hpp"
#include "base-audio-context.hpp"
#include "biquad-filter-node.hpp"
// #include "channel-merger-node.hpp"
// #include "channel-splitter-node.hpp"
// #include "constant-source-node.hpp"
#include "convolver-node.hpp"
#include "delay-node.hpp"
// #include "dynamics-compressor-node.hpp"
#include "gain-node.hpp"
// #include "iir-filter-node.hpp"
// #include "media-element-audio-source-node.hpp"
// #include "media-stream-audio-destination-node.hpp"
// #include "media-stream-audio-source-node.hpp"
// #include "offline-audio-context.hpp"
#include "oscillator-node.hpp"
#include "panner-node.hpp"
// #include "periodic-wave.hpp"
// #include "script-processor-node.hpp"
// #include "stereo-panner-node.hpp"
// #include "wave-shaper-node.hpp"


Napi::Object initModule(Napi::Env env, Napi::Object exports) {
	log_set_level(LOGLEVEL_WARN);
	
	BaseAudioContext::init(env, exports);
	AudioContext::init(env, exports);
	// // // OfflineAudioContext::init(env, exports);
	
	AudioBuffer::init(env, exports);
	AudioListener::init(env, exports);
	
	AudioParam::init(env, exports);
	AudioSetting::init(env, exports);
	
	// // // PeriodicWave::init(env, exports);
	// // // OfflineAudioCompletionEvent::init(env, exports);
	
	AudioNode::init(env, exports);
	
	AudioDestinationNode::init(env, exports);
	AudioScheduledSourceNode::init(env, exports);
	
	AnalyserNode::init(env, exports);
	AudioBufferSourceNode::init(env, exports);
	
	BiquadFilterNode::init(env, exports);
	// // // ChannelMergerNode::init(env, exports);
	// // // ChannelSplitterNode::init(env, exports);
	// ConstantSourceNode::init(env, exports);
	ConvolverNode::init(env, exports);
	DelayNode::init(env, exports);
	// // // DynamicsCompressorNode::init(env, exports);
	GainNode::init(env, exports);
	// // // IIRFilterNode::init(env, exports);
	// // // MediaElementAudioSourceNode::init(env, exports);
	// // // MediaStreamAudioDestinationNode::init(env, exports);
	// // // MediaStreamAudioSourceNode::init(env, exports);
	OscillatorNode::init(env, exports);
	PannerNode::init(env, exports);
	// // // ScriptProcessorNode::init(env, exports);
	// // // StereoPannerNode::init(env, exports);
	// // // WaveShaperNode::init(env, exports);
	
	return exports;
	
}


NODE_API_MODULE(webaudio, initModule)
