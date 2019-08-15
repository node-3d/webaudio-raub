
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
	
	Napi::Function ctor = DefineClass(env, "PeriodicWave", {
		ACCESSOR_M(PeriodicWave, destroy),
		ACCESSOR_R(PeriodicWave, isDestroyed),
	
	});
	
	_ctorPeriodicWave = Napi::Persistent(ctor);
	_ctorPeriodicWave.SuppressDestruct();
	
	exports.Set("PeriodicWave", ctor);
	
}


bool PeriodicWave::isPeriodicWave(Napi::Object obj) {
	return obj.InstanceOf(_ctorPeriodicWave.Value());
}


Napi::Object PeriodicWave::getNew() {
	
	Napi::Function ctor = Nan::New(_ctorPeriodicWave);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


PeriodicWave::PeriodicWave(const Napi::CallbackInfo &info): Napi::ObjectWrap<PeriodicWave>(info) {
	
	CTOR_CHECK("PeriodicWave");
	
	PeriodicWave *periodicWave = new PeriodicWave();
	
}


JS_METHOD(PeriodicWave::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(PeriodicWave::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
