#ifndef _CONVOLVER_NODE_HPP_
#define _CONVOLVER_NODE_HPP_


#include <addon-tools.hpp>


class ConvolverNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	ConvolverNode();
	virtual ~ConvolverNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(bufferGetter);
	static NAN_SETTER(bufferSetter);
	

	static NAN_GETTER(normalizeGetter);
	static NAN_SETTER(normalizeSetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	Nan::Persistent<v8::Object> _buffer;
	bool _normalize;
	
};


#endif // _CONVOLVER_NODE_HPP_
