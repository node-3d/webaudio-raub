#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/extended/AudioFileReader.h>
#include <LabSound/core/AudioContext.h>
#include <LabSound/core/DefaultAudioDestinationNode.h>
#include <LabSound/core/AudioListener.h>

#include "base-audio-context.hpp"
#include "audio-buffer.hpp"
#include "audio-listener.hpp"

// Nodes
// #include "analyser-node.hpp"
#include "audio-buffer-source-node.hpp"
#include "audio-destination-node.hpp"
// #include "audio-worklet-node.hpp"
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
#include "oscillator-node.hpp"
#include "panner-node.hpp"
// #include "script-processor-node.hpp"
// #include "stereo-panner-node.hpp"
// #include "wave-shaper-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_BASE_AUDIO_CONTEXT                                               \
	BaseAudioContext *baseAudioContext = Nan::ObjectWrap::Unwrap<BaseAudioContext>(info.This());

#define THIS_CHECK                                                            \
	if (baseAudioContext->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (baseAudioContext->CACHE == V) {                                       \
		return;                                                               \
	}                                                                         \
	baseAudioContext->CACHE = V;

#define NODE_CREATOR(M, C)                                                    \
NAN_METHOD(BaseAudioContext::create ## M) {                                   \
	THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;                                      \
	info.GetReturnValue().Set(C ## Node::getNew(info.This()));                \
}


bool compareMagic(const uint8_t *data, const int16_t *magic) {
	
	for (int i = 0; magic[i] != -2; i++) {
		
		if (magic[i] >= 0 && data[i] != magic[i]) {
			return false;
		}
		
	}
	
	return true;
	
}

string getExtension(const uint8_t *data) {
	
	static const int16_t wv[] = { 'w', 'v', 'p', 'k', -2 };
	static const int16_t wav[] = { 0x52, 0x49, 0x46, 0x46, -1, -1, -1, -1, 0x57, 0x41, 0x56, 0x45, -2 };
	static const int16_t flac[] = { 0x66, 0x4C, 0x61, 0x43, -2 };
	static const int16_t pat[] = { 0x47, 0x50, 0x41, 0x54, -2 };
	static const int16_t mid[] = { 0x4D, 0x54, 0x68, 0x64, -2 };
	static const int16_t opus[] = { 'O', 'p', 'u', 's', 'H', 'e', 'a', 'd', -2 };
	static const int16_t ogg[] = { 0x4F, 0x67, 0x67, 0x53, 0x00, 0x02, 0x00, 0x00, -2 };
	
	static const int16_t * numbers[] = { wv, wav, flac, pat, mid, opus, ogg, nullptr };
	static const char* extensions[] = { "wv", "wav", "flac", "pat", "mid", "opus", "ogg" };
	
	for (int i = 0; numbers[i] != nullptr; i++) {
		
		if (compareMagic(data, numbers[i])) {
			return extensions[i];
		}
		
	}
	
	return "";
	
}



// ------ Constructor and Destructor

BaseAudioContext::BaseAudioContext(bool isOffline, float sampleRate) {
	
	_isDestroyed = false;
	
	_impl.reset(new lab::AudioContext(isOffline));
	
	_impl->setDestinationNode(
		std::make_shared<lab::DefaultAudioDestinationNode>(
			_impl.get(), sampleRate
		)
	);
	_impl->lazyInitialize();
	
	_state = "running";
	
}


BaseAudioContext::~BaseAudioContext() {
	
	_destroy();
	
}


BaseAudioContext::CtxPtr BaseAudioContext::getContext() const {
	return _impl;
}


void BaseAudioContext::storeDestination(V8_VAR_OBJ context) {
	
	V8_VAR_OBJ node = AudioDestinationNode::getNew(context, _impl->destination());
	_destination.Reset(node);
	
	V8_VAR_OBJ listener = AudioListener::getNew(context, AudioListener::ListenerPtr(&_impl->listener()));
	_listener.Reset(listener);
	
}


void BaseAudioContext::_destroy() { DES_CHECK;
	
	if (_state != "closed") {
		_state = "closed";
	}
	
	_isDestroyed = true;
	
	_impl.reset();
	
}


// ------ Methods and props


NAN_METHOD(BaseAudioContext::createBuffer) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_INT32_ARG(0, numberOfChannels);
	REQ_INT32_ARG(1, numberOfFrames);
	REQ_FLOAT_ARG(2, sampleRate);
	
	// TODO: do something?
	
}


NAN_METHOD(BaseAudioContext::decodeAudioData) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_OBJ_ARG(0, audioData);
	REQ_FUN_ARG(1, successCallback);
	
	size_t len = Nan::Get(audioData, JS_STR("length")).ToLocalChecked()->Uint32Value();
	
	uint8_t *data = reinterpret_cast<uint8_t *>(node::Buffer::Data(audioData));
	vector<uint8_t> dataVec(data, data + len);
	
	string ext = getExtension(data);
	
	AudioBuffer::BusPtr bus = lab::MakeBusFromMemory(dataVec, ext, false);
	
	V8_VAR_VAL buffer = AudioBuffer::getNew(bus);
	
	Nan::Callback callback(successCallback);
	
	if (!callback.IsEmpty()) {
		Nan::AsyncResource async("BaseAudioContext::decodeAudioData()");
		callback.Call(1, &buffer, &async);
	}
	
}


