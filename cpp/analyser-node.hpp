#ifndef _ANALYSER_NODE_HPP_
#define _ANALYSER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class AnalyserNode : public AudioNode {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AnalyserNode();
	virtual ~AnalyserNode();
	
	static V8_STORE_FT _protoAnalyserNode;
	static V8_STORE_FUNC _ctorAnalyserNode;
	
	bool _isDestroyed;
	
	unsigned int _frequencyBinCount;
	unsigned int _fftSize;
	double _minDecibels;
	double _maxDecibels;
	double _smoothingTimeConstant;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(getFloatFrequencyData);
	static NAN_METHOD(getByteFrequencyData);
	static NAN_METHOD(getFloatTimeDomainData);
	static NAN_METHOD(getByteTimeDomainData);
	
	static NAN_GETTER(frequencyBinCountGetter);
	
	static NAN_GETTER(fftSizeGetter);
	static NAN_SETTER(fftSizeSetter);
	
	static NAN_GETTER(minDecibelsGetter);
	static NAN_SETTER(minDecibelsSetter);
	
	static NAN_GETTER(maxDecibelsGetter);
	static NAN_SETTER(maxDecibelsSetter);
	
	static NAN_GETTER(smoothingTimeConstantGetter);
	static NAN_SETTER(smoothingTimeConstantSetter);
	
};


#endif // _ANALYSER_NODE_HPP_
