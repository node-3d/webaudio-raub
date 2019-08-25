'use strict';

const { inspect } = require('util');

const EventEmitter = require('events');

const { AudioListener } = require('../core');
const AudioNode = require('./audio-node');


AudioListener.prototype.__proto__ = AudioNode.prototype;
AudioListener._Super = AudioNode.constructor;


class JsAudioListener extends AudioListener {
	
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
		return 'AudioListener {}';
	}
	
}

module.exports = JsAudioListener;
