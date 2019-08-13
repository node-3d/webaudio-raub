#ifndef _IIR_FILTER_NODE_HPP_
#define _IIR_FILTER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class IIRFilterNode : public AudioNode {
	
public:
	
	~IIRFilterNode();
	
	// Public V8 init
	static void init(Napi::Object target);
	
	static bool isIIRFilterNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	static Napi::Object getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	IIRFilterNode();
	
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
