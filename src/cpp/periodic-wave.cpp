
#include "periodic-wave.hpp"

#include "common.hpp"


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

Napi::FunctionReference PeriodicWave::_ctorPeriodicWave;


void PeriodicWave::init(Napi::Env env, Napi::Object exports) {
	
	
	ACCESSOR_R(obj, isDestroyed);
	
	
	
	// -------- dynamic
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	
	// -------- static
	
	Napi::Function ctor = DefineClass(env, "PeriodicWave", {
	
	});
	
	_ctorPeriodicWave = Napi::Persistent(ctor);
	_ctorPeriodicWave.SuppressDestruct();
	
	exports.Set("PeriodicWave", ctor);
	
}


bool PeriodicWave::isPeriodicWave(Napi::Object obj) {
	return obj.InstanceOf(_ctorPeriodicWave.Value());
}


Napi::Object PeriodicWave::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorPeriodicWave);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


JS_METHOD(PeriodicWave::newCtor) {
	
	CTOR_CHECK("PeriodicWave");
	
	PeriodicWave *periodicWave = new PeriodicWave();
	periodicWave->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


JS_METHOD(PeriodicWave::destroy) { THIS_PERIODIC_WAVE; THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(PeriodicWave::isDestroyedGetter) { THIS_PERIODIC_WAVE;
	
	RET_BOOL(_isDestroyed);
	
}
