import { EventEmitter } from 'events';


type TEvent = {
	type: string;
	[key: string]: unknown;
};

type TEventCb<T extends TEvent> = (event: T) => (void | boolean);


declare module "webaudio-raub" {
	class AudioListener extends EventEmitter {
		setOrientation(x: number, y: number, z: number, xUp: number, yUp: number, zUp: number): void;
		setPosition(x: number, y: number, z: number): void;
		readonly upZ: AudioParam;
		readonly upY: AudioParam;
		readonly upX: AudioParam;
		readonly forwardZ: AudioParam;
		readonly forwardY: AudioParam;
		readonly forwardX: AudioParam;
		readonly positionZ: AudioParam;
		readonly positionY: AudioParam;
		readonly positionX: AudioParam;
		destroy(): void;
	}
	
	class AudioContext extends EventEmitter {
		resume(): void;
		decodeAudioData(source: Buffer, cb: (buffer: AudioBuffer) => void): void;
		update(): void;
		
		readonly state: string;
		readonly listener: AudioListener;
		readonly sampleRate: number;
		readonly currentTime: number;
		readonly destination: AudioNode;
		
		getOutputTimestamp(): void;
		close(): void;
		suspend(): void;
		readonly baseLatency: number;
		destroy(): void;
		onstatechange: TEventCb<TEvent> | ReadonlyArray<TEventCb<TEvent>>;
		onerror: TEventCb<TEvent> | ReadonlyArray<TEventCb<TEvent>>;
	}
	
	class AudioNode extends EventEmitter {
		channelInterpretation: 'discrete' | 'speakers';
		channelCountMode: 'clamped-max' | 'explicit' | 'max';
		channelCount: number;
		disconnect(other: AudioNode, output: number, input: number): void;
		connect(): void;
		readonly numberOfOutputs: number;
		readonly numberOfInputs: number;
		context(): AudioContext;
		destroy(): void;
		onended: TEventCb<TEvent> | ReadonlyArray<TEventCb<TEvent>>;
		onerror: TEventCb<TEvent> | ReadonlyArray<TEventCb<TEvent>>;
	}
	
	class AudioBuffer extends EventEmitter {
		copyToChannel(): void;
		copyFromChannel(): void;
		getChannelData(): void;
		readonly numberOfChannels: number;
		readonly sampleRate: number;
		readonly duration: number;
		readonly length: number;
		destroy(): void;
	}
	
	class AudioParam extends EventEmitter {
		value: number;
		cancelAndHoldAtTime(startTime: number): void;
		cancelScheduledValues(startTime: number): void;
		setValueCurveAtTime(values: number[], time: number, duration: number): void;
		setTargetAtTime(target: number, time: number, timeConstant: number): void;
		exponentialRampToValueAtTime(values: number, time: number): void;
		linearRampToValueAtTime(values: number, time: number): void;
		setValueAtTime(values: number, time: number): void;
		readonly maxValue: number;
		readonly minValue: number;
		readonly defaultValue: number;
		destroy(): void;
		
		onended: TEventCb<TEvent> | ReadonlyArray<TEventCb<TEvent>>;
		onerror: TEventCb<TEvent> | ReadonlyArray<TEventCb<TEvent>>;
	}
	
	class AudioScheduledSourceNode extends AudioNode {
		stop(when: number): void;
		start(when: number): void;
		destroy(): void;
	}
	
	class AnalyserNode extends AudioNode {
		smoothingTimeConstant: number;
		maxDecibels: number;
		minDecibels: number;
		fftSize: number;
		getByteTimeDomainData(array: number[]): void;
		getFloatTimeDomainData(array: number[]): void;
		getByteFrequencyData(array: number[]): void;
		getFloatFrequencyData(array: number[]): void;
		readonly frequencyBinCount: number;
		destroy(): void;
	}
	
	class BiquadFilterNode extends AudioNode {
		type: number;
		getFrequencyResponse(): void;
		readonly gain: AudioParam;
		readonly Q: AudioParam;
		readonly detune: AudioParam;
		readonly frequency: AudioParam;
		destroy(): void;
	}
	
	class ConvolverNode extends AudioNode {
		normalize: boolean;
		buffer: AudioBuffer;
		destroy(): void;
	}
	
	class DelayNode extends AudioNode {
		readonly delayTime: AudioParam;
		destroy(): void;
	}
	
	class GainNode extends AudioNode {
		readonly gain: AudioParam;
		destroy(): void;
	}
	
	class PannerNode extends AudioNode {
		coneOuterGain: number;
		coneOuterAngle: number;
		coneInnerAngle: number;
		rolloffFactor: number;
		maxDistance: number;
		refDistance: number;
		distanceModel: 'linear' | 'inverse' | 'exponential';
		panningModel: 'equalpower' | 'HRTF';
		setOrientation(x: number, y: number, z: number): void;
		setPosition(x: number, y: number, z: number): void;
		setVelocity(x: number, y: number, z: number): void;
		readonly orientationZ: AudioParam;
		readonly orientationY: AudioParam;
		readonly orientationX: AudioParam;
		readonly positionZ: AudioParam;
		readonly positionY: AudioParam;
		readonly positionX: AudioParam;
		destroy(): void;
	}
	
	class AudioBufferSourceNode extends AudioNode {
		loopEnd: number;
		loopStart: number;
		loop: boolean;
		buffer: AudioBuffer;
		start(when: number, grainOffset: number, grainDuration: number): void;
		readonly detune: AudioParam;
		readonly playbackRate: AudioParam;
		destroy(): void;
	}
	
	class OscillatorNode extends AudioNode {
		type: 'sine' | 'square' | 'sawtooth' | 'triangle' | 'custom';
		setPeriodicWave(): void;
		readonly detune: AudioParam;
		readonly frequency: AudioParam;
		destroy(): void;
	}
}