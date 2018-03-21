#ifndef _BIQUAD_FILTER_NODE_HPP_
#define _BIQUAD_FILTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class BiquadFilterNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(v8::Local<v8::Object> target);
	
	void _destroy();
	
	
// Methods and props
protected:
	
	BiquadFilterNode();
	virtual ~BiquadFilterNode();
	
	static Nan::Persistent<v8::FunctionTemplate> _protoBiquadFilterNode; // for inheritance
	static Nan::Persistent<v8::Function> _ctorBiquadFilterNode;
	
	
// System methods and props for ObjectWrap
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(getFrequencyResponse);
	
	static NAN_GETTER(typeGetter);
	static NAN_SETTER(typeSetter);
	
	static NAN_GETTER(frequencyGetter);
	
	static NAN_GETTER(detuneGetter);
	
	static NAN_GETTER(QGetter);
	
	static NAN_GETTER(gainGetter);
	
	
private:
	
	bool _isDestroyed;
	
	std::string _type;
	Nan::Persistent<v8::Object> _frequency;
	Nan::Persistent<v8::Object> _detune;
	Nan::Persistent<v8::Object> _Q;
	Nan::Persistent<v8::Object> _gain;
	
};


#endif // _BIQUAD_FILTER_NODE_HPP_
