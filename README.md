# waa

Web Audio Api implementation for Node.js


## Install

```
npm i -s waa-raub
```

Note: as this is a compiled addon, compilation tools must be in place on your system.
Such as MSVS13 for Windows, where **ADMIN PRIVELEGED**
`npm i -g windows-build-tools` most probably helps.


## Usage

TODO(howto)




---

### class AnalyserNode

TODO(description)

```
const { AnalyserNode } = require('waa-raub');
const analyserNode = new AnalyserNode();
```


Constructor:
* `AnalyserNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set number frequencyBinCount` - TODO(description).
* `get/set number fftSize` - TODO(description).
* `get/set number minDecibels` - TODO(description).
* `get/set number maxDecibels` - TODO(description).
* `get/set number smoothingTimeConstant` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void getFloatFrequencyData(object getFloatFrequencyData)` - TODO(description).
* `void getByteFrequencyData(object getByteFrequencyData)` - TODO(description).
* `void getFloatTimeDomainData(object getFloatTimeDomainData)` - TODO(description).
* `void getByteTimeDomainData(object getByteTimeDomainData)` - TODO(description).





---

### class AudioBuffer

TODO(description)

```
const { AudioBuffer } = require('waa-raub');
const audioBuffer = new AudioBuffer();
```


Constructor:
* `AudioBuffer()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set number length` - TODO(description).
* `get/set number duration` - TODO(description).
* `get/set number sampleRate` - TODO(description).
* `get/set number numberOfChannels` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void getChannelData(number getChannelData)` - TODO(description).
* `void copyFromChannel(object copyFromChannel, number copyFromChannel, number copyFromChannel)` - TODO(description).
* `void copyToChannel(object copyToChannel, number copyToChannel, number copyToChannel)` - TODO(description).





---

### class AudioBufferSourceNode

TODO(description)

```
const { AudioBufferSourceNode } = require('waa-raub');
const audioBufferSourceNode = new AudioBufferSourceNode();
```


Constructor:
* `AudioBufferSourceNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object buffer` - TODO(description).
* `get/set object playbackRate` - TODO(description).
* `get/set object detune` - TODO(description).
* `get/set boolean loop` - TODO(description).
* `get/set number loopStart` - TODO(description).
* `get/set number loopEnd` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void start(number start, number start, number start)` - TODO(description).





---

### class AudioContext

TODO(description)

```
const { AudioContext } = require('waa-raub');
const audioContext = new AudioContext();
```


Constructor:
* `AudioContext()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set number baseLatency` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void suspend()` - TODO(description).
* `void close()` - TODO(description).
* `void getOutputTimestamp()` - TODO(description).
* `void createMediaElementSource(object createMediaElementSource)` - TODO(description).
* `void createMediaStreamSource(object createMediaStreamSource)` - TODO(description).
* `void createMediaStreamDestination()` - TODO(description).





---

### class AudioDestinationNode

TODO(description)

```
const { AudioDestinationNode } = require('waa-raub');
const audioDestinationNode = new AudioDestinationNode();
```


Constructor:
* `AudioDestinationNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set number maxChannelCount` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class AudioListener

TODO(description)

```
const { AudioListener } = require('waa-raub');
const audioListener = new AudioListener();
```


Constructor:
* `AudioListener()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set number positionX` - TODO(description).
* `get/set number positionY` - TODO(description).
* `get/set number positionZ` - TODO(description).
* `get/set number forwardX` - TODO(description).
* `get/set number forwardY` - TODO(description).
* `get/set number forwardZ` - TODO(description).
* `get/set number upX` - TODO(description).
* `get/set number upY` - TODO(description).
* `get/set number upZ` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void setPosition(number setPosition, number setPosition, number setPosition)` - TODO(description).
* `void setOrientation(number setOrientation, number setOrientation, number setOrientation, number setOrientation, number setOrientation, number setOrientation)` - TODO(description).





---

### class AudioNode

TODO(description)

```
const { AudioNode } = require('waa-raub');
const audioNode = new AudioNode();
```


Constructor:
* `AudioNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object context` - TODO(description).
* `get/set number numberOfInputs` - TODO(description).
* `get/set number numberOfOutputs` - TODO(description).
* `get/set number channelCount` - TODO(description).
* `get/set string channelCountMode` - TODO(description).
* `get/set string channelInterpretation` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void connect(object connect, number connect, number connect)` - TODO(description).
* `void disconnect(object disconnect, number disconnect, number disconnect)` - TODO(description).





