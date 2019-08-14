
#include "media-stream-audio-destination-node.hpp"

#include "common.hpp"


// ------ Aux macros

	Nan::ObjectWrap::Unwrap<MediaStreamAudioDestinationNode>(info.This());


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



JS_GETTER(MediaStreamAudioDestinationNode::streamGetter) {
	
	THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	RET_VALUE(__stream.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference MediaStreamAudioDestinationNode::_ctorMediaStreamAudioDestinationNode;


void MediaStreamAudioDestinationNode::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, stream);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "MediaStreamAudioDestinationNode", {
	
	});
	
	_ctorMediaStreamAudioDestinationNode = Napi::Persistent(ctor);
	_ctorMediaStreamAudioDestinationNode.SuppressDestruct();
	
	exports.Set("MediaStreamAudioDestinationNode", ctor);
	
}


bool MediaStreamAudioDestinationNode::isMediaStreamAudioDestinationNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorMediaStreamAudioDestinationNode.Value());
}


Napi::Object MediaStreamAudioDestinationNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorMediaStreamAudioDestinationNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(MediaStreamAudioDestinationNode::newCtor) {
	
	CTOR_CHECK("MediaStreamAudioDestinationNode");
	
	MediaStreamAudioDestinationNode *mediaStreamAudioDestinationNode =
		new MediaStreamAudioDestinationNode();
	mediaStreamAudioDestinationNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(MediaStreamAudioDestinationNode::destroy) {
	
	THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE; THIS_CHECK;
	
	mediaStreamAudioDestinationNode->emit("destroy");
	
	_destroy();
	
}


JS_GETTER(MediaStreamAudioDestinationNode::isDestroyedGetter) {
	
	THIS_MEDIA_STREAM_AUDIO_DESTINATION_NODE;
	
	RET_BOOL(_isDestroyed);
	
}
