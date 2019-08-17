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
#include "common.hpp"


// ------ Aux macros

#define NODE_CREATOR(M, C)                                                    \
JS_METHOD(BaseAudioContext::create ## M) { THIS_CHECK;                        \
	RET_VALUE(C ## Node::create(this));                                       \
}


bool compareMagic(const uint8_t *data, const int16_t *magic) {
	
	for (int i = 0; magic[i] != -2; i++) {
		
		if (magic[i] >= 0 && data[i] != magic[i]) {
			return false;
		}
		
	}
	
	return true;
	
}

std::string getExtension(const uint8_t *data) {
	
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
	
	_impl.reset(new lab::AudioContext(isOffline, false));
	
	_impl->setDestinationNode(
		std::make_shared<lab::DefaultAudioDestinationNode>(
			_impl.get(), 2, sampleRate
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


void BaseAudioContext::finishNew(Napi::Object context) {
	
	Napi::Object node = AudioDestinationNode::getNew(context, _impl->destination());
	_destination.Reset(node);
	
	Napi::Object listener = AudioListener::getNew(
		context,
		AudioListener::ListenerPtr(&_impl->listener())
	);
	_listener.Reset(listener);
	
	Napi::Function startUpdater = Napi::Function::Cast(
		Napi::Function::Cast(Nan::New(_constructor))->Get(
			JS_STR("startUpdater")
		)
	);
	Nan::Callback startUpdaterCb(startUpdater);
	
	Napi::Value argv = context;
	Nan::AsyncResource async("BaseAudioContext::finishNew()");
	startUpdaterCb.Call(1, &argv, &async);
	
}


void BaseAudioContext::_destroy() { DES_CHECK;
	
	Napi::Function stopUpdater = Napi::Function::Cast(
		Napi::Function::Cast(Nan::New(_constructor))->Get(
			JS_STR("stopUpdater")
		)
	);
	Nan::Callback stopUpdaterCb(stopUpdater);
	
	Napi::Value argv = handle();
	Nan::AsyncResource async("BaseAudioContext::_destroy()");
	stopUpdaterCb.Call(1, &argv, &async);
	
	if (_state != "closed") {
		_state = "closed";
	}
	
	_isDestroyed = true;
	
	_impl.reset();
	
}


// ------ Methods and props


JS_METHOD(BaseAudioContext::createBuffer) { THIS_CHECK;
	
	REQ_INT32_ARG(0, numberOfChannels);
	REQ_INT32_ARG(1, numberOfFrames);
	REQ_FLOAT_ARG(2, sampleRate);
	
	// TODO: do something?
	
}


JS_METHOD(BaseAudioContext::decodeAudioData) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, audioData);
	REQ_FUN_ARG(1, successCallback);
	
	size_t len = static_cast<size_t>(
		Nan::Get(
			audioData,
			JS_STR("length")
		).ToLocalChecked().As<v8::Integer>()->Value()
	);
	
	uint8_t *data = reinterpret_cast<uint8_t *>(node::Buffer::Data(audioData));
	vector<uint8_t> dataVec(data, data + len);
	
	std::string ext = getExtension(data);
	
	AudioBuffer::BusPtr bus = lab::MakeBusFromMemory(dataVec, ext, false);
	
	Napi::Value buffer = AudioBuffer::getNew(bus);
	
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



JS_METHOD(BaseAudioContext::createIIRFilter) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, feedForward);
	REQ_OBJ_ARG(1, feedBack);
	
	// TODO: do something?
	
}


JS_METHOD(BaseAudioContext::createDelay) { THIS_CHECK;
	
	LET_DOUBLE_ARG(0, delay);
	
	if (delay == 0.0) {
		delay = 1;
	}
	
	info.GetReturnValue().Set(DelayNode::getNew(info.This(), delay));
	
}


JS_METHOD(BaseAudioContext::createScriptProcessor) { THIS_CHECK;
	
	REQ_INT32_ARG(0, bufferSize);
	REQ_INT32_ARG(1, numberOfInputChannels);
	REQ_INT32_ARG(2, numberOfOutputChannels);
	
	// TODO: do something?
	
}


JS_METHOD(BaseAudioContext::createPeriodicWave) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, real);
	REQ_OBJ_ARG(1, imag);
	REQ_OBJ_ARG(2, options);
	
	// TODO: do something?
	
}


