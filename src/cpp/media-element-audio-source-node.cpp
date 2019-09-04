
#include "media-element-audio-source-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

MediaElementAudioSourceNode::MediaElementAudioSourceNode() :
AudioNode() {
	
	_isDestroyed = false;
	
}


MediaElementAudioSourceNode::~MediaElementAudioSourceNode() {
	
	_destroy();
	
}


void MediaElementAudioSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(MediaElementAudioSourceNode::mediaElementGetter) { THIS_CHECK;
	
	RET_VALUE(_mediaElement.Value());
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference MediaElementAudioSourceNode::_constructor;


void MediaElementAudioSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(mediaElement);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("MediaElementAudioSourceNode", ctor);
	
}


bool MediaElementAudioSourceNode::isMediaElementAudioSourceNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object MediaElementAudioSourceNode::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


MediaElementAudioSourceNode::MediaElementAudioSourceNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<MediaElementAudioSourceNode>(info) {
	
	MediaElementAudioSourceNode *mediaElementAudioSourceNode =
		new MediaElementAudioSourceNode();
	
}


JS_METHOD(MediaElementAudioSourceNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(MediaElementAudioSourceNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
