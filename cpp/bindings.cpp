#include <cstdlib>

#include <event-emitter.hpp>

#include "analyser-node.hpp"
#include "audio-buffer.hpp"
#include "audio-buffer-source-node.hpp"
#include "audio-context.hpp"
#include "audio-destination-node.hpp"
#include "audio-listener.hpp"
#include "audio-node.hpp"
#include "audio-param.hpp"
#include "audio-processing-event.hpp"
#include "audio-scheduled-source-node.hpp"
#include "audio-timestamp.hpp"
#include "audio-worklet.hpp"
#include "audio-worklet-global-scope.hpp"
#include "audio-worklet-node.hpp"
#include "audio-worklet-processor.hpp"
#include "base-audio-context.hpp"
#include "biquad-filter-node.hpp"
#include "channel-merger-node.hpp"
#include "channel-splitter-node.hpp"
#include "constant-source-node.hpp"
#include "convolver-node.hpp"
#include "delay-node.hpp"
#include "dynamics-compressor-node.hpp"
#include "gain-node.hpp"
#include "iir-filter-node.hpp"
#include "media-element-audio-source-node.hpp"
#include "media-stream-audio-destination-node.hpp"
#include "media-stream-audio-source-node.hpp"
#include "offline-audio-completion-event.hpp"
#include "offline-audio-context.hpp"
#include "oscillator-node.hpp"
#include "panner-node.hpp"
#include "periodic-wave.hpp"
#include "script-processor-node.hpp"
#include "stereo-panner-node.hpp"
#include "wave-shaper-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


extern "C" {


void init(Local<Object> target) {
	
	EventEmitter::init(target);
	
	BaseAudioContext::init(target);
	AudioContext::init(target);
	// OfflineAudioContext::init(target);
	
	AudioBuffer::init(target);
	// AudioListener::init(target);
	AudioParam::init(target);
	// AudioProcessingEvent::init(target);
	// AudioTimestamp::init(target);
	// AudioWorklet::init(target);
	// AudioWorkletGlobalScope::init(target);
	// AudioWorkletProcessor::init(target);
	// PeriodicWave::init(target);
	// OfflineAudioCompletionEvent::init(target);
	
	AudioNode::init(target);
	
	AudioDestinationNode::init(target);
	AudioScheduledSourceNode::init(target);
	
	// AnalyserNode::init(target);
	AudioBufferSourceNode::init(target);
	
	// AudioWorkletNode::init(target);
	// BiquadFilterNode::init(target);
	// ChannelMergerNode::init(target);
	// ChannelSplitterNode::init(target);
	// ConstantSourceNode::init(target);
	ConvolverNode::init(target);
	// DelayNode::init(target);
	// DynamicsCompressorNode::init(target);
	GainNode::init(target);
	// IIRFilterNode::init(target);
	// MediaElementAudioSourceNode::init(target);
	// MediaStreamAudioDestinationNode::init(target);
	// MediaStreamAudioSourceNode::init(target);
	OscillatorNode::init(target);
	// PannerNode::init(target);
	// ScriptProcessorNode::init(target);
	// StereoPannerNode::init(target);
	// WaveShaperNode::init(target);
	
}


NODE_MODULE(waa, init);


} // extern "C"
