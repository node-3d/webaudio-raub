#ifndef _GAIN_NODE_HPP_
#define _GAIN_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class GainNode : public AudioNode {
	
public:
	
	~GainNode();
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	explicit GainNode(V8_VAR_OBJ context);
	
	static V8_STORE_FT _protoGainNode;
	static V8_STORE_FUNC _ctorGainNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _gain;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_GETTER(gainGetter);
	
};


#endif // _GAIN_NODE_HPP_
