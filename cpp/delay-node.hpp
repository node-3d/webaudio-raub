#ifndef _DELAY_NODE_HPP_
#define _DELAY_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class DelayNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	DelayNode();
	virtual ~DelayNode();
	
	static V8_STORE_FT _protoDelayNode;
	static V8_STORE_FUNC _ctorDelayNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _delayTime;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(delayTimeGetter);
	
};


#endif // _DELAY_NODE_HPP_
