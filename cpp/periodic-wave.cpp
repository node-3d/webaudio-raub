#include <cstdlib>
#include <iostream>

#include "periodic-wave.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_PERIODIC_WAVE                                                    \
	PeriodicWave *periodicWave = ObjectWrap::Unwrap<PeriodicWave>(info.This());

#define THIS_CHECK                                                            \
	if (periodicWave->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (periodicWave->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	periodicWave->CACHE = V;


Nan::Persistent<v8::Function> PeriodicWave::_constructor;


void PeriodicWave::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("PeriodicWave"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("PeriodicWave"), ctor);
	
	
}


NAN_METHOD(PeriodicWave::newCtor) {
	
	CTOR_CHECK("PeriodicWave");
	
	PeriodicWave *periodicWave = new PeriodicWave();
	periodicWave->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


PeriodicWave::PeriodicWave() {
	
	_isDestroyed = false;
	
}


PeriodicWave::~PeriodicWave() {
	
	_destroy();
	
}


void PeriodicWave::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(PeriodicWave::destroy) { THIS_PERIODIC_WAVE; THIS_CHECK;
	
	periodicWave->_destroy();
	
}




NAN_GETTER(PeriodicWave::isDestroyedGetter) { THIS_PERIODIC_WAVE;
	
	RET_VALUE(JS_BOOL(periodicWave->_isDestroyed));
	
}


