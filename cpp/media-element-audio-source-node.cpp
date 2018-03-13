#include <cstdlib>
#include <iostream>

#include "media-element-audio-source-node.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE                                                    \
	MediaElementAudioSourceNode *mediaElementAudioSourceNode = ObjectWrap::Unwrap<MediaElementAudioSourceNode>(info.This());

#define THIS_CHECK                                                            \
	if (mediaElementAudioSourceNode->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (mediaElementAudioSourceNode->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	mediaElementAudioSourceNode->CACHE = V;


Nan::Persistent<v8::Function> MediaElementAudioSourceNode::_constructor;


void MediaElementAudioSourceNode::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("MediaElementAudioSourceNode"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("MediaElementAudioSourceNode"), ctor);
	
	
}


NAN_METHOD(MediaElementAudioSourceNode::newCtor) {
	
	CTOR_CHECK("MediaElementAudioSourceNode");
	
	MediaElementAudioSourceNode *mediaElementAudioSourceNode = new MediaElementAudioSourceNode();
	mediaElementAudioSourceNode->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


MediaElementAudioSourceNode::MediaElementAudioSourceNode() {
	
	_isDestroyed = false;
	
}


MediaElementAudioSourceNode::~MediaElementAudioSourceNode() {
	
	_destroy();
	
}


void MediaElementAudioSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(MediaElementAudioSourceNode::destroy) { THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	mediaElementAudioSourceNode->_destroy();
	
}




NAN_GETTER(MediaElementAudioSourceNode::isDestroyedGetter) { THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE;
	
	RET_VALUE(JS_BOOL(mediaElementAudioSourceNode->_isDestroyed));
	
}


NAN_GETTER(MediaElementAudioSourceNode::mediaElementGetter) { THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(JS_OBJ(mediaElementAudioSourceNode->_mediaElement));
	
}

NAN_SETTER(MediaElementAudioSourceNode::mediaElementSetter) { THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE; THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(mediaElementAudioSourceNode->_mediaElement) == v) {
		return;
	}
	mediaElementAudioSourceNode->_mediaElement.Reset(v);
	
	// TODO: may be additional actions on change?
	
}

