#ifndef _IIR_FILTER_NODE_HPP_
#define _IIR_FILTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class IIRFilterNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isIIRFilterNode(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	IIRFilterNode();
	virtual ~IIRFilterNode();
	
	static V8_STORE_FT _protoIIRFilterNode;
	static V8_STORE_FUNC _ctorIIRFilterNode;
	
	bool _isDestroyed;
	
	
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(getFrequencyResponse);
	
};


#endif // _IIR_FILTER_NODE_HPP_
