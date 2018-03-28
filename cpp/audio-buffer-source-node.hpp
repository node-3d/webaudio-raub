#ifndef _AUDIO_BUFFER_SOURCE_NODE_HPP_
#define _AUDIO_BUFFER_SOURCE_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-scheduled-source-node.hpp"


class AudioBufferSourceNode : public AudioScheduledSourceNode {
	
public:
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew(V8_VAR_OBJ context);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	explicit AudioBufferSourceNode(V8_VAR_OBJ context);
	virtual ~AudioBufferSourceNode();
	
	static V8_STORE_FT _protoAudioBufferSourceNode;
	static V8_STORE_FUNC _ctorAudioBufferSourceNode;
	
	bool _isDestroyed;
	
	V8_STORE_OBJ _buffer;
	V8_STORE_OBJ _playbackRate;
	V8_STORE_OBJ _detune;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	static NAN_METHOD(start);
	
	static NAN_GETTER(bufferGetter);
	static NAN_SETTER(bufferSetter);
	
	static NAN_GETTER(playbackRateGetter);
	
	static NAN_GETTER(detuneGetter);
	
	static NAN_GETTER(loopGetter);
	static NAN_SETTER(loopSetter);
	
	static NAN_GETTER(loopStartGetter);
	static NAN_SETTER(loopStartSetter);
	
	static NAN_GETTER(loopEndGetter);
	static NAN_SETTER(loopEndSetter);
	
};


#endif // _AUDIO_BUFFER_SOURCE_NODE_HPP_