NODE_CREATOR(BufferSource, AudioBufferSource);
// NODE_CREATOR(ConstantSource, ConstantSource);
NODE_CREATOR(Gain, Gain);
NODE_CREATOR(BiquadFilter, BiquadFilter);
// NODE_CREATOR(WaveShaper, WaveShaper);
NODE_CREATOR(Panner, Panner);
NODE_CREATOR(Convolver, Convolver);
// NODE_CREATOR(DynamicsCompressor, DynamicsCompressor);
// NODE_CREATOR(Analyser, Analyser);
// NODE_CREATOR(StereoPanner, StereoPanner);
NODE_CREATOR(Oscillator, Oscillator);



NAN_METHOD(BaseAudioContext::createIIRFilter) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_OBJ_ARG(0, feedForward);
	REQ_OBJ_ARG(1, feedBack);
	
	// TODO: do something?
	
}


NAN_METHOD(BaseAudioContext::createDelay) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	LET_DOUBLE_ARG(0, delay);
	
	if (delay == 0.0) {
		delay = 1;
	}
	
	info.GetReturnValue().Set(DelayNode::getNew(info.This(), delay));
	
}


NAN_METHOD(BaseAudioContext::createScriptProcessor) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_INT32_ARG(0, bufferSize);
	REQ_INT32_ARG(1, numberOfInputChannels);
	REQ_INT32_ARG(2, numberOfOutputChannels);
	
	// TODO: do something?
	
}


NAN_METHOD(BaseAudioContext::createPeriodicWave) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_OBJ_ARG(0, real);
	REQ_OBJ_ARG(1, imag);
	REQ_OBJ_ARG(2, options);
	
	// TODO: do something?
	
}


NAN_METHOD(BaseAudioContext::createChannelSplitter) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_INT32_ARG(0, numberOfOutputs);
	
	// TODO: do something?
	
}


NAN_METHOD(BaseAudioContext::createChannelMerger) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_INT32_ARG(0, numberOfInputs);
	
	// TODO: do something?
	
}


NAN_METHOD(BaseAudioContext::resume) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


NAN_METHOD(BaseAudioContext::createMediaElementSource) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaElement);
	
	// TODO: do something?
	
}


NAN_METHOD(BaseAudioContext::createMediaStreamSource) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaStream);
	
	// TODO: do something?
	
}


NAN_METHOD(BaseAudioContext::createMediaStreamDestination) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	// TODO: do something?
	
}


NAN_GETTER(BaseAudioContext::destinationGetter) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(baseAudioContext->_destination));
	
}