---

### class AudioParam

TODO(description)

```
const { AudioParam } = require('waa-raub');
const audioParam = new AudioParam();
```


Constructor:
* `AudioParam()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set number value` - TODO(description).
* `get/set number defaultValue` - TODO(description).
* `get/set number minValue` - TODO(description).
* `get/set number maxValue` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void setValueAtTime(number setValueAtTime, number setValueAtTime)` - TODO(description).
* `void linearRampToValueAtTime(number linearRampToValueAtTime, number linearRampToValueAtTime)` - TODO(description).
* `void exponentialRampToValueAtTime(number exponentialRampToValueAtTime, number exponentialRampToValueAtTime)` - TODO(description).
* `void setTargetAtTime(number setTargetAtTime, number setTargetAtTime, number setTargetAtTime)` - TODO(description).
* `void setValueCurveAtTime(object setValueCurveAtTime, number setValueCurveAtTime, number setValueCurveAtTime)` - TODO(description).
* `void cancelScheduledValues(number cancelScheduledValues)` - TODO(description).
* `void cancelAndHoldAtTime(number cancelAndHoldAtTime)` - TODO(description).





---

### class AudioProcessingEvent

TODO(description)

```
const { AudioProcessingEvent } = require('waa-raub');
const audioProcessingEvent = new AudioProcessingEvent();
```


Constructor:
* `AudioProcessingEvent()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set number playbackTime` - TODO(description).
* `get/set object inputBuffer` - TODO(description).
* `get/set object outputBuffer` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class AudioScheduledSourceNode

TODO(description)

```
const { AudioScheduledSourceNode } = require('waa-raub');
const audioScheduledSourceNode = new AudioScheduledSourceNode();
```


Constructor:
* `AudioScheduledSourceNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set function onended` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void start(number start)` - TODO(description).
* `void stop(number stop)` - TODO(description).





---

### class AudioTimestamp

TODO(description)

```
const { AudioTimestamp } = require('waa-raub');
const audioTimestamp = new AudioTimestamp();
```


Constructor:
* `AudioTimestamp()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set number contextTime` - TODO(description).
* `get/set number performanceTime` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class AudioWorkletGlobalScope

TODO(description)

```
const { AudioWorkletGlobalScope } = require('waa-raub');
const audioWorkletGlobalScope = new AudioWorkletGlobalScope();
```


Constructor:
* `AudioWorkletGlobalScope()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set number currentFrame` - TODO(description).
* `get/set number currentTime` - TODO(description).
* `get/set number sampleRate` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void registerProcessor(string registerProcessor, function registerProcessor)` - TODO(description).





---

### class AudioWorkletNode

TODO(description)

```
const { AudioWorkletNode } = require('waa-raub');
const audioWorkletNode = new AudioWorkletNode();
```


Constructor:
* `AudioWorkletNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object parameters` - TODO(description).
* `get/set object port` - TODO(description).
* `get/set function onprocessorerror` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class AudioWorkletProcessor

TODO(description)

```
const { AudioWorkletProcessor } = require('waa-raub');
const audioWorkletProcessor = new AudioWorkletProcessor();
```


Constructor:
* `AudioWorkletProcessor()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object port` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class BaseAudioContext

TODO(description)

```
const { BaseAudioContext } = require('waa-raub');
const baseAudioContext = new BaseAudioContext();
```


Constructor:
* `BaseAudioContext()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object destination` - TODO(description).
* `get/set number currentTime` - TODO(description).
* `get/set number sampleRate` - TODO(description).
* `get/set object listener` - TODO(description).
* `get/set string state` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void createBuffer(number createBuffer, number createBuffer, number createBuffer)` - TODO(description).
* `void decodeAudioData(object decodeAudioData, function decodeAudioData, function decodeAudioData)` - TODO(description).
* `void createBufferSource()` - TODO(description).
* `void createConstantSource()` - TODO(description).
* `void createGain()` - TODO(description).
* `void createDelay(number createDelay)` - TODO(description).
* `void createBiquadFilter()` - TODO(description).
* `void createIIRFilter(object createIIRFilter, object createIIRFilter)` - TODO(description).
* `void createWaveShaper()` - TODO(description).
* `void createPanner()` - TODO(description).
* `void createConvolver()` - TODO(description).
* `void createDynamicsCompressor()` - TODO(description).
* `void createAnalyser()` - TODO(description).
* `void createScriptProcessor(number createScriptProcessor, number createScriptProcessor, number createScriptProcessor)` - TODO(description).
* `void createStereoPanner()` - TODO(description).
* `void createOscillator()` - TODO(description).
* `void createPeriodicWave(object createPeriodicWave, object createPeriodicWave, object createPeriodicWave)` - TODO(description).
* `void createChannelSplitter(number createChannelSplitter)` - TODO(description).
* `void createChannelMerger(number createChannelMerger)` - TODO(description).
* `void resume()` - TODO(description).
* `void createMediaElementSource(object createMediaElementSource)` - TODO(description).
* `void createMediaStreamSource(object createMediaStreamSource)` - TODO(description).
* `void createMediaStreamDestination()` - TODO(description).