JS_METHOD(BaseAudioContext::createChannelSplitter) { THIS_CHECK;
	
	REQ_INT32_ARG(0, numberOfOutputs);
	
	// TODO: do something?
	
}


JS_METHOD(BaseAudioContext::createChannelMerger) { THIS_CHECK;
	
	REQ_INT32_ARG(0, numberOfInputs);
	
	// TODO: do something?
	
}


JS_METHOD(BaseAudioContext::update) { THIS_CHECK;
	
	_impl->dispatchEvents();
	
}


JS_METHOD(BaseAudioContext::resume) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_METHOD(BaseAudioContext::createMediaElementSource) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaElement);
	
	// TODO: do something?
	
}


JS_METHOD(BaseAudioContext::createMediaStreamSource) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, mediaStream);
	
	// TODO: do something?
	
}


JS_METHOD(BaseAudioContext::createMediaStreamDestination) { THIS_CHECK;
	
	// TODO: do something?
	
}


JS_GETTER(BaseAudioContext::destinationGetter) { THIS_CHECK;
	
	RET_VALUE(_destination.Value());
	
}


JS_GETTER(BaseAudioContext::currentTimeGetter) { THIS_CHECK;
	
	RET_NUM(_impl->currentTime());
	
}


JS_GETTER(BaseAudioContext::sampleRateGetter) { THIS_CHECK;
	
	RET_NUM(_impl->sampleRate());
	
}


JS_GETTER(BaseAudioContext::listenerGetter) { THIS_CHECK;
	
	RET_VALUE(_listener.Value());
	
}


JS_GETTER(BaseAudioContext::stateGetter) { THIS_CHECK;
	
	RET_STR(_state);
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference BaseAudioContext::_constructor;


void BaseAudioContext::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "BaseAudioContext", {
		ACCESSOR_M(BaseAudioContext, resume),
		ACCESSOR_M(BaseAudioContext, createMediaStreamDestination),
		ACCESSOR_M(BaseAudioContext, createMediaStreamSource),
		ACCESSOR_M(BaseAudioContext, createMediaElementSource),
		ACCESSOR_M(BaseAudioContext, createChannelMerger),
		ACCESSOR_M(BaseAudioContext, createChannelSplitter),
		ACCESSOR_M(BaseAudioContext, createPeriodicWave),
		ACCESSOR_M(BaseAudioContext, createOscillator),
		ACCESSOR_M(BaseAudioContext, createStereoPanner),
		ACCESSOR_M(BaseAudioContext, createScriptProcessor),
		ACCESSOR_M(BaseAudioContext, createAnalyser),
		ACCESSOR_M(BaseAudioContext, createDynamicsCompressor),
		ACCESSOR_M(BaseAudioContext, createConvolver),
		ACCESSOR_M(BaseAudioContext, createPanner),
		ACCESSOR_M(BaseAudioContext, createWaveShaper),
		ACCESSOR_M(BaseAudioContext, createIIRFilter),
		ACCESSOR_M(BaseAudioContext, createBiquadFilter),
		ACCESSOR_M(BaseAudioContext, createDelay),
		ACCESSOR_M(BaseAudioContext, createGain),
		ACCESSOR_M(BaseAudioContext, createConstantSource),
		ACCESSOR_M(BaseAudioContext, createBufferSource),
		ACCESSOR_M(BaseAudioContext, decodeAudioData),
		ACCESSOR_M(BaseAudioContext, createBuffer),
		ACCESSOR_M(BaseAudioContext, update),
		ACCESSOR_M(BaseAudioContext, destroy),
		ACCESSOR_R(BaseAudioContext, state),
		ACCESSOR_R(BaseAudioContext, listener),
		ACCESSOR_R(BaseAudioContext, sampleRate),
		ACCESSOR_R(BaseAudioContext, currentTime),
		ACCESSOR_R(BaseAudioContext, destination),
		ACCESSOR_R(BaseAudioContext, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("BaseAudioContext", ctor);
	
}


BaseAudioContext::BaseAudioContext(const Napi::CallbackInfo &info): Napi::ObjectWrap<BaseAudioContext>(info) {
	
	JS_THROW("Use 'AudioContext' or 'OfflineAudioContext' instead.");
	
}


JS_METHOD(BaseAudioContext::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(BaseAudioContext::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
