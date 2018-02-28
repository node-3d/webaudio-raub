#include <cstdlib>

#include "classes/ADSRNode.hpp"
#include "classes/AnalyserNode.hpp"
#include "classes/AudioBasicInspectorNode.hpp"
#include "classes/AudioBasicProcessorNode.hpp"
#include "classes/AudioBus.hpp"
#include "classes/AudioChannel.hpp"
#include "classes/AudioContext.hpp"
#include "classes/AudioDestinationNode.hpp"
#include "classes/AudioFileReader.hpp"
#include "classes/AudioHardwareSourceNode.hpp"
#include "classes/AudioNode.hpp"
#include "classes/AudioNodeInput.hpp"
#include "classes/AudioNodeOutput.hpp"
#include "classes/AudioParam.hpp"
#include "classes/AudioParamTimeline.hpp"
#include "classes/AudioScheduledSourceNode.hpp"
#include "classes/AudioSummingJunction.hpp"
#include "classes/BiquadFilterNode.hpp"
#include "classes/BPMDelay.hpp"
#include "classes/ChannelMergerNode.hpp"
#include "classes/ChannelSplitterNode.hpp"
#include "classes/ClipNode.hpp"
#include "classes/ConvolverNode.hpp"
#include "classes/DefaultAudioDestinationNode.hpp"
#include "classes/DelayNode.hpp"
#include "classes/DiodeNode.hpp"
#include "classes/DynamicsCompressorNode.hpp"
#include "classes/FunctionNode.hpp"
#include "classes/GainNode.hpp"
#include "classes/LabSound.hpp"
#include "classes/NoiseNode.hpp"
#include "classes/OfflineAudioDestinationNode.hpp"
#include "classes/OscillatorNode.hpp"
#include "classes/PannerNode.hpp"
#include "classes/PdNode.hpp"
#include "classes/PeakCompNode.hpp"
#include "classes/PingPongDelayNode.hpp"
#include "classes/PowerMonitorNode.hpp"
#include "classes/PWMNode.hpp"
#include "classes/RealtimeAnalyser.hpp"
#include "classes/RecorderNode.hpp"
#include "classes/SampledAudioNode.hpp"
#include "classes/SampledInstrumentNode.hpp"
#include "classes/SfxrNode.hpp"
#include "classes/SpatializationNode.hpp"
#include "classes/SpectralMonitorNode.hpp"
#include "classes/StereoPannerNode.hpp"
#include "classes/SupersawNode.hpp"
#include "classes/WaveShaperNode.hpp"
#include "classes/WaveTable.hpp"


using namespace v8;
using namespace node;
using namespace std;


extern "C" {


void init(Handle<Object> target) {
	
	ADSRNode::init(target);
	AnalyserNode::init(target);
	AudioBasicInspectorNode::init(target);
	AudioBasicProcessorNode::init(target);
	AudioBus::init(target);
	AudioChannel::init(target);
	AudioContext::init(target);
	AudioDestinationNode::init(target);
	AudioFileReader::init(target);
	AudioHardwareSourceNode::init(target);
	AudioNode::init(target);
	AudioNodeInput::init(target);
	AudioNodeOutput::init(target);
	AudioParam::init(target);
	AudioParamTimeline::init(target);
	AudioScheduledSourceNode::init(target);
	AudioSummingJunction::init(target);
	BiquadFilterNode::init(target);
	BPMDelay::init(target);
	ChannelMergerNode::init(target);
	ChannelSplitterNode::init(target);
	ClipNode::init(target);
	ConvolverNode::init(target);
	DefaultAudioDestinationNode::init(target);
	DelayNode::init(target);
	DiodeNode::init(target);
	DynamicsCompressorNode::init(target);
	FunctionNode::init(target);
	GainNode::init(target);
	LabSound::init(target);
	NoiseNode::init(target);
	OfflineAudioDestinationNode::init(target);
	OscillatorNode::init(target);
	PannerNode::init(target);
	PdNode::init(target);
	PeakCompNode::init(target);
	PingPongDelayNode::init(target);
	PowerMonitorNode::init(target);
	PWMNode::init(target);
	RealtimeAnalyser::init(target);
	RecorderNode::init(target);
	SampledAudioNode::init(target);
	SampledInstrumentNode::init(target);
	SfxrNode::init(target);
	SpatializationNode::init(target);
	SpectralMonitorNode::init(target);
	StereoPannerNode::init(target);
	SupersawNode::init(target);
	WaveShaperNode::init(target);
	WaveTable::init(target);
	
}


NODE_MODULE(NODE_GYP_MODULE_NAME, init);


} // extern "C"
