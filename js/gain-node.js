'use strict';

const { inspect } = require('util');

const { GainNode } = require('../core');
const AudioNode = require('./audio-node');


GainNode.prototype.__proto__ = AudioNode.prototype;
GainNode._Super = AudioNode.constructor;


class JsGainNode extends GainNode {
	
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
		return 'GainNode {}';
	}
	
}

module.exports = JsGainNode;
