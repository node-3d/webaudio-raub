#ifndef _CONVOLVER_NODE_HPP_
#define _CONVOLVER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class ConvolverNode : public AudioNode {
	
public:
	
	~ConvolverNode();
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	explicit ConvolverNode(V8_VAR_OBJ context);
	
	static V8_STORE_FT _protoConvolverNode;
	static V8_STORE_FUNC _ctorConvolverNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _buffer;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_GETTER(bufferGetter);
	static NAN_SETTER(bufferSetter);
	
	static NAN_GETTER(normalizeGetter);
	static NAN_SETTER(normalizeSetter);
	
};


#endif // _CONVOLVER_NODE_HPP_
