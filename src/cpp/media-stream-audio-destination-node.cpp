
#include "media-stream-audio-destination-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

MediaStreamAudioDestinationNode::MediaStreamAudioDestinationNode() :
AudioNode() {
	
	_isDestroyed = false;
	
}


MediaStreamAudioDestinationNode::~MediaStreamAudioDestinationNode() {
	
	_destroy();
	
}


void MediaStreamAudioDestinationNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(MediaStreamAudioDestinationNode::streamGetter) { THIS_CHECK;
	
	RET_VALUE(_stream.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference MediaStreamAudioDestinationNode::_constructor;


void MediaStreamAudioDestinationNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "MediaStreamAudioDestinationNode", {
		ACCESSOR_M(MediaStreamAudioDestinationNode, destroy),
		ACCESSOR_R(MediaStreamAudioDestinationNode, stream),
		ACCESSOR_R(MediaStreamAudioDestinationNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("MediaStreamAudioDestinationNode", ctor);
	
}


bool MediaStreamAudioDestinationNode::isMediaStreamAudioDestinationNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object MediaStreamAudioDestinationNode::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


MediaStreamAudioDestinationNode::MediaStreamAudioDestinationNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<MediaStreamAudioDestinationNode>(info) {
	
	CTOR_CHECK("MediaStreamAudioDestinationNode");
	
	MediaStreamAudioDestinationNode *mediaStreamAudioDestinationNode =
		new MediaStreamAudioDestinationNode();
	
}


JS_METHOD(MediaStreamAudioDestinationNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(MediaStreamAudioDestinationNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
