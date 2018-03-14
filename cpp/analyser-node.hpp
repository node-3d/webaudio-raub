#ifndef _ANALYSER_NODE_HPP_
#define _ANALYSER_NODE_HPP_


#include <addon-tools.hpp>

namespace lab { class AnalyserNode; };


class AnalyserNode : public Nan::ObjectWrap {
	
// Public V8 init
public:
	
	static void init(v8::Local<v8::Object> target);
	
	
// Public C++ methods: in-engine calls
public:
	
	
// Protected C++ methods: implementing JS calls
protected:
	
	AnalyserNode(size_t fftSize);
	virtual ~AnalyserNode();
	
	
// JS methods and props
protected:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	
	static NAN_METHOD(getFloatFrequencyData);
	static NAN_METHOD(getByteFrequencyData);
	static NAN_METHOD(getFloatTimeDomainData);
	static NAN_METHOD(getByteTimeDomainData);
	
	
	static NAN_GETTER(isDestroyedGetter);
	
	
	static NAN_GETTER(frequencyBinCountGetter);
	

	static NAN_GETTER(fftSizeGetter);
	static NAN_SETTER(fftSizeSetter);
	

	static NAN_GETTER(minDecibelsGetter);
	static NAN_SETTER(minDecibelsSetter);
	

	static NAN_GETTER(maxDecibelsGetter);
	static NAN_SETTER(maxDecibelsSetter);
	

	static NAN_GETTER(smoothingTimeConstantGetter);
	static NAN_SETTER(smoothingTimeConstantSetter);
	
	
// Actual destruction-handler
private:
	
	void _destroy();
	
	
// Stored JS constructor and helpers
private:
	
	static Nan::Persistent<v8::Function> _constructor;
	
	
// This-state storage
private:
	
	bool _isDestroyed;
	
	unsigned int _frequencyBinCount;
	size_t _fftSize;
	double _minDecibels;
	double _maxDecibels;
	double _smoothingTimeConstant;
	
	lab::AnalyserNode *_impl;
	
};


#endif // _ANALYSER_NODE_HPP_
