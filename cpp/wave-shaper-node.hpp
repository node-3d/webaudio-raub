#ifndef _WAVE_SHAPER_NODE_HPP_
#define _WAVE_SHAPER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class WaveShaperNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	WaveShaperNode();
	virtual ~WaveShaperNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoWaveShaperNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorWaveShaperNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(curveGetter);
	static NAN_SETTER(curveSetter);
	
	static NAN_GETTER(oversampleGetter);
	static NAN_SETTER(oversampleSetter);
	
	
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _curve;
	std::string _oversample;
	
};


#endif // _WAVE_SHAPER_NODE_HPP_
