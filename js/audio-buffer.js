'use strict';

const { inspect } = require('util');

const { AudioBuffer } = require('../core');
const AudioNode = require('./audio-node');


AudioBuffer.prototype.__proto__ = AudioNode.prototype;
AudioBuffer._Super = AudioNode.constructor;


class JsAudioBuffer extends AudioBuffer {
	
	constructor(ctx, _opts = {}) {
		
		const opts = {
			fftSize : 2048,
			maxDecibels : -30,
			minDecibels : -100,
			smoothingTimeConstant : 0.8,
			..._opts,
		};
		
		super(ctx);
		
		this.fftSize = opts.fftSize;
		this.maxDecibels = opts.maxDecibels;
		this.minDecibels = opts.minDecibels;
		this.smoothingTimeConstant = opts.smoothingTimeConstant;
		
	}
	
	
	[inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AudioBuffer {}';
	}
	
}

module.exports = JsAudioBuffer;
