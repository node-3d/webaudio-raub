#include <LabSound/LabSound.h>

#include "base-audio-context.hpp"
#include "audio-buffer.hpp"
#include "audio-listener.hpp"


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
		ACCESSOR_M(BaseAudioContext, update),
		ACCESSOR_R(BaseAudioContext, state),
		ACCESSOR_R(BaseAudioContext, listener),
		ACCESSOR_R(BaseAudioContext, sampleRate),
		ACCESSOR_R(BaseAudioContext, currentTime),
		ACCESSOR_R(BaseAudioContext, destination),
		ACCESSOR_M(BaseAudioContext, destroy)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("BaseAudioContext", ctor);
	
}


BaseAudioContext::BaseAudioContext(const Napi::CallbackInfo &info):
CommonCtx<BaseAudioContext>(info, "BaseAudioContext") { NAPI_ENV;
	
	// REQ_EXT_ARG(0, extCtx);
	REQ_OFFS_ARG(0, extCtx);
	
	// CtxPtr *ctx = reinterpret_cast<CtxPtr*>(extCtx.Data());
	CtxPtr *ctx = reinterpret_cast<CtxPtr*>(extCtx);
	
	reset(*ctx);
	
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
	
	std::cout << "lolo2 5" << std::endl;
	Napi::Object that = info.This().As<Napi::Object>();std::cout << "lolo2 6" << std::endl;
	Napi::Function ctor = _constructor.Value().As<Napi::Function>();std::cout << "lolo2 7" << std::endl;
	Napi::Function _Super = ctor.Get("_Super").As<Napi::Function>();std::cout << "lolo2 8" << std::endl;
	std::vector<napi_value> args;std::cout << "lolo2 9" << std::endl;
	// _Super.Call(that, args);
	std::cout << "lolo2 11" << std::endl;
	
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
	
	// int len;
	// uint8_t *data = getArrayData(env, audioData, &len)
	
	// std::vector<uint8_t> dataVec(data, data + len);
	
	// std::string ext = getExtension(data);
	
	// AudioBuffer::BusPtr bus = lab::MakeBusFromMemory(dataVec, ext, false);
	
	// Napi::Object buffer = AudioBuffer::create(bus);
	
	// std::vector<napi_value> args;
	// args.push_back(buffer);
	// successCallback.Call(args);
	
	RET_UNDEFINED;
	
}


JS_METHOD(BaseAudioContext::update) { THIS_CHECK;
	
	_impl->dispatchEvents();
	
	RET_UNDEFINED;
	
}


JS_METHOD(BaseAudioContext::resume) { THIS_CHECK;
	
	// TODO: do something?
	RET_UNDEFINED;
	
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


JS_METHOD(BaseAudioContext::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