---

### class BiquadFilterNode

TODO(description)

```
const { BiquadFilterNode } = require('waa-raub');
const biquadFilterNode = new BiquadFilterNode();
```


Constructor:
* `BiquadFilterNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set string type` - TODO(description).
* `get/set object frequency` - TODO(description).
* `get/set object detune` - TODO(description).
* `get/set object Q` - TODO(description).
* `get/set object gain` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void getFrequencyResponse(object getFrequencyResponse, object getFrequencyResponse, object getFrequencyResponse)` - TODO(description).





---

### class ChannelMergerNode

TODO(description)

```
const { ChannelMergerNode } = require('waa-raub');
const channelMergerNode = new ChannelMergerNode();
```


Constructor:
* `ChannelMergerNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.



Methods:
* `void destroy()` - destroys the instance.






---

### class ChannelSplitterNode

TODO(description)

```
const { ChannelSplitterNode } = require('waa-raub');
const channelSplitterNode = new ChannelSplitterNode();
```


Constructor:
* `ChannelSplitterNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.



Methods:
* `void destroy()` - destroys the instance.






---

### class ConstantSourceNode

TODO(description)

```
const { ConstantSourceNode } = require('waa-raub');
const constantSourceNode = new ConstantSourceNode();
```


Constructor:
* `ConstantSourceNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object offset` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class ConvolverNode

TODO(description)

```
const { ConvolverNode } = require('waa-raub');
const convolverNode = new ConvolverNode();
```


Constructor:
* `ConvolverNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object buffer` - TODO(description).
* `get/set boolean normalize` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class DelayNode

TODO(description)

```
const { DelayNode } = require('waa-raub');
const delayNode = new DelayNode();
```


Constructor:
* `DelayNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object delayTime` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class DynamicsCompressorNode

TODO(description)

```
const { DynamicsCompressorNode } = require('waa-raub');
const dynamicsCompressorNode = new DynamicsCompressorNode();
```


Constructor:
* `DynamicsCompressorNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object threshold` - TODO(description).
* `get/set object knee` - TODO(description).
* `get/set object ratio` - TODO(description).
* `get/set number reduction` - TODO(description).
* `get/set object attack` - TODO(description).
* `get/set object release` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class GainNode

TODO(description)

```
const { GainNode } = require('waa-raub');
const gainNode = new GainNode();
```


Constructor:
* `GainNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object gain` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class IIRFilterNode

TODO(description)

```
const { IIRFilterNode } = require('waa-raub');
const iIRFilterNode = new IIRFilterNode();
```


Constructor:
* `IIRFilterNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.



Methods:
* `void destroy()` - destroys the instance.
* `void getFrequencyResponse(object getFrequencyResponse, object getFrequencyResponse, object getFrequencyResponse)` - TODO(description).





---

### class MediaElementAudioSourceNode

