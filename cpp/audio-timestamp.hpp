#ifndef _AUDIO_TIMESTAMP_HPP_
#define _AUDIO_TIMESTAMP_HPP_


#include <addon-tools.hpp>


class AudioTimestamp : public Nan::ObjectWrap {
	
public:
	
	~AudioTimestamp();
	
	// Public V8 init
	static void init(V8_VAR_OBJ target);
	
	static bool isAudioTimestamp(V8_VAR_OBJ obj);
	
	// Make a new instance from C++ land
	static V8_VAR_OBJ getNew();
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioTimestamp();
	
	static V8_STORE_FT _protoAudioTimestamp;
	static V8_STORE_FUNC _ctorAudioTimestamp;
	
	bool _isDestroyed;
	
	double _contextTime;
	double _performanceTime;
	
	
// JS methods and props, available through V8 APIs
private:
	
	static NAN_METHOD(newCtor);
	
	static NAN_METHOD(destroy);
	static NAN_GETTER(isDestroyedGetter);
	
	
	
	static NAN_GETTER(contextTimeGetter);
	static NAN_SETTER(contextTimeSetter);
	
	static NAN_GETTER(performanceTimeGetter);
	static NAN_SETTER(performanceTimeSetter);
	
};


#endif // _AUDIO_TIMESTAMP_HPP_
