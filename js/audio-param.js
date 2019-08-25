 'use strict';

const { inspect } = require('util');

const { AudioParam } = require('../core');
const AudioNode = require('./audio-node');


AudioParam.prototype.__proto__ = EventEmitter.prototype;
AudioParam._Super = AudioNode.constructor;


class JsAudioParam extends AudioParam {
	
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
	
	
	[util.inspect.custom]() { return this.toString(); }
	
	toString() {
		return 'AudioParam {}';
	}
	
}

module.exports = JsAudioParam;
