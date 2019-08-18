#include <LabSound/extended/AudioFileReader.h>
#include <LabSound/core/AudioContext.h>
#include <LabSound/core/DefaultAudioDestinationNode.h>
#include <LabSound/core/AudioListener.h>

#include "base-audio-context.hpp"
#include "audio-buffer.hpp"
#include "audio-listener.hpp"

// Nodes
// #include "analyser-node.hpp"
// #include "audio-buffer-source-node.hpp"
// #include "audio-destination-node.hpp"
// // #include "audio-worklet-node.hpp"
// #include "biquad-filter-node.hpp"
// // #include "channel-merger-node.hpp"
// // #include "channel-splitter-node.hpp"
// // #include "constant-source-node.hpp"
// #include "convolver-node.hpp"
// #include "delay-node.hpp"
// // #include "dynamics-compressor-node.hpp"
// #include "gain-node.hpp"
// // #include "iir-filter-node.hpp"
// // #include "media-element-audio-source-node.hpp"
// // #include "media-stream-audio-destination-node.hpp"
// // #include "media-stream-audio-source-node.hpp"
// #include "oscillator-node.hpp"
// #include "panner-node.hpp"
// #include "script-processor-node.hpp"
// #include "stereo-panner-node.hpp"
// #include "wave-shaper-node.hpp"
#include "common.hpp"



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


Napi::FunctionReference BaseAudioContext::_constructor;

void BaseAudioContext::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "BaseAudioContext", {
		ACCESSOR_M(BaseAudioContext, resume),
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


BaseAudioContext::BaseAudioContext(const Napi::CallbackInfo &info):
Napi::ObjectWrap<BaseAudioContext>(info) {  NAPI_ENV;
	
	REQ_EXT_ARG(0, extCtx);
	
	CtxPtr *ctx = reinterpret_cast<CtxPtr *>(extCtx->Value());
	
	reset(*ctx);
	
	_impl->setDestinationNode(
		std::make_shared<lab::DefaultAudioDestinationNode>(
			_impl.get(), 2, _impl->sampleRate()
		)
	);
	_impl->lazyInitialize();
	
	_state = "running";
	
	// Napi::Object node = AudioDestinationNode::create(context, _impl->destination());
	// _destination.Reset(node);
	
	// Napi::Object listener = AudioListener::getNew(
	// 	context,
	// 	AudioListener::ListenerPtr(&_impl->listener())
	// );
	// _listener.Reset(listener);
	
	// Napi::Function startUpdater = Napi::Function::Cast(
	// 	Napi::Function::Cast(Nan::New(_constructor))->Get(
	// 		JS_STR("startUpdater")
	// 	)
	// );
	// Nan::Callback startUpdaterCb(startUpdater);
	
	// Napi::Value argv = context;
	// Nan::AsyncResource async("BaseAudioContext::finishNew()");
	// startUpdaterCb.Call(1, &argv, &async);
	
}


BaseAudioContext::~BaseAudioContext() {
	
	_destroy();
	
}


void BaseAudioContext::_destroy() { DES_CHECK;
	
	// Napi::Function stopUpdater = Napi::Function::Cast(
	// 	Napi::Function::Cast(Nan::New(_constructor))->Get(
	// 		JS_STR("stopUpdater")
	// 	)
	// );
	// Nan::Callback stopUpdaterCb(stopUpdater);
	
	// Napi::Object that = info.This().As<Napi::Object>();
	// Napi::Function _Super = that.Get("stopUpdater").As<Napi::Function>();
	// std::vector<napi_value> args;
	// args.push_back(context);
	// _Super.Call(that, args);
	
	// Napi::Value argv = handle();
	// Nan::AsyncResource async("BaseAudioContext::_destroy()");
	// stopUpdaterCb.Call(1, &argv, &async);
	
	// if (_state != "closed") {
	// 	_state = "closed";
	// }
	
	CommonCtx::_destroy();
	
}


// ------ Methods and props


JS_METHOD(BaseAudioContext::decodeAudioData) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, audioData);
	REQ_FUN_ARG(1, successCallback);
	
	int len;
	uint8_t *data = getArrayData(env, audioData, &len)
	
	vector<uint8_t> dataVec(data, data + len);
	
	std::string ext = getExtension(data);
	
	AudioBuffer::BusPtr bus = lab::MakeBusFromMemory(dataVec, ext, false);
	
	Napi::Object buffer = AudioBuffer::create(bus);
	
	std::vector<napi_value> args;
	args.push_back(buffer);
	successCallback.Call(args);
	
}


JS_METHOD(BaseAudioContext::update) { THIS_CHECK;
	
	_impl->dispatchEvents();
	
}


JS_METHOD(BaseAudioContext::resume) { THIS_CHECK;
	
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
