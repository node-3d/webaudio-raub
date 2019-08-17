
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




// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference PeriodicWave::_constructor;


void PeriodicWave::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "PeriodicWave", {
		ACCESSOR_M(PeriodicWave, destroy),
		ACCESSOR_R(PeriodicWave, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("PeriodicWave", ctor);
	
}


bool PeriodicWave::isPeriodicWave(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object PeriodicWave::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
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
