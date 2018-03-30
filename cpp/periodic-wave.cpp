#include <cstdlib>
//#include <iostream> // -> cout << "..." << endl;


#include "periodic-wave.hpp"


using namespace v8;
using namespace node;
using namespace std;


// ------ Aux macros

#define THIS_PERIODIC_WAVE                                                    \
	PeriodicWave *periodicWave = Nan::ObjectWrap::Unwrap<PeriodicWave>(info.This());

#define THIS_CHECK                                                            \
	if (periodicWave->_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (periodicWave->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	periodicWave->CACHE = V;


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


void PeriodicWave::init(V8_VAR_OBJ target) {
	
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


bool PeriodicWave::isPeriodicWave(V8_VAR_OBJ obj) {
	return Nan::New(_protoPeriodicWave)->HasInstance(obj);
}


V8_VAR_OBJ PeriodicWave::getNew() {
	
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
	
	RET_VALUE(JS_BOOL(periodicWave->_isDestroyed));
	
}
