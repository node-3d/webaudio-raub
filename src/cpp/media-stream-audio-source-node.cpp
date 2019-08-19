
#include "media-stream-audio-source-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

MediaStreamAudioSourceNode::MediaStreamAudioSourceNode() :
AudioNode() {
	
	_isDestroyed = false;
	
}


MediaStreamAudioSourceNode::~MediaStreamAudioSourceNode() {
	
	_destroy();
	
}


void MediaStreamAudioSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(MediaStreamAudioSourceNode::mediaStreamGetter) { THIS_CHECK;
	
	RET_VALUE(_mediaStream.Value());
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference MediaStreamAudioSourceNode::_constructor;


void MediaStreamAudioSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "MediaStreamAudioSourceNode", {
		ACCESSOR_M(MediaStreamAudioSourceNode, destroy),
		ACCESSOR_R(MediaStreamAudioSourceNode, mediaStream),
		ACCESSOR_R(MediaStreamAudioSourceNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("MediaStreamAudioSourceNode", ctor);
	
}


bool MediaStreamAudioSourceNode::isMediaStreamAudioSourceNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object MediaStreamAudioSourceNode::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


MediaStreamAudioSourceNode::MediaStreamAudioSourceNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<MediaStreamAudioSourceNode>(info) {
	
	CTOR_CHECK("MediaStreamAudioSourceNode");
	
	MediaStreamAudioSourceNode *mediaStreamAudioSourceNode = new MediaStreamAudioSourceNode();
	
}


JS_METHOD(MediaStreamAudioSourceNode::destroy) { THIS_CHECK;
	
	emit(env, "destroy");
	
	_destroy();
	
}


JS_GETTER(MediaStreamAudioSourceNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
