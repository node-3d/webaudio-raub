#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioListener.h>
#include <LabSound/core/PannerNode.h>
#include <LabSound/core/AudioParam.h>

#include "audio-listener.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_LISTENER                                                    \
	AudioListener *audioListener = Nan::ObjectWrap::Unwrap<AudioListener>(info.This());

#define THIS_CHECK                                                            \
	if (audioListener->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioListener->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioListener->CACHE = V;


// ------ Constructor and Destructor

AudioListener::AudioListener(V8_VAR_OBJ context, ListenerPtr listener) {
	
	_impl = listener;
	_context.Reset(context);
	
	double inf = std::numeric_limits<double>::infinity();
	#define MAKE_PARAM(NAME) make_shared<lab::AudioParam>(#NAME, 0., -inf, inf)
	
	_paramPositionX = MAKE_PARAM(positionX);
	_paramPositionY = MAKE_PARAM(positionY);
	_paramPositionZ = MAKE_PARAM(positionZ);
	_paramForwardX = MAKE_PARAM(forwardX);
	_paramForwardY = MAKE_PARAM(forwardY);
	_paramForwardZ = MAKE_PARAM(forwardZ);
	_paramUpX = MAKE_PARAM(upX);
	_paramUpY = MAKE_PARAM(upY);
	_paramUpZ = MAKE_PARAM(upZ);
	
	_positionX.Reset(AudioParam::getNew(context, _paramPositionX));
	_positionY.Reset(AudioParam::getNew(context, _paramPositionY));
	_positionZ.Reset(AudioParam::getNew(context, _paramPositionZ));
	_forwardX.Reset(AudioParam::getNew(context, _paramForwardX));
	_forwardY.Reset(AudioParam::getNew(context, _paramForwardY));
	_forwardZ.Reset(AudioParam::getNew(context, _paramForwardZ));
	_upX.Reset(AudioParam::getNew(context, _paramUpX));
	_upY.Reset(AudioParam::getNew(context, _paramUpY));
	_upZ.Reset(AudioParam::getNew(context, _paramUpZ));
	
	_isDestroyed = false;
	
}


AudioListener::~AudioListener() {
	
	_destroy();
	
}


void AudioListener::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props


NAN_METHOD(AudioListener::setPosition) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	audioListener->_impl->setPosition(x, y, z);
	
}


NAN_METHOD(AudioListener::setOrientation) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	REQ_FLOAT_ARG(3, xUp);
	REQ_FLOAT_ARG(4, yUp);
	REQ_FLOAT_ARG(5, zUp);
	
	audioListener->_impl->setOrientation(x, y, z, xUp, yUp, zUp);
	
}


NAN_GETTER(AudioListener::positionXGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_paramPositionX->setValue(audioListener->_impl->position().x);
	
	RET_VALUE(JS_OBJ(audioListener->_positionX));
	
}


NAN_GETTER(AudioListener::positionYGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_paramPositionY->setValue(audioListener->_impl->position().y);
	
	RET_VALUE(JS_OBJ(audioListener->_positionY));
	
}


NAN_GETTER(AudioListener::positionZGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_paramPositionZ->setValue(audioListener->_impl->position().z);
	
	RET_VALUE(JS_OBJ(audioListener->_positionZ));
	
}


NAN_GETTER(AudioListener::forwardXGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_paramForwardX->setValue(audioListener->_impl->orientation().x);
	
	RET_VALUE(JS_OBJ(audioListener->_forwardX));
	
}


NAN_GETTER(AudioListener::forwardYGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_paramForwardY->setValue(audioListener->_impl->orientation().y);
	
	RET_VALUE(JS_OBJ(audioListener->_forwardY));
	
}


NAN_GETTER(AudioListener::forwardZGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_paramForwardZ->setValue(audioListener->_impl->orientation().z);
	
	RET_VALUE(JS_OBJ(audioListener->_forwardZ));
	
}


NAN_GETTER(AudioListener::upXGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_paramUpX->setValue(audioListener->_impl->upVector().x);
	
	RET_VALUE(JS_OBJ(audioListener->_upX));
	
}


NAN_GETTER(AudioListener::upYGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_paramUpY->setValue(audioListener->_impl->upVector().y);
	
	RET_VALUE(JS_OBJ(audioListener->_upY));
	
}


NAN_GETTER(AudioListener::upZGetter) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_paramUpZ->setValue(audioListener->_impl->upVector().z);
	
	RET_VALUE(JS_OBJ(audioListener->_upZ));
	
}


// ------ System methods and props for ObjectWrap

V8_STORE_FT AudioListener::_protoAudioListener;
V8_STORE_FUNC AudioListener::_ctorAudioListener;


void AudioListener::init(V8_VAR_OBJ target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioListener"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	ACCESSOR_R(obj, positionX);
	ACCESSOR_R(obj, positionY);
	ACCESSOR_R(obj, positionZ);
	ACCESSOR_R(obj, forwardX);
	ACCESSOR_R(obj, forwardY);
	ACCESSOR_R(obj, forwardZ);
	ACCESSOR_R(obj, upX);
	ACCESSOR_R(obj, upY);
	ACCESSOR_R(obj, upZ);
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	Nan::SetPrototypeMethod(proto, "setPosition", setPosition);
	Nan::SetPrototypeMethod(proto, "setOrientation", setOrientation);
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoAudioListener.Reset(proto);
	_ctorAudioListener.Reset(ctor);
	
	Nan::Set(target, JS_STR("AudioListener"), ctor);
	
	
}


bool AudioListener::isAudioListener(V8_VAR_OBJ obj) {
	return Nan::New(_protoAudioListener)->HasInstance(obj);
}


V8_VAR_OBJ AudioListener::getNew(V8_VAR_OBJ context, ListenerPtr listener) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioListener);
	Local<External> extListener = JS_EXT(&listener);
	V8_VAR_VAL argv[] = { context, extListener };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


NAN_METHOD(AudioListener::newCtor) {
	
	CTOR_CHECK("AudioListener");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extListener);
	
	ListenerPtr *listener = reinterpret_cast<ListenerPtr *>(extListener->Value());
	
	AudioListener *audioListener = new AudioListener(context, *listener);
	audioListener->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(AudioListener::destroy) { THIS_AUDIO_LISTENER; THIS_CHECK;
	
	audioListener->_destroy();
	
}


NAN_GETTER(AudioListener::isDestroyedGetter) { THIS_AUDIO_LISTENER;
	
	RET_VALUE(JS_BOOL(audioListener->_isDestroyed));
	
}