NAN_GETTER(BaseAudioContext::currentTimeGetter) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(baseAudioContext->_currentTime));
	
}


NAN_GETTER(BaseAudioContext::sampleRateGetter) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(baseAudioContext->_sampleRate));
	
}


NAN_GETTER(BaseAudioContext::listenerGetter) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(baseAudioContext->_listener));
	
}


NAN_GETTER(BaseAudioContext::stateGetter) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	RET_VALUE(JS_UTF8(baseAudioContext->_state));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT BaseAudioContext::_protoBaseAudioContext;
V8_STORE_FUNC BaseAudioContext::_ctorBaseAudioContext;


void BaseAudioContext::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class BaseAudioContext inherits EventEmitter
	V8_VAR_FT parent = Nan::New(EventEmitter::_protoEventEmitter);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("BaseAudioContext"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, destination);
	ACCESSOR_R(obj, currentTime);
	ACCESSOR_R(obj, sampleRate);
	ACCESSOR_R(obj, listener);
	ACCESSOR_R(obj, state);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "createBuffer", createBuffer);
	Nan::SetPrototypeMethod(proto, "decodeAudioData", decodeAudioData);
	Nan::SetPrototypeMethod(proto, "createBufferSource", createBufferSource);
	// Nan::SetPrototypeMethod(proto, "createConstantSource", createConstantSource);
	Nan::SetPrototypeMethod(proto, "createGain", createGain);
	Nan::SetPrototypeMethod(proto, "createDelay", createDelay);
	Nan::SetPrototypeMethod(proto, "createBiquadFilter", createBiquadFilter);
	Nan::SetPrototypeMethod(proto, "createIIRFilter", createIIRFilter);
	// Nan::SetPrototypeMethod(proto, "createWaveShaper", createWaveShaper);
	Nan::SetPrototypeMethod(proto, "createPanner", createPanner);
	Nan::SetPrototypeMethod(proto, "createConvolver", createConvolver);
	// Nan::SetPrototypeMethod(proto, "createDynamicsCompressor", createDynamicsCompressor);
	// Nan::SetPrototypeMethod(proto, "createAnalyser", createAnalyser);
	Nan::SetPrototypeMethod(proto, "createScriptProcessor", createScriptProcessor);
	// Nan::SetPrototypeMethod(proto, "createStereoPanner", createStereoPanner);
	Nan::SetPrototypeMethod(proto, "createOscillator", createOscillator);
	Nan::SetPrototypeMethod(proto, "createPeriodicWave", createPeriodicWave);
	Nan::SetPrototypeMethod(proto, "createChannelSplitter", createChannelSplitter);
	Nan::SetPrototypeMethod(proto, "createChannelMerger", createChannelMerger);
	Nan::SetPrototypeMethod(proto, "createMediaElementSource", createMediaElementSource);
	Nan::SetPrototypeMethod(proto, "createMediaStreamSource", createMediaStreamSource);
	Nan::SetPrototypeMethod(proto, "createMediaStreamDestination", createMediaStreamDestination);
	Nan::SetPrototypeMethod(proto, "resume", resume);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoBaseAudioContext.Reset(proto);
	_ctorBaseAudioContext.Reset(ctor);
	
	Nan::Set(target, JS_STR("BaseAudioContext"), ctor);
	
	
}


NAN_METHOD(BaseAudioContext::newCtor) {
	
	Nan::ThrowTypeError("Use 'AudioContext' or 'OfflineAudioContext' instead.");
	
}


NAN_METHOD(BaseAudioContext::destroy) { THIS_BASE_AUDIO_CONTEXT; THIS_CHECK;
	
	baseAudioContext->_destroy();
	
}


NAN_GETTER(BaseAudioContext::isDestroyedGetter) { THIS_BASE_AUDIO_CONTEXT;
	
	RET_VALUE(JS_BOOL(baseAudioContext->_isDestroyed));
	
}
