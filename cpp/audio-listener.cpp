#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include <LabSound/core/AudioListener.h>
#include <LabSound/core/AudioParam.h>
#include <LabSound/core/FloatPoint3D.h>

#include "audio-listener.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_AUDIO_LISTENER                                                   \
	AudioListener *audioListener = Nan::ObjectWrap::Unwrap<AudioListener>(info.This());

#define THIS_CHECK                                                            \
	if (audioListener->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioListener->CACHE == V) {                                          \
		return;                                                               \
	}                                                                         \
	audioListener->CACHE = V;

#define PARAM_GETTER(NAME)                                                    \
NAN_GETTER(AudioListener::NAME ## Getter) { THIS_AUDIO_LISTENER; THIS_CHECK;  \
	RET_VALUE(JS_OBJ(audioListener->_ ## NAME));                              \
}


class ListenerParam : public lab::AudioParam {
	
public:
	
	enum ParamName {
		positionX,
		positionY,
		positionZ,
		forwardX,
		forwardY,
		forwardZ,
		upX,
		upY,
		upZ,
	};
	
	ListenerParam(string id, lab::AudioListener *target, ParamName name) :
	lab::AudioParam(id, 0., -_inf, _inf) {
		_target = target;
		_name = name;
	}
	
	float value() {
		
		if (_name == positionX) {
			return _target->position().x;
		} else if (_name == positionY) {
			return _target->position().y;
		} else if (_name == positionZ) {
			return _target->position().z;
		} else if (_name == forwardX) {
			return _target->orientation().x;
		} else if (_name == forwardY) {
			return _target->orientation().y;
		} else if (_name == forwardZ) {
			return _target->orientation().z;
		} else if (_name == upX) {
			return _target->upVector().x;
		} else if (_name == upY) {
			return _target->upVector().y;
		} else if (_name == upZ) {
			return _target->upVector().z;
		} else {
			return 0.f;
		}
		
	}
	
	void setValue(float v) {
		
		if (_name == positionX) {
			lab::FloatPoint3D pos = _target->position();
			pos.x = v;
			_target->setPosition(pos);
		} else if (_name == positionY) {
			lab::FloatPoint3D pos = _target->position();
			pos.y = v;
			_target->setPosition(pos);
		} else if (_name == positionZ) {
			lab::FloatPoint3D pos = _target->position();
			pos.z = v;
			_target->setPosition(pos);
		} else if (_name == forwardX) {
			lab::FloatPoint3D orient = _target->orientation();
			orient.x = v;
			_target->setOrientation(orient);
		} else if (_name == forwardY) {
			lab::FloatPoint3D orient = _target->orientation();
			orient.y = v;
			_target->setOrientation(orient);
		} else if (_name == forwardZ) {
			lab::FloatPoint3D orient = _target->orientation();
			orient.z = v;
			_target->setOrientation(orient);
		} else if (_name == upX) {
			lab::FloatPoint3D up = _target->upVector();
			up.x = v;
			_target->setUpVector(up);
		} else if (_name == upY) {
			lab::FloatPoint3D up = _target->upVector();
			up.y = v;
			_target->setUpVector(up);
		} else if (_name == upZ) {
			lab::FloatPoint3D up = _target->upVector();
			up.z = v;
			_target->setUpVector(up);
		}
		
	}
	
	
private:
	
	lab::AudioListener *_target;
	ParamName _name;
	
	static double _inf;
	
};

double ListenerParam::_inf = std::numeric_limits<double>::infinity();


// ------ Constructor and Destructor

AudioListener::AudioListener(V8_VAR_OBJ context, ListenerPtr listener) {
	
	_impl = listener;
	_context.Reset(context);
	
	#define MAKE_PARAM(NAME) make_shared<ListenerParam>(#NAME, _impl.get(), ListenerParam::NAME)
	
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


PARAM_GETTER(positionX);
PARAM_GETTER(positionY);
PARAM_GETTER(positionZ);
PARAM_GETTER(forwardX);
PARAM_GETTER(forwardY);
PARAM_GETTER(forwardZ);
PARAM_GETTER(upX);
PARAM_GETTER(upY);
PARAM_GETTER(upZ);


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
