#include <cstdlib>


#include "periodic-wave.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_PERIODIC_WAVE                                                    \
	PeriodicWave *periodicWave = Nan::ObjectWrap::Unwrap<PeriodicWave>(info.This());

#define CACHE_CAS(CACHE, V)                                                   \
	if (this.CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	this.CACHE = V;


// ------ Constructor and Destructor

PeriodicWave::PeriodicWave() {
	
	_isDestroyed = false;
	
}


PeriodicWave::~PeriodicWave() {
	
	_destroy();
	
}


void PeriodicWave::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props




// ------ System methods and props for ObjectWrap

V8_STORE_FT PeriodicWave::_protoPeriodicWave;
V8_STORE_FUNC PeriodicWave::_ctorPeriodicWave;


void PeriodicWave::init(Napi::Object target) {
	
	V8_VAR_FT proto = Nan::New<FunctionTemplate>(newCtor);

	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("PeriodicWave"));
	
	
	// Accessors
	V8_VAR_OT obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	V8_VAR_FUNC ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	_protoPeriodicWave.Reset(proto);
	_ctorPeriodicWave.Reset(ctor);
	
	Nan::Set(target, JS_STR("PeriodicWave"), ctor);
	
	
}


bool PeriodicWave::isPeriodicWave(Napi::Object obj) {
	return Nan::New(_protoPeriodicWave)->HasInstance(obj);
}


Napi::Object PeriodicWave::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorPeriodicWave);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


NAN_METHOD(PeriodicWave::newCtor) {
	
	CTOR_CHECK("PeriodicWave");
	
	PeriodicWave *periodicWave = new PeriodicWave();
	periodicWave->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


NAN_METHOD(PeriodicWave::destroy) { THIS_PERIODIC_WAVE; THIS_CHECK;
	
	periodicWave->_destroy();
	
}


NAN_GETTER(PeriodicWave::isDestroyedGetter) { THIS_PERIODIC_WAVE;
	
	RET_BOOL(periodicWave->_isDestroyed);
	
}