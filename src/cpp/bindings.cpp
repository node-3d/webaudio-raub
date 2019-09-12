#include "analyser-node.hpp"
#include "audio-buffer.hpp"
#include "audio-buffer-source-node.hpp"
#include "audio-context.hpp"
#include "audio-destination-node.hpp"
#include "audio-listener.hpp"
#include "audio-node.hpp"
#include "audio-param.hpp"
// #include "audio-processing-event.hpp"
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
// #include "offline-audio-completion-event.hpp"
// #include "offline-audio-context.hpp"
#include "oscillator-node.hpp"
#include "panner-node.hpp"
// #include "periodic-wave.hpp"
// #include "script-processor-node.hpp"
// #include "stereo-panner-node.hpp"
// #include "wave-shaper-node.hpp"


template <typename Duration>
void Wait(Duration duration) {
	std::mutex wait;
	std::unique_lock<std::mutex> lock(wait);
	std::condition_variable cv;
	cv.wait_for(lock, duration);
}

Napi::Object initModule(Napi::Env env, Napi::Object exports) {
	
	auto context = lab::Sound::MakeRealtimeAudioContext(lab::Channels::Stereo);
	std::shared_ptr<lab::AudioBus> musicClip = lab::MakeBusFromFile(
		"C:/_projects/node-3d/webaudio-raub/examples/samples/trainrolling.wav",
		false
	);
	if ( ! musicClip ) {
		std::cerr << "Could not open " << "C:/_projects/node-3d/webaudio-raub/examples/samples/trainrolling.wav" << std::endl;
	}

	std::shared_ptr<lab::OscillatorNode> oscillator;
	std::shared_ptr<lab::SampledAudioNode> musicClipNode;
	std::shared_ptr<lab::GainNode> gain;

	oscillator = std::make_shared<lab::OscillatorNode>(context->sampleRate());
	gain = std::make_shared<lab::GainNode>();
	gain->gain()->setValue(0.0625f);

	musicClipNode = std::make_shared<lab::SampledAudioNode>();
	{
		lab::ContextRenderLock r(context.get(), "Simple");
		musicClipNode->setBus(r, musicClip);
	}
	context->connect(gain, musicClipNode, 0, 0);
	musicClipNode->start(0.0f);

	// osc -> gain -> destination
	context->connect(gain, oscillator, 0, 0);
	context->connect(context->destination(), gain, 0, 0);

	oscillator->frequency()->setValue(440.f);
	oscillator->setType(lab::OscillatorType::SINE);
	oscillator->start(0.0f);
	std::cout << "before 111" << std::endl;
	Wait(std::chrono::seconds(6));
	std::cout << "after 111" << std::endl;
	
	
	BaseAudioContext::init(env, exports);
	AudioContext::init(env, exports);
	// // // OfflineAudioContext::init(env, exports);
	
	AudioBuffer::init(env, exports);
	AudioListener::init(env, exports);
	
	AudioParam::init(env, exports);
	
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
	std::cout << "ret 111" << std::endl;
	return exports;
	
}


NODE_API_MODULE(webaudio, initModule)
