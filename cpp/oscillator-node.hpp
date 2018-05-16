#ifndef _OSCILLATOR_NODE_HPP_
#define _OSCILLATOR_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-scheduled-source-node.hpp"


class OscillatorNode : public AudioScheduledSourceNode {
	
public:
	
	~OscillatorNode();
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isOscillatorNode(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	OscillatorNode(V8_VAR_OBJ context, float sampleRate);
	
	static V8_STORE_FT _protoOscillatorNode;
	static V8_STORE_FUNC _ctorOscillatorNode;
	
	bool _isDestroyed;
	
	std::string _type;
	V8_STORE_OBJ _frequency;
	V8_STORE_OBJ _detune;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(setPeriodicWave);
	
	static NAN_GETTER(typeGetter);
	static NAN_SETTER(typeSetter);
	
	static NAN_GETTER(frequencyGetter);
	
	static NAN_GETTER(detuneGetter);
	
};


#endif // _OSCILLATOR_NODE_HPP_