TODO(description)

```
const { MediaElementAudioSourceNode } = require('waa-raub');
const mediaElementAudioSourceNode = new MediaElementAudioSourceNode();
```


Constructor:
* `MediaElementAudioSourceNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object mediaElement` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class MediaStreamAudioDestinationNode

TODO(description)

```
const { MediaStreamAudioDestinationNode } = require('waa-raub');
const mediaStreamAudioDestinationNode = new MediaStreamAudioDestinationNode();
```


Constructor:
* `MediaStreamAudioDestinationNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object stream` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class MediaStreamAudioSourceNode

TODO(description)

```
const { MediaStreamAudioSourceNode } = require('waa-raub');
const mediaStreamAudioSourceNode = new MediaStreamAudioSourceNode();
```


Constructor:
* `MediaStreamAudioSourceNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object mediaStream` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class OfflineAudioCompletionEvent

TODO(description)

```
const { OfflineAudioCompletionEvent } = require('waa-raub');
const offlineAudioCompletionEvent = new OfflineAudioCompletionEvent();
```


Constructor:
* `OfflineAudioCompletionEvent()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object renderedBuffer` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class OfflineAudioContext

TODO(description)

```
const { OfflineAudioContext } = require('waa-raub');
const offlineAudioContext = new OfflineAudioContext();
```


Constructor:
* `OfflineAudioContext()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set function oncomplete` - TODO(description).
* `get/set number length` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void startRendering()` - TODO(description).
* `void suspend(number suspend)` - TODO(description).





---

### class OscillatorNode

TODO(description)

```
const { OscillatorNode } = require('waa-raub');
const oscillatorNode = new OscillatorNode();
```


Constructor:
* `OscillatorNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set string type` - TODO(description).
* `get/set object frequency` - TODO(description).
* `get/set object detune` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void setPeriodicWave(object setPeriodicWave)` - TODO(description).





---

### class PannerNode

TODO(description)

```
const { PannerNode } = require('waa-raub');
const pannerNode = new PannerNode();
```


Constructor:
* `PannerNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set string panningModel` - TODO(description).
* `get/set object positionX` - TODO(description).
* `get/set object positionY` - TODO(description).
* `get/set object positionZ` - TODO(description).
* `get/set object orientationX` - TODO(description).
* `get/set object orientationY` - TODO(description).
* `get/set object orientationZ` - TODO(description).
* `get/set string distanceModel` - TODO(description).
* `get/set number refDistance` - TODO(description).
* `get/set number maxDistance` - TODO(description).
* `get/set number rolloffFactor` - TODO(description).
* `get/set number coneInnerAngle` - TODO(description).
* `get/set number coneOuterAngle` - TODO(description).
* `get/set number coneOuterGain` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.
* `void setPosition(number setPosition, number setPosition, number setPosition)` - TODO(description).
* `void setOrientation(number setOrientation, number setOrientation, number setOrientation)` - TODO(description).





---

### class PeriodicWave

TODO(description)

```
const { PeriodicWave } = require('waa-raub');
const periodicWave = new PeriodicWave();
```


Constructor:
* `PeriodicWave()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.



Methods:
* `void destroy()` - destroys the instance.






---

### class ScriptProcessorNode

TODO(description)

```
const { ScriptProcessorNode } = require('waa-raub');
const scriptProcessorNode = new ScriptProcessorNode();
```


Constructor:
* `ScriptProcessorNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set function onaudioprocess` - TODO(description).
* `get/set number bufferSize` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class StereoPannerNode

TODO(description)

```
const { StereoPannerNode } = require('waa-raub');
const stereoPannerNode = new StereoPannerNode();
```


Constructor:
* `StereoPannerNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object pan` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.






---

### class WaveShaperNode

TODO(description)

```
const { WaveShaperNode } = require('waa-raub');
const waveShaperNode = new WaveShaperNode();
```


Constructor:
* `WaveShaperNode()`


Properties:
* `get bool isDestroyed` - if `destroy()` was called on this instance.
* `get/set object curve` - TODO(description).
* `get/set string oversample` - TODO(description).


Methods:
* `void destroy()` - destroys the instance.




