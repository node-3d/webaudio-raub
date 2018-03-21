#include <cstdlib>
//#include <iostream> // -> std::cout << "..." << std::endl;


#include "media-element-audio-source-node.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE                                                    \
	MediaElementAudioSourceNode *mediaElementAudioSourceNode = ObjectWrap::Unwrap<MediaElementAudioSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (mediaElementAudioSourceNode->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (mediaElementAudioSourceNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	mediaElementAudioSourceNode->CACHE = V;


// ------ Constructor and Destructor

MediaElementAudioSourceNode::MediaElementAudioSourceNode() : AudioNode() {
	
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



NAN_GETTER(MediaElementAudioSourceNode::mediaElementGetter) { THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(mediaElementAudioSourceNode->_mediaElement));
	
}


// ------ System methods and props for ObjectWrap

Nan::Persistent<v8::FunctionTemplate> MediaElementAudioSourceNode::_protoMediaElementAudioSourceNode;
Nan::Persistent<v8::Function> MediaElementAudioSourceNode::_ctorMediaElementAudioSourceNode;


void MediaElementAudioSourceNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	// class MediaElementAudioSourceNode inherits AudioNode
	Local<FunctionTemplate> parent = Nan::New(AudioNode::_protoAudioNode);
	proto->Inherit(parent);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("MediaElementAudioSourceNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, mediaElement);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoMediaElementAudioSourceNode.Reset(proto);
	_ctorMediaElementAudioSourceNode.Reset(ctor);
	
	Nan::Set(target, JS_STR("MediaElementAudioSourceNode"), ctor);
	
	
}


NAN_METHOD(MediaElementAudioSourceNode::newCtor) {
	
	CTOR_CHECK("MediaElementAudioSourceNode");
	
	MediaElementAudioSourceNode *mediaElementAudioSourceNode = new MediaElementAudioSourceNode();
	mediaElementAudioSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(MediaElementAudioSourceNode::destroy) { THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	mediaElementAudioSourceNode->_destroy();
	
}


NAN_GETTER(MediaElementAudioSourceNode::isDestroyedGetter) { THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(mediaElementAudioSourceNode->_isDestroyed));
	
}
