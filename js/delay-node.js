'use strict';

const { inspect } = require('util');

const { DelayNode } = require('../core');
const AudioNode = require('./audio-node');


DelayNode.prototype.__proto__ = AudioNode.prototype;
DelayNode._Super = AudioNode.constructor;


class JsDelayNode extends DelayNode {
	
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
		return 'DelayNode {}';
	}
	
}

module.exports = JsDelayNode;
